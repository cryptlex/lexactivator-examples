/* eslint-disable new-cap */
import { LexActivator, LexStatusCodes, LexActivatorException, PermissionFlags } from '@cryptlex/lexactivator'

function init() {
    /*
     * Product data needs to be hard-coded and this value is not sensitive or secret.
     * You can download the product.dat file from the product page of the admin dashboard.
     */
    LexActivator.SetProductData('PASTE_CONTENT_OF_PRODUCT.DAT_FILE');

    /*
     * Product Id is simply a unique identifier of your product and needs to be hard-coded.
     * Similarly this Id is not sensitive as well.
     * 
     * Setting permission flag to LA_USER in case of hosted-floating does not reset the license key upon deactivation.
     */

    LexActivator.SetProductId('PASTE_PRODUCT_ID', PermissionFlags.LA_USER);
}

function licenseCallback(status) {
    try {
        switch (status) {
            case LexStatusCodes.LA_OK:
            case LexStatusCodes.LA_EXPIRED:
            case LexStatusCodes.LA_SUSPENDED:
                console.log('License is genuinely activated!', status);
                break;
            default:
                throw new LexActivatorException(status);
        }
    } catch (error) {
        console.log(error.code, error.message);
    }
}

function main() {
    try {
        init();
        const licenseKey = LexActivator.GetLicenseKey();
        if (licenseKey == "") {
            LexActivator.SetLicenseKey("PASTE_LICENCE_KEY");
        }

        /*
         * Whenever the server sync occurs in a separate thread, and server returns the response,
           license callback function gets invoked.
         */
        LexActivator.SetLicenseCallback(licenseCallback);

        const status = LexActivator.IsLicenseGenuine();
        if (LexStatusCodes.LA_OK == status) {
            console.log('License is genuinely activated!');

            // You can execute your code as the user is licensed

            const expiryDate = LexActivator.GetLicenseExpiryDate();
            const daysLeft = (expiryDate - (new Date().getTime() / 1000)) / 86400;
            console.log('Days left:', daysLeft);

        }
        else if (LexStatusCodes.LA_EXPIRED == status) {
            console.log('License is genuinely activated but has expired!');
        } else if (LexStatusCodes.LA_SUSPENDED == status) {
            console.log('License is genuinely activated but has been suspended!');
        } else if (LexStatusCodes.LA_GRACE_PERIOD_OVER == status) {
            console.log('License is genuinely activated but grace period is over!');
        } else if (LexStatusCodes.LA_FAIL == status) {
            const status = LexActivator.ActivateLicense();
            if (LexStatusCodes.LA_OK == status || LexStatusCodes.LA_EXPIRED == status || LexStatusCodes.LA_SUSPENDED == status) {
                console.log('License activated successfully:', status);
                // execute your code here....

                // Is it right to ask users to write the code at these two places above and below?
            } else {
                console.log('License activation failed:', status);
            }
        }
        // need to ask if we have to wrap the deactivateLicense() in a condition for LA_OK?

        // In case of hosted floating license this function should be called  
        // when the application is closed to avoid zombie licenses.
        LexActivator.DeactivateLicense();

    } catch (error) {
        console.log(error.code, error.message);
    }
}

main();
