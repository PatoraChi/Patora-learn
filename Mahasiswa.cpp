#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//define itu berfungsi untuk menyetel nilai dari MAX_blablabla menjadi angka disampingnya
//jadi misalkan aku membuat seperti char NIM[MAX_NIM_LENGTH]; itu artinya sama dengan char NIM[11];
#define MAX_NIM_LENGTH 11 
#define MAX_NAMA_LENGTH 100
#define MAX_TAHUN_MASUK_LENGTH 5
//Note : 

struct Mahasiswa {
    char NIM[MAX_NIM_LENGTH];//kenapa 11?kan nim 10
    char nama[MAX_NAMA_LENGTH];
    char tahun_masuk[MAX_TAHUN_MASUK_LENGTH];//kenapa 5? kan tahun itu 4 misal 2020
    float IPK;
//karena untuk mengantisipasi eror kita menyediakan ruang untuk newline karakter(enter)
};//yah intinya jaga jaga lebih baik lebih daripada kurang gitu lah soalnya enter juga bisa diitung anjay

Mahasiswa mahasiswas[100]; // Membuat array mahasiswas dengan ukuran 100
//lah kok bisa ada tipe data Mahasiswa? lah kan udah buat itu struct Mahasiswa XD
int jumlahMahasiswa = 0;//apa bedanya buat int jumlahmahasiswa diatas int main dengan dibawah int main?
//kalo dibawah int main kita buat int jumlahmahasiswa, setiap fungsi(void) yang membutuhkan int mahasiswa itu kita perlu buat lagi
//kalo buat diatas int main itu namanya public, jadi semua fungsi dibawahnya bisa make si jumlahmahasiwa ini, sama halnya dengan mahasiswas


//untuk fungsi is valid is valid ini mengecek apakah true atau false, kalo di c++ itu bisa pake bool, jadi disini hanya ada 2 kemungkinan yaitu YES atau NO
int isNIMValid(const char* NIM) {//kalau const itu artinya tetap, jadi tidak bisa diubah,edit, makan,minum , dll. 
    if (strlen(NIM) != 10) // strlen itu menghitung panjang karena disini strlen(NIM) berarti menghitung panjang dari NIM, misal NIM itu 2020, maka hasil dari strlen(NIM) = 4
        return 0;// !=10 itu artinya jika tidak 10, karena diprogram ini NIM harus 10 biji

    for (int i = 0; i < strlen(NIM); ++i) { // mengecek apakah nim sudah berupa angka
        if (!(NIM[i] >= '0' && NIM[i] <= '9'))//jadi disini mengecek apakah nim lebih besar atau sama dengan 0 dan nim lebih kecil atau sama dengan 9, oh iya dicek per index ya
            return 0;//kalo salah satu tidak true maka NIM tidak valid, karena disini pakai && atau "and"
    }//lah kok cuma bandingin sama 0 dan 9 aja? emangnya ada angka yang (integer,0 koma sekian ga ikut) lebih kecil dari 0 dan lebih besar dari 9(1digit ya kalo 10 itu 2 digit)

    for (int j = 0; j < jumlahMahasiswa; ++j) {
        if (strcmp(mahasiswas[j].NIM, NIM) == 0) // strcmp itu kan membandingkan , mahasiswas[j].NIM itu NIM yang sudah tersimpan pada array mahasiswas dengan index j
            return 0;//jadi NIM yang dimasukan user(yg sekarang) dibandingkan dengan NIM yg sudah tersimpan di array mahasiswas
    }

    return 1;//jadi jika seluruh kondisi terpenuhi maka nim valid
}

int isNamaValid(const char* nama) {
    int hasAlpha = 0; // ya penanda aja ntr taudah apa gunanya
    for (int i = 0; i < strlen(nama); ++i) {//inget strlen untuk mencari panjang, jadi misal nama = patora, strlen nya = 6(itung sendiri maap kalo salah)
        if ((nama[i] >= 'a' && nama[i] <= 'z') || (nama[i] >= 'A' && nama[i] <= 'Z')) { // sama kayak nim tapi ini membandingkan dengan huruf, kalo di NIM kan di cek sama 0 dan 9, ini dicek sama a dan z, lalu di or kan dengan huruf kapitalnya A dan Z, jadi nama bisa kapital bisa gak
        	hasAlpha = 1;// kalo udah ada huruf 1 aja di nama maka hasAlpha diset 1, apa fungsinya? nnti aja tau
        } else if (nama[i] != ' ') { // ini intinya nama boleh isi sepasi, jadi kalo sepasi boleh tapi karakter aneh kayak & * @ ! gak ya, masa nama jadi p4t0r@ wkwkkwkw 
        	return 0;//kalo isi karakter aneh aneh nama tidak valid ya , langsung retutn 0
        }
    }
    return hasAlpha; // nah disini kalo hasalpha = 1 maka return 1(nama valid) kalo hasalpha masih 0 berarti nama hanya berisi sepasi saja tidak ada hurufnya maka nama tidak valid(return 0)
}

