#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

char message[1000];
int maxmsg = 1;
int totalBits = 0;
char filetext[100];

void checkmessage(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", filename);
        return;
    }
   
    uint32_t width, height;
    fseek(fp, 18, SEEK_SET); 
    fread(&width, sizeof(uint32_t), 1, fp); 
    fread(&height, sizeof(uint32_t), 1, fp);

    maxmsg = width * height * 3;

    fclose(fp);

    const char *endMarker = "<end>";
    int markerLength = strlen(endMarker);
    totalBits = (strlen(message) + markerLength) * 8;

    if (maxmsg < totalBits) {
        printf("Pesan terlalu panjang\n");
    } else {
        printf("Pesan akan diproses\n");
    }
}

void bacatext() {
    FILE *fp = fopen(filetext, "r");
    if (fp == NULL) {
        printf("File tidak ditemukan\n");
        return;
    } else {
        message[0] = '\0';  // Inisialisasi message agar kosong
        char line[1000];
        while (fgets(line, sizeof(line), fp) != NULL) {
            strcat(message, line);  // Gabungkan setiap baris dengan message
        }
    }
   
    fclose(fp);
}

void embedMessage(const char *inputFilename, const char *outputFilename) {
    FILE *inputFile = fopen(inputFilename, "rb");
    if (inputFile == NULL) {
        printf("Error: Tidak dapat membuka file %s\n", inputFilename);
        return;
    }

    FILE *outputFile = fopen(outputFilename, "wb");
    if (outputFile == NULL) {
        printf("Error: Tidak dapat membuat file %s\n", outputFilename);
        fclose(inputFile);
        return;
    }

    fseek(inputFile, 0, SEEK_END);
    long fileSize = ftell(inputFile);
    fseek(inputFile, 0, SEEK_SET);

    unsigned char *fileBuffer = (unsigned char*)malloc(fileSize);
    fread(fileBuffer, 1, fileSize, inputFile);
    fclose(inputFile);
	
    unsigned char *pixelData = fileBuffer + 54; 
    const char *endMarker = "<end>";
    char *fullMessage = (char*)malloc(strlen(message) + strlen(endMarker) + 1);

    strcpy(fullMessage, message);
    strcat(fullMessage, endMarker);

    int messageIndex = 0;
    int bitIndex = 7;
    int fullMessageLength = strlen(fullMessage);

    for (int i = 0; i < totalBits; i++) {
        if (fullMessage[messageIndex] & (1 << bitIndex)) { 
            pixelData[i] |= 1; 
        } else {
            pixelData[i] &= ~1;
        }

        bitIndex--;
        if (bitIndex < 0) {
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

    fseek(fp, 0, SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    unsigned char *fileBuffer = (unsigned char *)malloc(fileSize);
    fread(fileBuffer, 1, fileSize, fp);
    fclose(fp);

    unsigned char *pixelData = fileBuffer + 54; 

    char message[1000] = {0}; 
    int messageIndex = 0;
    int bitIndex = 0;
    unsigned char currentChar = 0;
    const char endTag[] = "<end>";  

    for (long i = 0; i < fileSize - 54; i++) { 
        currentChar |= (pixelData[i] & 1) << (7 - bitIndex);
        bitIndex++;

        if (bitIndex == 8) { 
            message[messageIndex] = currentChar;
            if (messageIndex >= (sizeof(endTag) - 1) && 
                strncmp(message + messageIndex - (sizeof(endTag) - 1), endTag, sizeof(endTag) - 1) == 0) {
                message[messageIndex - (sizeof(endTag) - 1)] = '\0'; // Hapus tag <end>
                break;
            }

            messageIndex++;
            bitIndex = 0; 
            currentChar = 0;

            if (messageIndex >= sizeof(message) - 1) {
                break; 
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

int main() {
    char filename[100];
    char filehasil[100];
    int pilihan;

    menu();
    printf("Pilihan : ");
    scanf("%i", &pilihan);
    getchar();

    switch(pilihan) {
        case 1: {
            printf("Masukkan nama file gambar BMP: ");
            scanf("%s", filename);
            getchar();
            if (strstr(filename, ".bmp") == NULL) {
            strcat(filename, ".bmp");
            }
            
            printf("Masukkan nama file txt: ");
            scanf("%s", filetext);
            getchar(); 
            if (strstr(filetext, ".txt") == NULL) {
            strcat(filetext, ".txt");
            }
            bacatext();
            checkmessage(filename);
            printf("Masukkan nama file hasil gambar BMP: ");
            scanf("%s", filehasil);
            if (strstr(filehasil, ".bmp") == NULL) {
            strcat(filehasil, ".bmp");
            }
            if (maxmsg >= totalBits) {
                embedMessage(filename, filehasil);
            }
            break;
        }
        case 2: {
            printf("Masukkan nama file gambar BMP: ");
            scanf("%s", filename);
            if (strstr(filename, ".bmp") == NULL) {
            strcat(filename, ".bmp");
            }
            extractMessage(filename);
            break;
        }
        default:
            printf("Pilihan tidak valid.\n");
    }
    return 0;
}
