#pragma once
#ifndef _HTTPS_C_LINUX_CLIENT_TEST_
#define _HTTPS_C_LINUX_CLIENT_TEST_


#include <stdint.h>


typedef struct HttpHeaderCreateInfo {
	char*		pMethod;
	char*		pPath;
	char*		pVersion;
	char*		pHead;
	char*		pBody;
} HttpHeaderCreateInfo;


typedef struct HttpMultipleHeadersCreateInfo {
	char**		ppHeads;
	char**		ppJsons;
	uint8_t		headersCount;
} HttpMultipleHeadersCreateInfo;


typedef struct HttpMultipleHeaders {
	char**		ppHeaders;
	uint16_t*	pHeadersLen;
	uint8_t		headersCount;
} HttpMultipleHeaders;


typedef int (*PFN_httpsClientConnect)(const char *const pHostname, const HttpMultipleHeaders *const pSentHeaders, HttpMultipleHeaders *const pServerResponses, const uint16_t serverResponseMaxLength);
typedef void (*PFN_httpCreateMultipleHeaders)(const HttpMultipleHeadersCreateInfo *const pMultipleHeadersCreateInfo, HttpMultipleHeaders* pMultipleHeaders);


static PFN_httpsClientConnect httpsClientConnect;
static PFN_httpCreateMultipleHeaders httpCreateMultipleHeaders;



#endif
