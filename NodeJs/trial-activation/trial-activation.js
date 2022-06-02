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
function activateTrial() {
	LexActivator.SetTrialActivationMetadata('key1', 'value1');
	const status = LexActivator.ActivateTrial();
	if (LexStatusCodes.LA_OK == status) {
		console.log('Product trial activated successfully!');
	} else if (LexStatusCodes.LA_TRIAL_EXPIRED == status) {
		console.log('Product trial has expired!');
	} else {
		console.log('Product trial activation failed:', status);
	}
}

function main() {
    try {
        init();
        const trialStatus = LexActivator.IsTrialGenuine();
			if (LexStatusCodes.LA_OK == trialStatus) {
				const expiryDate = LexActivator.GetTrialExpiryDate();
				const daysLeft = (expiryDate - (new Date().getTime() / 1000)) / 86400;
				console.log('Trial days left:', daysLeft);
			} else if (LexStatusCodes.LA_TRIAL_EXPIRED == trialStatus) {
				console.log('Trial has expired!');
				// Time to buy the license and activate the app
			} else {
				console.log('Either trial has not started or has been tampered!');
				// Activating the trial
				activateTrial();
			}
    } catch (error) {
        console.log(error.code, error.message);
    }
}

main();