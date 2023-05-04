#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_key(char *key, int length) {
    int i;
    for (i = 0; i < length; i++) {
        key[i] = rand() % 256;
    }
}

void encrypt(char *plaintext, char *key, char *ciphertext, int length) {
    int i;
    for (i = 0; i < length; i++) {
        ciphertext[i] = plaintext[i] ^ key[i];
    }
}

void decrypt(char *ciphertext, char *key, char *plaintext, int length) {
    int i;
    for (i = 0; i < length; i++) {
        plaintext[i] = ciphertext[i] ^ key[i];
    }
}

int main(int argc, char **argv) {
    FILE *fp1, *fp2, *fp3, *fp4;
    int plaintext_length, key_length, i;
    char *plaintext, *key, *ciphertext, *decrypted_text;
    time_t t;

    /* Initialize random number generator */
    srand((unsigned) time(&t));

    /* Open input files */
    fp1 = fopen("message.txt", "r");
    fp2 = fopen("key.txt", "r");

    /* Open output files */
    fp3 = fopen("encrypted.txt", "w");
    fp4 = fopen("decrypted.txt", "w");

    /* Determine length of plaintext and key */
    fseek(fp1, 0L, SEEK_END);
    plaintext_length = ftell(fp1);
    fseek(fp1, 0L, SEEK_SET);

    fseek(fp2, 0L, SEEK_END);
    key_length = ftell(fp2);
    fseek(fp2, 0L, SEEK_SET);

    /* Allocate memory for plaintext, key, ciphertext, and decrypted text */
    plaintext = (char*) malloc(plaintext_length + 1);
    key = (char*) malloc(key_length + 1);
    ciphertext = (char*) malloc(plaintext_length + 1);
    decrypted_text = (char*) malloc(plaintext_length + 1);

    /* Read plaintext and key from files */
    fread(plaintext, sizeof(char), plaintext_length, fp1);
    fread(key, sizeof(char), key_length, fp2);

    /* Generate random key if key length is smaller than plaintext length */
    if (key_length < plaintext_length) {
        generate_key(key + key_length, plaintext_length - key_length);
    }

    /* Encrypt plaintext with key */
    encrypt(plaintext, key, ciphertext, plaintext_length);

    /* Write ciphertext to output file */
    fwrite(ciphertext, sizeof(char), plaintext_length, fp3);

    /* Decrypt ciphertext with key */
    decrypt(ciphertext, key, decrypted_text, plaintext_length);

    /* Write decrypted text to output file */
    fwrite(decrypted_text, sizeof(char), plaintext_length, fp4);

    /* Close files and free memory */
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    free(plaintext);
    free(key);
    free(ciphertext);
    free(decrypted_text);

    return 0;
}

