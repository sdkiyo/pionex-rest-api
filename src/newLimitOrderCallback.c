#include <createSignature.h>
#include <callbackStructs.h>


#define SKIP_NEXT_SERVER_RESPONSE 4
#define CALLBACK_FIRST_TRY 2
#define CALLBACK_CLOSE_CONNECTION 1

uint8_t newLimitOrderCallback(const char *const pResponse, const uint16_t responseLen, char* pRequest, uint16_t* pCurrentRequestLen, const uint16_t requestMaxLen, void* pUserData, const uint8_t prevCallbackReturnValue)
{
	printf("\033[32mnewLimitOrder callback start\n\033[0m");

	if (prevCallbackReturnValue == CALLBACK_FIRST_TRY)// first try
	{
		char signature[EVP_MAX_MD_SIZE+1] = {};
		uint64_t timestamp = 0;

		char body[256];

		snprintf(body, 256, "{\"symbol\":\"%s\",\"side\":\"%s\",\"type\":\"LIMIT\",\"size\":\"%s\",\"price\":\"%s\",\"IOC\":%s}\0", ((NewLimitOrderRequest*)pUserData)->pSymbol, ((NewLimitOrderRequest*)pUserData)->pSide, ((NewLimitOrderRequest*)pUserData)->pSize, ((NewLimitOrderRequest*)pUserData)->pPrice, ((NewLimitOrderRequest*)pUserData)->pIOC);

		createSignature(((NewLimitOrderRequest*)pUserData)->pPrivateKeys->pApiSecret, ((NewLimitOrderRequest*)pUserData)->pPrivateKeys->apiSecretLen, "POST", "/api/v1/trade/order", body, signature, &timestamp);

		snprintf(pRequest, requestMaxLen, "POST /api/v1/trade/order?timestamp=%ld HTTP/1.1\nHost:api.pionex.com\nPIONEX-KEY:%s\nPIONEX-SIGNATURE:%s\nContent-Length:%ld\nContent-Type:application/json\n\n%s\0", timestamp, ((NewLimitOrderRequest*)pUserData)->pPrivateKeys->pApiKey, signature, strlen(body), body);

		*pCurrentRequestLen = (uint16_t)strlen(pRequest);// FIXME можно ли убрать strlen?

		printf("currentRequestLen: %d\n", *pCurrentRequestLen);
		printf("\033[35mnewLimitOrder callback end\n\033[0m");
		printf("request:\n%s\n", pRequest);
		return 0;
	}
	else if (prevCallbackReturnValue != CALLBACK_FIRST_TRY && responseLen == 0)// NOT first try + no response
	{
		printf("\033[33mUSER CALLBACK END (no response)\n\033[0m");
		return CALLBACK_CLOSE_CONNECTION;// close connection with server
	}
	else if (prevCallbackReturnValue != CALLBACK_FIRST_TRY && responseLen > 0)// get response
	{
		printf("server responce start (len: %d): ", responseLen);
		for (uint16_t i = 0; i < responseLen; i++)
		{
			printf("%c", pResponse[i]);
		}
		printf("\nserver responce end\n");

		printf("\033[35mnewLimitOrder callback end\n\033[0m");
		return CALLBACK_CLOSE_CONNECTION;
	}

	return CALLBACK_CLOSE_CONNECTION;
}
