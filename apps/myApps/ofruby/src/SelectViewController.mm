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
        self.title = @"Home";
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // NavButton
    UIBarButtonItem* addButton = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemAdd
                                                                               target:self
                                                                               action:@selector(tapAddButton)];
    self.navigationItem.rightBarButtonItem = addButton;

    // TableView
    NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
    mDataSource = [defaults objectForKey:@"SelectViewControllerDataSource"];
    if (mDataSource == nil) {
        mDataSource = [[NSMutableArray alloc]initWithObjects: nil];
    }
}

- (void)tapAddButton
{
    UIAlertView* alert = [[UIAlertView alloc] init];
    alert.title = @"New File";
    //alert.message = @"Enter file name.";
    alert.delegate = self;
    [alert addButtonWithTitle:@"Cancel"];
    [alert addButtonWithTitle:@"OK"];
    [alert setAlertViewStyle:UIAlertViewStylePlainTextInput];
    alert.cancelButtonIndex = 0;
    [alert show];
}

- (void)alertView:(UIAlertView*)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex != alertView.cancelButtonIndex) {
        NSString* text = [[alertView textFieldAtIndex:0] text];

        // Insert new file
        [mDataSource insertObject:text atIndex:0];
        NSUserDefaults* defaults = [NSUserDefaults standardUserDefaults];
        [defaults setObject:mDataSource forKey:@"SelectViewControllerDataSource"];

        // Update table view
        NSUInteger newIndex[] = {0, 0}; // section, row
        NSIndexPath* newPath = [[NSIndexPath alloc] initWithIndexes:newIndex length:2];
        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:newPath]
                              withRowAnimation:UITableViewRowAnimationTop];
    }
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [mDataSource count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString *cellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    
    if (!cell) {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    cell.textLabel.text = [mDataSource objectAtIndex:indexPath.row];
    
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSString* tableCellName = [mDataSource objectAtIndex:indexPath.row];
    NSString* path = [FCFileManager pathForDocumentsDirectoryWithPath:tableCellName];

    // Create a file if not exists
    if (![FCFileManager existsItemAtPath:path]) {
        [FCFileManager createFileAtPath:path withContent:@"def setup\nend\n\ndef update\nend\n\ndef draw\n  rect 160, 240, 80, 40\nend\n"];
    }
    
    EditViewController* viewController = [[EditViewController alloc] initWithFileName:path];
    [self.navigationController pushViewController:viewController animated:YES];
}

@end
