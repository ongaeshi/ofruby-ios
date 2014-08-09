#include "rubykokuban/BindColor.hpp"

#include "mruby/array.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/value.h"
#include "ofColor.h"

namespace rubykokuban {

namespace {
ofColor& obj(mrb_value self)
{
    return *((ofColor*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((ofColor*)p);
    }
}

struct mrb_data_type data_type = { "rubykokuban_color", free };

float LIMIT = 255.0f;

mrb_value initialize(mrb_state *mrb, mrb_value self)
{
    mrb_int r, g, b, a = LIMIT;
    mrb_get_args(mrb, "iii|i", &r, &g, &b, &a);

    ofColor* obj = new ofColor(r, g, b, a);

    return BindColor::ToMrb(mrb, mrb_class_ptr(self), obj);
}

mrb_value hex(mrb_state *mrb, mrb_value self)
{
    mrb_int h;
    mrb_float a = LIMIT;
    mrb_get_args(mrb, "i|f", &h, &a);

    ofColor* obj = new ofColor(ofColor::fromHex(h, a));

    return BindColor::ToMrb(mrb, mrb_class_ptr(self), obj);
}

mrb_value hsb(mrb_state *mrb, mrb_value self)
{
    mrb_float hue, saturation, brightness, alpha = LIMIT;
    mrb_get_args(mrb, "fff|f", &hue, &saturation, &brightness, &alpha);

    ofColor* obj = new ofColor(ofColor::fromHsb(hue, saturation, brightness, alpha));

    return BindColor::ToMrb(mrb, mrb_class_ptr(self), obj);
}

mrb_value r(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).r);
}

mrb_value r_set(mrb_state *mrb, mrb_value self)
{
    mrb_int r;
    mrb_get_args(mrb, "i", &r);
    obj(self).r = r;
    return mrb_nil_value();
}

mrb_value g(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).g);
}

mrb_value g_set(mrb_state *mrb, mrb_value self)
{
    mrb_int g;
    mrb_get_args(mrb, "i", &g);
    obj(self).g = g;
    return mrb_nil_value();
}

mrb_value b(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).b);
}

mrb_value b_set(mrb_state *mrb, mrb_value self)
{
    mrb_int b;
    mrb_get_args(mrb, "i", &b);
    obj(self).b = b;
    return mrb_nil_value();
}

mrb_value a(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).a);
}

mrb_value a_set(mrb_state *mrb, mrb_value self)
{
    mrb_int a;
    mrb_get_args(mrb, "i", &a);
    obj(self).a = a;
    return mrb_nil_value();
}

mrb_value clone(mrb_state *mrb, mrb_value self)
{
    return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self)));
}

mrb_value set(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    switch (argc) {
    case 1:
        // set(color)
        obj(self).set(*BindColor::ToPtr(mrb, mrb_obj_class(mrb, self), argv[0]));
        break;
    case 3:
        // set(r, g, b)
        obj(self).set(
            mrb_fixnum(mrb_Integer(mrb, argv[0]))
            , mrb_fixnum(mrb_Integer(mrb, argv[1]))
            , mrb_fixnum(mrb_Integer(mrb, argv[2]))
            );
        break;
    case 4:
        // set(r, g, b, a)
        obj(self).set(
            mrb_fixnum(mrb_Integer(mrb, argv[0]))
            , mrb_fixnum(mrb_Integer(mrb, argv[1]))
            , mrb_fixnum(mrb_Integer(mrb, argv[2]))
            , mrb_fixnum(mrb_Integer(mrb, argv[3]))
            );
        break;
    default:
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
        break;
    }

    return mrb_nil_value();
}

mrb_value to_hex(mrb_state *mrb, mrb_value self)
{
    return mrb_fixnum_value(obj(self).getHex());
}

mrb_value set_hex(mrb_state *mrb, mrb_value self)
{
    mrb_int hex;
    mrb_float alpha = LIMIT;
    mrb_get_args(mrb, "i|f", &hex, &alpha);
    obj(self).setHex(hex, alpha);
    return mrb_nil_value();
}

mrb_value clamp(mrb_state *mrb, mrb_value self)
{
    return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self).getClamped()));
}

