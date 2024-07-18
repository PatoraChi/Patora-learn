#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Mahasiswa {
    char NIM[11];
    char nama[100];
    char tahun_masuk[5];
    float IPK;
    char FileNames[100];
    
};

Mahasiswa mahasiswas[100]; 
int jumlahMahasiswa = 0;


char File[100];
char isi[100];
int count = 0;
FILE *fp;

void menu1() {
    printf("Menu:\n");
    printf("1. Buat File Baru\n");
    printf("2. Buka FIle\n");
    printf("3. Tampilkan File Tersedia\n");
    printf("4. Hapus File\n");
    printf("5. Rename File\n");
    printf("6. Keluar\n");
    printf("File tersedia = %i\n", count);
    printf("Pilihan : ");

	
}
void menu2() {
    printf("Menu:\n");
    printf("1. Tambah Data\n");
    printf("2. Hapus Data\n");
    printf("3. Edit Data\n");
    printf("4. Tampilkan Data\n");
    printf("5. Cari Data\n");
    printf("6. Keluar\n\n\n");

    printf("Pilih menu: ");
}

void csv() {
    if (strstr(File, ".csv") == NULL) {
        strcat(File, ".csv");
    }
}



void simpanfilelist() {
    fp = fopen("filelist.txt", "w");
    if (fp == NULL) {
        printf("File tidak ditemukan");
    } else {
        for (int i = 0; i < count; i++) {
            fprintf(fp, "%s\n", mahasiswas[i].FileNames);
        }
        fflush(fp); 
        fclose(fp);
    }
}


void enter() {
    printf("Tekan enter untuk melanjutkan...");
    while (getchar() != '\n')
        ;
    getchar();
}

void bacafilelist() {
    count = 0;
    fp = fopen("filelist.txt", "r");
    if (fp == NULL) {
        printf("file tidak ditemukan");
    } else {
        while (fgets(isi, sizeof(isi), fp) != NULL) {
            isi[strcspn(isi, "\n")] = 0; 
            strcpy(mahasiswas[count].FileNames, isi);
            count++;
        }
        fclose(fp);
    }
}

void tampilkanfilelist() {

    for (int i = 0; i < count; i++) {
        printf("%s\n", mahasiswas[i].FileNames);
    }
}

void hapusfile(const char *File) {
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(mahasiswas[i].FileNames, File) == 0) {
            found = 1;
            if (remove(File) == 0) {
                printf("File berhasil dihapus\n");
                for (int j = i; j < count - 1; j++) {
                    strcpy(mahasiswas[j].FileNames, mahasiswas[j + 1].FileNames);
                }
                count--;
                simpanfilelist();
            } else {
                printf("Gagal menghapus file\n");
            }
            break;
        }
    }
    if (!found) {
        printf("File tidak ditemukan\n");
    }
}

void renamefile(const char* xFile){
	char newfile[100];
	int found = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(mahasiswas[i].FileNames, xFile) == 0) {
            found = 1;
            printf("Masukan Nama File Baru : ");
            scanf("%s",newfile);
            if (strstr(newfile, ".csv") == NULL) {
                    strcat(newfile, ".csv");
            }
            if (rename(mahasiswas[i].FileNames,newfile) == 0) {
                printf("File berhasil direname\n");
                strcpy(mahasiswas[i].FileNames,newfile);
                simpanfilelist();
            } else {
                printf("Gagal mengrename file\n");
            }
            break;
        }
    }
    if (!found) {
        printf("File tidak ditemukan\n");
    }
}


int isNIMValid(const char* NIM) {
    if (strlen(NIM) != 10) 
        return 0;

    for (int i = 0; i < strlen(NIM); ++i) { 
        if (!(NIM[i] >= '0' && NIM[i] <= '9'))
            return 0;
    }

    for (int j = 0; j < jumlahMahasiswa; ++j) {
        if (strcmp(mahasiswas[j].NIM, NIM) == 0) 
            return 0;
    }

    return 1;
}

int isNamaValid(const char* nama) {
    int hasAlpha = 0; 
    for (int i = 0; i < strlen(nama); ++i) {
        if ((nama[i] >= 'a' && nama[i] <= 'z') || (nama[i] >= 'A' && nama[i] <= 'Z')) {
        	hasAlpha = 1;
        } else if (nama[i] != ' ') {
        	return 0;
        }
    }
    return hasAlpha;
}

