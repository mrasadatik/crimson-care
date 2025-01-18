#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <openssl/sha.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <stdbool.h>

#define SALT_LENGTH 16
#define IV_LENGTH 16
#define KEY_LENGTH 32
#define HASH_LENGTH SHA256_DIGEST_LENGTH

typedef struct EncryptionContext {
    unsigned char key[KEY_LENGTH];
    unsigned char iv[IV_LENGTH];
    unsigned char salt[SALT_LENGTH];
} EncryptionContext;

void generateSalt(unsigned char* salt);
void hashPassword(const char* password, const unsigned char* salt, unsigned char* hash);
bool verifyPassword(const char* password, const unsigned char* salt, const unsigned char* hash);
void initializeEncryption(EncryptionContext* context);
bool encryptData(const unsigned char* data, size_t dataLen,
                const EncryptionContext* context, unsigned char** encrypted, size_t* encLen);
bool decryptData(const unsigned char* encrypted, size_t encLen,
                const EncryptionContext* context, unsigned char** decrypted, size_t* decLen);

#endif
