#import <UIKit/UIKit.h>

@interface SelectViewController : UITableViewController
{
    NSMutableArray* mDataSource;
    NSString* mFileDirectory;
    NSString* mTitle;
}

- (id)initWithFileDirectory:(NSString*)directory title:(NSString*)title;

@end
