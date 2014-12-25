#import "AppDelegate.h"
#import "SelectViewController.h"
#import "HelpViewController.h"

@implementation AppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen]bounds]];

    tabBarController = [[UITabBarController alloc] init];
    tabBarController.title = @"Home";

    UIViewController* tab1 = [[SelectViewController alloc]init];
    tab1.title = @"Files";
    UIViewController* tab2 = [[HelpViewController alloc]init];
    tab2.title = @"Help";
    NSArray* tabs = [NSArray arrayWithObjects:tab1, tab2, nil];
    [tabBarController setViewControllers:tabs animated:NO];

    naviController = [[UINavigationController alloc]
                      initWithRootViewController:tabBarController];

    [self.window addSubview:naviController.view];
    [self.window makeKeyAndVisible];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
　　NSNotification* n = [NSNotification notificationWithName:@"applicationDidEnterBackground" object:self];
　　[[NSNotificationCenter defaultCenter] postNotification:n];
}

@end
