#import "TopViewController.h"

@interface TopViewController ()

@end

@implementation TopViewController

/**
 * イニシャライザ
 */
- (id)init
{
    self = [super init];
    if (self) {
        // タイトルを設定
        self.title = @"トップ";
    }
    return self;
}

/**
 * ビューがロードし終わったとき
 */
- (void)viewDidLoad
{
    [super viewDidLoad];
    dataSource = [[NSArray alloc]initWithObjects:
                  @"Snoopy", @"Spike", @"Olaf",@"Marbles", @"Belle", @"Andy", nil];
}

/**
 * テーブルのセルの数を返す
 */
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [dataSource count];
}

/**
 * 指定されたインデックスパスのセルを作成する
 */
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *cellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    // セルが作成されていないか?
    if (!cell) { // yes
        // セルを作成
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    // セルにテキストを設定
    cell.textLabel.text = [dataSource objectAtIndex:indexPath.row];
    
    return cell;
}

/**
 * セルが選択されたとき
 */
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    Class class = NSClassFromString(@"SecondViewController");
    NSString *text = [[dataSource objectAtIndex:indexPath.row] stringByAppendingString:@"ffff"];
    id viewController = [[class alloc]initWithTitle:text];
    if (viewController) {
        [self.navigationController pushViewController:viewController animated:YES];
    }
}

@end
