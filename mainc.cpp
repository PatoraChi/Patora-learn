#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NIM_LENGTH 11
#define MAX_NAMA_LENGTH 100
#define MAX_TAHUN_MASUK_LENGTH 5


struct Mahasiswa {
    char NIM[MAX_NIM_LENGTH];
    char nama[MAX_NAMA_LENGTH];
    char tahun_masuk[MAX_TAHUN_MASUK_LENGTH];
    float IPK;
};

Mahasiswa mahasiswas[100]; // Maksimum 100 mahasiswa, sesuaikan dengan kebutuhan

int jumlahMahasiswa = 0;

int isNIMValid(const char* NIM) {
    if (strlen(NIM) != 10) // mengecek apakah nim sudah berisi 10 digits
        return 0;

    for (int i = 0; i < strlen(NIM); ++i) { // mengecek apakah nim sudah berupa angka
        if (!(NIM[i] >= '0' && NIM[i] <= '9'))
            return 0;
    }

    for (int j = 0; j < jumlahMahasiswa; ++j) {
        if (strcmp(mahasiswas[j].NIM, NIM) == 0) // mengecek apakah nim sudah ada
            return 0;
    }

    return 1;
}

int isNamaValid(const char* nama) {
    int hasAlpha = 0; // untuk menandai apakah nama mengandung huruf
    for (int i = 0; i < strlen(nama); ++i) {
        if ((nama[i] >= 'a' && nama[i] <= 'z') || (nama[i] >= 'A' && nama[i] <= 'Z')) { // mengecek apakah nama sudah berupa huruf
        	hasAlpha = 1;
        } else if (nama[i] != ' ') { // memperbolehkan nama berisi spasi
        	return 0;
        }
    }
    return hasAlpha; // kembalikan 0 jika nama hanya berisi spasi, selain itu kembalikan 1
}

int isTahunMasukValid(const char* tahun_masuk) { // mengecek apakah tahun masuk sudah berjumlah 4 digit dan hanya berupa angka
    if (strlen(tahun_masuk) != 4)
        return 0;
    for (int i = 0; i < strlen(tahun_masuk); ++i) {
        if (!(tahun_masuk[i] >= '0' && tahun_masuk[i] <= '9'))
            return 0;
    }
    return 1;
}

int isIPKValid(float IPK) { // mengecek apakah ipk sudah berupa angka 0-4
    return IPK >= 0 && IPK <= 4;
}

void tambahkanData(const char* File) {
    Mahasiswa mhs;
    printf("Masukkan NIM: ");
    scanf("%s", mhs.NIM);
    if (!isNIMValid(mhs.NIM)) {
        printf("NIM tidak valid atau sudah ada.\n");
        return;
    }
    printf("Masukkan Nama: ");
    getchar(); // Membersihkan newline character dari buffer input
    fgets(mhs.nama, sizeof(mhs.nama), stdin);
    mhs.nama[strcspn(mhs.nama, "\n")] = '\0'; // Mengganti newline character dengan null terminator
    if (!isNamaValid(mhs.nama)) {
        printf("Nama tidak valid. Nama harus berupa huruf.\n");
        return;
    }
    printf("Masukkan Tahun Masuk: ");
    scanf("%s", mhs.tahun_masuk);
    if (!isTahunMasukValid(mhs.tahun_masuk)) {
        printf("Tahun masuk tidak valid. Tahun masuk harus terdiri dari 4 digit angka.\n");
        return;
    }
    printf("Masukkan IPK: ");
    scanf("%f", &mhs.IPK);
    if (!isIPKValid(mhs.IPK)) {
        printf("IPK tidak valid. IPK harus berada dalam rentang 0-4.\n");
        return;
    }

    // Menulis data ke file
    FILE *file = fopen(File, "a");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", File);
        return;
    }
    fprintf(file, "%s,%s,%s,%.2f\n", mhs.NIM, mhs.nama, mhs.tahun_masuk, mhs.IPK);
    fclose(file);

    // Memasukkan data ke dalam array mahasiswas
    mahasiswas[jumlahMahasiswa++] = mhs;
    printf("Data berhasil ditambahkan.\n");
}

