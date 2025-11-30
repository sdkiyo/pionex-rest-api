#include <https_interface.h>
#include <dlfcn.h>
#include <restInit.h>
#include <stdio.h>


int restInit(const char* const pHttpsLibPath)
{
	httpsClientLib = dlopen(pHttpsLibPath, RTLD_LAZY);
	httpCreateMultipleHeaders = dlsym(httpsClientLib, "httpCreateMultipleHeaders");
	httpsClientConnect = dlsym(httpsClientLib, "httpsClientConnect");
	if (httpCreateMultipleHeaders = nullptr)
	{
		printf("null типа прям ваще реально\n");
	}


	return 0;
}
