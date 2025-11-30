#pragma once
#ifndef REST_PIONEX_INCLUDES_REST_INTERFACE_H_
#define REST_PIONEX_INCLUDES_REST_INTERFACE_H_


#include <stdint.h>


typedef int (*PFN_getBalance)(const char *const pApiKey, const uint8_t keyLen, const char *const pApiSecret, const uint8_t secretLen, double *const pBalance);
typedef int (*PFN_restInit)(const char* const pHttpsLibPath);
typedef int (*PFN_newLimitOrder)(const char *const pApiKey, const uint8_t keyLen, const char *const pApiSecret, const uint8_t secretLen, const char *const pSymbol, const char *const pSide, const char *const pSize, const char *const pPrice, const char *const pIOC);


static PFN_getBalance getBalance;
static PFN_restInit restInit;
static PFN_newLimitOrder newLimitOrder;


#endif // REST_PIONEX_INCLUDES_REST_INTERFACE_H_