void tampilkanMenu() {
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

void tampilkanData(const char* File,const Mahasiswa* data) {
    printf("NIM: %s\n", data->NIM);
    printf("Nama: %s\n", data->nama);
    printf("Tahun Masuk: %s\n", data->tahun_masuk);
    printf("IPK: %.2f\n", data->IPK);
}
void editData(const char* File,const char* nim) {
    int i;
    for (i = 0; i < jumlahMahasiswa; ++i) {
        if (strcmp(mahasiswas[i].NIM, nim) == 0) {
            Mahasiswa *mhs = &mahasiswas[i]; // Menemukan mahasiswa dengan NIM yang sesuai

            Mahasiswa newMhs;

            printf("Masukkan NIM baru (tekan enter untuk mempertahankan NIM sebelumnya): ");
            getchar(); // Membersihkan newline character dari buffer input
            fgets(newMhs.NIM, sizeof(newMhs.NIM), stdin);
            newMhs.NIM[strcspn(newMhs.NIM, "\n")] = '\0'; // Mengganti newline character dengan null terminator
            if (newMhs.NIM[0] == '\0') { // Jika input kosong, pertahankan NIM sebelumnya
                strcpy(newMhs.NIM, mhs->NIM);
                
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

            // Mengganti data jika semua data baru valid
            *mhs = newMhs;

            // Menulis ulang data ke file CSV
            FILE *file = fopen(File, "w");
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
        if (strcmp(mahasiswas[i].NIM, NIM) == 0) {
            printf("Data dengan NIM %s berhasil dihapus.\n", NIM);

            // Menghapus data dari array mahasiswas
            for (int j = i; j < jumlahMahasiswa - 1; ++j) {
                mahasiswas[j] = mahasiswas[j + 1];
            }
            jumlahMahasiswa--;

            // Menulis ulang data ke file CSV
            FILE *file = fopen(File, "w");
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

void bacaData(char* File) {
    jumlahMahasiswa = 0; // Reset jumlah mahasiswa

    FILE *file = fopen(File, "r");
    if (file == NULL) {
        printf("File %s tidak ditemukan. Buat file baru.\n", File);
        return;
    }

    char buffer[200]; // Buffer untuk menyimpan setiap baris dari file CSV
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Pisahkan data dari setiap baris
        char* token = strtok(buffer, ",");
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].NIM, token);
        } else {
            break; // Jika token pertama kosong, hentikan pembacaan file
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].nama, token);
        } else {
            break; // Jika token kedua kosong, hentikan pembacaan file
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].tahun_masuk, token);
        } else {
            break; // Jika token ketiga kosong, hentikan pembacaan file
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            mahasiswas[jumlahMahasiswa].IPK = atof(token);
        } else {
            break; // Jika token keempat kosong, hentikan pembacaan file
        }

        jumlahMahasiswa++; // Tambahkan jumlah mahasiswa setiap kali membaca satu baris data
    }

    fclose(file);
}

void cariData(const char* File,const char* keyword) {
    int found = 0;
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        Mahasiswa *mhs = &mahasiswas[i];
        // Cek apakah NIM, nama, atau tahun_masuk mengandung kata kunci
        if (strstr(mhs->NIM, keyword) != NULL ||
            strstr(mhs->nama, keyword) != NULL ||
            strstr(mhs->tahun_masuk, keyword) != NULL) {
            found = 1;
            tampilkanData(File,mhs);
            printf("\n");
        } else {
            char ipkString[10];
            snprintf(ipkString, sizeof(ipkString), "%.2f", mhs->IPK);
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
    // // Membaca data saat program dimulai
    int pilihan;
    char input[100];

    do {
        system("cls"); // Clear screen
        tampilkanMenu();
        scanf("%s", input);

        if (strlen(input) != 1 || !(input[0] >= '1' && input[0] <= '8')) {
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

