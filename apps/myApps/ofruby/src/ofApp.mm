#include "ofApp.h"

//--------------------------------------------------------------
ofApp::ofApp()
{
    NSString *filePath = [[NSBundle mainBundle] pathForResource:@"hello" ofType:@"rb"];
    NSLog(@"filePath = %@", filePath);
    char* scriptPath = (char *)[filePath UTF8String];

    mScriptApp = new ScriptApp(scriptPath);
}


//--------------------------------------------------------------
void ofApp::setup(){
    mScriptApp->setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    mScriptApp->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	mScriptApp->draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::touchDown(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchMoved(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchUp(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchDoubleTap(ofTouchEventArgs & touch){

}

//--------------------------------------------------------------
void ofApp::touchCancelled(ofTouchEventArgs & touch){
    
}

//--------------------------------------------------------------
void ofApp::lostFocus(){

}

//--------------------------------------------------------------
void ofApp::gotFocus(){

}

//--------------------------------------------------------------
void ofApp::gotMemoryWarning(){

}

//--------------------------------------------------------------
void ofApp::deviceOrientationChanged(int newOrientation){

}
