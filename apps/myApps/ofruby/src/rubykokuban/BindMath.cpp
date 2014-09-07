#include "rubykokuban/Bind.hpp"

#include "mruby.h"
#include "mrubybind.h"
#include "ofMath.h"

namespace rubykokuban {

namespace {
mrb_value srand(mrb_state *mrb, mrb_value self)
{
    mrb_int seed;

    if (mrb_get_args(mrb, "|i", &seed) == 1) {
        ofSeedRandom(seed);
    } else {
        ofSeedRandom();
    }

    return mrb_nil_value();
}

mrb_value rand(mrb_state *mrb, mrb_value self)
{
    mrb_float max;
    
    if (mrb_get_args(mrb, "|f", &max) == 1) {
        return mrb_float_value(mrb, ofRandom(max));
    } else {
        return mrb_float_value(mrb, ofRandomuf());
    }
}

mrb_value noise(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, z;
    int num = mrb_get_args(mrb, "f|ff", &x, &y, &z);

    switch (num) {
        case 1:
            return mrb_float_value(mrb, ofNoise(x));
        case 2:
            return mrb_float_value(mrb, ofNoise(x, y));
        case 3:
            return mrb_float_value(mrb, ofNoise(x, y, z));
        default:
            return mrb_nil_value();
    }
}

}

//--------------------------------------------------------------------------------
void BindMath(mrb_state* mrb)
{
    mrb_define_module_function(mrb, mrb->kernel_module, "srand"             , srand               , MRB_ARGS_REQ(0));
    mrb_define_module_function(mrb, mrb->kernel_module, "rand"              , rand                , MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mrb->kernel_module, "noise"             , noise               , MRB_ARGS_ARG(1, 2));

}

}