int isTahunMasukValid(const char* tahun_masuk) { // mengecek apakah tahun masuk sudah berjumlah 4 digit dan hanya berupa angka,gitu intinya
    if (strlen(tahun_masuk) != 4)
        return 0;
    for (int i = 0; i < strlen(tahun_masuk); ++i) {
        if (!(tahun_masuk[i] >= '0' && tahun_masuk[i] <= '9'))
            return 0;
    }
    return 1;
}

int isIPKValid(float IPK) { 
    return IPK >= 0 && IPK <= 4;//intinya ipk harus lebih besar atau sama dengan 0 dan lebih kecil atau sama dengan 4, boleh isi koma koma sekian
}//kalo kedua / salah satu kondisi tidak terpenuhi makaa return 0(tidak valid)

void tambahkanData(const char* File) {//const char file itu untuk nama file yang sedang digunakan
    Mahasiswa mhs; // membuat variable mhs dengan tipe data mahasiswa
    printf("Masukkan NIM: ");//bentar ni perlu tak jelasin?
    scanf("%s", mhs.NIM);
    if (!isNIMValid(mhs.NIM)) {// ingat tanda ! itu not, jadi jika nim tidak valid ya print itu
        printf("NIM tidak valid atau sudah ada.\n");
        return;
    }
    printf("Masukkan Nama: ");
    getchar(); // Membersihkan newline character dari buffer input,apa itu buffer? pas mau ngetik tu dah buffer namanya, tempat ngetik itu buffer
    fgets(mhs.nama, sizeof(mhs.nama), stdin);//apa itu fgets? fgets sama kayak scanf cuma versi premium aja,lebih banyak fitur aja, no iklan juga hehe. di fgets ini (enter) bisa diambil/masuk paham lah kan? misal "patora(enter)" gitu jadinya
    mhs.nama[strcspn(mhs.nama, "\n")] = '\0'; // enter yang tadi tak jelasin dihapus,kok dihapus? ya kalo mau operasi string itu lebih baik diakhiri dengan NULL(\0) bukan enter(\n)
    if (!isNamaValid(mhs.nama)) {// ingat tanda ! itu not, jadi jika nama tidak valid ya print itu
        printf("Nama tidak valid. Nama harus berupa huruf.\n");
        return;
    }
    printf("Masukkan Tahun Masuk: "); //au ah males jelasin sama kek diatas 
    scanf("%s", mhs.tahun_masuk);
    if (!isTahunMasukValid(mhs.tahun_masuk)) {
        printf("Tahun masuk tidak valid. Tahun masuk harus terdiri dari 4 digit angka.\n");
        return;
    }
    printf("Masukkan IPK: ");//sama juga
    scanf("%f", &mhs.IPK);
    if (!isIPKValid(mhs.IPK)) {
        printf("IPK tidak valid. IPK harus berada dalam rentang 0-4.\n");
        return;
    }

    // Menulis data ke file
    FILE *file = fopen(File, "a");//membuat pointer tipe data FILE dengan nama file, fopen itu ya membuat file, f untuk file open ya open, kalo "a" itu artinya "add" (mungkin) hehe
//membuka file dengan mode "a" itu sama artinya menambah data baru ke file, oh ya menambahkannya ini selalu di paling belakang, kalo tau stack ya kyk gitu dah
    if (file == NULL) {//kalo null berarti file gada
        printf("Gagal membuka file %s.\n", File);
        return;
    }
    fprintf(file, "%s,%s,%s,%.2f\n", mhs.NIM, mhs.nama, mhs.tahun_masuk, mhs.IPK);//fprintf itu melakukan printf tapi file, f didepan artinya file, jangan lupa isi koma soalnya csv itu isi koma koma, benernya ga penting sih wkwkkw
    fclose(file);// jangan lupa tutup filenya abis itu

    // Memasukkan data ke dalam array mahasiswas
    mahasiswas[jumlahMahasiswa++] = mhs;//mahasiswa index jumlahmahasiswa + 1 = mhs, misal, mahasiswas sekarang index 3(data yang sudah tersimpan ada 3), lalu menambah data . jadi mahasiswas[3+1] = mhs(data yang baru), jadi setelah penambahan data mahasiswas jadi ada 4
    printf("Data berhasil ditambahkan.\n");
}

