#pragma once

#include "mruby.h"

namespace rubykokuban {
    class TouchPoint;
}

//----------------------------------------------------------
namespace rubykokuban {

class BindTouchPoint {
public:
    static mrb_value ToMrb(mrb_state* mrb, TouchPoint* aPtr);
    static mrb_value ToMrb(mrb_state* mrb, struct RClass* aClass, TouchPoint* aPtr);
    static void Bind(mrb_state* mrb);
};

}
