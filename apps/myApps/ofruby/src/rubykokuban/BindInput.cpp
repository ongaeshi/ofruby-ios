#include "rubykokuban/BindInput.hpp"

#include "mruby.h"
#include "mruby/array.h"
#include "mruby/variable.h"
#include "ofAppRunner.h"
#include "rubykokuban/Input.hpp"
#include "rubykokuban/Touch.hpp"
#include "rubykokuban/BindTouchPoint.hpp"

namespace rubykokuban {
namespace {
Input* sInput = NULL;

mrb_value input_mouse_x(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(sInput->mouse().x());
}

mrb_value input_mouse_y(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(sInput->mouse().y());
}

mrb_value input_mouse_is_press(mrb_state *mrb, mrb_value self)
{
    mrb_int code;
    mrb_get_args(mrb, "i", &code);
    return mrb_bool_value(sInput->mouse().isPress(code));
}

mrb_value input_mouse_is_down(mrb_state *mrb, mrb_value self)
{
    mrb_int code;
    mrb_get_args(mrb, "i", &code);
    return mrb_bool_value(sInput->mouse().isDown(code));
}

mrb_value input_mouse_is_release(mrb_state *mrb, mrb_value self)
{
    mrb_int code;
    mrb_get_args(mrb, "i", &code);
    return mrb_bool_value(sInput->mouse().isRelease(code));
}

mrb_value touch(mrb_state *mrb, mrb_value self)
{
    mrb_int index;
    mrb_get_args(mrb, "i", &index);
    mrb_value array = mrb_cv_get(mrb, self, mrb_intern(mrb, "touch"));
    return mrb_ary_ref(mrb, array, index);
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
    // Bind the classes necessary to first
    BindTouchPoint::Bind(mrb);

    // Main
    struct RClass* c = mrb_define_module(mrb, "Input");

    mrb_define_module_function(mrb, c, "mouse_x", input_mouse_x, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, c, "mouse_y", input_mouse_y, MRB_ARGS_NONE());
    mrb_define_module_function(mrb, c, "mouse_press?", input_mouse_is_press, ARGS_REQ(1));
    mrb_define_module_function(mrb, c, "mouse_down?",  input_mouse_is_down,  ARGS_REQ(1));
    mrb_define_module_function(mrb, c, "mouse_release?",  input_mouse_is_release,  ARGS_REQ(1));
    mrb_define_module_function(mrb, c, "touch", touch, ARGS_REQ(1));

    // @@touch
    mrb_value array = mrb_ary_new(mrb);
    for (int i = 0; i < Touch::TOUCH_POINT_MAX; i++) {
        mrb_ary_push(mrb, array, BindTouchPoint::ToMrb(mrb, &sInput->touch().point(i)));
    }
    mrb_mod_cv_set(mrb, c, mrb_intern(mrb, "touch"), array);
}

}
