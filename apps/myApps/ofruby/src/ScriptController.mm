//
//  CustomAppViewController.m
//  Created by lukasz karluk on 8/02/12.
//

#import "ScriptController.h"
#import "ofxiOSExtras.h"

@implementation ScriptController

- (id) initWithFrame:(CGRect)frame app:(ofxiOSApp *)app {
    
    ofxiOSGetOFWindow()->setOrientation( OF_ORIENTATION_DEFAULT );   //-- default portait orientation.
    
    return self = [super initWithFrame:frame app:app];
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation {
    return NO;
}

- (void)viewWillAppear:(BOOL)animated {
    //  [super viewWillAppear:animated];
    //[self.navigationController setNavigationBarHidden:YES animated:YES];
}

@end
