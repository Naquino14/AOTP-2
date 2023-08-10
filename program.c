#include <pthread.h>>
#include <stdio.h>

#include "AOTP-2.h"

long getTime(void) {
    return time(NULL);
}

int main() {
    uint8_t key[AOTP_KEY_SIZE];
    for (int i = 0; i < AOTP_KEY_SIZE; i++)
        key[i] = i;
    AOTP2* conf = createConfig(key, 1456732, 5, getTime);
    conf->code = malloc(AOTP_CODE_LEN);
    for (;;) {
        readCodeRaw(conf->code, conf);
        printf("%02x%02x%02x%02x\n", conf->code[0], conf->code[1], conf->code[2], conf->code[3]);
        sleep(1);
    }
    free(conf->code);
    destroyConfig(conf);
    return 0;
}