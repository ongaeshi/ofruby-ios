#include "BindTouchPoint.hpp"

#include "mruby/value.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"
#include "rubykokuban/TouchPoint.hpp"

namespace rubykokuban {

namespace {
TouchPoint& obj(mrb_value self)
{
    return *((TouchPoint*)DATA_PTR(self));
}

// TouchPoint instance has C++
struct mrb_data_type data_type = { "rubykokuban_touch_point", NULL };

mrb_value x(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).x());
}

mrb_value y(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).y());
}

mrb_value valid_p(mrb_state *mrb, mrb_value self)
{
    return mrb_bool_value(obj(self).isValid());
}

mrb_value press_p(mrb_state *mrb, mrb_value self)
{
    return mrb_bool_value(obj(self).isPress());
}

mrb_value down_p(mrb_state *mrb, mrb_value self)
{
    return mrb_bool_value(obj(self).isDown());
}

mrb_value release_p(mrb_state *mrb, mrb_value self)
{
    return mrb_bool_value(obj(self).isRelease());
}

}

//----------------------------------------------------------
mrb_value BindTouchPoint::ToMrb(mrb_state* mrb, TouchPoint* aPtr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "TouchPoint"), aPtr);
}

//----------------------------------------------------------
mrb_value BindTouchPoint::ToMrb(mrb_state* mrb, struct RClass* aClass, TouchPoint* aPtr)
{
    struct RData *data = mrb_data_object_alloc(mrb, aClass, aPtr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
void BindTouchPoint::Bind(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "TouchPoint", mrb->object_class);

    mrb_define_method(mrb, cc,       "x"                 , x                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "y"                 , y                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "valid?"            , valid_p             , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "press?"            , press_p             , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "down?"             , down_p              , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "release?"          , release_p           , MRB_ARGS_NONE());
}

}
