#pragma once
#ifndef _TET_H_123_
#define _TET_H_123_


#include <sys/time.h>
#include <string.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>


int createSignature(const unsigned char *const pApiSecret, const uint8_t apiSecretLen, const char *const pMethod, const char *const pPath, const char *const pBody, unsigned char *const pResult, uint64_t *const pTimestamp);



#endif
