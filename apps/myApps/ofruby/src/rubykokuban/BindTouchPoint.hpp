#pragma once

#include "mruby.h"

//----------------------------------------------------------
namespace rubykokuban {

class BindTouchPoint {
public:
    static void Bind(mrb_state* mrb);
};

}
