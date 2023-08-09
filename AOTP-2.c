#include "AOTP-2.h"

AOTP2* createConfig(uint8_t* key, long epoch, int duration, long (*unixTime)(void)) {
    return NULL;  // NYI
}

void readCode(char* buf, AOTP2* conf) {
    return;  // NYI
}

void readCodeRaw(uint8_t* buf, AOTP2* conf) {
    return;  // NYI
}

void destroyConfig(AOTP2* conf) {
    return;  // NYI
}