#include "rubykokuban/Bind.hpp"

#include "mruby.h"
#include "mrubybind.h"
#include "ofAppRunner.h"

namespace rubykokuban {

namespace {
    float get_frame_rate() { return ofGetFrameRate(); }
    void set_window_pos(int x, int y) { ofSetWindowPosition(x, y); }
    void set_window_size(int width, int height) { ofSetWindowShape(width, height); }
    int window_pos_x() { return ofGetWindowPositionX(); }
    int window_pos_y() { return ofGetWindowPositionY(); }
    // int window_width() { return ofGetWidth(); }
    // int window_height() { return ofGetHeight(); }
    int window_width() { return ofGetWindowWidth(); }
    int window_height() { return ofGetWindowHeight(); }
    int screen_width() { return ofGetScreenWidth(); }
    int screen_height() { return ofGetScreenHeight(); }
}

//----------------------------------------------------------
void BindApplication(mrb_state* mrb)
{
    mrubybind::MrubyBind b(mrb);

    b.bind("get_frame_rate", get_frame_rate);
    b.bind("set_window_pos", set_window_pos);
    b.bind("set_window_size", set_window_size);
    b.bind("window_pos_x", window_pos_x);
    b.bind("window_pos_y", window_pos_y);
    b.bind("window_width", window_width);
    b.bind("window_height", window_height);
    b.bind("screen_width", screen_width);
    b.bind("screen_height", screen_height);
}

}
//EOF
