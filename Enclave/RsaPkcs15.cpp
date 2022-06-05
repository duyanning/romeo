#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/err.h>
#include <cstdio>
#include <cstring>

#include "base64.h" // usingcpp

// linklib crypto

using namespace std;

int padding = RSA_PKCS1_PADDING; // PKCS #1 v1.5 padding. This currently is the most widely used mode.
//int padding = RSA_PKCS1_OAEP_PADDING; // EME-OAEP as defined in PKCS #1 v2.0 with SHA-1, MGF1 and an empty encoding parameter. This mode is recommended for all new applications.
// 作者文章说:private key encryption supports only these paddings. RSA_PKCS1_PADDING and RSA_NO_PADDING.

RSA* createRSA(unsigned char* key, int ispublic)
{
    RSA* rsa = NULL;
    BIO* keybio;
    keybio = BIO_new_mem_buf(key, -1);
    if (keybio == NULL) {
        //printf("Failed to create key BIO");
        return nullptr;
    }
    if (ispublic) {
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    }
    else {
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    }
    if (rsa == NULL) {
        //printf("Failed to create RSA");
        return nullptr;
    }

    return rsa;
}

//int public_encrypt(unsigned char* data, int data_len, unsigned char* key, unsigned char* encrypted)
//{
//    RSA* rsa = createRSA(key, 1);
//    int result = RSA_public_encrypt(data_len, data, encrypted, rsa, padding);
//    return result;
//}
//int private_decrypt(unsigned char* enc_data, int data_len, unsigned char* key, unsigned char* decrypted)
//{
//    RSA* rsa = createRSA(key, 0);
//    int  result = RSA_private_decrypt(data_len, enc_data, decrypted, rsa, padding);
//    return result;
//}


int private_encrypt(unsigned char* data, int data_len, unsigned char* key, unsigned char* encrypted)
{
    RSA* rsa = createRSA(key, 0);
    int result = RSA_private_encrypt(data_len, data, encrypted, rsa, padding);
    return result;
}
int public_decrypt(unsigned char* enc_data, int data_len, unsigned char* key, unsigned char* decrypted)
{
    RSA* rsa = createRSA(key, 1);
    int  result = RSA_public_decrypt(data_len, enc_data, decrypted, rsa, padding);
    return result;
}

void printLastError(const char* msg)
{
    char* err = (char*)malloc(130);;
    ERR_load_crypto_strings();
    ERR_error_string(ERR_get_error(), err);
    //printf("%s ERROR: %s\n", msg, err);
    free(err);
}

unsigned char publicKey[] = "-----BEGIN PUBLIC KEY-----\n"\
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEA8EmWJUZ/Osz4vXtUU2S+\n"\
"0M4BP9+s423gjMjoX+qP1iCnlcRcFWxthQGN2CWSMZwR/vY9V0un/nsIxhZSWOH9\n"\
"iKzqUtZD4jt35jqOTeJ3PCSr48JirVDNLet7hRT37Ovfu5iieMN7ZNpkjeIG/CfT\n"\
"/QQl7R+kO/EnTmL3QjLKQNV/HhEbHS2/44x7PPoHqSqkOvl8GW0qtL39gTLWgAe8\n"\
"01/w5PmcQ38CKG0oT2gdJmJqIxNmAEHkatYGHcMDtXRBpOhOSdraFj6SmPyHEmLB\n"\
"ishaq7Jm8NPPNK9QcEQ3q+ERa5M6eM72PpF93g2p5cjKgyzzfoIV09Zb/LJ2aW2g\n"\
"QwIDAQAB\n"\
"-----END PUBLIC KEY-----";


