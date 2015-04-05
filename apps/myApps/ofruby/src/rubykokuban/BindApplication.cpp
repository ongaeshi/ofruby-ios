#include "rubykokuban/Bind.hpp"

#include "mruby.h"
#include "mruby/value.h"
#include "ofAppRunner.h"

namespace rubykokuban {

namespace {
mrb_value frame_rate(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, ofGetFrameRate());
}

mrb_value set_window_pos(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_get_args(mrb, "ii", &x, &y);
    
    ofSetWindowPosition(x, y);
    
    return mrb_nil_value();
}

mrb_value set_window_size(mrb_state *mrb, mrb_value self)
{
    mrb_int width, height;
    mrb_get_args(mrb, "ii", &width, &height);

    ofSetWindowShape(width, height);
    
    return mrb_nil_value();
}

mrb_value window_pos_x(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetWindowPositionX());
}

mrb_value window_pos_y(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetWindowPositionY());
}

mrb_value window_width(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetWindowWidth());
}

mrb_value window_height(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetWindowHeight());
}

mrb_value screen_width(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetScreenWidth());
}

mrb_value screen_height(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetScreenHeight());
}

mrb_value width(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetWidth());
}

mrb_value height(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(ofGetHeight());
}

}

//----------------------------------------------------------
void BindApplication(mrb_state* mrb)
{
    mrb_define_module_function(mrb, mrb->kernel_module, "frame_rate"        , frame_rate          , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "set_window_pos"    , set_window_pos      , MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb->kernel_module, "set_window_size"   , set_window_size     , MRB_ARGS_REQ(2));
    mrb_define_module_function(mrb, mrb->kernel_module, "window_pos_x"      , window_pos_x        , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "window_pos_y"      , window_pos_y        , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "window_width"      , window_width        , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "window_height"     , window_height       , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "screen_width"      , screen_width        , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "screen_height"     , screen_height       , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "width"             , width               , MRB_ARGS_NONE());
    mrb_define_module_function(mrb, mrb->kernel_module, "height"            , height              , MRB_ARGS_NONE());
}

}
//EOF