void tampilkanMenu() {// begitu lah
    printf("Menu:\n");
    printf("1. Tambah Data\n");
    printf("2. Hapus Data\n");
    printf("3. Edit Data\n");
    printf("4. Tampilkan Data\n");
    printf("5. Cari Data\n");
    printf("6. Open File\n");
    printf("7. New File\n");
    printf("8. Keluar\n\n\n");
    printf("Silahkan Lakukan Open File atau New File Jika Program Baru Di Buka\n");
    printf("Pilih menu: ");
}

void tampilkanData(const char* File,const Mahasiswa* data) {// const char* FIle disini itu ga kepake heheh XD
    printf("NIM: %s\n", data->NIM);//melakukan print
    printf("Nama: %s\n", data->nama);//melakukan print
    printf("Tahun Masuk: %s\n", data->tahun_masuk);//melakukan print
    printf("IPK: %.2f\n", data->IPK);//melakukan print
}
void editData(const char* File,const char* nim) {
    int i;
    for (i = 0; i < jumlahMahasiswa; ++i) {
        if (strcmp(mahasiswas[i].NIM, nim) == 0) {//membandingkan NIM yang dimasukan user dengan NIM yg ada di array
            Mahasiswa *mhs = &mahasiswas[i]; // kalo ada ditandai misal yg dimasukan 2020, kebetulan mahasiswas index 4 itu nim nya = 2020, maka mahasiswas index 4 ditandai dengan pointer mhs

            Mahasiswa newMhs;
//sebenernya sisanya sama kayak tambahkan data nanti
            printf("Masukkan NIM baru (tekan enter untuk mempertahankan NIM sebelumnya): ");
            getchar(); 
            fgets(newMhs.NIM, sizeof(newMhs.NIM), stdin);//lah kok ini beda? tadi pake scanf, jadi gini, di editdata ini kita bisa tidak mengganti NIM pada data dengan cara menekan enter saja, karena fgets saja yg dapat menerima enter maka pake fgets, kalo scanf ga bisa nerima enter
            newMhs.NIM[strcspn(newMhs.NIM, "\n")] = '\0'; // Mengganti newline character dengan null terminator
            if (newMhs.NIM[0] == '\0') { // nah disini kalo cuma masukin enter aja berarti NIM tidak berubah,oh iya enter udah diganti jadi null diatas 
                strcpy(newMhs.NIM, mhs->NIM);//strcpy itu mengcopy nilai ya
                
            } else if (!isNIMValid(newMhs.NIM)) {
                printf("NIM tidak valid atau sudah ada.\n");
                return;
            }
			getchar();
            printf("Masukkan Nama baru: ");
            
            fgets(newMhs.nama, sizeof(newMhs.nama), stdin);
            newMhs.nama[strcspn(newMhs.nama, "\n")] = '\0'; // Mengganti newline character dengan null terminator
            if (!isNamaValid(newMhs.nama)) {
                printf("Nama tidak valid. Nama harus berupa huruf.\n");
                return;
            }

            printf("Masukkan Tahun Masuk baru: ");
            scanf("%s", newMhs.tahun_masuk);
            if (!isTahunMasukValid(newMhs.tahun_masuk)) {
                printf("Tahun masuk tidak valid. Tahun masuk harus terdiri dari 4 digit angka.\n");
                return;
            }

            printf("Masukkan IPK baru: ");
            scanf("%f", &newMhs.IPK);
            if (!isIPKValid(newMhs.IPK)) {
                printf("IPK tidak valid. IPK harus berada dalam rentang 0-4.\n");
                return;
            }

            //nah newMhs di taruh di posisi mhs, pointer yg udh nandai tadi
            *mhs = newMhs;

            // Menulis ulang data ke file CSV
            FILE *file = fopen(File, "w");//untuk fopen mode "w" itu jika file tidak ditemukan maka program akan membuat file baru dan menulis isinya yg udah dimasukan
	//lalu jika file sudah ada maka program akan menghapus file dan membuat baru dengan isi yg baru, ini agar kita dapat mengubah data dari mahasiswa
            if (file == NULL) {
                printf("Gagal membuka file %s.\n", File);
                return;
            }
            for (int j = 0; j < jumlahMahasiswa; ++j) {
                fprintf(file, "%s,%s,%s,%.2f\n", mahasiswas[j].NIM, mahasiswas[j].nama, mahasiswas[j].tahun_masuk, mahasiswas[j].IPK);
            }
            fclose(file);

            printf("Data berhasil diedit.\n");
            return;
        }
    }
    printf("Data dengan NIM %s tidak ditemukan.\n", nim);
}


