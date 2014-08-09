#include "ofMain.h"
#include "ofAppiOSWindow.h"

int main(int argc, char *argv[]) {
    ofAppiOSWindow *window = new ofAppiOSWindow();
    ofSetupOpenGL(ofPtr<ofAppBaseWindow>(window), 1024,768, OF_FULLSCREEN);
    window->startAppWithDelegate("AppDelegate");
}
