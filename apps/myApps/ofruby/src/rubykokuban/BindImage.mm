#include "rubykokuban/BindImage.hpp"

#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"
#include "mruby/string.h"
#include "ofAppRunner.h"
#include "ofImage.h"
#include "rubykokuban/BindColor.hpp"
#import "FCFileManager.h"

namespace rubykokuban {

namespace {
ofImage& obj(mrb_value self)
{
    return *((ofImage*)DATA_PTR(self));
}

void free(mrb_state *mrb, void *p)
{
    if (p) {
        delete ((ofImage*)p);
    }
}

struct mrb_data_type data_type = { "rubykokuban_image", free };

mrb_value loadIN(mrb_state *mrb, mrb_value self, string filename, string subpath)
{
    ofImage* obj = new ofImage();

    bool isSuccess = obj->loadImage(filename);

    if (!isSuccess) {
        string message = "not found " + subpath;
        mrb_raise(mrb, E_ARGUMENT_ERROR, message.c_str());
    }

    return BindImage::ToMrb(mrb, mrb_class_ptr(self), obj);
}

mrb_value load(mrb_state *mrb, mrb_value self)
{
    mrb_value str;
    mrb_get_args(mrb, "S", &str);

    const char* path = mrb_string_value_ptr(mrb, str);
    NSString *npath = [[NSString alloc] initWithUTF8String:path];
    // DOCUMENTS/image/path/to/test.png
    string filename([[[FCFileManager pathForDocumentsDirectoryWithPath: @"image"] stringByAppendingPathComponent: npath] UTF8String]);

    return loadIN(mrb, self, filename, [npath UTF8String]);
}

mrb_value sample(mrb_state *mrb, mrb_value self)
{
    mrb_value str;
    mrb_get_args(mrb, "S", &str);

    const char* path = mrb_string_value_ptr(mrb, str);
    NSString *npath = [[NSString alloc] initWithUTF8String:path];
    // RESOURCES/sample/image/path/to/test.png
    string filename([[[FCFileManager pathForMainBundleDirectoryWithPath: @"sample/image"] stringByAppendingPathComponent: npath] UTF8String]);

    return loadIN(mrb, self, filename, [npath UTF8String]);
}

mrb_value grab_screen(mrb_state *mrb, mrb_value self)
{
    ofImage* obj = new ofImage();

    mrb_int x, y, w, h;

    switch (mrb_get_args(mrb, "|iiii", &x, &y, &w, &h)) {
    case 0:
        obj->grabScreen(0, 0, ofGetWindowWidth(), ofGetWindowHeight());
        break;
    case 4:
        obj->grabScreen(x, y, w, h);
        break;
    default:
        mrb_raise(mrb, E_TYPE_ERROR, "wrong number of arguments");
        break;
    }

    return BindImage::ToMrb(mrb, mrb_class_ptr(self), obj);
}

mrb_value clone(mrb_state *mrb, mrb_value self)
{
    ofImage* newObj = new ofImage();

    newObj->clone(obj(self));

    return BindImage::ToMrb(mrb, mrb_obj_class(mrb, self), newObj);
}

mrb_value save(mrb_state *mrb, mrb_value self)
{
    mrb_value str;
    mrb_get_args(mrb, "S", &str);

    string filename(mrb_string_value_ptr(mrb, str));
    obj(self).saveImage(filename);

    return self;
}

mrb_value color(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_get_args(mrb, "ii", &x, &y);

    ofColor* color = new ofColor(obj(self).getColor(x, y));

    return BindColor::ToMrb(mrb, color);
}

mrb_value set_color(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y;
    mrb_value cobj;
    mrb_get_args(mrb, "iio", &x, &y, &cobj);

    ofColor* color = BindColor::ToPtr(mrb, cobj);

    obj(self).setColor(x, y, *color);

    return mrb_nil_value();
}

mrb_value resize(mrb_state *mrb, mrb_value self)
{
    mrb_int width, height;
    mrb_get_args(mrb, "ii", &width, &height);

    obj(self).resize(width, height);

    return self;
}

mrb_value set_image_type(mrb_state *mrb, mrb_value self)
{
    return mrb_nil_value();
}

mrb_value crop_bang(mrb_state *mrb, mrb_value self)
{
    mrb_int x, y, w, h;
    mrb_get_args(mrb, "iiii", &x, &y, &w, &h);
    
    obj(self).crop(x, y, w, h);

    return self;
}

mrb_value crop(mrb_state *mrb, mrb_value self)
{
    ofImage* newObj = new ofImage();

    mrb_int x, y, w, h;
    mrb_get_args(mrb, "iiii", &x, &y, &w, &h);

    newObj->cropFrom(obj(self), x, y, w, h);

    return BindImage::ToMrb(mrb, mrb_obj_class(mrb, self), newObj);
}

mrb_value rotate90(mrb_state *mrb, mrb_value self)
{
    mrb_int rotation = 1;
    mrb_get_args(mrb, "|i", &rotation);
    
    obj(self).rotate90(rotation);

    return self;
}

mrb_value mirror(mrb_state *mrb, mrb_value self)
{
    mrb_bool vertical, horizontal;
    mrb_get_args(mrb, "bb", &vertical, &horizontal);
    
    obj(self).mirror(vertical, horizontal);
    
    return self;
}

mrb_value update(mrb_state *mrb, mrb_value self)
{
    obj(self).update();
    return self;
}

mrb_value set_anchor_percent(mrb_state *mrb, mrb_value self)
{
    mrb_float xpct, ypct;
    mrb_get_args(mrb, "ff", &xpct, &ypct);
    
    obj(self).setAnchorPercent(xpct, ypct);
    
    return self;
}

mrb_value set_anchor_point(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y;
    mrb_get_args(mrb, "ff", &x, &y);
    
    obj(self).setAnchorPoint(x, y);
    
    return self;
}

mrb_value reset_anchor(mrb_state *mrb, mrb_value self)
{
    obj(self).resetAnchor();
    return self;
}

mrb_value draw(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h;
    int argNum = mrb_get_args(mrb, "ff|ff", &x, &y, &w, &h);

    if (argNum == 4)
        obj(self).draw(x, y, w, h);
    else 
        obj(self).draw(x, y);

    return self;
}

mrb_value draw_sub(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h, sx, sy, sw, sh;
    int argNum = mrb_get_args(mrb, "ffffff|ff", &x, &y, &w, &h, &sx, &sy, &sw, &sh);

    if (argNum == 8)
        obj(self).drawSubsection(x, y, w, h, sx, sy, sw, sh);
    else 
        obj(self).drawSubsection(x, y, w, h, sx, sy);

    return self;
}

mrb_value height(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, obj(self).getHeight());
}

mrb_value width(mrb_state *mrb, mrb_value self)
{
    return mrb_float_value(mrb, obj(self).getWidth());
}

mrb_value each_pixels(mrb_state *mrb, mrb_value self)
{
    int width = obj(self).width;
    int height = obj(self).height;

    mrb_int x_step = 1, y_step = 1;
    mrb_value block;
    mrb_get_args(mrb, "|ii&", &x_step, &y_step, &block);

    for (int i = 0; i < width; i += x_step) {
        for (int j = 0; j < height; j += y_step) {
            static const int ARGC = 2;

            mrb_value argv[ARGC];
            argv[0] = mrb_fixnum_value(i);
            argv[1] = mrb_fixnum_value(j);
            mrb_yield_argv(mrb, block, ARGC, argv);
        }
    }

    return mrb_nil_value();
}

mrb_value map_pixels(mrb_state *mrb, mrb_value self)
{
    ofImage* newObj = new ofImage();
    newObj->clone(obj(self));

    int width = obj(self).width;
    int height = obj(self).height;

    mrb_int x_step = 1, y_step = 1;
    mrb_value block;
    mrb_get_args(mrb, "|ii&", &x_step, &y_step, &block);

    for (int i = 0; i < width; i += x_step) {
        for (int j = 0; j < height; j += y_step) {
            static const int ARGC = 2;

            mrb_value argv[ARGC];
            argv[0] = mrb_fixnum_value(i);
            argv[1] = mrb_fixnum_value(j);

            mrb_value value = mrb_yield_argv(mrb, block, ARGC, argv);
            ofColor* color = BindColor::ToPtr(mrb, value);
            newObj->setColor(i, j, *color);
        }
    }

    newObj->update();

    return BindImage::ToMrb(mrb, mrb_obj_class(mrb, self), newObj);
}

}

