#pragma once

#include "mruby.h"
#include "ofColor.h"

//----------------------------------------------------------
namespace rubykokuban {

class BindColor {
public:
    static mrb_value ToMrb(mrb_state* mrb, ofColor* aPtr);
    static mrb_value ToMrb(mrb_state* mrb, struct RClass* aClass, ofColor* aPtr);
    static ofColor* ToPtr(mrb_state* mrb, mrb_value aValue);
    static ofColor* ToPtr(mrb_state* mrb, struct RClass* aClass, mrb_value aValue);
    static void Bind(mrb_state* mrb);
};

}
