#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
    status = SetProductId("PASTE_PRODUCT_ID", LA_USER); // Setting permission flag to LA_USER in case of hosted-floating
                                                        // does not reset the license key upon deactivation.
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
    char licenseKey[256];
    wchar_t wLicenseKey[256];
    char licenseType[256];
    uint32_t length = 256;
    wchar_t wLicenseType[256];
    int status;

    init();
    status = IsLicenseGenuine();
    if (LA_FAIL == status)
    {
#if _WIN32
        status = GetLicenseKey(wLicenseKey, length);
        if (LA_OK == status)
        {
            if (strcmp(wLicenseKey, "") == 0)
            {
                // ask for license key
                status = SetLicenseKey(L"PASTE_LICENCE_KEY");
                if (LA_OK != status)
                {
                    printf("Error code: %d", status);
                    getchar();
                    exit(status);
                }
            }
        }
#else
        status = GetLicenseKey(licenseKey, length);
        if (LA_OK == status)
        {
            if (strcmp(licenseKey, "") == 0)
            {
                // ask for license key
                status = SetLicenseKey("PASTE_LICENCE_KEY");
                if (LA_OK != status)
                {
                    printf("Error code: %d", status);
                    getchar();
                    exit(status);
                }
            }
        }
#endif
        if (LA_OK == status)
        {
            int activationStatus = ActivateLicense();
            if (LA_OK == activationStatus || LA_EXPIRED == activationStatus || LA_SUSPENDED == activationStatus)
            {
                printf("License activated successfully: %d", activationStatus);
                status = LA_OK;
            }
            else
            {
                printf("License activation failed: %d", activationStatus);
            }
        }
    }
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

    status = DeactivateLicense(); // In case of hosted floating license this function should be called
    if (LA_OK != status)          // when the application is closed to avoid zombie licenses.
    {
        printf("Error code: %d", status);
        getchar();
        exit(status);
    }
    getchar();
    return 0;
}