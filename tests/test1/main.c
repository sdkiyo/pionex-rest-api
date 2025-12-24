#include <stdio.h>
#include <dlfcn.h>
#include <string.h>

#include "../../../net-client/include/netInterface.h"

#include "../../include/callbackStructs.h"


int main(const int argc, const char *const argv[])
{
	if (argc < 2)
	{
		fprintf(stderr, "\033[33mplease add api keys in arguments\033[0m\n");
		return 0;
	}

	fprintf(stderr, "test1 start\n");


	void* httpsClientLib = dlopen("../../../../net-client/tests/test1/build/libnet-client.so", RTLD_LAZY);

	PFN_httpsClientConnect httpsClientConnect = (PFN_httpsClientConnect)dlsym(httpsClientLib, "httpsClientConnect");

	void* pionexRestLib = dlopen("./libPionexRestApi.so", RTLD_LAZY);

	PFN_httpsUserCallback getBalanceCallback = (PFN_httpsUserCallback)dlsym(pionexRestLib, "getBalanceCallback");


	PionexPrivateKeys privateKeys = {};
	privateKeys.pApiKey		= argv[1];
	privateKeys.pApiSecret		= argv[2];
	privateKeys.apiKeyLen		= (uint16_t)strlen(privateKeys.pApiKey);
	privateKeys.apiSecretLen	= (uint16_t)strlen(privateKeys.pApiSecret);

	GetBalanceRequest getBalanceRequest = {};
	getBalanceRequest.pPrivateKeys	= &privateKeys;
	getBalanceRequest.pCoinName	= "BTC";

	if (httpsClientConnect("api.pionex.com", getBalanceCallback, (uint16_t)340, (uint16_t)2048, (void*)&getBalanceRequest) != 0)
	{
		fprintf(stderr, "httpsClientConnect() failed\n");
		return -1;
	}

	printf("balance (%s): %.15f\n", getBalanceRequest.pCoinName, getBalanceRequest.currentBalance);


	dlclose(httpsClientLib);


	fprintf(stderr, "test1 end\n");
	return 0;
}
