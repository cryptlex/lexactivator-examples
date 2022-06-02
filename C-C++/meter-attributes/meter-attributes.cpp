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

int main()
{
	init();

	int status = IsLicenseGenuine();
	if (LA_OK == status)
	{
		printf("License is genuinely activated!");
		getchar();

		// You can now execute your code as the user is genuine/licensed.

		// Changes made to the meter attribute will get reflected after the server sync.

		// Checking the values of Allowed uses, Total uses, and Gross uses.

		int status;
		uint32_t allowedUses;
		uint32_t totalUses;
		uint32_t grossUses;
#if _WIN32
		status = GetLicenseMeterAttribute(L"MeterAttributeName", &allowedUses, &totalUses, &grossUses);
#else
		status = GetLicenseMeterAttribute("MeterAttributeName", &allowedUses, &totalUses, &grossUses);
#endif
		if (LA_OK == status)
		{
			printf("Allowed Uses: %d\n", allowedUses);
			printf("Total Uses: %d\n", totalUses);
			printf("Gross Uses: %d\n", grossUses);
		}
		else
		{
			printf("Error code: %d", status);
			getchar();
			exit(status);
		}

		uint32_t increment; // value by which you want to increment the meter attribute

		// call the IncrementActivationMeterAttributeUses() function everytime the feature that you want to measure
		// was used successfuly.

#if _WIN32
		status = IncrementActivationMeterAttributeUses(L"MeterAttributeName", increment);
#else
		status = IncrementActivationMeterAttributeUses("MeterAttributeName", increment);
#endif
		if (LA_OK == status)
		{
			printf("Incremented the MeterAttribute by: %d\n", increment);
		}
		else
		{
			printf("Error code: %d", status);
			getchar();
			exit(status);
		}

		uint32_t decrement; // value by which you want to decrement the meter attribute

		// call the DecrementActivationMeterAttributeUses() function if you want to decrease the usage value

#if _WIN32
		status = DecrementActivationMeterAttributeUses(L"MeterAttributeName", decrement);
#else
		status = DecrementActivationMeterAttributeUses("MeterAttributeName", decrement);
#endif
		if (LA_OK == status)
		{
			printf("Decremented the MeterAttribute by: %d\n", decrement);
		}
		else
		{
			printf("Error code: %d", status);
			getchar();
			exit(status);
		}

		//  ResetActivationMeterAttributeUses() helps you reset the meter attribute usage

#if _WIN32
		status = ResetActivationMeterAttributeUses(L"MeterAttributeName");
#else
		status = ResetActivationMeterAttributeUses("MeterAttributeName");
#endif
		if (LA_OK == status)
		{
			printf("MeterAttribute resetted successfully\n");
		}
		else
		{
			printf("Error code: %d", status);
			getchar();
			exit(status);
		}
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