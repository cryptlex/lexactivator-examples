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
	status = SetProductData("RUJERkIzNEZGNTFFMDZCM0M3NzFEOEY4QUVEMUYyQTA=.AWrFSVN2C3YxJucvRQroQCOE2FKk2MzsLBf4XSiCGpxGe6YXS7HDC1yAoVv9Pttl5JfI5odDnaJSXO86WBnG/UHdZ3w3ux5wUvf9N0O/iEARk65wYJafvlNpLGoeOaPY6S45V+jeey9cFmwu1ggU5Prkw5pcCEf9+7zzQ1Rkh9sYQ7TyAQeW17KGA8MYSGv/8KN3hQ1uUDoCeCACmj28ZXRwwkfNuELiXa9kvySPUYvsACoh0A9H7/f5H07SwQrp2hERhQAyQoiYGH5OlEwEW2G+UPuyNGQBamKVIOFV1Uf/AVlK3vih8qZKkUGh0yOV/19Sy3yNHbU3PnDntMtybmeasSQpUiar2cKQAEwoe3anOpA6+axK8gKty094m8Q23swEwL7aE3B6fq9G3b2f7oFDVfGJjBV2SpEtIsOPaPs5JXvwqt8QqDGR9q2gd1TDUmK17nn2oar4zS3NlZaKWNCfwH12MPY7cXlBvKlJOfSnD553sy9abCpagFHb1v8JzvULHe1mHn3Ub8xT9sw7gdF0O+XVwygdrQnTnfzqLqysI51vcp685/15957m68LDFd1X1EqH03ZwLuTRvbYM/Aeh4Muu2xzFNP8HnA87Y93MMw3hfaOB6Ck3lAlbOQ6Q4y+ox/Ev+0bXTeuZnoEB+tWasibdLUSG4YHMGSVxc0xNLZBbiUtTZFfKp5dRh+tJbx5f7yuTLUzDwucIH8YD4hS1qFNTWrYiW5nfezs3ZR4=");
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
	status = SetProductId("96d27e32-4e08-4a80-a332-2b4446613c02", LA_USER);
#endif
	if (LA_OK != status)
	{
		printf("Error code: %d", status);
		getchar();
		exit(status);
	}
}

/*
 * Offline activations

 * Offline activation involves the below-mentioned steps:
 *
 * 1) Generate offline activation request file using GenerateOfflineActivationRequest()function.
 * 2) Go to the Activations page of the license on the admin dashboard and click on the offline activations tab.
 * 3) Paste the content of the request file and click on the activate button. This will create an activation
 * 	  on the server-side. Download the response file.
 * 4) Call the ActivateLicenseOffline() function and pass the downloaded response file path as an argument to this
 *    function. This will create an activation on the client side.
 */

void generateRequest()
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
#if _WIN32
	status = GenerateOfflineActivationRequest(L"./Offline_Activation_request.txt");
#else
	status = GenerateOfflineActivationRequest("./Offline_Activation_request.txt");
#endif
	if (LA_OK != status)
	{
		printf("Error code: %d", status);
		getchar();
		exit(status);
	}
}

void activateOffline()
{
	int status;
#if _WIN32
	status = ActivateLicenseOffline(L"PATH_OF_THE_RESPONSE_FILE");
#else
	status = ActivateLicenseOffline("PATH_OF_THE_RESPONSE_FILE");
#endif
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

	generateRequest(); //

	// activateOffline(); // call this function once you have the response file

	int status = IsLicenseValid();

	if (LA_OK == status)
	{
		printf("License is genuinely activated!\n");
		// Execute your code here.
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
	else if (LA_FAIL == status)
	{
		printf("License is not activated!");
	}
	else
	{
		printf("License validation failed! Error code: %d", status);
	}
	return 0;
}
