#include <createSignature.h>


int createSignature(const char *const pApiSecret, const uint16_t apiSecretLen, const char *const pMethod, const char *const pPath, const char *const pBody, char *const pResult, uint64_t *const pTimestamp)
{
	struct timespec tp = {};
	clock_gettime(CLOCK_REALTIME, &tp);

	const uint64_t timestamp_in_milliseconds = (uint64_t)((tp.tv_sec * 1'000) + (tp.tv_nsec / 1'000'000) + 74'000);// pionex timestamp different on ~72000 milliseconds (or timestamp on my computer wrong, idk.)
	*pTimestamp = timestamp_in_milliseconds;

	const uint16_t hmacInputDataLen = 256;
	char* hmacInputData = malloc(sizeof(*hmacInputData) * hmacInputDataLen);

	snprintf(hmacInputData, hmacInputDataLen, "%s%s?timestamp=%ld%s\0", pMethod, pPath, timestamp_in_milliseconds, pBody);
	printf("hmac input data: %s\n", hmacInputData);

	unsigned char hmacResult[EVP_MAX_MD_SIZE];
	unsigned int hmacResultLen = 0;

	HMAC(EVP_sha256(), (const unsigned char *const)pApiSecret, apiSecretLen, (unsigned char*)hmacInputData, strlen(hmacInputData), hmacResult, &hmacResultLen);
	free(hmacInputData);

	uint8_t itr = 0;
	for (uint8_t i = 0; i < hmacResultLen; i++)
	{
		sprintf(&pResult[itr], "%02x", hmacResult[i]);
		itr += 2;
	}
	pResult[itr] = '\0';

	return 0;
}
