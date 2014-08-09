//#include "ofMain.h"
//#include "ofApp.h"
#include <UIKit/UIKit.h>
#import "SampleAppDelegate.h"

int main(int argc, char *argv[]){
    //	ofSetupOpenGL(1024,768,OF_FULLSCREEN);			// <-------- setup the GL context
    //
    //	ofRunApp(new ofApp());

    @autoreleasepool {
        return UIApplicationMain(argc, argv, nil, NSStringFromClass([SampleAppDelegate class]));
    }
    
}