unsigned char privateKey[] = "-----BEGIN PRIVATE KEY-----\n"\
"MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQDwSZYlRn86zPi9\n"\
"e1RTZL7QzgE/36zjbeCMyOhf6o/WIKeVxFwVbG2FAY3YJZIxnBH+9j1XS6f+ewjG\n"\
"FlJY4f2IrOpS1kPiO3fmOo5N4nc8JKvjwmKtUM0t63uFFPfs69+7mKJ4w3tk2mSN\n"\
"4gb8J9P9BCXtH6Q78SdOYvdCMspA1X8eERsdLb/jjHs8+gepKqQ6+XwZbSq0vf2B\n"\
"MtaAB7zTX/Dk+ZxDfwIobShPaB0mYmojE2YAQeRq1gYdwwO1dEGk6E5J2toWPpKY\n"\
"/IcSYsGKyFqrsmbw0880r1BwRDer4RFrkzp4zvY+kX3eDanlyMqDLPN+ghXT1lv8\n"\
"snZpbaBDAgMBAAECggEBAIVxmHzjBc11/73bPB2EGaSEg5UhdzZm0wncmZCLB453\n"\
"XBqEjk8nhDsVfdzIIMSEVEowHijYz1c4pMq9osXR26eHwCp47AI73H5zjowadPVl\n"\
"uEAot/xgn1IdMN/boURmSj44qiI/DcwYrTdOi2qGA+jD4PwrUl4nsxiJRZ/x7PjL\n"\
"hMzRbvDxQ4/Q4ThYXwoEGiIBBK/iB3Z5eR7lFa8E5yAaxM2QP9PENBr/OqkGXLWV\n"\
"qA/YTxs3gAvkUjMhlScOi7PMwRX9HsrAeLKbLuC1KJv1p2THUtZbOHqrAF/uwHaj\n"\
"ygUblFaa/BTckTN7PKSVIhp7OihbD04bSRrh+nOilcECgYEA/8atV5DmNxFrxF1P\n"\
"ODDjdJPNb9pzNrDF03TiFBZWS4Q+2JazyLGjZzhg5Vv9RJ7VcIjPAbMy2Cy5BUff\n"\
"EFE+8ryKVWfdpPxpPYOwHCJSw4Bqqdj0Pmp/xw928ebrnUoCzdkUqYYpRWx0T7YV\n"\
"RoA9RiBfQiVHhuJBSDPYJPoP34kCgYEA8H9wLE5L8raUn4NYYRuUVMa+1k4Q1N3X\n"\
"Bixm5cccc/Ja4LVvrnWqmFOmfFgpVd8BcTGaPSsqfA4j/oEQp7tmjZqggVFqiM2m\n"\
"J2YEv18cY/5kiDUVYR7VWSkpqVOkgiX3lK3UkIngnVMGGFnoIBlfBFF9uo02rZpC\n"\
"5o5zebaDImsCgYAE9d5wv0+nq7/STBj4NwKCRUeLrsnjOqRriG3GA/TifAsX+jw8\n"\
"XS2VF+PRLuqHhSkQiKazGr2Wsa9Y6d7qmxjEbmGkbGJBC+AioEYvFX9TaU8oQhvi\n"\
"hgA6ZRNid58EKuZJBbe/3ek4/nR3A0oAVwZZMNGIH972P7cSZmb/uJXMOQKBgQCs\n"\
"FaQAL+4sN/TUxrkAkylqF+QJmEZ26l2nrzHZjMWROYNJcsn8/XkaEhD4vGSnazCu\n"\
"/B0vU6nMppmezF9Mhc112YSrw8QFK5GOc3NGNBoueqMYy1MG8Xcbm1aSMKVv8xba\n"\
"rh+BZQbxy6x61CpCfaT9hAoA6HaNdeoU6y05lBz1DQKBgAbYiIk56QZHeoZKiZxy\n"\
"4eicQS0sVKKRb24ZUd+04cNSTfeIuuXZrYJ48Jbr0fzjIM3EfHvLgh9rAZ+aHe/L\n"\
"84Ig17KiExe+qyYHjut/SC0wODDtzM/jtrpqyYa5JoEpPIaUSgPuTH/WhO3cDsx6\n"\
"3PIW4/CddNs8mCSBOqTnoaxh\n"\
"-----END PRIVATE KEY-----";


void rsa_pkcs15_decrypt(void* enc, void* dec, int* dec_len)
{

    //unsigned char plainText[2048 / 8] = "Hello this is Ravi"; //key length : 2048


    //unsigned char  encrypted[4098] = {};
    //unsigned char decrypted[4098] = {};

    //int encrypted_length;
    //int decrypted_length;

    ////FILE* fp = fopen("encrypted-base64encoded.txt", "r");
    //char encrypted_base64encoded[1000];
    ////fscanf(fp, "%s", encrypted_base64encoded);
    ////fclose(fp);

    //std::vector<BYTE> encrypted_vec = base64_decode(encrypted_base64encoded);



    //decrypted_length = public_decrypt(encrypted,encrypted_length,publicKey, decrypted);
    //decrypted_length = public_decrypt(&encrypted_vec[0], 256, publicKey, decrypted);
    *dec_len = public_decrypt((unsigned char*)enc, 256, publicKey, (unsigned char*)dec);
    // 256来自前面被注释掉的加密代码的输出.大概跟2048/8=256有关. plainText[2048/8]
    // 我要加密的文字很短,应该可以满足要求.
    //if (decrypted_length == -1) {
    //    printLastError("Public Decrypt failed");
    //    //exit(0);
    //}
    //printf("Decrypted Text =%s\n", decrypted);
    //printf("Decrypted Length =%d\n", decrypted_length);

}