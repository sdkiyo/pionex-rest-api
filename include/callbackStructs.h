#pragma once
#ifndef PIONEX_REST_API_INCLUDE_CALLBACK_STRUCTS_H_
#define PIONEX_REST_API_INCLUDE_CALLBACK_STRUCTS_H_


typedef struct PionexPrivateKeys {
	const char*		pApiKey;
	const char*		pApiSecret;
	uint16_t	apiKeyLen;
	uint16_t	apiSecretLen;
} PionexPrivateKeys;

typedef struct GetBalanceRequest {
	PionexPrivateKeys*	pPrivateKeys;
	char*			pCoinName;
	double			currentBalance;
} GetBalanceRequest;

typedef struct NewLimitOrderRequest {
	PionexPrivateKeys*	pPrivateKeys;
	char*			pSymbol;
	char*			pSide;
	char*			pSize;
	char*			pPrice;
	char*			pIOC;
} NewLimitOrderRequest;


#endif // PIONEX_REST_API_INCLUDE_CALLBACK_STRUCTS_H_
