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
    /*
     * Product data needs to be hard-coded and this value is not sensitive or secret.
     */

    int status;

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

void activateTrial()
{
    int status = ActivateTrial();
    if (LA_OK == status)
    {
        printf("Product trial activated successfully!");
    }
    else if (LA_TRIAL_EXPIRED == status)
    {
        printf("Product trial has expired!");
    }
    else
    {
        printf("Product trial activation failed: %d", status);
    }
}

int main()
{
    init();

    activateTrial();

    int trialStatus;
    trialStatus = IsTrialGenuine();
    if (LA_OK == trialStatus)
    {
        unsigned int trialExpiryDate = 0;
        GetTrialExpiryDate(&trialExpiryDate);
        int daysLeft = (trialExpiryDate - time(NULL)) / 86400;
        printf("Trial days left: %d", daysLeft);
    }
    else if (LA_TRIAL_EXPIRED == trialStatus)
    {
        printf("Trial has expired!");

        // Time to buy the license and activate the app
    }

    getchar();
    return 0;
}