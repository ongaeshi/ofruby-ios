#import <Foundation/Foundation.h>
#import "TopViewController.h"

@interface SampleAppDelegate : NSObject <UIApplicationDelegate> {
    UINavigationController *naviController;
    TopViewController *topController;
}

@property (nonatomic, retain) UIWindow *window;

@end