int isTahunMasukValid(const char* tahun_masuk) { 
    if (strlen(tahun_masuk) != 4)
        return 0;
    for (int i = 0; i < strlen(tahun_masuk); ++i) {
        if (!(tahun_masuk[i] >= '0' && tahun_masuk[i] <= '9'))
            return 0;
    }
    return 1;
}

int isIPKValid(float IPK) { 
    return IPK >= 0 && IPK <= 4;
}

void tambahkanData() {
    Mahasiswa mhs;
    printf("Masukkan NIM: ");
    scanf("%s", mhs.NIM);
    if (!isNIMValid(mhs.NIM)) {
        printf("NIM tidak valid atau sudah ada.\n");
        return;
    }
    printf("Masukkan Nama: ");
    getchar(); 
    fgets(mhs.nama, sizeof(mhs.nama), stdin);
    mhs.nama[strcspn(mhs.nama, "\n")] = '\0'; 
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

    
    FILE *file = fopen(File, "a");
    if (file == NULL) {
        printf("Gagal membuka file %s.\n", File);
        return;
    }
    fprintf(file, "%s,%s,%s,%.2f\n", mhs.NIM, mhs.nama, mhs.tahun_masuk, mhs.IPK);
    fclose(file);

    
    mahasiswas[jumlahMahasiswa++] = mhs;
    printf("Data berhasil ditambahkan.\n");
}
void tampilkanData(const Mahasiswa* data) {
    printf("NIM: %s\n", data->NIM);
    printf("Nama: %s\n", data->nama);
    printf("Tahun Masuk: %s\n", data->tahun_masuk);
    printf("IPK: %.2f\n", data->IPK);
}
void editData(const char* nim) {
    int i;
    for (i = 0; i < jumlahMahasiswa; ++i) {
        if (strcmp(mahasiswas[i].NIM, nim) == 0) {
            Mahasiswa *mhs = &mahasiswas[i]; 

            Mahasiswa newMhs;
        	printf("Masukkan NIM baru (tekan enter untuk mempertahankan NIM sebelumnya): ");
            getchar(); 
            fgets(newMhs.NIM, sizeof(newMhs.NIM), stdin);
            newMhs.NIM[strcspn(newMhs.NIM, "\n")] = '\0'; 
            if (newMhs.NIM[0] == '\0') { 
                strcpy(newMhs.NIM, mhs->NIM);
               
            } else if (!isNIMValid(newMhs.NIM)) {
                printf("NIM tidak valid atau sudah ada.\n");
                return;
            }
        	getchar();
			printf("Masukkan Nama baru: ");
		    fgets(newMhs.nama, sizeof(newMhs.nama), stdin);
		    newMhs.nama[strcspn(newMhs.nama, "\n")] = '\0'; 
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

            
            *mhs = newMhs;

            
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


void hapusData(const char* NIM) {
    int i;
    for (i = 0; i < jumlahMahasiswa; ++i) {
        if (strcmp(mahasiswas[i].NIM, NIM) == 0) {
            printf("Data dengan NIM %s berhasil dihapus.\n", NIM);

            
            for (int j = i; j < jumlahMahasiswa - 1; ++j) {
                mahasiswas[j] = mahasiswas[j + 1];
            }
            jumlahMahasiswa--;

            
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

void bacaData() {
    jumlahMahasiswa = 0;
    FILE *file = fopen(File, "r");
    if (file == NULL) {
        printf("File %s tidak ditemukan. Buat file baru.\n", File);
        return;
    }

    char buffer[200]; 
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
       
        char* token = strtok(buffer, ",");
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].NIM, token);
        } else {
            break; 
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].nama, token);
        } else {
            break;
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            strcpy(mahasiswas[jumlahMahasiswa].tahun_masuk, token);
        } else {
            break; 
        }

        token = strtok(NULL, ",");
        if (token != NULL) {
            mahasiswas[jumlahMahasiswa].IPK = atof(token);
        } else {
            break;
        }

        jumlahMahasiswa++; 
    }

    fclose(file);
}
void cariData(const char* keyword) {
    int found = 0;
    for (int i = 0; i < jumlahMahasiswa; ++i) {
        Mahasiswa *mhs = &mahasiswas[i];
        
        if (strstr(mhs->NIM, keyword) != NULL ||
            strstr(mhs->nama, keyword) != NULL ||
            strstr(mhs->tahun_masuk, keyword) != NULL) {
            found = 1;
            tampilkanData(mhs);
            printf("\n");
        } else {
            char ipkString[10];
            snprintf(ipkString, sizeof(ipkString), "%.2f", mhs->IPK);
            if (strstr(ipkString, keyword) != NULL) {
                found = 1;
                tampilkanData(mhs);
                printf("\n");
            }
        }
    }
    if (!found) {
        printf("Data dengan kata kunci '%s' tidak ditemukan.\n", keyword);
    }
}



