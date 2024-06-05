#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <cmath>

int hitung_sum(int data[], int panjang) {//membuat fungsi untuk sum "int data[], array untuk menyimpan angka yang dimasukan user) panjang dari mana? nanti liat di bagian sum ya
    int total = 0;// kenapa total 0? karena total akan ditambahkan dengan bilangan yang dimasukan user ,jika total tidak 0 maka hasil tidak valid
    for (int i = 0; i < panjang; ++i) {// lakukan perulangan sebanyak "panjang"
        total += data[i];//total ditambah data/angka yang dimasukan user
    }
    return total;//mengembalikan nilai total, jadi pada fungsi ini akan mengeluarkan total sebagai output
}

double hitung_average(int data[], int panjang) { //kenapa double? tadikan int, bebas sih hehe, boleh ganti jadi int kalo mau XD
    if (panjang == 0) {//kalo panjang 0 kan gada angka ya? ini ga harus isi sih hehe
        return 0;// dihapus bagian if ini gpp kok XD
    }
    int total = hitung_sum(data, panjang);//karena average(rata-rata) perlu menjumlahkan jadi kita pake hitung_sumnya, dari pada buat ulang mumpung udah buat hehe
    return (double) total / panjang;// kenapa isi double? jadi double di depan total itu berfungsi untuk mengubah variable total yang awalnya integer menjadi double
}//kenapa diubah jadi double? karena pada fungsi ini


