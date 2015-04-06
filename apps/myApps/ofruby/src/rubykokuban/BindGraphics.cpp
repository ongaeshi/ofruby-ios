#include "rubykokuban/Bind.hpp"

#include "mruby.h"
#include "mruby/string.h"
#include "ofGraphics.h"
#include "rubykokuban/BindColor.hpp"

namespace rubykokuban {

namespace {
float LIMIT = 255.0f;

mrb_value push_matrix(mrb_state *mrb, mrb_value self)
{
    mrb_value block = mrb_nil_value();
    mrb_get_args(mrb, "|&", &block);

    ofPushMatrix();

    if (!mrb_nil_p(block)) {
        mrb_yield_argv(mrb, block, 0, NULL);
        ofPopMatrix();
    }

    return mrb_nil_value();
}

mrb_value pop_matrix(mrb_state *mrb, mrb_value self)
{
    ofPopMatrix();
    return mrb_nil_value();
}

mrb_value translate(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_get_args(mrb, "ff", &x, &y);
    ofTranslate(x, y);
    return mrb_nil_value();
}

mrb_value scale(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_get_args(mrb, "ff", &x, &y);
    ofScale(x, y);
    return mrb_nil_value();
}

mrb_value rotate(mrb_state *mrb, mrb_value self)
{
    mrb_float degrees;
    mrb_get_args(mrb, "f", &degrees);
    ofRotate(degrees);
    return mrb_nil_value();
}

mrb_value set_circle_resolution(mrb_state *mrb, mrb_value self)
{
    mrb_int res;
    mrb_get_args(mrb, "i", &res);

    ofSetCircleResolution(res);

    return mrb_nil_value();
}

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

mrb_value set_no_fill(mrb_state *mrb, mrb_value self)
{
    ofNoFill();
    return mrb_nil_value();
}

mrb_value is_fill(mrb_state *mrb, mrb_value self)
{
    return mrb_bool_value(ofGetFill() == OF_FILLED);
}

mrb_value set_line_width(mrb_state *mrb, mrb_value self)
{
    mrb_float width;
    mrb_get_args(mrb, "f", &width);

    ofSetLineWidth(width);

    return mrb_nil_value();
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

mrb_value set_background_auto(mrb_state *mrb, mrb_value self)
{
    mrb_bool flag;
    mrb_get_args(mrb, "b", &flag);
    
    ofSetBackgroundAuto(flag);

    return mrb_bool_value(flag);
}

mrb_value triangle(mrb_state *mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2, x3, y3;
    mrb_get_args(mrb, "ffffff", &x1, &y1, &x2, &y2, &x3, &y3);

    ofTriangle(x1, y1, x2, y2, x3, y3);

    return mrb_nil_value();
}

mrb_value circle(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, radius;
    mrb_get_args(mrb, "fff", &x, &y, &radius);

    ofCircle(x, y, radius);

    return mrb_nil_value();
}

mrb_value ellipse(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, width, height;
    mrb_get_args(mrb, "ffff", &x, &y, &width, &height);

    ofEllipse(x, y, width, height);

    return mrb_nil_value();
}

mrb_value line(mrb_state *mrb, mrb_value self)
{
    mrb_float x1, y1, x2, y2;
    mrb_get_args(mrb, "ffff", &x1, &y1, &x2, &y2);

    ofLine(x1, y1, x2, y2);

    return mrb_nil_value();
}

mrb_value rect(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h;
    mrb_get_args(mrb, "ffff", &x, &y, &w, &h);

    ofRect(x, y, w, h);
    
    return mrb_nil_value();
}

mrb_value rect_rounded(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h, r;
    mrb_get_args(mrb, "fffff", &x, &y, &w, &h, &r);

    ofRectRounded(x, y, w, h, r);
    
    return mrb_nil_value();
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

    return mrb_nil_value();
}

}

//----------------------------------------------------------
void BindGraphics(mrb_state* mrb)
{
    struct RClass *cc = mrb->kernel_module;

    mrb_define_method(mrb, cc,       "push_matrix"          , push_matrix         , MRB_ARGS_OPT(1));
    mrb_define_method(mrb, cc,       "pop_matrix"           , pop_matrix          , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "translate"            , translate           , MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,       "scale"                , scale               , MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,       "rotate"               , rotate              , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "set_circle_resolution", set_circle_resolution, MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "set_fill"             , set_fill            , MRB_ARGS_OPT(1));
    mrb_define_method(mrb, cc,       "set_no_fill"          , set_no_fill         , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "is_fill"              , is_fill             , MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,       "set_line_width"       , set_line_width      , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "set_color"            , set_color           , MRB_ARGS_ARG(1, 3));
    mrb_define_method(mrb, cc,       "set_color_hex"        , set_color_hex       , MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, cc,       "set_background"       , set_background      , MRB_ARGS_ARG(1, 3));
    mrb_define_method(mrb, cc,       "set_background_hex"   , set_background_hex  , MRB_ARGS_ARG(1, 1));
    mrb_define_method(mrb, cc,       "set_background_auto"  , set_background_auto , MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,       "triangle"             , triangle            , MRB_ARGS_REQ(6));
    mrb_define_method(mrb, cc,       "circle"               , circle              , MRB_ARGS_REQ(3));
    mrb_define_method(mrb, cc,       "ellipse"              , ellipse             , MRB_ARGS_REQ(4));
    mrb_define_method(mrb, cc,       "line"                 , line                , MRB_ARGS_REQ(4));
    mrb_define_method(mrb, cc,       "rect"                 , rect                , MRB_ARGS_REQ(4));
    mrb_define_method(mrb, cc,       "rect_rounded"         , rect_rounded        , MRB_ARGS_REQ(5));
    mrb_define_method(mrb, cc,       "text"                 , text                , MRB_ARGS_REQ(3));
}

}
