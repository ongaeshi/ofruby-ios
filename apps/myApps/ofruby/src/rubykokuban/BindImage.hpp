#pragma once

#include "mruby.h"
#include "ofImage.h"

//----------------------------------------------------------
namespace rubykokuban {

class BindImage {
public:
    static mrb_value ToMrb(mrb_state* mrb, ofImage* aPtr);
    static mrb_value ToMrb(mrb_state* mrb, struct RClass* aClass, ofImage* aPtr);
    static ofImage* ToPtr(mrb_state* mrb, mrb_value aValue);
    static void Bind(mrb_state* mrb);
};

}
