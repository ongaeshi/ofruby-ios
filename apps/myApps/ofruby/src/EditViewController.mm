//
//  EditViewController.m
//  ofruby
//
//  Created by ongaeshi on 2014/08/09.
//
//

#import "EditViewController.h"

#import "FCFileManager.h"

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

    CGRect rect = self.view.bounds;
    UITextView *textView = [[UITextView alloc]initWithFrame:rect];

    textView.editable = YES;
    textView.textAlignment = UITextAlignmentLeft;
    //textView.font = [UIFont fontWithName:@"Helvetica" size:14];
    textView.backgroundColor = [UIColor whiteColor];
    textView.delegate = self;

    textView.text = [FCFileManager readFileAtPath:mFileName];

    [self.view addSubview:textView];
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
