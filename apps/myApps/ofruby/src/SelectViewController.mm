#include "SelectViewController.h"

#include "EditViewController.h"
#include "FCFileManager.h"
#include "ScriptApp.h"
#include "ScriptController.h"

@interface SelectViewController ()

@end

@implementation SelectViewController

- (id)init
{
    self = [super init];
    if (self) {
        self.title = @"ofruby";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    dataSource = [[NSArray alloc]initWithObjects: @"hello.rb", @"line.rb", nil];
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [dataSource count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *cellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    cell.textLabel.text = [dataSource objectAtIndex:indexPath.row];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString* tableCellName = [dataSource objectAtIndex:indexPath.row];
    NSString* path = [FCFileManager pathForDocumentsDirectoryWithPath:tableCellName];

    // Create a file if not exists
    if (![FCFileManager existsItemAtPath:path]) {
        [FCFileManager createFileAtPath:path withContent:@"def draw\n  rect 150, 0, 40, 480\nend\n"];
    }
    
    // EditViewController* viewController = [[EditViewController alloc] initWithFileName:path];

    char* scriptPath = (char *)[path UTF8String];
    ScriptController* viewController = [[ScriptController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
                                                                    scriptName:scriptPath];

    [self.navigationController pushViewController:viewController animated:YES];
    self.navigationController.navigationBar.topItem.title = tableCellName;
}

@end
