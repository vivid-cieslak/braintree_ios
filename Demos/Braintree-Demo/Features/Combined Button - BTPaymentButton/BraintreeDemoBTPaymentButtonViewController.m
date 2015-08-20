#import "BraintreeDemoBTPaymentButtonViewController.h"
#import <BraintreeCard/BraintreeCard.h>
#import <BraintreeUI/BraintreeUI.h>
#import <PureLayout/ALView+PureLayout.h>

@interface BraintreeDemoBTPaymentButtonViewController () <BTAppSwitchDelegate, UITableViewDelegate>
@end

@implementation BraintreeDemoBTPaymentButtonViewController

- (UIView *)paymentButton {
    BTPaymentButton *paymentButton = [[BTPaymentButton alloc] initWithAPIClient:self.apiClient completion:^(id<BTTokenized> tokenization, NSError *error) {
        if (tokenization) {
            self.progressBlock(@"Got a nonce 💎!");
            NSLog(@"%@", [tokenization debugDescription]);
            self.completionBlock(tokenization);
        } else if (error) {
            self.progressBlock(error.localizedDescription);
        } else {
            self.progressBlock(@"Canceled 🔰");
        }
    }];
    paymentButton.appSwitchDelegate = self;
    return paymentButton;
}


- (void)appSwitcherWillPerformAppSwitch:(id)appSwitcher {
    self.progressBlock(@"Will perform app switch");
}

- (void)appSwitcher:(id)appSwitcher didPerformSwitchToTarget:(BTAppSwitchTarget)target {
    self.progressBlock(@"Did perform app switch");
}

- (void)appSwitcherWillProcessPaymentInfo:(id)appSwitcher {
    self.progressBlock(@"Processing payment info...");
}

@end
