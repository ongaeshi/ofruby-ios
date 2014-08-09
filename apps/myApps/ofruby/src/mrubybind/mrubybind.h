#ifndef __MRUBYBIND_H__
#define __MRUBYBIND_H__

#include <mruby.h>
#include <mruby/class.h>
#include <mruby/data.h>
#include "mrubybind_types.h"

namespace mrubybind {

class MrubyBind {
public:
  MrubyBind(mrb_state* mrb);
  MrubyBind(mrb_state* mrb, RClass* mod);
  ~MrubyBind();

  // Bind constant value.
  template <class T>
  void bind_const(const char* name, T v) {
    mrb_define_const(mrb_, mod_, name, Type<T>::ret(mrb_, v));
  }

  // Bind function.
  template <class Func>
  void bind(const char* func_name, Func func_ptr) {
    mrb_value mod = mrb_obj_value(mod_);
    mrb_value binder = mrb_voidp_value(mrb_, (void*)Binder<Func>::call);
    mrb_value func_name_v = mrb_str_new_cstr(mrb_, func_name);
    mrb_value func_ptr_v = mrb_voidp_value(mrb_, reinterpret_cast<void*>(func_ptr));
    mrb_value nparam_v = mrb_fixnum_value(Binder<Func>::NPARAM);
    mrb_funcall(mrb_, mod_mrubybind_, "define_function", 5, mod, binder, func_name_v,
                func_ptr_v, nparam_v);
  }

  // Bind class.
  template <class Func>
  void bind_class(const char* class_name, Func new_func_ptr) {
    struct RClass *tc = mrb_define_class(mrb_, class_name, mrb_->object_class);
    MRB_SET_INSTANCE_TT(tc, MRB_TT_DATA);
    mrb_value binder = mrb_voidp_value(mrb_, (void*)ClassBinder<Func>::ctor);
    mrb_value class_name_v = mrb_str_new_cstr(mrb_, class_name);
    mrb_value new_func_ptr_v = mrb_voidp_value(mrb_, (void*)new_func_ptr);
    mrb_value nparam_v = mrb_fixnum_value(ClassBinder<Func>::NPARAM);
    mrb_funcall(mrb_, mod_mrubybind_, "bind_class", 4, binder, class_name_v,
                new_func_ptr_v, nparam_v);
  }

  // Bind class method.
  template <class Method>
  void bind_class_method(const char* class_name, const char* method_name,
                         Method method_ptr) {
    mrb_value binder = mrb_voidp_value(mrb_, (void*)ClassBinder<Method>::call);
    mrb_value class_name_v = mrb_str_new_cstr(mrb_, class_name);
    mrb_value method_name_v = mrb_str_new_cstr(mrb_, method_name);
    mrb_value method_pptr_v = mrb_str_new(mrb_,
                                          reinterpret_cast<char*>(&method_ptr),
                                          sizeof(method_ptr));
    mrb_value nparam_v = mrb_fixnum_value(ClassBinder<Method>::NPARAM);
    mrb_funcall(mrb_, mod_mrubybind_, "bind_class_method", 5, binder,
                class_name_v, method_name_v, method_pptr_v, nparam_v);
  }

private:
  void Initialize();

  mrb_state* mrb_;
  mrb_value mod_mrubybind_;
  RClass* mod_;
  int arena_index_;
};

}  // namespace mrubybind

#endif
