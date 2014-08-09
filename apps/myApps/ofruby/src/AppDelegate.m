#import "AppDelegate.h"

@implementation AppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen]bounds]];

    topController = [[TopViewController alloc]init];
    naviController = [[UINavigationController alloc]
                      initWithRootViewController:topController];

    [self.window addSubview:naviController.view];
    [self.window makeKeyAndVisible];
}

@end
