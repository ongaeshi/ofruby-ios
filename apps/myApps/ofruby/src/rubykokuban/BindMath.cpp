#include "rubykokuban/Bind.hpp"

#include "mruby.h"
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

mrb_value dist(mrb_state *mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2;
    mrb_get_args(mrb, "ffff", &x1, &y1, &x2, &y2);
    return mrb_float_value(mrb, ofDist(x1, y1, x2, y2));
}

mrb_value dist_squared(mrb_state *mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2;
    mrb_get_args(mrb, "ffff", &x1, &y1, &x2, &y2);
    return mrb_float_value(mrb, ofDistSquared(x1, y1, x2, y2));
}

mrb_value clamp(mrb_state *mrb, mrb_value self)
{
    mrb_float value, min, max;
    mrb_get_args(mrb, "fff", &value, &min, &max);
    return mrb_float_value(mrb, ofClamp(value, min, max));
}

// mrb_value normalize(mrb_state *mrb, mrb_value self)
// {
//     mrb_float value, min, max;
//     mrb_get_args(mrb, "fff", &value, &min, &max);
//     return mrb_float_value(mrb, ofNormalize(value, min, max));
// }

mrb_value rad_to_deg(mrb_state *mrb, mrb_value self)
{
    mrb_float radians;
    mrb_get_args(mrb, "f", &radians);
    return mrb_float_value(mrb, ofRadToDeg(radians));
}

mrb_value deg_to_rad(mrb_state *mrb, mrb_value self)
{
    mrb_float degrees;
    mrb_get_args(mrb, "f", &degrees);
    return mrb_float_value(mrb, ofDegToRad(degrees));
}

mrb_value lerp(mrb_state *mrb, mrb_value self)
{
    mrb_float start, stop, amt;
    mrb_get_args(mrb, "fff", &start, &stop, &amt);
    return mrb_float_value(mrb, ofLerp(start, stop, amt));
}

}

//--------------------------------------------------------------------------------
void BindMath(mrb_state* mrb)
{
    mrb_define_module_function(mrb, mrb->kernel_module, "srand"             , srand               , MRB_ARGS_REQ(0));
    mrb_define_module_function(mrb, mrb->kernel_module, "rand"              , rand                , MRB_ARGS_OPT(1));
    mrb_define_module_function(mrb, mrb->kernel_module, "noise"             , noise               , MRB_ARGS_ARG(1, 2));
    mrb_define_module_function(mrb, mrb->kernel_module, "dist"              , dist                , MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mrb->kernel_module, "dist_squared"      , dist_squared        , MRB_ARGS_REQ(4));
    mrb_define_module_function(mrb, mrb->kernel_module, "clamp"             , clamp               , MRB_ARGS_REQ(3));
    // mrb_define_module_function(mrb, mrb->kernel_module, "normalize"         , normalize           , MRB_ARGS_REQ(3));
    mrb_define_module_function(mrb, mrb->kernel_module, "rad_to_deg"        , rad_to_deg          , MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb->kernel_module, "deg_to_rad"        , deg_to_rad          , MRB_ARGS_REQ(1));
    mrb_define_module_function(mrb, mrb->kernel_module, "lerp"              , lerp                , MRB_ARGS_REQ(3));

}

}
