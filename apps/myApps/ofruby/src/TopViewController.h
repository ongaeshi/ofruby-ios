#import <UIKit/UIKit.h>
#import "SecondViewController.h"

@interface TopViewController : UITableViewController {
    SecondViewController *secondController;
    NSArray *dataSource;
}

@end