#include <signature.h>
#include <https_interface.h>


int responseCallback(const char *const pServerResponse, const uint16_t pResponseLen, void* pUserData)
{
	*(double*)pUserData = 4.0;
	printf("response len: %d\n", pResponseLen);
	printf("server responce start: \n%sserver responce end\n", pServerResponse);

	return 0;
}

int getBalance(const char *const pApiKey, const uint8_t keyLen, const char *const pApiSecret, const uint8_t secretLen, double *const pBalance)
{
	printf("%s() start\n", __func__);

	char tempHead1[340];

	char signature[EVP_MAX_MD_SIZE+1];
	uint64_t timestamp = 0;

	createSignature(pApiSecret, secretLen, "GET", "/api/v1/account/balances", "", signature, &timestamp);

	printf("signature: %s\n", signature);

	snprintf(tempHead1, 340, "GET /api/v1/account/balances?timestamp=%ld HTTP/1.1\nHost:api.pionex.com\nPIONEX-KEY:%s\nPIONEX-SIGNATURE:%s\0", timestamp, pApiKey, signature);

	const char *const heads[] = {
		tempHead1
	};

	const char *const jsons[] = {
		""
	};

	HttpMultipleHeadersCreateInfo multipleHeadersCreateInfo = {
		.ppHeads = heads,
		.ppJsons = jsons,
		.headersCount = 1
	};

	HttpMultipleHeaders sentHeaders = {};
	if (httpCreateMultipleHeaders = nullptr)
	{
		printf("null типа прям ваще реально\n");
	}
#include <dlfcn.h>
	void* httpsClientLib = dlopen("/home/eugene/FILES/Programming/https_client/tests/test1/build/libhttps_client_test.so", RTLD_LAZY);
	httpCreateMultipleHeaders = dlsym(httpsClientLib, "httpCreateMultipleHeaders");
	httpsClientConnect = dlsym(httpsClientLib, "httpsClientConnect");
	httpCreateMultipleHeaders(&multipleHeadersCreateInfo, &sentHeaders);

	httpsClientConnect("api.pionex.com", &sentHeaders, responseCallback, (void*)pBalance, 4096);


	printf("%s() end\n", __func__);
	return 0;
}
