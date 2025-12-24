#include <createSignature.h>
#include <callbackStructs.h>
#include <stdlib.h>


#define SKIP_NEXT_SERVER_RESPONSE 4
#define CALLBACK_FIRST_TRY 2
#define CALLBACK_CLOSE_CONNECTION 1

uint8_t getBalanceCallback(const char *const pResponse, const uint16_t responseLen, char* pRequest, uint16_t* pCurrentRequestLen, const uint16_t requestMaxLen, void* pUserData, const uint8_t prevCallbackReturnValue)
{
	printf("\033[32mbalance callback start\n\033[0m");

	if (prevCallbackReturnValue == CALLBACK_FIRST_TRY)// first try
	{
		char signature[EVP_MAX_MD_SIZE+1] = {};
		uint64_t timestamp = 0;

		createSignature(((GetBalanceRequest*)pUserData)->pPrivateKeys->pApiSecret, ((GetBalanceRequest*)pUserData)->pPrivateKeys->apiSecretLen, "GET", "/api/v1/account/balances", "", signature, &timestamp);

		snprintf(pRequest, requestMaxLen, "GET /api/v1/account/balances?timestamp=%ld HTTP/1.1\nHost:api.pionex.com\nPIONEX-KEY:%s\nPIONEX-SIGNATURE:%s\n\n\0", timestamp, ((GetBalanceRequest*)pUserData)->pPrivateKeys->pApiKey, signature);
		*pCurrentRequestLen = (uint16_t)strlen(pRequest);// FIXME можно ли убрать strlen?

		printf("currentRequestLen: %d\n", *pCurrentRequestLen);
		printf("\033[35mbalance callback end\n\033[0m");
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

		/* временные костыли. нет ничего более постоянного чем что-то временное*/
		char* tempStr = strstr(pResponse, ((GetBalanceRequest*)pUserData)->pCoinName);

		tempStr += (10 + strlen(((GetBalanceRequest*)pUserData)->pCoinName));

		for (uint8_t i = 0; i < 20; i++)
		{
			if (tempStr[i] == '"')
			{
				tempStr[i] = '\0';
				break;
			}
		}

		((GetBalanceRequest*)pUserData)->currentBalance = strtod(tempStr, nullptr);
		/* временные костыли. нет ничего более постоянного чем что-то временное*/

		printf("\033[35mbalance callback end\n\033[0m");
		return CALLBACK_CLOSE_CONNECTION;
	}

	return CALLBACK_CLOSE_CONNECTION;
}
