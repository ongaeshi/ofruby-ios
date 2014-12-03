#include "ofMain.h"
#include "ofAppiOSWindow.h"

extern "C" {
    size_t fwrite$UNIX2003( const void *a, size_t b, size_t c, FILE *d )
    {
        return fwrite(a, b, c, d);
    }
    char* strerror$UNIX2003( int errnum )
    {
        return strerror(errnum);
    }
    time_t mktime$UNIX2003(struct tm * a)
    {
        return mktime(a);
    }
    double strtod$UNIX2003(const char * a, char ** b) {
        return strtod(a, b);
    }
}

int main(int argc, char *argv[]) {
    ofAppiOSWindow *window = new ofAppiOSWindow();
    ofSetupOpenGL(ofPtr<ofAppBaseWindow>(window), 1024,768, OF_FULLSCREEN);
    window->startAppWithDelegate("AppDelegate");
}