mrb_value invert(mrb_state *mrb, mrb_value self)
{
    return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self).getInverted()));
}

mrb_value normalize(mrb_state *mrb, mrb_value self)
{
    return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self).getNormalized()));
}

mrb_value lerp(mrb_state *mrb, mrb_value self)
{
    mrb_value targetValue;
    mrb_float amount;
    mrb_get_args(mrb, "of", &targetValue, &amount);
    ofColor& target = *BindColor::ToPtr(mrb, targetValue);

    return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self).getLerped(target, amount)));
}

mrb_value hue(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, obj(self).getHue());
}

mrb_value saturation(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, obj(self).getSaturation());
}

mrb_value brightness(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, obj(self).getBrightness());
}

mrb_value lightness(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, obj(self).getLightness());
}

mrb_value to_hsb(mrb_state *mrb, mrb_value self)
{
    float hue, saturation, brightness; // Because can't use mrb_float
    obj(self).getHsb(hue, saturation, brightness); 

    mrb_value array = mrb_ary_new(mrb);
    mrb_ary_push(mrb, array, mrb_float_value(mrb, hue));
    mrb_ary_push(mrb, array, mrb_float_value(mrb, saturation));
    mrb_ary_push(mrb, array, mrb_float_value(mrb, brightness));
    
    return array;
}

mrb_value hue_set(mrb_state *mrb, mrb_value self)
{
    mrb_float value;
    mrb_get_args(mrb, "f", &value);
    obj(self).setHue(value);
    return mrb_nil_value();
}

mrb_value saturation_set(mrb_state *mrb, mrb_value self)
{
    mrb_float value;
    mrb_get_args(mrb, "f", &value);
    obj(self).setSaturation(value);
    return mrb_nil_value();
}

mrb_value brightness_set(mrb_state *mrb, mrb_value self)
{
    mrb_float value;
    mrb_get_args(mrb, "f", &value);
    obj(self).setBrightness(value);
    return mrb_nil_value();
}

mrb_value set_hsb(mrb_state *mrb, mrb_value self)
{
    mrb_float hue, saturation, brightness, alpha = LIMIT;
    mrb_get_args(mrb, "fff|f", &hue, &saturation, &brightness, &alpha);
    obj(self).setHsb(hue, saturation, brightness, alpha);
    return mrb_nil_value();
}

mrb_value equal(mrb_state *mrb, mrb_value self)
{
    mrb_value targetValue;
    mrb_get_args(mrb, "o", &targetValue);
    ofColor& target = *BindColor::ToPtr(mrb, targetValue);

    return mrb_bool_value(obj(self) == target);
}

mrb_value add(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    if (argc != 1) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
    }

    if (mrb_obj_is_instance_of(mrb, argv[0], mrb_obj_class(mrb, self))) {
        ofColor& target = *static_cast<ofColor*>(DATA_PTR(argv[0]));
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) + target));

    } else {
        mrb_value value = mrb_Float(mrb, argv[0]);
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) + mrb_float(value)));
    }
}

mrb_value sub(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    if (argc != 1) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
    }

    if (mrb_obj_is_instance_of(mrb, argv[0], mrb_obj_class(mrb, self))) {
        ofColor& target = *static_cast<ofColor*>(DATA_PTR(argv[0]));
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) - target));

    } else {
        mrb_value value = mrb_Float(mrb, argv[0]);
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) - mrb_float(value)));
    }
}

mrb_value mul(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    if (argc != 1) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
    }

    if (mrb_obj_is_instance_of(mrb, argv[0], mrb_obj_class(mrb, self))) {
        ofColor& target = *static_cast<ofColor*>(DATA_PTR(argv[0]));
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) * target));

    } else {
        mrb_value value = mrb_Float(mrb, argv[0]);
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) * mrb_float(value)));
    }
}

mrb_value div(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    if (argc != 1) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
    }

    if (mrb_obj_is_instance_of(mrb, argv[0], mrb_obj_class(mrb, self))) {
        ofColor& target = *static_cast<ofColor*>(DATA_PTR(argv[0]));
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) / target));

    } else {
        mrb_value value = mrb_Float(mrb, argv[0]);
        return BindColor::ToMrb(mrb, mrb_obj_class(mrb, self), new ofColor(obj(self) / mrb_float(value)));
    }
}

