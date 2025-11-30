#include <signature.h>
#include <https_interface.h>
#include <stdint.h>
#include <dlfcn.h>


int limitOrderResponseCallback(const char *const pServerResponse, const uint16_t pResponseLen, void* pUserData)
{
	printf("userData: %s\n", (char*)pUserData);
	printf("response len: %d\n", pResponseLen);
	printf("server responce start: \n%sserver responce end\n", pServerResponse);
	return 0;
}


int newLimitOrder(const char *const pApiKey, const uint8_t keyLen, const char *const pApiSecret, const uint8_t secretLen, const char *const pSymbol, const char *const pSide, const char *const pSize, const char *const pPrice, const char *const pIOC)
{
	void* httpsClientLib = dlopen("/home/eugene/FILES/Programming/https_client/tests/test1/build/libhttps_client_test.so", RTLD_LAZY);
	httpCreateMultipleHeaders = dlsym(httpsClientLib, "httpCreateMultipleHeaders");
	httpsClientConnect = dlsym(httpsClientLib, "httpsClientConnect");

	char tempHead1[340];

	char signature[EVP_MAX_MD_SIZE+1];
	uint64_t timestamp = 0;

	char body[256];



	snprintf(body, 256, "{\"symbol\":\"%s\",\"side\":\"%s\",\"type\":\"LIMIT\",\"size\":\"%s\",\"price\":\"%s\",\"IOC\":%s}\0", pSymbol, pSide, pSize, pPrice, pIOC);
	printf("body: %s\n", body);

	createSignature(pApiSecret, secretLen, "POST", "/api/v1/trade/order", body, signature, &timestamp);

	printf("signature: %s\n", signature);

	snprintf(tempHead1, 340, "POST /api/v1/trade/order?timestamp=%ld HTTP/1.1\nHost:api.pionex.com\nPIONEX-KEY:%s\nPIONEX-SIGNATURE:%s\nContent-Length:%ld\nContent-Type:application/json\0", timestamp, pApiKey, signature, strlen(body));

	const char *const heads[] = {
		tempHead1
	};

	const char *const jsons[] = {
		body
	};

	HttpMultipleHeadersCreateInfo multipleHeadersCreateInfo = {
		.ppHeads = heads,
		.ppJsons = jsons,
		.headersCount = 1
	};

	HttpMultipleHeaders sentHeaders = {};
	httpCreateMultipleHeaders(&multipleHeadersCreateInfo, &sentHeaders);

	httpsClientConnect("api.pionex.com", &sentHeaders, limitOrderResponseCallback, nullptr, 4096);

	return 0;
}
