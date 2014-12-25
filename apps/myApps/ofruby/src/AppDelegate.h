#import <Foundation/Foundation.h>

@interface AppDelegate : NSObject <UIApplicationDelegate> {
    UINavigationController *naviController;
    UITabBarController *tabBarController;
}

@property (nonatomic, retain) UIWindow *window;

@end
