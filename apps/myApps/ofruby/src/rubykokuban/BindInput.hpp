#pragma once

#include "mruby.h"
#include "rubykokuban/Input.hpp"

//----------------------------------------------------------
namespace rubykokuban {

class BindInput {
public:
    static void Setup(Input& aInput);
    static void Bind(mrb_state* mrb);
};

}
