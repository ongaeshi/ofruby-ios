#include "mrubybind.h"
#include <mruby/compile.h>
#include <mruby/dump.h>
#include <mruby/proc.h>
#include <mruby/string.h>
#include <mruby/variable.h>

namespace mrubybind {

static
#include "mrubybind.dat"

const char Type<int>::TYPE_NAME[] = "Fixnum";
const char Type<unsigned int>::TYPE_NAME[] = "Fixnum";
const char Type<float>::TYPE_NAME[] = "Float";
const char Type<double>::TYPE_NAME[] = "Float";
const char Type<const char*>::TYPE_NAME[] = "String";
const char Type<std::string>::TYPE_NAME[] = "String";
const char Type<const std::string>::TYPE_NAME[] = "String";
const char Type<const std::string&>::TYPE_NAME[] = "String";
const char Type<bool>::TYPE_NAME[] = "Bool";
const char Type<void*>::TYPE_NAME[] = "Voidp";

mrb_value raise(mrb_state *mrb, int parameter_index,
                const char* required_type_name, mrb_value value) {
  const char * argument_class_name = mrb_obj_classname(mrb, value);
  mrb_raisef(mrb, E_TYPE_ERROR, "Illegal type %S, %S required, but %S(%S)",
             mrb_fixnum_value(parameter_index),
             mrb_str_new_cstr(mrb, required_type_name),
             mrb_str_new_cstr(mrb, argument_class_name), value);
  return mrb_nil_value();
}

static mrb_value call_cfunc(mrb_state *mrb, mrb_value /*self*/) {
  mrb_value binder;
  mrb_value func_ptr_v;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "oo*", &binder, &func_ptr_v, &args, &narg);
  typedef mrb_value (*BindFunc)(mrb_state*, void*, mrb_value*, int);
  BindFunc binderp = reinterpret_cast<BindFunc>(mrb_voidp(binder));
  return binderp(mrb, mrb_voidp(func_ptr_v), args, narg);
}

static mrb_value call_ctorfunc(mrb_state *mrb, mrb_value self) {
  mrb_value binder;
  mrb_value self_v;
  mrb_value new_func_ptr_v;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "ooo*", &binder, &self_v, &new_func_ptr_v, &args, &narg);
  typedef mrb_value (*BindFunc)(mrb_state*, mrb_value, void*, mrb_value*, int);
  BindFunc binderp = reinterpret_cast<BindFunc>(mrb_voidp(binder));
  binderp(mrb, self_v, mrb_voidp(new_func_ptr_v), args, narg);
  return self;
}

static mrb_value call_cmethod(mrb_state *mrb, mrb_value /*self*/) {
  mrb_value binder;
  mrb_value self_v;
  mrb_value method_pptr_v;
  mrb_value* args;
  int narg;
  mrb_get_args(mrb, "ooS*", &binder, &self_v, &method_pptr_v, &args, &narg);
  typedef mrb_value (*BindFunc)(mrb_state*, mrb_value, void*, mrb_value*, int);
  BindFunc binderp = reinterpret_cast<BindFunc>(mrb_voidp(binder));
  return binderp(mrb, self_v, RSTRING_PTR(method_pptr_v), args, narg);
}

MrubyBind::MrubyBind(mrb_state* mrb) : mrb_(mrb), mod_(mrb_->kernel_module) {
  Initialize();
}

MrubyBind::MrubyBind(mrb_state* mrb, RClass* mod) : mrb_(mrb), mod_(mod) {
  Initialize();
}

MrubyBind::~MrubyBind() {
  mrb_gc_arena_restore(mrb_, arena_index_);
}

void MrubyBind::Initialize() {
  arena_index_ = mrb_gc_arena_save(mrb_);
  mrb_sym sym_mrubybind = mrb_intern(mrb_, "MrubyBind");
  if (mrb_const_defined(mrb_, mrb_obj_value(mrb_->kernel_module),
                        sym_mrubybind)) {
    mod_mrubybind_ = mrb_const_get(mrb_, mrb_obj_value(mrb_->kernel_module),
                                   sym_mrubybind);
  } else {
    RClass* mrubybind = mrb_define_module(mrb_, "MrubyBind");
    mod_mrubybind_ = mrb_obj_value(mrubybind);
    mrb_define_module_function(mrb_, mrubybind, "call_cfunc", call_cfunc,
                               ARGS_REQ(2) | ARGS_REST());
    mrb_define_module_function(mrb_, mrubybind, "call_ctorfunc", call_ctorfunc,
                               ARGS_REQ(3) | ARGS_REST());
    mrb_define_module_function(mrb_, mrubybind, "call_cmethod", call_cmethod,
                               ARGS_REQ(3) | ARGS_REST());
    int n = mrb_read_irep(mrb_, binder);
    if (n >= 0) {
      mrb_run(mrb_, mrb_proc_new(mrb_, mrb_->irep[n]), mrb_top_self(mrb_));
    }
  }
}

}  // namespace mrubybind
