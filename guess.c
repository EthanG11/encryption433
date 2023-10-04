#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/rand.h>
#define KEYSIZE 16

int stream_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext)
{
    /* Declare cipher context */
    EVP_CIPHER_CTX *ctx;

    int len, ciphertext_len;

    /* Create and initialize the context */
    ctx = EVP_CIPHER_CTX_new();

    /* Initialize the encryption operation. */
    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv) == 0)
    {
        perror("encrypt init error");
        exit(-1);
    }

    /* Provide the message to be encrypted, and obtain the encrypted output. EVP_EncryptUpdate can be called multiple times if necessary */
    if (EVP_EncryptUpdate(ctx, ciphertext, &ciphertext_len, plaintext, plaintext_len) == 0)
    {
        perror("encrypt UPDATE error");
        exit(-1);
    }

    /* Finalize the encryption. Further ciphertext bytes may be written at this stage. */
    if (EVP_EncryptFinal_ex(ctx, ciphertext, &ciphertext_len) == 0)
    {
        perror("encrypt FINAL error");
        exit(-1);
    }

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

void main()
{

    unsigned int start = 1524020929 - (60 * 60 * 2);
    unsigned int end = 1524020929;
    unsigned char key[KEYSIZE];

    FILE *fp;
    fp = fopen("keys.txt", "w");
    int i;

    // printf("%lld\n", (long long)time(NULL));
    for (; start <= end; start++)
    {
        srand(start);
        for (i = 0; i < KEYSIZE; i++)
        {
            key[i] = rand() % 256;

            fprintf(fp, "%.2X", key[i]);
        }
        putc('\n', fp);
    }
    fclose(fp);
}
