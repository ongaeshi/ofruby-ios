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
	
    ofSetColor(0, 0, 0);

	// ofBackground(127,127,127);
	ofBackground(255, 255, 255);

    ofSetCircleResolution(32);
    
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
}

//--------------------------------------------------------------
void ScriptApp::touchMoved(ofTouchEventArgs & touch)
{
}

//--------------------------------------------------------------
void ScriptApp::touchUp(ofTouchEventArgs & touch)
{
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