int main(int argc, char** argv) {// Patora Ask : kalian tau perbedaan argc dan argv?
//argc merupakan jumlah berapa kata yang kalian masukan saat memulai program ini di command prompt
//misalkan "./kalkulator.exe 1 + 1" ini berarti agrc = 4, karena yang dihitung itu, (kalkulator.exe,1,+,1) paham kan
//sedangkan argv itu yang dimasukan user, yaitu (kalkulator.exe,1,+,1), itu semua argv, jadi argv itu barangnya argc itu menghitung jumlah barangnya dh gitu aja
    int num1, num2;//ni perlu tak jelasin?
    char operationSign[10]; // operationsign itu nanti tandanya misal, sum, avg, +, - ,/ ,log,sin,cos dll
    strcpy(operationSign, argv[1]); // strcpy itu mengcopy nilai dari argv[1] dan dimasukan ke operatorsign, misalkan "./kalkulator.exe 1 + 1", index 0 dimulai dari kalkulator.exe
    if (strcmp(operationSign, "sum") == 0 || strcmp(operationSign, "avg") == 0) {//strcmp itu membandingkan operationsign dengan "sum" atau dengan "avg", tanda "||" itu artinya "or", jadi jika salah satu true maka akan true hasilnya
//contoh jika "./kalkulator.exe sum 1 2 3" index 1 = sum, karena operationsign nya itu sum(argv[1]) maka pada bagian "strcmp(operationSign, "sum") == 0" menjadi true sehingga melakukan program dibawahnya
//namun jika "./kalkulator.exe 3 + 1" index 1 = 3, karena operationsign nya itu 3(argv[1]) maka tidak ada kondisi yang true, program akan lanjut ke bagian "else if"
        int data[argc - 2]; // membuat array integer yang akan memuat angka angka yang dimasukan user misal "./kalkulator.exe sum 1 2 3" maka 1 2 3 akan dimasukan disini
//kenapa[argc-2]? karena 2 argv pertama tidak dimasukan (./kalkulator.exe dan operationsign(sum/avg))
	for (int i = 2; i < argc; i++) {//disini karena int i = 2 maka perulangan mengikuti argc, jika int i = 0, maka argc disini dapat diganti dengan argc - 2
            data[i - 2] = atoi(argv[i]); // data[i-2] karena i = 2, jika i = 0 dan argc diganti menjadi argc - 2 pada perulangan, maka data[i-2] dapat ditulis data[i]
        }//index data dikurang 2 karena untuk menulis mulai dari index 0
//nah sekarang kita bahas atoi, atoi(argv[i]), atoi ini mengambil angka pada argv[i] , jadi atoi ini hanya mengambil angka saja dari input user
//misal "./kalkulator.exe sum 1 2 3 empat 5" maka atoi akan mengambil (1,2,3,5) dan menyimpannya di data, "empat akan dihiraukan(gak diajak kasian)"
        if (strcmp(operationSign, "sum") == 0) {//ini membandingkan lagi operationsign dengan "sum" karena pada if yang tadi ada 2 kondisi yaitu "sum" dan "avg"
            int total = hitung_sum(data, argc - 2); //nah disini kita pake fungsi yang udah dibuat tadi "hitung_sum(data, argc - 2)" jadi argc-2 itu sebagai panjang pada perulangan di hitung_sum paham kan? masa nanya lagi kok di kurang 2, baca lagi deh diatas dah tak jelasin -_- 
            printf("%d", total);//lah kok %d patora sensei? %d itu artinya double, kenapa double? ya gpp biar keren aja anjay wkwkwkw, pake %i juga gpp XD
        } else if (strcmp(operationSign, "avg") == 0) {//ini membandingkan lagi operationsign dengan "avg" karena pada if yang tadi ada 2 kondisi yaitu "sum" dan "avg"
            double avg = hitung_average(data, argc - 2); // sama aja cuma average
            printf("%.2f", avg);//ini perlu tak jelasin?
        }
    }else if (argc == 4) { // argc 4 itu contohnya "kalkulator.exe 1 + 1" kok 4? dah tak jelasin diatas baca ya hehehe
        num1 = atoi(argv[1]); //jadi angka pertama dimasukin disini (num1)
        num2 = atoi(argv[3]); //angka kedua disini
        strcpy(operationSign, argv[2]); // dah tak jelasin tadi ini untuk menyalin argv index 2
// index 2 disini misal "kalkulator.exe 1 + 1" berarti "+" sebagai index 2 ok paham?
        // ini sebenernya sama semua jadi tak jelasin disini aja deh
	//strcmp itukan membandingkan operationsign kan berupa index kedua dari input user
	//jadi operationsign dibandingin satu satu ama tanda tanda kyk "+,-,/,*,dan lain2)
	//kalo true ya dijalanin yang dibawahnya kalo gak true ya else if di cek
        if (strcmp(operationSign, "+") == 0) { 
            int x = num1 + num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "-") == 0) {
            int x = num1 - num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "*") == 0) {
            int x = num1 * num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "/") == 0) {
            float x = (float) num1 / (float) num2;//patora sensei ini kok isi float didepan num1 sama num2 nya
            printf("%f", x);//jadi tipedata didepan variable pas operasi gini itu fungsi nya untuk mengubah tipe datanya, karena tadi num1 dan num2 itu integer,disini diubah jadi float, kenapa float? entah dah lupa kwkwkwk
    	}else if (strcmp(operationSign, "div") == 0) {
            int x = (int) num1 / (int) num2;//ini kok isi int sensei? kan udah integer num1 sama num2 nya
            printf("%i", x);
    	}else if (strcmp(operationSign, "%") == 0) {
            int x = (int) num1 / (int) num2;// ini juga, jawabannya cuma 1, ya gpp cuma iseng hehe
            int y = num1 % num2;
            printf("Hasil = %i, Sisa = %i", x,y);
        } else if (strcmp(operationSign, "mod") == 0) {
            int x = num1 % num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "^") == 0) {
            int x = pow(num1, num2);//pow itu apa? pow itu pangkat, dah dikasi sama #include <cmath>, jadi pake aj, kalo mau buat manual juga gpp
            printf("%i", x);
        } else if (strcmp(operationSign, "log") == 0) {
            double result = log(num2) / log(num1);// log juga ada di #include <cmath>
            printf("%.1f\n", result);
        } else {
            printf("Tanda yang Anda masukkan salah\n");
        }
    }else if (argc == 3) { // Untuk 2 argumen lagi nanya? tak pukul t(o-ot)
        num1 = atoi(argv[2]);// disini cuma ada num1 wkwkkw jomblo 
        strcpy(operationSign, argv[1]);//sama kek diatas menulis argv[1] sebagai operationsign
//contoh "kalkulator.exe akar 1" "akar" sebagai index 1 = operationsign, "1" sebagai index 2 sebagai num1
        if (strcmp(operationSign, "akar") == 0) {//membandingkan operationsing dengan "akar" eh dah tak jelasin au ah
            int x = sqrt(num1);//sqrt dah ada di #include <cmath> 
            printf("%i", x);
        } else if (strcmp(operationSign, "log") == 0) {
            float x = log10(num1);//lah tadi cuma "log" sekarang kok ada 10nya? 10 itu sebagai pengganti num2, tapi yang ini udah fix 10, misal "kalkulator.exe 100 log 10" itu sama dengan "kalkulator log 100" paham kan? kalo ga harus paham
            printf("%f", x);
        } else if (strcmp(operationSign, "sin") == 0) {
            double angle_radians, result;
            angle_radians = num1 * M_PI / 180;//M_PI itu phi ya 22/7 atau 3,14 atau 3,14159265358979323846, kenapa dikali phi dan dibagi 180? gtw rumus nya kek gitu cari aja deh
            float x = sin(angle_radians);//sin sudah tersedia di #include <cmath>
            result = sin(angle_radians);
            printf("%f", result);
        } else if (strcmp(operationSign, "cos") == 0) {//sama kek diatas cuma cos
            double angle_radians, result;
            angle_radians = num1 * M_PI / 180;
            float x = cos(angle_radians);
            result = cos(angle_radians);
            printf("%f", result);
        } else if (strcmp(operationSign, "tan") == 0) {//sama kek diatas cuma tan eh ada beda jir
            float angle_radians, result;
		//jadi jika num1 itu 90 atau angka berapapun yang pas dibagi sama 180 itu sisa 90 contoh 270 bagi 180 sisa 90, maka print itu baca sendiri, ingat tanda "||" itu artinya "or" jika salah satu saja true maka akan true
            if((num1==90)||(num1%180==90)){//jadi disini tan 90 dan apapun yang dibagi 180 sisa nya 90 itu hasilnya tak terdefinikan
            	printf("Tak Terdefinisikan");//gak percaya? cel gogel wkwkkw,
			}else{
			angle_radians = num1 * M_PI / 180;
            result = tan(angle_radians);//tan sudah ada di #include <cmath>
            printf("%f", result);
			}	
        } else if (strcmp(operationSign, "factorial") == 0) {
            int faktorial = 1;//tau faktorial kan? misal "kalkulator.exe factorial 3" itu berarti 1 * 2 * 3
		//kok faktorial = 1? karena ini melakukan perkalian, agar tidak merubah/merusak hasil, kalo di set 0 (faktorial = 0) hasilnya bakal terus 0 wkwkwkw
            for (int i = 1; i <= num1; i++) {//perulangan hingga sejumlah num1, i = 1 itu dengan sama alasannya kayak faktorial = 1
                faktorial *= i;// ini sama dengan faktorial = faktorial * i
            }
            printf("%d", faktorial);
        } else if (strcmp(operationSign, "ln") == 0) {//jangan nanya bagian ln karena saya tidak pintar matematika hehe
            float x = log(num1);
            printf("%f", x);
        } else {
            printf("Tanda yang Anda masukkan salah\n");
        }
    }
    return 0;
}
