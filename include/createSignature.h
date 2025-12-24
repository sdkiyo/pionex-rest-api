#pragma once
#ifndef PIONEX_REST_API_INCLUDE_CREATE_SIGNATURE_H_
#define PIONEX_REST_API_INCLUDE_CREATE_SIGNATURE_H_


#include <stdint.h>
#define __USE_POSIX199309 // for clock_gettime() and CLOCK_REALTIME, FIXME [2025.12.22 23:10:00 PM]
#include <sys/time.h>
#include <time.h>

#include <string.h>
#include <openssl/sha.h>
#include <openssl/hmac.h>


int createSignature(const char *const pApiSecret, const uint16_t apiSecretLen, const char *const pMethod, const char *const pPath, const char *const pBody, char *const pResult, uint64_t *const pTimestamp);


#endif // PIONEX_REST_API_INCLUDE_CREATE_SIGNATURE_H_
