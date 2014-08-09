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
    //  [super viewWillAppear:animated];
    //[self.navigationController setNavigationBarHidden:YES animated:YES];
}

@end
