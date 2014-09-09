//
//  CustomAppViewController.m
//  Created by lukasz karluk on 8/02/12.
//

#import "ScriptController.h"
#import "ScriptApp.h"
#import "ofxiOSExtras.h"

@implementation ScriptController

- (id) initWithFrame:(CGRect)frame scriptName:(char*)scriptPath {
    ofxiOSGetOFWindow()->setOrientation( OF_ORIENTATION_DEFAULT );   //-- default portait orientation.
    return self = [super initWithFrame:frame app:new ScriptApp(scriptPath)];
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    return NO;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    [self.navigationController setNavigationBarHidden:YES];
}


- (void)viewWillDisappear:(BOOL)animated {
    [super viewWillDisappear:animated];
    [self.navigationController setNavigationBarHidden:NO];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    UIButton* button = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [button setTitle:@"Back" forState:UIControlStateNormal];
    [button sizeToFit];
    button.frame = CGRectMake(280, 5, 40, 20);
    [button addTarget:self action:@selector(backButton) forControlEvents:UIControlEventTouchUpInside];
    [self.view addSubview:button];
}

- (void)backButton {
    [self.navigationController popViewControllerAnimated:YES];
}

@end
