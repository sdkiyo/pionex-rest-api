#include <stdio.h>
#include <dlfcn.h>
#include <string.h>
#include <stdlib.h>

#include "../../includes/rest_interface.h"


int main(const int argumentCount, const char *const *const argumentValue)
{
	fprintf(stderr, "test1 start\n");

	if (argumentCount < 3)
	{
		printf("please set the 'api key' and 'api secret' in arguments\n");
		return 0;
	}


	void* restLib = dlopen("./libPionexRest.so", RTLD_LAZY);
	getBalance = dlsym(restLib, "getBalance");
	newLimitOrder = dlsym(restLib, "newLimitOrder");
	restInit = dlsym(restLib, "restInit");
	restInit("/home/eugene/FILES/Programming/https_client/tests/test1/build/libhttps_client_test.so");

	const unsigned char *const key = argumentValue[1];
	const unsigned char *const secret = argumentValue[2];

	double balance = 0.0;
	getBalance(key, strlen(key), secret, strlen(secret), &balance);

	newLimitOrder(key, strlen(key), secret, strlen(secret), "BTC_USDT", "SELL", "0.0002", "99168.0", "false");
	printf("balance: %f\n", balance);


	dlclose(restLib);


	fprintf(stderr, "test1 end\n");
	return 0;
}