int main() {

    int pilihan,pilihan2;


    do {
        bacafilelist();
        system("cls");
        menu1();
        scanf("%i", &pilihan);
        switch (pilihan) {
           case 1: {
                int found = 0;
                printf("Masukan Nama File : ");
                scanf("%s", File);
                csv();
                for (int i = 0; i < count; i++) {
                    if (strcmp(mahasiswas[i].FileNames, File) == 0) {
                        found = 1;
                        break;
                    }
                }
                if (found) {
                    printf("File Sudah Ada\n");
                    enter();
                } else {
                    fp = fopen(File, "w");
                    if (fp == NULL) {
                        printf("Gagal membuat file.\n");
                    } else {
                    	fclose(fp);
                        strcpy(mahasiswas[count].FileNames, File);
                        count++;
                        simpanfilelist();
                       
                        printf("File Berhasil Dibuat\n");
                    }
                    enter();
                }
                break;
            }
            case 2: {
                printf("Masukan Nama File: ");
                scanf("%s", File);			   
				if (strstr(File, ".csv") == NULL){
			    strcat(File, ".csv");	
				}
                FILE *file = fopen(File, "r");
                if (file == NULL) {
                    printf("File tidak ditemukan.\n");
                    enter();
                } else {
                    fclose(file);
                    system("cls");
                    

                do {
                    system("cls");
                    menu2();
                    bacaData();
                    scanf("%i", &pilihan2);
                    switch (pilihan2) {
                            case 1:
                                tambahkanData();
                                enter();
                                break;
                            case 2:
				               char NIM[11];
				                printf("Masukkan NIM yang akan dihapus: ");
				                scanf("%s", NIM);
				                hapusData(NIM);
				                enter();
                                break;
                            case 3:
						        char nim[11];
						        printf("Masukkan NIM dari data yang akan diedit: ");
						        scanf("%s", nim);
						        editData(nim);
						        enter();
                                break;
                            case 4:
				                if (jumlahMahasiswa == 0) {
				                    printf("Tidak ada data yang tersedia.\n");
				                } else {
				                    printf("Data Mahasiswa:\n");
				                    for (int i = 0; i < jumlahMahasiswa; ++i) {
				                        printf("Data ke-%d:\n", i + 1);
				                        tampilkanData(&mahasiswas[i]);
				                        printf("\n");
				                    }
				                }				   
								enter();            
                                break;
                            case 5:
				                char keyword[100];
				                printf("Masukkan kata kunci: ");
				                scanf("%s", keyword);
				                cariData(keyword);
				                enter();
                                break;
                            case 6:
                                printf("Program selesai.\n");
                                break;
                            default:
                                printf("Pilihan tidak valid (>_<).\n");
                                enter();
                    }

                } while (pilihan2 != 6);
			}
                break;
            }
            case 3: {
                tampilkanfilelist();
                enter();
                break;
            }
            case 4: {
                char tumbal[100];
                printf("Masukan File yg Ingin di Hapus : ");
                scanf("%s", tumbal);
			    if (strstr(tumbal, ".csv") == NULL) {
			        strcat(tumbal, ".csv");
			    }
                hapusfile(tumbal);
                enter();
                break;
            }
            case 5: {
            	char tumbal[100];
                printf("Masukan File yg Ingin di Rename : ");
                scanf("%s", tumbal);
                if (strstr(tumbal, ".csv") == NULL) {
                    strcat(tumbal, ".csv");
                }
                renamefile(tumbal);
                enter();
				break;
			}
            case 6: {
            	printf("Program selesai.\n");
				break;
			}
            default :
                printf("Pilihan Tidak Valid (>_<)\n");
                enter();
        }
    } while (pilihan != 6);

    return 0;
}
