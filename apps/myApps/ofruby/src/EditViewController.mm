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
    if (self) {
        mFileName = aFileName;
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // NavButton
    UIBarButtonItem* runButton = [[UIBarButtonItem alloc] initWithTitle:@"Run"
                                                                  style:UIBarButtonSystemItemDone
                                                                 target:self
                                                                 action:@selector(tapRunButton)];
    UIBarButtonItem* helpButton = [[UIBarButtonItem alloc] initWithTitle:@"[?]"
                                                                  style:UIBarButtonSystemItemDone
                                                                 target:self
                                                                 action:@selector(tapHelpButton)];
    self.navigationItem.rightBarButtonItems = [NSArray arrayWithObjects:runButton, helpButton, nil];

    // TextView
    CGRect rect = self.view.bounds;
    mTextView = [[UITextView alloc]initWithFrame:rect];
    mTextView.editable = YES;
    mTextView.textAlignment = UITextAlignmentLeft;
    //textView.font = [UIFont fontWithName:@"Helvetica" size:14];
    //mTextView.backgroundColor = [UIColor whiteColor];
    mTextView.autocapitalizationType = UITextAutocapitalizationTypeNone;
    mTextView.delegate = self;
    mTextView.text = [FCFileManager readFileAtPath:mFileName];
    [self.view addSubview:mTextView];

    // Tap title
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    button.backgroundColor = [UIColor clearColor];
    // button.titleLabel.font =[UIFont boldSystemFontOfSize:16.0];
    [button setTitle:[mFileName lastPathComponent] forState:UIControlStateNormal];
    [button setTitleColor:[UIColor blackColor] forState:UIControlStateNormal];
    button.frame = CGRectMake(0.0, 0.0, 120.0, self.navigationController.navigationBar.frame.size.height);
    [button addTarget:self action:@selector(tapTitleButton) forControlEvents:UIControlEventTouchUpInside];
    self.navigationItem.titleView = button;
}

- (void)tapTitleButton {
    [mTextView resignFirstResponder];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    // [mTextView becomeFirstResponder];
}

- (void)tapRunButton
{
    char* scriptPath = (char *)[mFileName UTF8String];
    ScriptController* viewController = [[ScriptController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
                                                                    scriptName:scriptPath];
    [self.navigationController pushViewController:viewController animated:YES];
}

- (void)tapHelpButton
{
    NSLog(@"Go to help");
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    // Shrink TextView size because appear the software keyboard
    static const CGFloat kKeyboardHeight = 216.0; //TODO: To the constant
    CGRect frame = mTextView.frame;
    frame.size.height = self.view.bounds.size.height - kKeyboardHeight;
    mTextView.frame = frame;
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    // Restore TextView size
    mTextView.frame = self.view.bounds;

    // Save file
    [FCFileManager writeFileAtPath:mFileName content:textView.text];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
