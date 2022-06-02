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
     */

    LexActivator.SetProductId('PASTE_PRODUCT_ID', PermissionFlags.LA_USER);
}

// Ideally on a button click inside a dialog.

function activate() {
	LexActivator.SetLicenseKey('PASTE_LICENCE_KEY');
    /*
     * SetActivationMetadata() can be used to get info from client to server.
     * The metadata appears along with the activation details of the license on the dashboard.
     * This function is not a required function.
     */
	LexActivator.SetActivationMetadata('key1', 'value1');
	const status = LexActivator.ActivateLicense();
	if (LexStatusCodes.LA_OK == status || LexStatusCodes.LA_EXPIRED == status || LexStatusCodes.LA_SUSPENDED == status) {
		console.log('License activated successfully:', status);
	} else {
		console.log('License activation failed:', status);
	}
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
        activate(); // in case of node-locekd this function only needs to be called once.

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
        }

    } catch (error) {
        console.log(error.code, error.message);
    }
}

main();