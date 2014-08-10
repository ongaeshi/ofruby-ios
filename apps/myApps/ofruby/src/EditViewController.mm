//
//  EditViewController.m
//  ofruby
//
//  Created by ongaeshi on 2014/08/09.
//
//

#import "EditViewController.h"

#import "FCFileManager.h"
#import "ScriptController.h"

@implementation EditViewController

- (id) initWithFileName:(NSString*)aFileName
{
    self = [super init];
    mFileName = aFileName;
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // NavButton
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"Run"
                                                                              style:UIBarButtonSystemItemDone
                                                                             target:self
                                                                             action:@selector(doneDidPush)];

    // TextView
    CGRect rect = self.view.bounds;
    mTextView = [[UITextView alloc]initWithFrame:rect];

    mTextView.editable = YES;
    mTextView.textAlignment = UITextAlignmentLeft;
    //textView.font = [UIFont fontWithName:@"Helvetica" size:14];
    mTextView.backgroundColor = [UIColor whiteColor];
    mTextView.delegate = self;

    mTextView.text = [FCFileManager readFileAtPath:mFileName];

    [self.view addSubview:mTextView];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    // [mTextView becomeFirstResponder];
}

- (void)doneDidPush {
    char* scriptPath = (char *)[mFileName UTF8String];
    ScriptController* viewController = [[ScriptController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
                                                                    scriptName:scriptPath];
    [self.navigationController pushViewController:viewController animated:YES];
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    [FCFileManager writeFileAtPath:mFileName content:textView.text];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
