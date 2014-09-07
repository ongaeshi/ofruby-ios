#include "ScriptApp.h"

#include "rubykokuban/BindInput.hpp"

//--------------------------------------------------------------
ScriptApp::ScriptApp(const char* aScriptPath)
: mInput()
, mScriptEngine(aScriptPath)
{
    rubykokuban::BindInput::Setup(mInput);
}

//--------------------------------------------------------------
void ScriptApp::setup()
{
	// initialize the accelerometer
	ofxAccelerometer.setup();
	
	//If you want a landscape oreintation
	//iPhoneSetOrientation(OFXIPHONE_ORIENTATION_LANDSCAPE_RIGHT);

    // Set default settings
    ofSetColor(0, 0, 0);
	ofBackground(255, 255, 255);
    ofSetCircleResolution(32);
    ofSetBackgroundAuto(true);
    
    // bind & call function
    mScriptEngine.setup();
}

//--------------------------------------------------------------
void ScriptApp::update()
{
    mInput.update();
    mScriptEngine.funcallIf("update");
}

//--------------------------------------------------------------
void ScriptApp::draw()
{
    // for (int i = 0; i < 5; i++) {
    //     const rubykokuban::TouchPoint& tp = mInput.touch().point(i);

    //     if (tp.isValid()) {
    //         char buff[100];
    //         sprintf(buff, "i: %d, touch: x: %f, y: %f", i, tp.x(), tp.y());
    //         ofDrawBitmapString(buff, 0, 100 + i * 15);
    //     }
    // }

    mScriptEngine.draw();
    // ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ScriptApp::exit()
{
}

//--------------------------------------------------------------
void ScriptApp::touchDown(ofTouchEventArgs & touch)
{
    mInput.touch().touchDown(touch);
}

//--------------------------------------------------------------
void ScriptApp::touchMoved(ofTouchEventArgs & touch)
{
    mInput.touch().touchMoved(touch);
}

//--------------------------------------------------------------
void ScriptApp::touchUp(ofTouchEventArgs & touch)
{
    mInput.touch().touchUp(touch);
}

//--------------------------------------------------------------
void ScriptApp::touchDoubleTap(ofTouchEventArgs & touch)
{
}

//--------------------------------------------------------------
void ScriptApp::touchCancelled(ofTouchEventArgs & touch)
{
}

//--------------------------------------------------------------
void ScriptApp::lostFocus()
{
}

//--------------------------------------------------------------
void ScriptApp::gotFocus()
{
}

//--------------------------------------------------------------
void ScriptApp::gotMemoryWarning()
{
}

//--------------------------------------------------------------
void ScriptApp::deviceOrientationChanged(int newOrientation)
{
}

