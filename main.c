#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

#include "https_interface.h"
#include "colors.h"
#include "tet.h"


int main()
{
	fprintf(stderr, TRANSPARENT_COLOR "test1 start" RESET_COLOR "\n");


	void* httpsClientLib = dlopen("/home/eugene/FILES/Programming/https_client/tests/test1/build/libhttps_client_test.so", RTLD_LAZY);
	httpCreateMultipleHeaders = dlsym(httpsClientLib, "httpCreateMultipleHeaders");
	httpsClientConnect = dlsym(httpsClientLib, "httpsClientConnect");

	//const unsigned char key[] = "\0";
	//const unsigned char secret[] = "\0";
	const unsigned char key[] = "\0";
	const unsigned char secret[] = "\0";

	char tempHead1[340];
	char tempHead2[340];

	char signature[EVP_MAX_MD_SIZE];
	uint64_t timestamp = 0;

	char body[256];
	snprintf(body, 256, "{\"symbol\":\"BTC_USDT\",\"orders\":[{\"side\":\"SELL\",\"type\":\"LIMIT\",\"price\":\"99567.91\",\"size\":\"0.0001\"}]}\0");
	printf("body: %s\n", body);

//	createSignature(secret, strlen(secret), "GET", "/api/v1/account/balances?", "", signature, &timestamp);
	createSignature(secret, strlen(secret), "POST", "/api/v1/trade/massOrder", body, signature, &timestamp);

	fprintf(stderr, MAGENTA "signature: %s\n" RESET_COLOR, signature);

	snprintf(tempHead1, 340, "POST /api/v1/trade/massOrder?timestamp=%ld HTTP/1.1\nHost: api.pionex.com\nPIONEX-KEY: %s\nPIONEX-SIGNATURE: %s\nContent-Type: application/json\0", timestamp, key, signature);
//	snprintf(tempHead1, 340, "GET /api/v1/account/balances?timestamp=%ld HTTP/1.1\nHost: api.pionex.com\nPIONEX-KEY: %s\nPIONEX-SIGNATURE: %s\0", timestamp, key, signature);
	snprintf(tempHead2, 340, "GET /api/v1/common/symbols?symbol=BTC_USDT HTTP/1.1\nHost: api.pionex.com\0");

	char* heads[] = {
		tempHead1,
		tempHead2
	};

	char* jsons[] = {
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

	HttpMultipleHeaders serverResponse = {};
	httpsClientConnect("api.pionex.com", &sentHeaders, &serverResponse, 1984);



	dlclose(httpsClientLib);

	fprintf(stderr, TRANSPARENT_COLOR "test1 end" RESET_COLOR "\n");
	return 0;
}
