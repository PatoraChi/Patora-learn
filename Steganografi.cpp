#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
//klarifikasi dulu modul ini masih belom 100% paham juga jadi kaloa ada salah ya maap wkwkwk XD, sama kemungkinan dikit ada penjelasan/karena dikit aja pahamnya

int maxmsg = 1;
int totalBits = 0;
// P note akan memandu menjelaskan program "sebisanya"
void checkmessage(const char *filename, const char *message) {
    FILE *fp = fopen(filename, "rb");// fopen mode rb itu sama kayak mode r tapi versi binner
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }

    uint32_t width, height;
    fseek(fp, 18, SEEK_SET); // Pindah ke posisi lebar (offset 18), berisi width(translate sendiri) , kenapa 18? liat aja format nya di https://en.wikipedia.org/wiki/BMP_file_format
    fread(&width, sizeof(uint32_t), 1, fp); //menulis panjang(mungkin) gambar, size of unit32_t itu artinya sebesar 4bit, karena unit32_t itu besarnya 4bit, kalo 1 itu kita menulisnya sebanyak 1 aja
    fread(&height, sizeof(uint32_t), 1, fp);//menulis lebar(mungkin) gambar

    maxmsg = width * height * 3;//dikasi 3 karena 1 pixel berisi 3 warna yaitu RGB, jadi 1 pixel bisa memuat 3 bit
//jadi kenpa 1pixel cuma bisa 3? karena kita pake LSB kalo ga salah namanya, artinya cuma menggunakan bit paling akhir di bagian pixel warna
//1 warna itu ada 255 ya, 11111111, jadi kita cuma make 1 paling kanan aja sisanya ga diapa apain
    fclose(fp);

    const char *endMarker = "<end>";// end marker untuk penanda kalo pesan dah berakhir nnti tau dah fungsinya
    int markerLength = strlen(endMarker);
    totalBits = (strlen(message) + markerLength) * 8;//kenapa dikali 8? karena 1 karakter aschii itu ada 8bit ya, ceka aj aschi table untuk selengkapnya

    
    if (maxmsg < totalBits) {// kayaknya mustahil ini true, karena panjang banget wkwkwk
        printf("Pesan terlalu panjang\n");
    } else {
        printf("Pesan akan diproses\n");
    }
}

void embedMessage(const char *inputFilename, const char *outputFilename, const char *message) {
    FILE *inputFile = fopen(inputFilename, "rb"); //fopen mode rb itu sama kayak mode r tapi versi binner
    if (inputFile == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", inputFilename);
        return;
    }

    FILE *outputFile = fopen(outputFilename, "wb");//fopen mode wb itu sama kayak mode w tapi versi binner
    if (outputFile == NULL) {
        printf("Error: Tidak dapat membuat file %s\n", outputFilename);
        fclose(inputFile);
        return;
    }

    fseek(inputFile, 0, SEEK_END);//keliling untuk membaca ukuran file gambar dalam ukuran byte, misal filenya 8mb, itung dah tu brp byte
    long fileSize = ftell(inputFile);//ditulis disini
    fseek(inputFile, 0, SEEK_SET);//balek ke awal

    unsigned char *fileBuffer = (unsigned char*)malloc(fileSize);//menyiapkan filebuffer dengan ukuran sebesar filenya
    fread(fileBuffer, 1, fileSize, inputFile);//pointer filebuffer menunjuk ke bagian tempat ukuran filegambar "MUNGKIN" offser = 0 XD
    fclose(inputFile);
	
    unsigned char *pixelData = fileBuffer + 54; // pointer ini menunjuk ke awal bit pixel, karena 54 untuk header, jadi +54 untuk melwatkan header

    const char *endMarker = "<end>";
    char *fullMessage = (char*)malloc(strlen(message) + strlen(endMarker) + 1);//kenapa + 1? kemungkinan jaga jaga biar ga abis abis banget, inget lebih baik lebih dari pada kurang

    strcpy(fullMessage, message);//menulis message yg dimasukan user ke fullmessage
    strcat(fullMessage, endMarker);//menambahkan endmarker (<end>) ke fullmessage

    int messageIndex = 0;//index dari 0
    int bitIndex = 7;//kenapa 7? karena dari 0, jadi 1 karakter ada 8bit
    int fullMessageLength = strlen(fullMessage);

    for (int i = 0; i < totalBits; i++) {
        if (fullMessage[messageIndex] & (1 << bitIndex)) { // "<<" artinya menggeser "1" kekanan kebanyak bitIndex, eh mungkin kiri
//jadi maksud 1 digeger kekiri ini tu kykgini, 1 dalam binner itu kan 00000001, digeser sebanyak bit index, kalo diawal bit index itu 7 berarti digeser 7 kali jadi, 10000000
//lalu akan di "and" kan dengan pesannya (berupa binnerjuga) misal pesannya "akira" index awal nya kan "a" di ubah ke binner jadi 01000001, nah si "a" ini di "and" dengan "1" yg dah digeser
/*contoh ya a di "and" dengan 1, untuk yg pertama 1 digeser sebanyak 7 kali dari 00000001 menjadi 10000000 dan "a" itu 01000001 di asci tabel
 jadi	01000001
 	10000000
  ----------------- and
  	00000000
   lalu a digeser sebanyak 6 kali dari 00000001 menjadi 01000000
   jadi	01000001
 	01000000
  ----------------- and
  	01000000
    lalu a digeser sebanyak 5 kali dari 00000001 menjadi 00100000
   jadi	01000001
 	00100000
  ----------------- and
  	00000000
   dan seterusnya sebanyak 8 kali karena 1 karakter terdapat 8bit, nanti akan menhasilkan 01000001
*/
		pixelData[i] |= 1; // apapun di or kan dengan 1 menghasilkan 1
        } else {
            pixelData[i] &= ~1; // apapun di and kan dengan 0 menghasilkan 0
        }

        bitIndex--;//sama dengan bitindex = bitindex - 1
        if (bitIndex < 0) {//kalo bit index dah -1, karena dari awal kan 7 , terus dikurang 1, nah misal udah sampe -1, bit index jadi 7 lagi
            bitIndex = 7; 
            messageIndex++;
            if (messageIndex >= fullMessageLength) {
                break;
            }
        }
    }

    fwrite(fileBuffer, 1, fileSize, outputFile);
    fclose(outputFile);
    free(fileBuffer);
    free(fullMessage);

    printf("Pesan telah disisipkan ke dalam file %s\n", outputFilename);
}