void hapusData(const char* File,const char* NIM) {
    int i;
    for (i = 0; i < jumlahMahasiswa; ++i) {
        if (strcmp(mahasiswas[i].NIM, NIM) == 0) {// sama kayak edit data , mencari NIM yang dimasukan user di array mahasiswas
            printf("Data dengan NIM %s berhasil dihapus.\n", NIM);

            // Menghapus data dari array mahasiswas
            for (int j = i; j < jumlahMahasiswa - 1; ++j) {
                mahasiswas[j] = mahasiswas[j + 1];//untuk algoritma ini seperti , misalnih kita mencari mahasiswa dengan nim 2020 , ternyata dia ada di index 3
            }//mahasiswa di index 3 di ganti dengan index selanjutnya, jadi si index 3 ini udah diganti isinya dengan si index 4, trus index 4 gmn? ya diganti juga jadi index selanjutnya sampai mentok
            jumlahMahasiswa--;//jgn lupa mengurangi jumlah mahasiswa

            // Menulis ulang data ke file CSV
            FILE *file = fopen(File, "w");//sama pake mode w karena mengganti data pada file, kalo mengganti data inget pake mode w
            if (file == NULL) {
                printf("Gagal membuka file %s.\n", File);
                return;
            }
            for (int k = 0; k < jumlahMahasiswa; ++k) {
                fprintf(file, "%s,%s,%s,%.2f\n", mahasiswas[k].NIM, mahasiswas[k].nama, mahasiswas[k].tahun_masuk, mahasiswas[k].IPK);
            }
            fclose(file);
            return;
        }
    }
    printf("Data dengan NIM %s tidak ditemukan.\n", NIM);
}

void bacaData(char* File) {//void penting karena ini akan dilakukan setiap menu muncul
    jumlahMahasiswa = 0; // Reset jumlah mahasiswa, kenapa reset? ya liat aja deh 

    FILE *file = fopen(File, "r");//mode r , artinya read atau baca, jadi mode ini tidak bisa melakukan perubahan, cuma baca aja, wkwkwk gak premium ni XD
    if (file == NULL) {
        printf("File %s tidak ditemukan. Buat file baru.\n", File);//kalo tidak ditemukan tidak membuat file baru ya wkwkwk, cuma mode w aja yg bisa buat file, ini salah ini siapa yg nulis buat file baru hadeh
        return;
    }

    char buffer[200]; // Buffer untuk menyimpan setiap baris dari file CSV
    while (fgets(buffer, sizeof(buffer), file) != NULL) {//selama baris file sekarang tidak null, lakukan ini
        // Pisahkan data dari setiap baris
        char* token = strtok(buffer, ","); //jadi tadi kan pas nyimpen di file itu kyk gini "%s,%s,%s" isi koma nya, jadi disini kita menjadi koma nya dan kalo dah ketemu stringnya dipisah
	//misal (patora,2024,glory) strtok akan menemukan koma setelah patora, jadi patora ini akan disimpan di token dan buffer sisnya jadi (2024,glory)
        if (token != NULL) {//kalo ga null disimpen token yg udah diambil disimpen di mahasiswas index jumlahmahasiswa ,kalo NIM ya NIM , nama ya nama, karena urutannya itu NIM NAMA TAHUNMSK IPK, jadi yg pertama ini NIM 
            strcpy(mahasiswas[jumlahMahasiswa].NIM, token);
        } else {
            break; // Jika token pertama kosong, hentikan pembacaan file
        }

        token = strtok(NULL, ",");//lah tadi kan buffer sekarang kok pake NULL? dipake NULL karena ini kita mau melanjutkan yang tadi,misal (patora,2024,glory) strtok pertama akan menghasilkan patora dan buffer sisa (null 2024,glory) nah dari null ini dimulai gitu tau, paham kan?
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].nama, token);
        } else {
            break; // Jika token kedua kosong, hentikan pembacaan file
        }

        token = strtok(NULL, ",");//sama aja
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].tahun_masuk, token);
        } else {
            break; // Jika token ketiga kosong, hentikan pembacaan file
        }

        token = strtok(NULL, ",");//sama aja
        if (token != NULL) {
            mahasiswas[jumlahMahasiswa].IPK = atof(token);//barua aj bilang sama dah ada kata baru atof wkwkwk
        } else {//jadi atof itu membaca string (token) dan mengubahnya menjadi floating point
            break; // Jika token keempat kosong, hentikan pembacaan file
        }

        jumlahMahasiswa++; // Tambahkan jumlah mahasiswa setiap kali membaca satu baris data, nah disini kita benar benar membaca ulang file makanya tadi jumlahnya di set 0
    }

    fclose(file);
}

