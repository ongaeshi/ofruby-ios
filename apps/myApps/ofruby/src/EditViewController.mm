//
//  EditViewController.m
//  ofruby
//
//  Created by ongaeshi on 2014/08/09.
//
//

#import "EditViewController.h"

#import "FCFileManager.h"
#import "HelpViewController.h"
#import "RubyHighlightingTextStorage.h"
#import "ScriptController.h"
#import "ICTextView.h"

@implementation EditViewController
{
    UITextView* mTextView;
	RubyHighlightingTextStorage* mTextStorage;
}

- (id) initWithFileName:(NSString*)aFileName edit:(BOOL)aEditable;
{
    self = [super init];
    if (self) {
        mEditable = aEditable;
        mFileName = aFileName;
        mTouched = NO;
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

    if ([self isSyntaxHighlight]) {
        // TextStorage
        mTextStorage = [RubyHighlightingTextStorage new];
        [mTextStorage replaceCharactersInRange:NSMakeRange(0, 0) withString:[FCFileManager readFileAtPath:mFileName]];

        // LayoutManager
        NSLayoutManager *textLayout = [[NSLayoutManager alloc] init];
        [mTextStorage addLayoutManager:textLayout]; 

        // TextContainer
        NSTextContainer *textContainer = [[NSTextContainer alloc] initWithSize:self.view.bounds.size];
        [textLayout addTextContainer:textContainer];

        // TextView
        mTextView = [[ICTextView alloc] initWithFrame:self.view.bounds textContainer:textContainer];
    } else {
        // TextView
        mTextView = [[ICTextView alloc] initWithFrame:self.view.bounds];
        mTextView.text = [FCFileManager readFileAtPath:mFileName];
    }

    // TextView (Common)
    mTextView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    mTextView.editable = mEditable;
    mTextView.textAlignment = UITextAlignmentLeft;
    //textView.font = [UIFont fontWithName:@"Helvetica" size:14];
    //mTextView.backgroundColor = [UIColor whiteColor];
    mTextView.autocapitalizationType = UITextAutocapitalizationTypeNone;
    mTextView.delegate = self;

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

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];

    NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter addObserver:self selector:@selector(keyboardWillShow:) name:UIKeyboardWillShowNotification object:nil];
    [notificationCenter addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    [notificationCenter addObserver:self selector:@selector(applicationDidEnterBackground) name:@"applicationDidEnterBackground" object:nil];
}
 
- (void)viewDidDisappear:(BOOL)animated
{
    [super viewDidDisappear:animated];

    NSNotificationCenter *notificationCenter = [NSNotificationCenter defaultCenter];
    [notificationCenter removeObserver:self name:UIKeyboardWillShowNotification object:nil];
    [notificationCenter removeObserver:self name:UIKeyboardWillHideNotification object:nil];
    [notificationCenter removeObserver:self name:@"applicationDidEnterBackground" object:nil];
}

- (void)tapTitleButton 
{
    [mTextView resignFirstResponder];
}

- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    // [mTextView becomeFirstResponder];
}

- (void)tapRunButton
{
    // Save file (For iOS <= 6.1)
    [self saveFileIfTouched];

    // Run
    char* scriptPath = (char *)[mFileName UTF8String];
    ScriptController* viewController = [[ScriptController alloc] initWithFrame:[[UIScreen mainScreen] bounds]
                                                                    scriptName:scriptPath];
    [self.navigationController pushViewController:viewController animated:YES];
}

- (void)tapHelpButton
{
    HelpViewController* viewController = [[HelpViewController alloc] init];
    [self.navigationController pushViewController:viewController animated:YES];
}

- (void)textViewDidBeginEditing:(UITextView *)textView
{
    mTouched = YES;
}

- (void)textViewDidEndEditing:(UITextView *)textView
{
    [self saveFileIfTouched];
}

- (void)keyboardWillShow:(NSNotification *)aNotification
{
    // Shrink TextView size because appear the software keyboard
    NSDictionary *info = [aNotification userInfo];
    CGSize kbSize = [[info objectForKey:UIKeyboardFrameEndUserInfoKey] CGRectValue].size;
    CGRect frame = mTextView.frame;
    frame.size.height = self.view.bounds.size.height - kbSize.height;
    mTextView.frame = frame;
}

- (void)keyboardWillHide:(NSNotification*)aNotification
{
    // Restore TextView size
    mTextView.frame = self.view.bounds;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)saveFileIfTouched
{
    if (mTouched) {
        if ([self isSyntaxHighlight]) {
            [FCFileManager writeFileAtPath:mFileName content:mTextStorage.string];
        } else {
            [FCFileManager writeFileAtPath:mFileName content:mTextView.text];
        }
        mTouched = NO;
    }
}

- (void)applicationDidEnterBackground
{
    [self saveFileIfTouched];
}

-(BOOL)isSyntaxHighlight
{
    return NO;
    // return floor(NSFoundationVersionNumber) >= NSFoundationVersionNumber_iOS_7_0;
}

@end