mrb_value aref(mrb_state *mrb, mrb_value self)
{
    mrb_int n;
    mrb_get_args(mrb, "i", &n);

    return mrb_fixnum_value(obj(self)[n]);
}

mrb_value aref_set(mrb_state *mrb, mrb_value self)
{
    mrb_int n, value;
    mrb_get_args(mrb, "ii", &n, &value);

    obj(self)[n] = value;

    return mrb_nil_value();
}

mrb_value inspect(mrb_state *mrb, mrb_value self)
{
    char buff[30];

    if (obj(self).a == LIMIT)
        sprintf(buff, "(%d,%d,%d)", obj(self).r, obj(self).g, obj(self).b);
    else
        sprintf(buff, "(%d,%d,%d,%d)", obj(self).r, obj(self).g, obj(self).b, obj(self).a);
        
    return mrb_str_new_cstr(mrb, buff);
}

}

//----------------------------------------------------------
mrb_value BindColor::ToMrb(mrb_state* mrb, ofColor* aPtr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "Color"), aPtr);
}

//----------------------------------------------------------
mrb_value BindColor::ToMrb(mrb_state* mrb, struct RClass* aClass, ofColor* aPtr)
{
    struct RData *data = mrb_data_object_alloc(mrb, aClass, aPtr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
ofColor* BindColor::ToPtr(mrb_state* mrb, mrb_value aValue)
{
    return ToPtr(mrb, mrb_class_get(mrb, "Color"), aValue);
}

//----------------------------------------------------------
ofColor* BindColor::ToPtr(mrb_state* mrb, struct RClass* aClass, mrb_value aValue)
{
    if (!mrb_obj_is_instance_of(mrb, aValue, aClass)) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<ofColor*>(DATA_PTR(aValue));
}

//----------------------------------------------------------
void BindColor::Bind(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Color", mrb->object_class);

    mrb_define_class_method(mrb, cc, "new"               , initialize          , MRB_ARGS_ARG(3, 1));
    mrb_define_class_method(mrb, cc, "hex"               , hex                 , MRB_ARGS_ARG(1, 1));
    mrb_define_class_method(mrb, cc, "hsb"               , hsb                 , MRB_ARGS_ARG(3, 1));

    int ai = mrb_gc_arena_save(mrb);
    mrb_define_const(mrb, cc, "White"                , ToMrb(mrb, cc, new ofColor(ofColor::white)));
    mrb_define_const(mrb, cc, "Gray"                 , ToMrb(mrb, cc, new ofColor(ofColor::gray)));
    mrb_define_const(mrb, cc, "Black"                , ToMrb(mrb, cc, new ofColor(ofColor::black)));
    mrb_define_const(mrb, cc, "Red"                  , ToMrb(mrb, cc, new ofColor(ofColor::red)));
    mrb_define_const(mrb, cc, "Green"                , ToMrb(mrb, cc, new ofColor(ofColor::green)));
    mrb_define_const(mrb, cc, "Blue"                 , ToMrb(mrb, cc, new ofColor(ofColor::blue)));
    mrb_define_const(mrb, cc, "Cyan"                 , ToMrb(mrb, cc, new ofColor(ofColor::cyan)));
    mrb_define_const(mrb, cc, "Magenta"              , ToMrb(mrb, cc, new ofColor(ofColor::magenta)));
    mrb_define_const(mrb, cc, "Yellow"               , ToMrb(mrb, cc, new ofColor(ofColor::yellow)));
    mrb_define_const(mrb, cc, "AliceBlue"            , ToMrb(mrb, cc, new ofColor(ofColor::aliceBlue)));
    mrb_define_const(mrb, cc, "AntiqueWhite"         , ToMrb(mrb, cc, new ofColor(ofColor::antiqueWhite)));
    mrb_define_const(mrb, cc, "Aqua"                 , ToMrb(mrb, cc, new ofColor(ofColor::aqua)));
    mrb_define_const(mrb, cc, "Aquamarine"           , ToMrb(mrb, cc, new ofColor(ofColor::aquamarine)));
    mrb_define_const(mrb, cc, "Azure"                , ToMrb(mrb, cc, new ofColor(ofColor::azure)));
    mrb_define_const(mrb, cc, "Beige"                , ToMrb(mrb, cc, new ofColor(ofColor::beige)));
    mrb_define_const(mrb, cc, "Bisque"               , ToMrb(mrb, cc, new ofColor(ofColor::bisque)));
    mrb_define_const(mrb, cc, "BlanchedAlmond"       , ToMrb(mrb, cc, new ofColor(ofColor::blanchedAlmond)));
    mrb_define_const(mrb, cc, "BlueViolet"           , ToMrb(mrb, cc, new ofColor(ofColor::blueViolet)));
    mrb_define_const(mrb, cc, "Brown"                , ToMrb(mrb, cc, new ofColor(ofColor::brown)));
    mrb_define_const(mrb, cc, "BurlyWood"            , ToMrb(mrb, cc, new ofColor(ofColor::burlyWood)));
    mrb_define_const(mrb, cc, "CadetBlue"            , ToMrb(mrb, cc, new ofColor(ofColor::cadetBlue)));
    mrb_define_const(mrb, cc, "Chartreuse"           , ToMrb(mrb, cc, new ofColor(ofColor::chartreuse)));
    mrb_define_const(mrb, cc, "Chocolate"            , ToMrb(mrb, cc, new ofColor(ofColor::chocolate)));
    mrb_define_const(mrb, cc, "Coral"                , ToMrb(mrb, cc, new ofColor(ofColor::coral)));
    mrb_define_const(mrb, cc, "CornflowerBlue"       , ToMrb(mrb, cc, new ofColor(ofColor::cornflowerBlue)));
    mrb_define_const(mrb, cc, "Cornsilk"             , ToMrb(mrb, cc, new ofColor(ofColor::cornsilk)));
    mrb_define_const(mrb, cc, "Crimson"              , ToMrb(mrb, cc, new ofColor(ofColor::crimson)));
    mrb_define_const(mrb, cc, "DarkBlue"             , ToMrb(mrb, cc, new ofColor(ofColor::darkBlue)));
    mrb_define_const(mrb, cc, "DarkCyan"             , ToMrb(mrb, cc, new ofColor(ofColor::darkCyan)));
    mrb_define_const(mrb, cc, "DarkGoldenRod"        , ToMrb(mrb, cc, new ofColor(ofColor::darkGoldenRod)));
    mrb_define_const(mrb, cc, "DarkGray"             , ToMrb(mrb, cc, new ofColor(ofColor::darkGray)));
    mrb_define_const(mrb, cc, "DarkGrey"             , ToMrb(mrb, cc, new ofColor(ofColor::darkGrey)));
    mrb_define_const(mrb, cc, "DarkGreen"            , ToMrb(mrb, cc, new ofColor(ofColor::darkGreen)));
    mrb_define_const(mrb, cc, "DarkKhaki"            , ToMrb(mrb, cc, new ofColor(ofColor::darkKhaki)));
    mrb_define_const(mrb, cc, "DarkMagenta"          , ToMrb(mrb, cc, new ofColor(ofColor::darkMagenta)));
    mrb_define_const(mrb, cc, "DarkOliveGreen"       , ToMrb(mrb, cc, new ofColor(ofColor::darkOliveGreen)));
    mrb_define_const(mrb, cc, "Darkorange"           , ToMrb(mrb, cc, new ofColor(ofColor::darkorange)));
    mrb_define_const(mrb, cc, "DarkOrchid"           , ToMrb(mrb, cc, new ofColor(ofColor::darkOrchid)));
    mrb_define_const(mrb, cc, "DarkRed"              , ToMrb(mrb, cc, new ofColor(ofColor::darkRed)));
    mrb_define_const(mrb, cc, "DarkSalmon"           , ToMrb(mrb, cc, new ofColor(ofColor::darkSalmon)));
    mrb_define_const(mrb, cc, "DarkSeaGreen"         , ToMrb(mrb, cc, new ofColor(ofColor::darkSeaGreen)));
    mrb_define_const(mrb, cc, "DarkSlateBlue"        , ToMrb(mrb, cc, new ofColor(ofColor::darkSlateBlue)));
    mrb_define_const(mrb, cc, "DarkSlateGray"        , ToMrb(mrb, cc, new ofColor(ofColor::darkSlateGray)));
    mrb_define_const(mrb, cc, "DarkSlateGrey"        , ToMrb(mrb, cc, new ofColor(ofColor::darkSlateGrey)));
    mrb_define_const(mrb, cc, "DarkTurquoise"        , ToMrb(mrb, cc, new ofColor(ofColor::darkTurquoise)));
    mrb_define_const(mrb, cc, "DarkViolet"           , ToMrb(mrb, cc, new ofColor(ofColor::darkViolet)));
    mrb_define_const(mrb, cc, "DeepPink"             , ToMrb(mrb, cc, new ofColor(ofColor::deepPink)));
    mrb_define_const(mrb, cc, "DeepSkyBlue"          , ToMrb(mrb, cc, new ofColor(ofColor::deepSkyBlue)));
    mrb_define_const(mrb, cc, "DimGray"              , ToMrb(mrb, cc, new ofColor(ofColor::dimGray)));
    mrb_define_const(mrb, cc, "DimGrey"              , ToMrb(mrb, cc, new ofColor(ofColor::dimGrey)));
    mrb_define_const(mrb, cc, "DodgerBlue"           , ToMrb(mrb, cc, new ofColor(ofColor::dodgerBlue)));
    mrb_gc_arena_restore(mrb, ai);
    mrb_define_const(mrb, cc, "FireBrick"            , ToMrb(mrb, cc, new ofColor(ofColor::fireBrick)));
    mrb_define_const(mrb, cc, "FloralWhite"          , ToMrb(mrb, cc, new ofColor(ofColor::floralWhite)));
    mrb_define_const(mrb, cc, "ForestGreen"          , ToMrb(mrb, cc, new ofColor(ofColor::forestGreen)));
    mrb_define_const(mrb, cc, "Fuchsia"              , ToMrb(mrb, cc, new ofColor(ofColor::fuchsia)));
    mrb_define_const(mrb, cc, "Gainsboro"            , ToMrb(mrb, cc, new ofColor(ofColor::gainsboro)));
    mrb_define_const(mrb, cc, "GhostWhite"           , ToMrb(mrb, cc, new ofColor(ofColor::ghostWhite)));
    mrb_define_const(mrb, cc, "Gold"                 , ToMrb(mrb, cc, new ofColor(ofColor::gold)));
    mrb_define_const(mrb, cc, "GoldenRod"            , ToMrb(mrb, cc, new ofColor(ofColor::goldenRod)));
    mrb_define_const(mrb, cc, "Grey"                 , ToMrb(mrb, cc, new ofColor(ofColor::grey)));
    mrb_define_const(mrb, cc, "GreenYellow"          , ToMrb(mrb, cc, new ofColor(ofColor::greenYellow)));
    mrb_define_const(mrb, cc, "HoneyDew"             , ToMrb(mrb, cc, new ofColor(ofColor::honeyDew)));
    mrb_define_const(mrb, cc, "HotPink"              , ToMrb(mrb, cc, new ofColor(ofColor::hotPink)));
    mrb_define_const(mrb, cc, "IndianRed"            , ToMrb(mrb, cc, new ofColor(ofColor::indianRed)));
    mrb_define_const(mrb, cc, "Indigo"               , ToMrb(mrb, cc, new ofColor(ofColor::indigo)));
    mrb_define_const(mrb, cc, "Ivory"                , ToMrb(mrb, cc, new ofColor(ofColor::ivory)));
    mrb_define_const(mrb, cc, "Khaki"                , ToMrb(mrb, cc, new ofColor(ofColor::khaki)));
    mrb_define_const(mrb, cc, "Lavender"             , ToMrb(mrb, cc, new ofColor(ofColor::lavender)));
    mrb_define_const(mrb, cc, "LavenderBlush"        , ToMrb(mrb, cc, new ofColor(ofColor::lavenderBlush)));
    mrb_define_const(mrb, cc, "LawnGreen"            , ToMrb(mrb, cc, new ofColor(ofColor::lawnGreen)));
    mrb_define_const(mrb, cc, "LemonChiffon"         , ToMrb(mrb, cc, new ofColor(ofColor::lemonChiffon)));
    mrb_define_const(mrb, cc, "LightBlue"            , ToMrb(mrb, cc, new ofColor(ofColor::lightBlue)));
    mrb_define_const(mrb, cc, "LightCoral"           , ToMrb(mrb, cc, new ofColor(ofColor::lightCoral)));
    mrb_define_const(mrb, cc, "LightCyan"            , ToMrb(mrb, cc, new ofColor(ofColor::lightCyan)));
    mrb_define_const(mrb, cc, "LightGoldenRodYellow" , ToMrb(mrb, cc, new ofColor(ofColor::lightGoldenRodYellow)));
    mrb_define_const(mrb, cc, "LightGray"            , ToMrb(mrb, cc, new ofColor(ofColor::lightGray)));
    mrb_define_const(mrb, cc, "LightGrey"            , ToMrb(mrb, cc, new ofColor(ofColor::lightGrey)));
    mrb_define_const(mrb, cc, "LightGreen"           , ToMrb(mrb, cc, new ofColor(ofColor::lightGreen)));
    mrb_define_const(mrb, cc, "LightPink"            , ToMrb(mrb, cc, new ofColor(ofColor::lightPink)));
    mrb_define_const(mrb, cc, "LightSalmon"          , ToMrb(mrb, cc, new ofColor(ofColor::lightSalmon)));
    mrb_define_const(mrb, cc, "LightSeaGreen"        , ToMrb(mrb, cc, new ofColor(ofColor::lightSeaGreen)));
    mrb_define_const(mrb, cc, "LightSkyBlue"         , ToMrb(mrb, cc, new ofColor(ofColor::lightSkyBlue)));
    mrb_define_const(mrb, cc, "LightSlateGray"       , ToMrb(mrb, cc, new ofColor(ofColor::lightSlateGray)));
    mrb_define_const(mrb, cc, "LightSlateGrey"       , ToMrb(mrb, cc, new ofColor(ofColor::lightSlateGrey)));
    mrb_define_const(mrb, cc, "LightSteelBlue"       , ToMrb(mrb, cc, new ofColor(ofColor::lightSteelBlue)));
    mrb_define_const(mrb, cc, "LightYellow"          , ToMrb(mrb, cc, new ofColor(ofColor::lightYellow)));
    mrb_define_const(mrb, cc, "Lime"                 , ToMrb(mrb, cc, new ofColor(ofColor::lime)));
    mrb_define_const(mrb, cc, "LimeGreen"            , ToMrb(mrb, cc, new ofColor(ofColor::limeGreen)));
    mrb_define_const(mrb, cc, "Linen"                , ToMrb(mrb, cc, new ofColor(ofColor::linen)));
    mrb_define_const(mrb, cc, "Maroon"               , ToMrb(mrb, cc, new ofColor(ofColor::maroon)));
    mrb_define_const(mrb, cc, "MediumAquaMarine"     , ToMrb(mrb, cc, new ofColor(ofColor::mediumAquaMarine)));
    mrb_define_const(mrb, cc, "MediumBlue"           , ToMrb(mrb, cc, new ofColor(ofColor::mediumBlue)));
    mrb_define_const(mrb, cc, "MediumOrchid"         , ToMrb(mrb, cc, new ofColor(ofColor::mediumOrchid)));
    mrb_define_const(mrb, cc, "MediumPurple"         , ToMrb(mrb, cc, new ofColor(ofColor::mediumPurple)));
    mrb_define_const(mrb, cc, "MediumSeaGreen"       , ToMrb(mrb, cc, new ofColor(ofColor::mediumSeaGreen)));
    mrb_define_const(mrb, cc, "MediumSlateBlue"      , ToMrb(mrb, cc, new ofColor(ofColor::mediumSlateBlue)));
    mrb_define_const(mrb, cc, "MediumSpringGreen"    , ToMrb(mrb, cc, new ofColor(ofColor::mediumSpringGreen)));
    mrb_define_const(mrb, cc, "MediumTurquoise"      , ToMrb(mrb, cc, new ofColor(ofColor::mediumTurquoise)));
    mrb_define_const(mrb, cc, "MediumVioletRed"      , ToMrb(mrb, cc, new ofColor(ofColor::mediumVioletRed)));
    mrb_define_const(mrb, cc, "MidnightBlue"         , ToMrb(mrb, cc, new ofColor(ofColor::midnightBlue)));
    mrb_define_const(mrb, cc, "MintCream"            , ToMrb(mrb, cc, new ofColor(ofColor::mintCream)));
    mrb_gc_arena_restore(mrb, ai);
    mrb_define_const(mrb, cc, "MistyRose"            , ToMrb(mrb, cc, new ofColor(ofColor::mistyRose)));
    mrb_define_const(mrb, cc, "Moccasin"             , ToMrb(mrb, cc, new ofColor(ofColor::moccasin)));
    mrb_define_const(mrb, cc, "NavajoWhite"          , ToMrb(mrb, cc, new ofColor(ofColor::navajoWhite)));
    mrb_define_const(mrb, cc, "Navy"                 , ToMrb(mrb, cc, new ofColor(ofColor::navy)));
    mrb_define_const(mrb, cc, "OldLace"              , ToMrb(mrb, cc, new ofColor(ofColor::oldLace)));
    mrb_define_const(mrb, cc, "Olive"                , ToMrb(mrb, cc, new ofColor(ofColor::olive)));
    mrb_define_const(mrb, cc, "OliveDrab"            , ToMrb(mrb, cc, new ofColor(ofColor::oliveDrab)));
    mrb_define_const(mrb, cc, "Orange"               , ToMrb(mrb, cc, new ofColor(ofColor::orange)));
    mrb_define_const(mrb, cc, "OrangeRed"            , ToMrb(mrb, cc, new ofColor(ofColor::orangeRed)));
    mrb_define_const(mrb, cc, "Orchid"               , ToMrb(mrb, cc, new ofColor(ofColor::orchid)));
    mrb_define_const(mrb, cc, "PaleGoldenRod"        , ToMrb(mrb, cc, new ofColor(ofColor::paleGoldenRod)));
    mrb_define_const(mrb, cc, "PaleGreen"            , ToMrb(mrb, cc, new ofColor(ofColor::paleGreen)));
    mrb_define_const(mrb, cc, "PaleTurquoise"        , ToMrb(mrb, cc, new ofColor(ofColor::paleTurquoise)));
    mrb_define_const(mrb, cc, "PaleVioletRed"        , ToMrb(mrb, cc, new ofColor(ofColor::paleVioletRed)));
    mrb_define_const(mrb, cc, "PapayaWhip"           , ToMrb(mrb, cc, new ofColor(ofColor::papayaWhip)));
    mrb_define_const(mrb, cc, "PeachPuff"            , ToMrb(mrb, cc, new ofColor(ofColor::peachPuff)));
    mrb_define_const(mrb, cc, "Peru"                 , ToMrb(mrb, cc, new ofColor(ofColor::peru)));
    mrb_define_const(mrb, cc, "Pink"                 , ToMrb(mrb, cc, new ofColor(ofColor::pink)));
    mrb_define_const(mrb, cc, "Plum"                 , ToMrb(mrb, cc, new ofColor(ofColor::plum)));
    mrb_define_const(mrb, cc, "PowderBlue"           , ToMrb(mrb, cc, new ofColor(ofColor::powderBlue)));
    mrb_define_const(mrb, cc, "Purple"               , ToMrb(mrb, cc, new ofColor(ofColor::purple)));
    mrb_define_const(mrb, cc, "RosyBrown"            , ToMrb(mrb, cc, new ofColor(ofColor::rosyBrown)));
    mrb_define_const(mrb, cc, "RoyalBlue"            , ToMrb(mrb, cc, new ofColor(ofColor::royalBlue)));
    mrb_define_const(mrb, cc, "SaddleBrown"          , ToMrb(mrb, cc, new ofColor(ofColor::saddleBrown)));
    mrb_define_const(mrb, cc, "Salmon"               , ToMrb(mrb, cc, new ofColor(ofColor::salmon)));
    mrb_define_const(mrb, cc, "SandyBrown"           , ToMrb(mrb, cc, new ofColor(ofColor::sandyBrown)));
    mrb_define_const(mrb, cc, "SeaGreen"             , ToMrb(mrb, cc, new ofColor(ofColor::seaGreen)));
    mrb_define_const(mrb, cc, "SeaShell"             , ToMrb(mrb, cc, new ofColor(ofColor::seaShell)));
    mrb_define_const(mrb, cc, "Sienna"               , ToMrb(mrb, cc, new ofColor(ofColor::sienna)));
    mrb_define_const(mrb, cc, "Silver"               , ToMrb(mrb, cc, new ofColor(ofColor::silver)));
    mrb_define_const(mrb, cc, "SkyBlue"              , ToMrb(mrb, cc, new ofColor(ofColor::skyBlue)));
    mrb_define_const(mrb, cc, "SlateBlue"            , ToMrb(mrb, cc, new ofColor(ofColor::slateBlue)));
    mrb_define_const(mrb, cc, "SlateGray"            , ToMrb(mrb, cc, new ofColor(ofColor::slateGray)));
    mrb_define_const(mrb, cc, "SlateGrey"            , ToMrb(mrb, cc, new ofColor(ofColor::slateGrey)));
    mrb_define_const(mrb, cc, "Snow"                 , ToMrb(mrb, cc, new ofColor(ofColor::snow)));
    mrb_define_const(mrb, cc, "SpringGreen"          , ToMrb(mrb, cc, new ofColor(ofColor::springGreen)));
    mrb_define_const(mrb, cc, "SteelBlue"            , ToMrb(mrb, cc, new ofColor(ofColor::steelBlue)));
    mrb_define_const(mrb, cc, "Tan"                  , ToMrb(mrb, cc, new ofColor(ofColor::tan)));
    mrb_define_const(mrb, cc, "Teal"                 , ToMrb(mrb, cc, new ofColor(ofColor::teal)));
    mrb_define_const(mrb, cc, "Thistle"              , ToMrb(mrb, cc, new ofColor(ofColor::thistle)));
    mrb_define_const(mrb, cc, "Tomato"               , ToMrb(mrb, cc, new ofColor(ofColor::tomato)));
    mrb_define_const(mrb, cc, "Turquoise"            , ToMrb(mrb, cc, new ofColor(ofColor::turquoise)));
    mrb_define_const(mrb, cc, "Violet"               , ToMrb(mrb, cc, new ofColor(ofColor::violet)));
    mrb_define_const(mrb, cc, "Wheat"                , ToMrb(mrb, cc, new ofColor(ofColor::wheat)));
    mrb_define_const(mrb, cc, "WhiteSmoke"           , ToMrb(mrb, cc, new ofColor(ofColor::whiteSmoke)));
    mrb_define_const(mrb, cc, "YellowGreen"          , ToMrb(mrb, cc, new ofColor(ofColor::yellowGreen)));
    mrb_gc_arena_restore(mrb, ai);

    mrb_define_method(mrb, cc,       "r"                 , r                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "r="                , r_set               , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "g"                 , g                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "g="                , g_set               , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "b"                 , b                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "b="                , b_set               , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "a"                 , a                   , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "a="                , a_set               , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "clone"             , clone               , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "set"               , set                 , MRB_ARGS_ARG(3, 1));
    mrb_define_method(mrb, cc,       "to_hex"            , to_hex              , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "set_hex"           , set_hex             , MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, cc,       "clamp"             , clamp               , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "invert"            , invert              , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "normalize"         , normalize           , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "lerp"              , lerp                , MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,       "hue"               , hue                 , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "saturation"        , saturation          , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "brightness"        , brightness          , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "lightness"         , lightness           , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "to_hsb"            , to_hsb              , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "hue="              , hue_set             , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "saturation="       , saturation_set      , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "brightness="       , brightness_set      , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "set_hsb"           , set_hsb             , MRB_ARGS_ARG(3, 1));
    mrb_define_method(mrb, cc,       "=="                , equal               , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "+"                 , add                 , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "-"                 , sub                 , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "*"                 , mul                 , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "/"                 , div                 , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "[]"                , aref                , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "[]="               , aref_set            , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "inspect"           , inspect             , MRB_ARGS_NONE());
}

}
