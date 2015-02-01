#import "AppDelegate.h"
#import "FileViewController.h"
#import "SampleViewController.h"

@implementation AppDelegate

@synthesize window;

- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen]bounds]];

    tabBarController = [[UITabBarController alloc] init];
    tabBarController.title = @"";

    UIViewController* tab1 = [[FileViewController alloc]init];
    UIImage* icon1 = [UIImage imageNamed:@"tabbar_files.png"];
    tab1.tabBarItem = [[UITabBarItem alloc] initWithTitle:@"File" image:icon1 tag:0];

    UIViewController* tab2 = [[SampleViewController alloc]init];
    UIImage* icon2 = [UIImage imageNamed:@"tabbar_samples.png"];
    tab2.tabBarItem = [[UITabBarItem alloc] initWithTitle:@"Sample" image:icon2 tag:0];

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
