#include "rubykokuban/BindInput.hpp"

#include "mruby.h"
#include "ofAppRunner.h"
#include "rubykokuban/Input.hpp"

namespace rubykokuban {
namespace {
    Input* sInput = NULL;

    static mrb_value input_mouse_x(mrb_state *mrb, mrb_value self)
    {
        return mrb_fixnum_value(sInput->mouse().x());
    }

    static mrb_value input_mouse_y(mrb_state *mrb, mrb_value self)
    {
        return mrb_fixnum_value(sInput->mouse().y());
    }

    static mrb_value input_mouse_is_press(mrb_state *mrb, mrb_value self)
    {
        mrb_int code;
        mrb_get_args(mrb, "i", &code);
        return mrb_bool_value(sInput->mouse().isPress(code));
    }

    static mrb_value input_mouse_is_down(mrb_state *mrb, mrb_value self)
    {
        mrb_int code;
        mrb_get_args(mrb, "i", &code);
        return mrb_bool_value(sInput->mouse().isDown(code));
    }

    static mrb_value input_mouse_is_release(mrb_state *mrb, mrb_value self)
    {
        mrb_int code;
        mrb_get_args(mrb, "i", &code);
        return mrb_bool_value(sInput->mouse().isRelease(code));
    }
}

//--------------------------------------------------------------------------------
void BindInput::Setup(::rubykokuban::Input& aInput)
{
    sInput = &aInput;
}

//--------------------------------------------------------------------------------
void BindInput::Bind(mrb_state* mrb)
{
    struct RClass* c = mrb_define_module(mrb, "Input");

    mrb_define_module_function(mrb, c, "mouse_x", input_mouse_x, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, c, "mouse_y", input_mouse_y, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, c, "mouse_press?", input_mouse_is_press, ARGS_REQ(1));
    mrb_define_module_function(mrb, c, "mouse_down?",  input_mouse_is_down,  ARGS_REQ(1));
    mrb_define_module_function(mrb, c, "mouse_release?",  input_mouse_is_release,  ARGS_REQ(1));
}

}
