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

        /*          #### Using License metadata for feature management ####         */

        // Changes made to the metadata value will get reflected after the server sync.

        char value[256];
#if _WIN32
        status = GetLicenseMetadata(L"FeatureA", value, 265);
#else
        status = GetLicenseMetadata("FeatureA", value, 256);
#endif
        if (LA_OK == status)
        {
            if (strcmp(value, "allowed") == 0)
            {
                // user can use this feature
            }
            else
            {
                printf("FeatureA not allowed");
            }
        }
        else
        {
            printf("Error code: %d", status);
            getchar();
            exit(status);
        }

        /*       #### Using cryptlex's feature management ####      */

        // Changes made to the product version or feature flag will get reflected after the server sync.

        unsigned int enabled; // it can either be true or false depicting if the feature is enabled or disabled
        wchar_t featureDataA[256];
        char featureData[256]; // data passed with the feature.

#if _WIN32
        status = GetProductVersionFeatureFlag(L"feature-1", &enabled, featureDataA, 256);
#else
        status = GetProductVersionFeatureFlag("feature-1", &enabled, featureData, 256);
#endif

        if (LA_OK == status)
        {
#if _WIN32
            printf("enabled:  %d\n", enabled);
            printf("Data: %c\n", featureDataA);
#else
            printf("enabled:  %d\n", enabled);
            printf("Data: %s\n", featureData);
#endif
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