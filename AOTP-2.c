#include "AOTP-2.h"

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
    return;  // NYI
}

void readCodeRaw(uint8_t* buf, AOTP2* conf) {
    return;  // NYI
}

void destroyConfig(AOTP2* conf) {
    free(conf);
}