#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen]bounds]];

    rootController = [[SelectViewController alloc]init];
    naviController = [[UINavigationController alloc]
                      initWithRootViewController:rootController];

    [self.window addSubview:naviController.view];
    [self.window makeKeyAndVisible];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
　　NSNotification* n = [NSNotification notificationWithName:@"applicationDidEnterBackground" object:self];
　　[[NSNotificationCenter defaultCenter] postNotification:n];
}

@end