//----------------------------------------------------------
mrb_value BindImage::ToMrb(mrb_state* mrb, ofImage* aPtr)
{
    return ToMrb(mrb, mrb_class_get(mrb, "Image"), aPtr);
}

//----------------------------------------------------------
mrb_value BindImage::ToMrb(mrb_state* mrb, struct RClass* aClass, ofImage* aPtr)
{
    struct RData *data = mrb_data_object_alloc(mrb, aClass, aPtr, &data_type);
    return mrb_obj_value(data);
}

//----------------------------------------------------------
ofImage* BindImage::ToPtr(mrb_state* mrb, mrb_value aValue)
{
    if (!mrb_obj_is_instance_of(mrb, aValue, mrb_class_get(mrb, "Image"))) {
        mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
    }

    return static_cast<ofImage*>(DATA_PTR(aValue));
}

//----------------------------------------------------------
void BindImage::Bind(mrb_state* mrb)
{
    struct RClass *cc = mrb_define_class(mrb, "Image", mrb->object_class);

    mrb_define_class_method(mrb , cc, "load",               load,               MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb , cc, "sample",             sample,             MRB_ARGS_REQ(1));
    mrb_define_class_method(mrb , cc, "grab_screen",        grab_screen,        MRB_ARGS_OPT(4));
                                                             
    mrb_define_method(mrb, cc,        "clone",              clone,              MRB_ARGS_NONE());
    // mrb_define_method(mrb, cc,        "save",               save,               MRB_ARGS_ARG(2, 1));
    mrb_define_method(mrb, cc,        "color",              color,              MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,        "set_color",          set_color,          MRB_ARGS_REQ(3));
    mrb_define_method(mrb, cc,        "resize",             resize,             MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,        "set_image_type",     set_image_type,     MRB_ARGS_REQ(1));
    mrb_define_method(mrb, cc,        "crop",               crop,               MRB_ARGS_REQ(4));
    mrb_define_method(mrb, cc,        "crop!",              crop_bang,          MRB_ARGS_REQ(4));
    mrb_define_method(mrb, cc,        "rotate90",           rotate90,           MRB_ARGS_OPT(1));
    mrb_define_method(mrb, cc,        "mirror",             mirror,             MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,        "update",             update,             MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,        "set_anchor_percent", set_anchor_percent, MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,        "set_anchor_point",   set_anchor_point,   MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,        "reset_anchor",       reset_anchor,       MRB_ARGS_REQ(2));
    mrb_define_method(mrb, cc,        "draw",               draw,               MRB_ARGS_ARG(2, 2));
    mrb_define_method(mrb, cc,        "draw_sub",           draw_sub,           MRB_ARGS_ARG(6, 2));
    mrb_define_method(mrb, cc,        "height",             height,             MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,        "width",              width,              MRB_ARGS_NONE());
    mrb_define_method(mrb, cc,        "each_pixels",        each_pixels,        MRB_ARGS_OPT(2));
    mrb_define_method(mrb, cc,        "map_pixels",         map_pixels,         MRB_ARGS_OPT(2));
}

}
