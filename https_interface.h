#pragma once
#ifndef _HTTPS_C_LINUX_CLIENT_TEST_
#define _HTTPS_C_LINUX_CLIENT_TEST_


#include <stdint.h>


typedef struct HttpMultipleHeadersCreateInfo {
	const char *const *	ppHeads;
	const char *const *	ppJsons;
	uint8_t			headersCount;
} HttpMultipleHeadersCreateInfo;

typedef struct HttpMultipleHeaders {
	char**		ppHeaders;
	uint16_t*	pHeadersLen;
	uint8_t		headersCount;
} HttpMultipleHeaders;


typedef int (*PFN_httpsClientConnect)(
	const char *const			pHostname,
	const HttpMultipleHeaders *const	pSentHeaders,
	int (responseCallback)(const char *const, const uint16_t, void*), /* <- function pointer */
	void*					pUserData,
	const uint16_t				serverResponseMaxLen);


typedef void (*PFN_httpCreateMultipleHeaders)(
	const HttpMultipleHeadersCreateInfo *const	pMultipleHeadersCreateInfo,
	HttpMultipleHeaders*				pMultipleHeaders);


static PFN_httpsClientConnect			httpsClientConnect;
static PFN_httpCreateMultipleHeaders		httpCreateMultipleHeaders;


#endif
