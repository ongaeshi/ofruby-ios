#include "BindTouchPoint.hpp"

#include "mruby/value.h"

namespace rubykokuban {

namespace {
mrb_value x(mrb_state *mrb, mrb_value self)
{
    // return self;
    return mrb_nil_value();
}

mrb_value y(mrb_state *mrb, mrb_value self)
{
    // return self;
    return mrb_nil_value();
}

mrb_value valid_p(mrb_state *mrb, mrb_value self)
{
    // return self;
    return mrb_nil_value();
}

mrb_value inspect(mrb_state *mrb, mrb_value self)
{
    // return self;
    return mrb_nil_value();
}

}

void BindTouchPoint::Bind(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "TouchPoint", mrb->object_class);

    mrb_define_method(mrb, cc,       "x"                 , x                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "y"                 , y                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "valid?"            , valid_p             , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "inspect"           , inspect             , MRB_ARGS_NONE());
}

}
