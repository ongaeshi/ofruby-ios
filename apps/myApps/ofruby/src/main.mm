#include "ofMain.h"
#include "ofApp.h"

int main(int argc, char *argv[]) {
    ofAppiOSWindow *window = new ofAppiOSWindow();
    ofSetupOpenGL(ofPtr<ofAppBaseWindow>(window), 1024,768, OF_FULLSCREEN);
    window->startAppWithDelegate("SampleAppDelegate");
}
