#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <cmath>

int hitung_sum(int data[], int panjang) {//membuat fungsi untuk sum "int data[], array untuk menyimpan angka yang dimasukan user) panjang dari mana? nanti liat di bagian sum ya
    int total = 0;
    for (int i = 0; i < panjang; ++i) {
        total += data[i];
    }
    return total;
}

double hitung_average(int data[], int panjang) {
    if (panjang == 0) {
        return 0;
    }
    int total = hitung_sum(data, panjang);
    return (double) total / panjang;
}


int main(int argc, char** argv) {
    int num1, num2;
    char operationSign[10]; // Menggunakan array karakter untuk menyimpan tanda operasi 
    strcpy(operationSign, argv[1]); // Mengambil tanda operasi dari argumen pertama
    if (strcmp(operationSign, "sum") == 0 || strcmp(operationSign, "avg") == 0) {
        int data[argc - 2]; // Array untuk menyimpan argumen angka
        for (int i = 2; i < argc; i++) {
            data[i - 2] = atoi(argv[i]); // Menyimpan argumen sebagai integer dalam array
        }

        if (strcmp(operationSign, "sum") == 0) {
            int total = hitung_sum(data, argc - 2); // Menghitung jumlah dari argumen
            printf("%d", total);
        } else if (strcmp(operationSign, "avg") == 0) {
            double avg = hitung_average(data, argc - 2); // Menghitung rata-rata dari argumen
            printf("%.2f", avg);
        }
    }else if (argc == 4) { // Untuk 3 argumen
        num1 = atoi(argv[1]);
        num2 = atoi(argv[3]);
        strcpy(operationSign, argv[2]); // Menggunakan strcpy untuk menyalin string ke variabel karakter

        // Memproses operasi matematika berdasarkan tanda operasi yang diberikan
        if (strcmp(operationSign, "+") == 0) { // Menggunakan strcmp untuk membandingkan string
            int x = num1 + num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "-") == 0) {
            int x = num1 - num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "*") == 0) {
            int x = num1 * num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "/") == 0) {
            float x = (float) num1 / (float) num2;
            printf("%f", x);
    	}else if (strcmp(operationSign, "div") == 0) {
            int x = (int) num1 / (int) num2;
            printf("%i", x);
    	}else if (strcmp(operationSign, "%") == 0) {
            int x = (int) num1 / (int) num2;
            int y = num1 % num2;
            printf("Hasil = %i, Sisa = %i", x,y);
        } else if (strcmp(operationSign, "mod") == 0) {
            int x = num1 % num2;
            printf("%i", x);
        } else if (strcmp(operationSign, "^") == 0) {
            int x = pow(num1, num2);
            printf("%i", x);
        } else if (strcmp(operationSign, "log") == 0) {
            double result = log(num2) / log(num1);
            printf("%.1f\n", result);
        } else {
            printf("Tanda yang Anda masukkan salah\n");
        }
    }else if (argc == 3) { // Untuk 2 argumen
        num1 = atoi(argv[2]);
        strcpy(operationSign, argv[1]);

        if (strcmp(operationSign, "akar") == 0) {
            int x = sqrt(num1);
            printf("%i", x);
        } else if (strcmp(operationSign, "log") == 0) {
            float x = log10(num1);
            printf("%f", x);
        } else if (strcmp(operationSign, "sin") == 0) {
            double angle_radians, result;
            angle_radians = num1 * M_PI / 180;
            float x = sin(angle_radians);
            result = sin(angle_radians);
            printf("%f", result);
        } else if (strcmp(operationSign, "cos") == 0) {
            double angle_radians, result;
            angle_radians = num1 * M_PI / 180;
            float x = cos(angle_radians);
            result = cos(angle_radians);
            printf("%f", result);
        } else if (strcmp(operationSign, "tan") == 0) {
            float angle_radians, result;
            if((num1==90)||(num1%180==90)){
            	printf("Tak Terdefinisikan");
			}else{
			angle_radians = num1 * M_PI / 180;
            result = tan(angle_radians);
            printf("%f", result);
			}	
        } else if (strcmp(operationSign, "factorial") == 0) {
            int faktorial = 1;
            for (int i = 1; i <= num1; i++) {
                faktorial *= i;
            }
            printf("%d", faktorial);
        } else if (strcmp(operationSign, "ln") == 0) {
            float x = log(num1);
            printf("%f", x);
        } else {
            printf("Tanda yang Anda masukkan salah\n");
        }
    }
    return 0;
}
