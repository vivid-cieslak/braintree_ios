#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#import <Braintree/Braintree-API.h>
#import <Braintree/Braintree-PayPal.h>
#import <Braintree/Braintree-Payments-UI.h>
#import "BTDropInViewController.h"

typedef void (^BraintreeNonceCompletionBlock)(NSString *nonce, NSError *error);

/// The `Braintree` class is the front door to the Braintree SDK for iOS. It contains
/// everything you need to easily start accepting payments in your mobile app.
///
/// You can choose: Drop-In or tokenization.
///
/// With Drop-In, you can rely us to provide a fast, easy-to-use UI, which your users will
/// interact with in order to provide payment details. The result, from the programmer's
/// perspective, is a nonce. Send this nonce to your server to perform a variety of payment 
/// operations, such as creating a sale
///
/// With tokenization, you have more control of your UI, but errors will be handled on the
/// server-side via multiple server-side calls to Braintree. Like Drop-In, the end result is
/// a nonce, which may transmit to your servers.
///
/// For advanced integrations, see Braintree-API.h, Braintree-PayPal.h and Braintree-Payments-UI.h.
@interface Braintree : NSObject

/// Returns an instance of `Braintree`, the public interface of Braintree-iOS.
///
/// @param clientToken value that is generated on your sever using a Braintree server-side
/// client library that contains all necessary configuration to setup the client SDKs. It also
/// authenticates the application to communicate directly to Braintree.
///
/// @note You should generate a new client token before each checkout to ensure it has not expired.
///
/// @return An instance of the Braintree Library to perform payment operations.
+ (Braintree *)braintreeWithClientToken:(NSString *)clientToken;

#pragma mark Drop In - PayPal


/// Creates and returns a payment flow for accepting credit card and PayPal-based payments.
///
/// Present this view controller in your app to prompt your user for payment info, and you will
/// receive a payment method nonce.
///
/// @param completionBlock Completion block that is called exactly once asynchronously, providing either a nonce or an error.
///
/// @return A Drop-In view controller to be presented in your app's payment flow.
- (BTDropInViewController *)dropInViewControllerWithCompletion:(BraintreeNonceCompletionBlock)completionBlock;

/// Creates and returns a PayPal control that can be added to the UI. When tapped, this control will initiate the PayPal authorization flow.
///
/// @param completionBlock Completion block that is called exactly once asynchronously, providing either a nonce (upon user agreement and success) or an error (failure).
///
/// @return A PayPal control (button) to be added as a subview in your UI.
- (BTPayPalControl *)payPalControlWithCompletion:(BraintreeNonceCompletionBlock)completionBlock;

#pragma mark Tokenization

/// Creates and returns a nonce for the given credit card details.
///
/// @note The credit card details provided are not validated until a
/// Braintree operation, such as `Transaction.Create` is performed on
/// your server.
///
/// @param cardNumber      Card number to tokenize
/// @param expirationMonth Card's expiration month
/// @param expirationYear  Card's expiration year
/// @param completionBlock Completion block that is called exactly once asynchronously, providing either a nonce upon success or an error upon failure.
- (void)tokenizeCardWithNumber:(NSString *)cardNumber
               expirationMonth:(NSString *)expirationMonth
                expirationYear:(NSString *)expirationYear
                    completion:(BraintreeNonceCompletionBlock)completionBlock;


#pragma mark - Library Metadata

/// Returns the current library version.
///
/// @return A string representation of this library's current semver.org version (if integrating with CocoaPods).
+ (NSString *)libraryVersion;


@end