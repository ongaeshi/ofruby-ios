#import "SampleAppDelegate.h"

@implementation SampleAppDelegate

@synthesize window;

/**
 * アプリケーションの起動処理が終わったとき
 */
- (void)applicationDidFinishLaunching:(UIApplication *)application
{
    self.window = [[UIWindow alloc] initWithFrame:[[UIScreen mainScreen]bounds]];
    
    // ナビゲーションコントローラにベースとなるコントローラをセット
    topController = [[TopViewController alloc]init];
    naviController = [[UINavigationController alloc]
                      initWithRootViewController:topController];
    
    // ナビゲーションコントローラのビューをウィンドウに貼付ける
    [self.window addSubview:naviController.view];
    
    [self.window makeKeyAndVisible];
}

@end