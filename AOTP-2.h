#ifndef AOTP2_H
#define AOTP2_H

#include "lib/ACH-2.h"

/// AOTP Key size
#define AOTP_KEY_SIZE 16
/// AOTP Code length
#define AOTP_CODE_LEN 4
/// AOTP Code string length
#define AOTP_STR_CODE_LEN 8

/// @brief AOTP config struct
typedef struct AOTP2_t {
    /// @brief The Unix timestamp function
    long (*unixTime)(void);
    /// @brief TOTP epoch
    long epoch;
    /// @brief The code buffer
    volatile uint8_t* code;
    /// @brief The TOTP key
    uint8_t key[AOTP_KEY_SIZE];
    /// @brief The lifespan of a code.
    int duration;
} AOTP2;

#ifdef __cplusplus
extern "C" {
#endif

/// @brief Create an AOTP-2 config, using ACH-2 as the hashing algorithm.
/// @param key The private key to be used in the HMAC.
/// @param epoch The Unix timetamp epoch to be used.
/// @param duration The duration of the OTP codes.
/// @param unixTime A function to get the current Unix timestamp.
/// @returns a populated AOTP-2 config struct.
AOTP2* createConfig(uint8_t* key, long epoch, int duration, long (*unixTime)(void));

/// @brief read a code, as a hex string, safely, from an AOTP-2 config into a buffer.
/// @param buf the buffer to store the code. Must be at least 8 characters long.
/// @param conf
void readCode(char* buf, AOTP2* conf);

/// @brief read a raw code, safely, from an AOTP-2 config into a buffer.
/// @param buf the buffer to store the raw code. Must be at least 4 bytes long.
/// @param conf
void readCodeRaw(uint8_t* buf, AOTP2* conf);

/// @brief Destroy an AOTP-2 config
/// @param conf the config to destroy
void destroyConfig(AOTP2* conf);

#ifdef __cplusplus
}
#endif  // !__cplusplus

#endif  // !AOTP2_H