void extractMessage(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }

    fseek(fp, 0, SEEK_END);//sama kyk diatas liat aja
    long fileSize = ftell(fp);//sama kyk diatas liat aja
    fseek(fp, 0, SEEK_SET);//sama kyk diatas liat aja

    unsigned char *fileBuffer = (unsigned char *)malloc(fileSize);
    fread(fileBuffer, 1, fileSize, fp);
    fclose(fp);

    unsigned char *pixelData = fileBuffer + 54; //sama kyk diatas liat aja

    char message[1000] = {0}; //menyiapkan 1000 karakter yang di set menjadi null karakter "\0" kenapa null? gtw wkwkwk canda, jadi cari aja di google
    int messageIndex = 0;
    int bitIndex = 0;
    unsigned char currentChar = 0;
    const char endTag[] = "<end>";  // jangan lupa di beri <end> biar untuk tau letak berakhirnya pesan
// tapi kalo user masukan pesan <end> dia bakal dikira endtag wkwkwk
    for (long i = 0; i < fileSize - 54; i++) { //mengambil 1 1 bit pada pixeldata, kalo gasalah LSB
        currentChar |= (pixelData[i] & 1) << (7 - bitIndex);
        bitIndex++;

        if (bitIndex == 8) { // kalo index sekarang 8(yang terakhir dibaca index 7)
            message[messageIndex] = currentChar;

            // Periksa apakah sudah mencapai tag <end>
            /*(>-<) kondisi pertama mengecek apakah message sudah cukup untuk di isi <end> 
            jika messageindex sudah lebih besar atau sama dengan endtag maka true
            kondisi kedua membandingkan message(5 karakter terakhir) dengan <end>

     jadi endtag ini kan berupa "<end>" itu ada 5 karakter kenapa dikurang 1? karena index dari 0, misal message sekarang index 3 berarti 3 itu masih kurang dari 4, jadi ini tidak true
     kalo bit index sekarang 4 ato lebih baru yg bagian "messageIndex >= (sizeof(endTag) - 1)" ini menjadi true
     lalu untuk bagian "strncmp(message + messageIndex - (sizeof(endTag) - 1), endTag, sizeof(endTag) - 1)" kita mengambil 5 karakter terakhir dari message
     atau mengambil 5 index dari belakang, misal message sekarng "patora" berarti 5 terakhir itu "atora" nah 5 karakter terakhir ini dibandingkan dengan endtag "<end>" jika sama maka true jika beda maka false
     contoh kasus bener , message = "patora<end>" maka yang dibandingkan adalah <end> dengan <end>, sama kan? true gitu

     message[messageIndex - (sizeof(endTag) - 1)] = '\0'; ini menghapus endtag nya biar dari message = "patora<end>", menjadi message = "patora"
			*/
            if (messageIndex >= (sizeof(endTag) - 1) && 
                strncmp(message + messageIndex - (sizeof(endTag) - 1), endTag, sizeof(endTag) - 1) == 0) {
                message[messageIndex - (sizeof(endTag) - 1)] = '\0'; // Hapus tag <end>
                break;
            }

            messageIndex++;
            bitIndex = 0; // tuh index di jadiin 0 kan
            currentChar = 0;

            if (messageIndex >= sizeof(message) - 1) {
                break; // Pesan terlalu panjang, siapa juga naruh pesan panjang banget
            }
        }
    }

    free(fileBuffer);

    if (messageIndex == 0) {
        printf("Tidak ada pesan yang ditemukan atau pesan terlalu panjang.\n");
    } else {
        printf("Pesan yang ditemukan: %s\n", message);
    }
}

void menu(){
	printf("1. Tulis Pesan\n");
	printf("2. Baca Pesan\n");

}
// int main perlu dijelaskan?? t(>-<t)
int main(){
    char message[1000];
    char filename[100];
	char filehasil[100];
	
	int pilihan;
	menu();
	printf("Pilihan : ");
	scanf("%i",&pilihan);
	getchar();

	
	
	switch(pilihan) {
		case 1:{
			printf("Masukkan nama file gambar BMP: ");
		    scanf("%s", filename);
		    getchar(); 
		
		    printf("Masukkan pesan: ");
		    fgets(message, sizeof(message), stdin);
		    message[strcspn(message, "\n")] = 0;
		
		    checkmessage(filename, message);
			printf("Masukkan nama file hasil gambar BMP: ");
		    scanf("%s", filehasil);
		    if (maxmsg >= totalBits) {
		        embedMessage(filename, filehasil, message);
		    }
			break;
		}
		case 2: {
			printf("Masukkan nama file gambar BMP: ");
		    scanf("%s", filename);
		
		    extractMessage(filename);
			break;
		}
            default:
                printf("Pilihan tidak valid.\n");
        }
			return 0;
	}
		
	
	
	

