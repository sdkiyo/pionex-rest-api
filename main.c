#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

#include "https_interface.h"
#include "colors.h"
#include "tet.h"


int responseCallback(const char *const pServerResponse, const uint16_t pResponseLen, void* pUserData)
{
	printf("userData: %s\n", (char*)pUserData);
	printf("response len: %d\n", pResponseLen);
	printf(BLUE "server responce start: \n" RESET_COLOR "%s" BLUE "server responce end\n" RESET_COLOR, pServerResponse);
	return 0;
}


int main(const int argumentCount, const char *const *const argumentValue)
{
	fprintf(stderr, TRANSPARENT_COLOR "test1 start" RESET_COLOR "\n");

	if (argumentCount < 3)
	{
		printf("please set the 'api key' and 'api secret' in arguments\n");
		return 0;
	}


	void* httpsClientLib = dlopen("/home/eugene/FILES/Programming/https_client/tests/test1/build/libhttps_client_test.so", RTLD_LAZY);
	httpCreateMultipleHeaders = dlsym(httpsClientLib, "httpCreateMultipleHeaders");
	httpsClientConnect = dlsym(httpsClientLib, "httpsClientConnect");

	const unsigned char *const key = argumentValue[1];
	const unsigned char *const secret = argumentValue[2];

	char tempHead1[340];
	char tempHead2[340];

	char signature[EVP_MAX_MD_SIZE+1];
	uint64_t timestamp = 0;

	char body[256];
	//snprintf(body, 256, "{\"symbol\": \"BTC_USDT\", \"side\": \"SELL\", \"type\": \"LIMIT\", \"clientOrderId\": null, \"size\": \"0.0001\", \"price\": \"99168.73\", \"amount\": null, \"IOC\": true}\0");
	snprintf(body, 256, "{\"symbol\":\"BTC_USDT\",\"side\":\"SELL\",\"type\":\"LIMIT\",\"size\":\"0.0007\",\"price\":\"99168.73\",\"IOC\":false}\0");
	printf("body: %s\n", body);

//	createSignature(secret, strlen(secret), "GET", "/api/v1/account/balances", "", signature, &timestamp);
	createSignature(secret, strlen(secret), "POST", "/api/v1/trade/order", body, signature, &timestamp);

	printf(MAGENTA "signature: %s\n" RESET_COLOR, signature);

	snprintf(tempHead1, 340, "POST /api/v1/trade/order?timestamp=%ld HTTP/1.1\nHost:api.pionex.com\nPIONEX-KEY:%s\nPIONEX-SIGNATURE:%s\nContent-Length:97\nContent-Type:application/json\0", timestamp, key, signature);
//	snprintf(tempHead1, 340, "GET /api/v1/account/balances?timestamp=%ld HTTP/1.1\nHost:api.pionex.com\nPIONEX-KEY:%s\nPIONEX-SIGNATURE:%s\0", timestamp, key, signature);
	snprintf(tempHead2, 340, "GET /api/v1/common/symbols?symbol=BTC_USDT HTTP/1.1\nHost:api.pionex.com\0");

	const char *const heads[] = {
		tempHead1,
		tempHead2
	};

	const char *const jsons[] = {
		body,
		""
	};

	HttpMultipleHeadersCreateInfo multipleHeadersCreateInfo = {
		.ppHeads = heads,
		.ppJsons = jsons,
		.headersCount = 2
	};

	HttpMultipleHeaders sentHeaders = {};
	httpCreateMultipleHeaders(&multipleHeadersCreateInfo, &sentHeaders);

	httpsClientConnect("api.pionex.com", &sentHeaders, responseCallback, nullptr, 4096);



	dlclose(httpsClientLib);

	fprintf(stderr, TRANSPARENT_COLOR "test1 end" RESET_COLOR "\n");
	return 0;
}
