#import <Foundation/Foundation.h>
#include "TopViewController.h"
#include "SecondViewController.h"
#include "ScriptController.h"
#include "ScriptApp.h"

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
                  @"hello.rb", @"line.rb", @"Snoopy", @"Spike", @"Olaf",@"Marbles", @"Belle", @"Andy", nil];
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
    // NSLog(@"indexPath: %d", indexPath.row);

    if (indexPath.row == 0 || indexPath.row == 1) {
//        NSLog(@"Run %@", [dataSource objectAtIndex:indexPath.row]);
        NSString* fullFileName = [dataSource objectAtIndex:indexPath.row];
        NSString* fileName = [[fullFileName lastPathComponent] stringByDeletingPathExtension];
        NSString* extension = [fullFileName pathExtension];
        NSString *filePath = [[NSBundle mainBundle] pathForResource:fileName ofType:extension];
        
//        NSLog(@"filePath = %@", filePath);
        char* scriptPath = (char *)[filePath UTF8String];
        
        ScriptController* viewController = [[[ScriptController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
                                                                     app:new ScriptApp(scriptPath)] autorelease];
        
        [self.navigationController pushViewController:viewController animated:YES];
        self.navigationController.navigationBar.topItem.title = @"ScriptApp";
        
        
    } else {
        NSString *text = [[dataSource objectAtIndex:indexPath.row] stringByAppendingString:@" clicked"];
        SecondViewController* viewController = [[SecondViewController alloc]initWithTitle:text];
        if (viewController) {
            [self.navigationController pushViewController:viewController animated:YES];
        }
    }
}

@end
