#import "SecondViewController.h"

@interface SecondViewController ()

@end

@implementation SecondViewController

/**
 * イニシャライザ
 * @param text 表示するテキスト
 */
- (id)initWithTitle:(NSString *)title
{
    self = [super init];
    if (self) {
        // タイトルを設定
        self.title = title;
        
        // ラベルを設定
        CGRect rect = CGRectMake(0, 0, 320, 50);
        UILabel *label = [[UILabel alloc]initWithFrame:rect];
        label.center = CGPointMake(160, 160);
        label.text = title;
        label.font = [UIFont fontWithName:@"Arial" size:48];
        label.textAlignment = UITextAlignmentLeft;
        [self.view addSubview:label];
        
        // 背景色を設定
        self.view.backgroundColor = [UIColor whiteColor];
    }
    return self;
}

@end
