#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include "../../../https-client/include/netInterface.h"

#include "../../include/callbackStructs.h"


int main(const int argc, const char *const argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "\033[33mplease add api keys in arguments\033[0m\n");
		return 0;
	}

	fprintf(stderr, "test1 start\n");


	void* httpsClientLib = dlopen("../../../../https-client/tests/test1/build/libnet-client.so", RTLD_LAZY);

	PFN_httpsClientConnect httpsClientConnect = (PFN_httpsClientConnect)dlsym(httpsClientLib, "httpsClientConnect");

	void* pionexRestLib = dlopen("./libPionexRestApi.so", RTLD_LAZY);

	PFN_httpsUserCallback newLimitOrderCallback = (PFN_httpsUserCallback)dlsym(pionexRestLib, "newLimitOrderCallback");


	PionexPrivateKeys privateKeys = {};
	privateKeys.pApiKey		= argv[1];
	privateKeys.pApiSecret		= argv[2];
	privateKeys.apiKeyLen		= (uint16_t)strlen(privateKeys.pApiKey);
	privateKeys.apiSecretLen	= (uint16_t)strlen(privateKeys.pApiSecret);

	NewLimitOrderRequest newLimitOrderRequest = {};
	newLimitOrderRequest.pPrivateKeys	= &privateKeys;
	newLimitOrderRequest.pSymbol		= "BTC_USDT\0";
	newLimitOrderRequest.pSide		= "SELL\0";
	newLimitOrderRequest.pSize		= "0.0002\0";
	newLimitOrderRequest.pPrice		= "99123.0\0";
	newLimitOrderRequest.pIOC		= "false\0";

	if (httpsClientConnect("api.pionex.com", newLimitOrderCallback, (uint16_t)1024, (uint16_t)2048, (void*)&newLimitOrderRequest) != 0)
	{
		fprintf(stderr, "httpsClientConnect() failed\n");
		return -1;
	}



	dlclose(httpsClientLib);


	fprintf(stderr, "test1 end\n");
	return 0;
}
