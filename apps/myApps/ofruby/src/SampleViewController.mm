#include "SampleViewController.h"

#include "EditViewController.h"
#include "FCFileManager.h"
#include "ScriptApp.h"
#include "ScriptController.h"

@interface SampleViewController ()

@end

@implementation SampleViewController

- (id)init
{
    self = [super init];
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    // Title
    self.tabBarController.title = @"Sample";

    // Add Button
    self.tabBarController.navigationItem.rightBarButtonItem = NULL;
    self.tabBarController.navigationItem.leftBarButtonItem = NULL;

    // TableView
    mDataSource = [self updateDataSourceFromFiles];
    [self.tableView reloadData];
}

- (void)alertView:(UIAlertView*)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (buttonIndex != alertView.cancelButtonIndex) {
        NSString* text = [[alertView textFieldAtIndex:0] text];

        // Remove a directory path and Add the ".rb" extension.
        text = [[[text lastPathComponent] stringByDeletingPathExtension] stringByAppendingString:@".rb"];

        //  File name is illegal
        if ([text isEqualToString:@".rb"]) {
            UIAlertView* alert = [[UIAlertView alloc] init];
            alert.title = @"Invalid file name";
            [alert addButtonWithTitle:@"OK"];
            [alert show];
            return;
        }

        // Create path
        NSString* path = [FCFileManager pathForDocumentsDirectoryWithPath:text];

        // Alert if file already exists
        if ([FCFileManager existsItemAtPath:path]) {
            UIAlertView* alert = [[UIAlertView alloc] init];
            alert.title = @"Already exists";
            [alert addButtonWithTitle:@"OK"];
            [alert show];
            return;
        }

        // Create a new file
        [FCFileManager createFileAtPath:path
                            withContent:@"def setup\n"
                                         "end\n"
                                         "\n"
                                         "def update\n"
                                         "end\n"
                                         "\n"
                                         "def draw\n"
                                         "  # set_color 204, 52, 45\n"
                                         "  rect 120, 220, 80, 40\n"
                                         "end\n"
            ];

        // Update data source
        mDataSource = [self updateDataSourceFromFiles];

        // Insert table view
        NSUInteger newIndex[] = {0, 0}; // section, row
        NSIndexPath* newPath = [[NSIndexPath alloc] initWithIndexes:newIndex length:2];
        [self.tableView insertRowsAtIndexPaths:[NSArray arrayWithObject:newPath]
                              withRowAnimation:UITableViewRowAnimationTop];

        // Reload all
        // [self.tableView reloadData];
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
    // NSString* path = [FCFileManager pathForDocumentsDirectoryWithPath:tableCellName];
    NSString* path = [FCFileManager pathForMainBundleDirectoryWithPath:@"sample"];
    path = [path stringByAppendingPathComponent:tableCellName];
    EditViewController* viewController = [[EditViewController alloc] initWithFileName:path];
    [self.navigationController pushViewController:viewController animated:YES];
}

- (void)tableView:(UITableView*)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // File
        NSString* tableCellName = [mDataSource objectAtIndex:indexPath.row];
        NSString* path = [FCFileManager pathForDocumentsDirectoryWithPath:tableCellName];
        [FCFileManager removeItemAtPath:path];

        // Data Source
        [mDataSource removeObjectAtIndex:indexPath.row];

        // Table Row
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]
                         withRowAnimation:UITableViewRowAnimationFade];

    }
}

- (NSMutableArray *) updateDataSourceFromFiles
{
    NSError *error = nil;

    // Collect files
    NSString* path = [FCFileManager pathForDocumentsDirectory];
    // NSArray*  files = [FCFileManager listFilesInDirectoryAtPath:path];

    NSBundle *mainBundle = [NSBundle mainBundle];
    NSString *filePath = [mainBundle pathForResource:@"hello" ofType:@"rb" inDirectory:@"sample"];
    NSLog(@"resourcePath: %@", filePath);

    NSString *resourcePath = [mainBundle resourcePath];
    NSString *samplePath = [resourcePath stringByAppendingPathComponent:@"sample"];
    NSLog(@"samplePath: %@", samplePath);
    NSArray* files = [FCFileManager listFilesInDirectoryAtPath:samplePath];

    // Create array adding ModDate
    NSMutableArray* filesAndModDates = [NSMutableArray arrayWithCapacity:[files count]];

    for (NSString* file in files) {
        NSDictionary* attributes = [[NSFileManager defaultManager] attributesOfItemAtPath:file error:&error];
        NSDate* modDate = [attributes objectForKey:NSFileModificationDate];

        if (error == nil) {
            [filesAndModDates addObject:[NSDictionary dictionaryWithObjectsAndKeys:
                                         file, @"Path",
                                         modDate, @"ModDate",
                                         nil]];
        }
    }

    // Sort by ModDate
    NSArray* sortedFiles = [filesAndModDates sortedArrayUsingComparator:
                            ^(id path1, id path2)
                            {
                                NSComparisonResult comp = [[path1 objectForKey:@"ModDate"] compare:
                                                           [path2 objectForKey:@"ModDate"]];

                                // Invert ordering
                                if (comp == NSOrderedDescending) {
                                    comp = NSOrderedAscending;
                                }
                                else if(comp == NSOrderedAscending){
                                    comp = NSOrderedDescending;
                                }

                                return comp;
                            }];

    // Map file
    NSMutableArray* array = [[NSMutableArray alloc]initWithObjects: nil];

    for (NSDictionary* dict in sortedFiles) {
        [array addObject:[[dict objectForKey:@"Path"] lastPathComponent]];
    }


    return array;
}

@end