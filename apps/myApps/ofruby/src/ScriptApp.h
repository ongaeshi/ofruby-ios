#pragma once

#include "ofMain.h"
#include "ofxiOS.h"
#include "ofxiOSExtras.h"
#include "rubykokuban/ScriptEngine.hpp"
#include "rubykokuban/Input.hpp"

class ScriptApp : public ofxiOSApp {
public:
    ScriptApp(const char* aScriptPath);
    
    void setup();
    void update();
    void draw();
    void exit();
	
    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
    void touchDoubleTap(ofTouchEventArgs & touch);
    void touchCancelled(ofTouchEventArgs & touch);
    
    void lostFocus();
    void gotFocus();
    void gotMemoryWarning();
    void deviceOrientationChanged(int newOrientation);
    
private:
    rubykokuban::Input        mInput;
    rubykokuban::ScriptEngine mScriptEngine;
    ofColor                   mBgColor;
};