void cariData(const char* File,const char* keyword) {
    int found = 0;//penanda aja
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        Mahasiswa *mhs = &mahasiswas[i];
        // Cek apakah NIM, nama, atau tahun_masuk mengandung kata kunci
        if (strstr(mhs->NIM, keyword) != NULL ||//strstr itu sama membandingkan kyk strcmp, trus apa bedanya sensei?, bedanya kalo strcmp itu harus sama percis, misal keyword nya "a" maka harus "a" baru true dia
            strstr(mhs->nama, keyword) != NULL ||//tapi kalo strstr itu kalo ketemu "a" di string yang akan dibandingkan maka akan langsung true, gak harus bener bener "a" doang gitu paham kan?
            strstr(mhs->tahun_masuk, keyword) != NULL) {
            found = 1;//kalo ketemu ditandai 
            tampilkanData(File,mhs);//di print langsung
            printf("\n");
        } else {
            char ipkString[10];
            snprintf(ipkString, sizeof(ipkString), "%.2f", mhs->IPK);//lah ini kok snprintf? jadi scanf tadi kan versi premiumnya fgets, kalo ini versi premium dari printf ya fungsinya sama aja lah
            if (strstr(ipkString, keyword) != NULL) {
                found = 1;
                tampilkanData(File,mhs);
                printf("\n");
            }
        }
    }
    if (!found) {
        printf("Data dengan kata kunci '%s' tidak ditemukan.\n", keyword);
    }
}

int main() {
    char File[100];	
    int pilihan;
    char input[100];

    do {
        system("cls"); // Clear screen
        tampilkanMenu();
	bacaData(File);//data dibaca setiap program dimulai atau tiap muncul menu baca data
        scanf("%s", input);

        if (strlen(input) != 1 || !(input[0] >= '1' && input[0] <= '8')) {//jika input lebih dari 1 digit atau input kurang dari 1 dan lebih dari 8 jadi eror 
            printf("Masukkan tidak valid. Silakan masukkan angka menu.\n");
            getchar();
            getchar();
            continue;
        }

        pilihan = input[0] - '0'; // Mengubah input karakter menjadi angka

        switch (pilihan) {
            case 1:
                tambahkanData(File);
                break;
            case 2: {
                char NIM[MAX_NIM_LENGTH];
                printf("Masukkan NIM yang akan dihapus: ");
                scanf("%s", NIM);
                hapusData(File,NIM);
                break;
            }
		    case 3: {
		        char nim[MAX_NIM_LENGTH];
		        printf("Masukkan NIM dari data yang akan diedit: ");
		        scanf("%s", nim);
		        editData(File,nim);
		        break;
		    }
            case 4:
                if (jumlahMahasiswa == 0) {
                    printf("Tidak ada data yang tersedia.\n");
                } else {
                    printf("Data Mahasiswa:\n");
                    for (int i = 0; i < jumlahMahasiswa; ++i) {
                        printf("Data ke-%d:\n", i + 1);
                        tampilkanData(File,&mahasiswas[i]);
                        printf("\n");
                    }
                }
               
                break;
            case 5: {
                char keyword[100];
                printf("Masukkan kata kunci: ");
                scanf("%s", keyword);
                cariData(File,keyword);
                break;
            }
            case 6: {
            	printf("Masukan Nama File :");
            	scanf("%s",File);
            	bacaData(File);
				break;
			}
			case 7: {
            	printf("Masukan Nama File :");
            	scanf("%s",File);
			 FILE *file = fopen(File, "w");
			    if (file == NULL) {
			        printf("File %s tidak ditemukan. Buat file baru.\n", File);
			    }
			    fclose(file);
				break;
			}
            case 8:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
        if (pilihan != 8) {
            printf("Tekan tombol enter untuk melanjutkan...");
            getchar(); // Membersihkan newline character dari buffer input
            getchar(); // Wait for user to press Enter
        }
    } while (pilihan != 8);

    return 0;
}
//semoga dipahami kalo ga hubungi orang yang membuat memberi kalian link ini wkwkkwk XD
