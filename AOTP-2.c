#include "AOTP-2.h"

#define byte uint8_t
#define uint unsigned int

static void otpArray(byte* array, uint n, byte* key) {
    for (uint i = 0; i < n; i++)
        array[i] ^= key[i];
}

AOTP2* createConfig(uint8_t* key, long epoch, int duration, long (*unixTime)(void)) {
    if (unixTime == NULL || key == NULL)
        return NULL;

    AOTP2* config = malloc(sizeof(AOTP2));
    for (int i = 0; i < AOTP_KEY_SIZE; i++)
        config->key[i] = key[i];
    config->epoch = epoch;
    config->duration = duration;
    config->unixTime = unixTime;

    return config;
}

void readCode(char* buf, AOTP2* conf) {
    if (buf == NULL || conf == NULL) {
        buf = "ERRNULL";
        return;
    }
    // turn a code into a string
    byte* code = malloc(AOTP_CODE_LEN);
    readCodeRaw(code, conf);
    sprintf(buf, "%02x%02x%02x%02x", code[0], code[1], code[2], code[3]);
    buf[8] = 0;
}

void readCodeRaw(uint8_t* buf, AOTP2* conf) {
    if (buf == NULL || conf == NULL)
        return;

    // get counter value
    long t = conf->unixTime(),
         ct = (long)floor((double)(t - conf->epoch) / conf->duration);

    // compute mac
    byte* pad0 = malloc(32);
    byte* pad1 = malloc(32);
    for (int i = 0; i < 32; i++) {
        pad0[i] = 0xA;  // 0b1010
        pad1[i] = 0x3;  // 0b0011
    }
    // xor key and pad
    otpArray(pad0, AOTP_KEY_SIZE, conf->key);
    // append ct
    char ctString[16];
    sprintf(ctString, "%ld", ct);
    int ctStringLen = strlen(ctString);
    int padSumLen = 32 + ctStringLen;
    byte padSum0[padSumLen];
    memcpy(padSum0, pad0, 32);
    memcpy((padSum0 + 32), ctString, ctStringLen);

    // hash
    byte* hash0 = computeHash(padSum0, padSumLen);
    // condense into 32 bytes
    byte* sum = malloc(32);
    for (int i = 0; i < 32; i++)
        sum[i] = hash0[i] ^ hash0[i + 32];

    // xor key and pad 2
    otpArray(pad1, AOTP_KEY_SIZE, conf->key);
    byte padSum1[64];
    memcpy(padSum1, pad1, 32);
    memcpy(padSum1 + 32, sum, 32);

    // hash
    byte* hash1 = computeHash(padSum1, 64);
    // condense
    for (int i = 0; i < 32; i++)
        sum[i] = hash1[i] ^ hash1[i + 32];

    // select which 4 bytes to grab from the sum
    byte select = (sum[7] & 0x8) | (sum[15] & 0x4) | (sum[23] & 0x2) | (sum[31] & 0x1);
    for (int i = 0; i < 4; i++)
        buf[i] = sum[((i + 1) * select) % 32];

    // cleanup
    free(pad0);
    free(pad1);
    free(hash0);
    free(hash1);
    free(sum);
}

void destroyConfig(AOTP2* conf) {
    free(conf);
}

#undef byte