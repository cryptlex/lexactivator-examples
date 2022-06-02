#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../header/LexActivator.h"

using namespace std;

// Uncomment following for Windows static build
/*
#if _WIN32
#define LEXACTIVATOR_STATIC
#pragma comment(lib, "winhttp")
#if _WIN64
#pragma comment(lib, "x64/libcurl_MD")
#pragma comment(lib, "x64/LexActivator")
#else
#pragma comment(lib, "x86/libcurl_MD")
#pragma comment(lib, "x86/LexActivator")
#endif
#endif
*/

#if _WIN32
#if _WIN64
#pragma comment(lib, "x64/LexActivator")
#else
#pragma comment(lib, "x86/LexActivator")
#endif
#endif

void init()
{
	int status;

	/*
	 * Product data needs to be hard-coded and this value is not sensitive or secret.
	 */

#if _WIN32
	status = SetProductData(L"PASTE_CONTENT_OF_PRODUCT.DAT_FILE");
#else
	status = SetProductData("PASTE_CONTENT_OF_PRODUCT.DAT_FILE");
#endif
	if (LA_OK != status)
	{
		printf("Error code: %d", status);
		getchar();
		exit(status);
	}

	/*
	 * Product Id is simply a unique identifier of your product and needs to be hard-coded.
	 * Similarly this Id is not sensitive as well.
	 */

#if _WIN32
	status = SetProductId(L"PASTE_PRODUCT_ID", LA_USER);
#else
	status = SetProductId("PASTE_PRODUCT_ID", LA_USER);
#endif
	if (LA_OK != status)
	{
		printf("Error code: %d", status);
		getchar();
		exit(status);
	}
}

/*
 * Ideally on a button click inside a dialog
 */

void activate()
{
	int status;
#if _WIN32
	status = SetLicenseKey(L"PASTE_LICENCE_KEY");
#else
	status = SetLicenseKey("PASTE_LICENCE_KEY");
#endif
	if (LA_OK != status)
	{
		printf("Error code: %d", status);
		getchar();
		exit(status);
	}

	status = ActivateLicense();
	if (LA_OK == status || LA_EXPIRED == status || LA_SUSPENDED == status)
	{
		printf("License activated successfully: %d", status);
	}
	else
	{
		printf("License activation failed: %d", status);
	}
}

int main()
{
	init();

	activate(); // in case of node-locekd this function only needs to be called once.

	int status = IsLicenseGenuine();
	if (LA_OK == status)
	{
		// You can now run your code as the user is genuine/licensed.

		unsigned int expiryDate = 0;
		GetLicenseExpiryDate(&expiryDate);
		int daysLeft = (expiryDate - time(NULL)) / 86400;
		printf("Days left: %d\n", daysLeft);
		printf("License is genuinely activated!");
	}
	else if (LA_EXPIRED == status)
	{
		printf("License is genuinely activated but has expired!");
	}
	else if (LA_SUSPENDED == status)
	{
		printf("License is genuinely activated but has been suspended!");
	}
	else if (LA_GRACE_PERIOD_OVER == status)
	{
		printf("License is genuinely activated but grace period is over!");
	}
	else
	{
		printf("Something went wrong! Error code: %d", status);
	}
	getchar();
	return 0;
}