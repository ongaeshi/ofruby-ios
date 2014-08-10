#import <Foundation/Foundation.h>
#import "SelectViewController.h"

@interface AppDelegate : NSObject <UIApplicationDelegate> {
    UINavigationController *naviController;
    SelectViewController *rootController;
}

@property (nonatomic, retain) UIWindow *window;

@end
