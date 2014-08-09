#include "SelectViewController.h"
#include "ScriptController.h"
#include "ScriptApp.h"
#include "EditViewController.h"

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
    NSString* fullFileName = [dataSource objectAtIndex:indexPath.row];
    NSString* fileName = [[fullFileName lastPathComponent] stringByDeletingPathExtension];
    NSString* extension = [fullFileName pathExtension];
    NSString *filePath = [[NSBundle mainBundle] pathForResource:fileName ofType:extension];
        
    char* scriptPath = (char *)[filePath UTF8String];
    
//    ScriptController* viewController = [[[ScriptController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
//                                                                     scriptName:scriptPath] autorelease];
    
    EditViewController* viewController = [[[EditViewController alloc] init] autorelease];

    [self.navigationController pushViewController:viewController animated:YES];
    self.navigationController.navigationBar.topItem.title = fullFileName;
}

@end
