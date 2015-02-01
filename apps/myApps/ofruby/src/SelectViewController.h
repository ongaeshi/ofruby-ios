#import <UIKit/UIKit.h>

@interface SelectViewController : UITableViewController
{
    NSMutableArray* mDataSource;
    NSString* mFileDirectory;
}

- (id)initWithFileDirectory:(NSString*)directory;

@end
