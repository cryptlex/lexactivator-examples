#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "header/LexActivator.h"

using namespace std;

// Uncomment following for Windows static build
/*
// 
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

#if _WIN32
    // status = SetProductFile(L"ABSOLUTE_PATH_OF_PRODUCT.DAT_FILE");
    status = SetProductData(L"PASTE_CONTENT_OF_PRODUCT.DAT_FILE");
#else
    //  status = SetProductFile("ABSOLUTE_PATH_OF_PRODUCT.DAT_FILE");
    status = SetProductData("RUJERkIzNEZGNTFFMDZCM0M3NzFEOEY4QUVEMUYyQTA=.AWrFSVN2C3YxJucvRQroQCOE2FKk2MzsLBf4XSiCGpxGe6YXS7HDC1yAoVv9Pttl5JfI5odDnaJSXO86WBnG/UHdZ3w3ux5wUvf9N0O/iEARk65wYJafvlNpLGoeOaPY6S45V+jeey9cFmwu1ggU5Prkw5pcCEf9+7zzQ1Rkh9sYQ7TyAQeW17KGA8MYSGv/8KN3hQ1uUDoCeCACmj28ZXRwwkfNuELiXa9kvySPUYvsACoh0A9H7/f5H07SwQrp2hERhQAyQoiYGH5OlEwEW2G+UPuyNGQBamKVIOFV1Uf/AVlK3vih8qZKkUGh0yOV/19Sy3yNHbU3PnDntMtybmeasSQpUiar2cKQAEwoe3anOpA6+axK8gKty094m8Q23swEwL7aE3B6fq9G3b2f7oFDVfGJjBV2SpEtIsOPaPs5JXvwqt8QqDGR9q2gd1TDUmK17nn2oar4zS3NlZaKWNCfwH12MPY7cXlBvKlJOfSnD553sy9abCpagFHb1v8JzvULHe1mHn3Ub8xT9sw7gdF0O+XVwygdrQnTnfzqLqysI51vcp685/15957m68LDFd1X1EqH03ZwLuTRvbYM/Aeh4Muu2xzFNP8HnA87Y93MMw3hfaOB6Ck3lAlbOQ6Q4y+ox/Ev+0bXTeuZnoEB+tWasibdLUSG4YHMGSVxc0xNLZBbiUtTZFfKp5dRh+tJbx5f7yuTLUzDwucIH8YD4hS1qFNTWrYiW5nfezs3ZR4=");
#endif
    if (LA_OK != status)
    {
        printf("Error code: %d", status);
        getchar();
        exit(status);
    }

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

int main(int argc, char *argv[])
{
    init();

    if (argc == 6)
    {

        if (string(argv[4]) == "--license-key")
        {

            string key = argv[5];
            int status = SetLicenseKey(key.c_str());
            if (status != LA_OK)
            {
                printf("Invalid license key: %d", status);
                return 0;
            }

            if (string(argv[1]) == "--generate-offline-activation-request")
            {
                string requestFilePath = argv[3];
                int status = GenerateOfflineActivationRequest(requestFilePath.c_str());
                if (status != LA_OK)
                {
                    printf("Unable to Generate offline activation request: %d", status);
                    return 0;
                }
                else
                {
                    printf("Offline Activation request generated successfully.");
                    return 0;
                }
            }
            else
            {
                printf("Invalid command .Please check --help");
                return 0;
            }
        }
        else
        {
            printf("Invalid command .Please check --help");
            return 0;
        }
    }

    if (argc == 4)
    {
        if ((string(argv[1]) == "--activate-offline") && (string(argv[2]) == "--response-file-path"))
        {
            string responseFilePath = argv[3];
            int status = ActivateLicenseOffline(responseFilePath.c_str());
            if (status == LA_OK || status == LA_EXPIRED)
            {
                printf("License Activated successfully %d\n", status);
            }
            else
            {
                printf("Activate license offline failed. Status: %d", status);
                return 0;
            }
        }
        else
        {
            printf("Invalid command. Please check --help");
            return 0;
        }
    }

    if (argc == 2)
    {
        if (string(argv[1]) == "--help")
        {
            printf("Command for generating offline req : ./offline-node-locked-license --generate-offline-activation-request --request-file-path ./req.txt --license-key XXXX \n");
            printf("Command for Activating offline : ./offline-node-locked-license --activate-offline --response-file-path ./res.dat");
            return 0;
        }
    }

    int status = IsLicenseGenuine();
    printf("IsLicenseGenuine %d\n", status);
    if (LA_OK == status)
    {
        printf("License is genuinely activated!\n");
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
