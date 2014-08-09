#include "rubykokuban/Bind.hpp"

#include "mruby.h"
#include "mrubybind.h"
#include "ofGraphics.h"
#include "rubykokuban/BindColor.hpp"

namespace rubykokuban {

namespace {
float LIMIT = 255.0f;

mrb_value set_fill(mrb_state *mrb, mrb_value self)
{
    mrb_bool is_fill;

    if (mrb_get_args(mrb, "|b", &is_fill) == 0) {
        ofFill();
        return mrb_bool_value(true);
    } else {
        if (is_fill)
            ofFill();
        else
            ofNoFill();
        return mrb_bool_value(is_fill);
    }
}

void set_no_fill()
{
    ofNoFill();
}

bool is_fill()
{
    return ofGetFill() == OF_FILLED;
}

void set_line_width(float width)
{
    ofSetLineWidth(width);
}

mrb_value set_color(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    switch (argc) {
    case 1:
        // set_color(color)
        ofSetColor(*BindColor::ToPtr(mrb, argv[0]));
        break;
    case 2:
        // set_color(color, alpha)
        ofSetColor(
            *BindColor::ToPtr(mrb, argv[0])
            , mrb_fixnum(mrb_Integer(mrb, argv[1]))
            );
        break;
    case 3:
        // set_color(r, g, b)
        ofSetColor(
            mrb_fixnum(mrb_Integer(mrb, argv[0]))
            , mrb_fixnum(mrb_Integer(mrb, argv[1]))
            , mrb_fixnum(mrb_Integer(mrb, argv[2]))
            );
        break;
    case 4:
        // set_color(r, g, b, a)
        ofSetColor(
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

mrb_value set_color_hex(mrb_state *mrb, mrb_value self)
{
    mrb_int h;
    mrb_float a = LIMIT;
    mrb_get_args(mrb, "i|f", &h, &a);

    ofSetColor(ofColor::fromHex(h, a));

    return mrb_nil_value();
}

mrb_value set_background(mrb_state *mrb, mrb_value self)
{
    mrb_value *argv;
    int argc;

    mrb_get_args(mrb, "*", &argv, &argc);

    switch (argc) {
    case 1:
        // set_background(color)
        ofBackground(*BindColor::ToPtr(mrb, argv[0]));
        break;
    // case 2:
    //     // set_background(color, alpha)
    //     ofBackground(
    //         *BindColor::ToPtr(mrb, argv[0])
    //         , mrb_fixnum(mrb_Integer(mrb, argv[1]))
    //         );
    //     break;
    case 3:
        // set_background(r, g, b)
        ofBackground(
            mrb_fixnum(mrb_Integer(mrb, argv[0]))
            , mrb_fixnum(mrb_Integer(mrb, argv[1]))
            , mrb_fixnum(mrb_Integer(mrb, argv[2]))
            );
        break;
    // case 4:
    //     // set_background(r, g, b, a)
    //     ofBackground(
    //         mrb_fixnum(mrb_Integer(mrb, argv[0]))
    //         , mrb_fixnum(mrb_Integer(mrb, argv[1]))
    //         , mrb_fixnum(mrb_Integer(mrb, argv[2]))
    //         , mrb_fixnum(mrb_Integer(mrb, argv[3]))
    //         );
    //     break;
     default:
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
        break;
    }

    return mrb_nil_value();
}

mrb_value set_background_hex(mrb_state *mrb, mrb_value self)
{
    mrb_int h, a = LIMIT;
    mrb_get_args(mrb, "i|i", &h, &a);

    ofBackgroundHex(h, a);

    return mrb_nil_value();
}

void triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    ofTriangle(x1, y1, x2, y2, x3, y3);
}

void circle(float x, float y, float radius)
{
    ofCircle(x, y, radius);
}

void ellipse(float x, float y, float width, float height)
{
    ofEllipse(x, y, width, height);
}

void line(float x1, float y1, float x2, float y2)
{
    ofLine(x1, y1, x2, y2);
}

void rect(float x, float y, float w, float h)
{
    ofRect(x, y, w, h);
}

void rect_rounded(float x, float y, float w, float h, float r)
{
    ofRectRounded(x, y, w, h, r);
}

mrb_value text(mrb_state *mrb, mrb_value self)
{
    mrb_value str;
    mrb_int x, y;

#if 1
    mrb_get_args(mrb, "Sii", &str, &x, &y);
    ofDrawBitmapString(mrb_str_to_cstr(mrb, str), x, y);
#else
    // Display any object#to_s
    mrb_get_args(mrb, "oii", &str, &x, &y);
    ofDrawBitmapString(mrb_str_to_cstr(mrb, mrb_obj_as_string(mrb, str)), x, y);
#endif 
}

}

//----------------------------------------------------------
void BindGraphics(mrb_state* mrb)
{
    struct RClass *cc = mrb->kernel_module;
    mrubybind::MrubyBind b(mrb);

    mrb_define_method(mrb, cc, "set_fill",            set_fill          , MRB_ARGS_OPT(1));
    b.bind(                    "set_no_fill",         set_no_fill       );
    b.bind(                    "is_fill",             is_fill           );
    b.bind(                    "set_line_width",      set_line_width    );
    mrb_define_method(mrb, cc, "set_color",           set_color         , MRB_ARGS_ARG(1, 3));
    mrb_define_method(mrb, cc, "set_color_hex",       set_color_hex     , MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, cc, "set_background",      set_background    , MRB_ARGS_ARG(1, 3));
    mrb_define_method(mrb, cc, "set_background_hex",  set_background_hex, MRB_ARGS_ARG(1, 1));
    b.bind(                    "triangle",            triangle          );
    b.bind(                    "circle",              circle            );
    b.bind(                    "ellipse",             ellipse           );
    b.bind(                    "line",                line              );
    b.bind(                    "rect",                rect              );
    b.bind(                    "rect_rounded",        rect_rounded      );
    mrb_define_method(mrb, cc, "text",                text              , MRB_ARGS_REQ(3));
}

}
