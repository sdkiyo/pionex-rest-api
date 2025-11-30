#pragma once
#ifndef REST_PIONEX_INCLUDES_ORDERS_H_
#define REST_PIONEX_INCLUDES_ORDERS_H_


int newLimitOrder(
	const char *const	pApiKey,
	const uint8_t		keyLen,
	const char *const	pApiSecret,
	const uint8_t		secretLen,
	const char *const	pSymbol,
	const uint8_t		symbolLen,
	const char *const	pSide,
	const uint8_t		sideLen,
	const char *const	pSize,
	const uint8_t		sizeLen,
	const char *const	pPrice,
	const uint8_t		priceLen,
	const bool		IOC);


#endif // REST_PIONEX_INCLUDES_ORDERS_H_
