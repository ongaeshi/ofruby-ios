// This file is generated from gen_template.rb
#define ARG(i)  Type<P##i>::get(args[i])
#define CHECK(i)  {if(!Type<P##i>::a_check(args[i])) return RAISE(i);}
#define RAISE(i)  raise(mrb, i, Type<P##i>::TYPE_NAME, args[i])

// void f(void);
template<>
struct Binder<void (*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(mrb);(void)(args);(void)(narg);
    void (*fp)(void) = (void (*)(void))func_ptr;
    fp();
    return mrb_nil_value();
  }
};

// R f(void);
template<class R>
struct Binder<R (*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(mrb);(void)(args);(void)(narg);
    R (*fp)(void) = (R (*)(void))func_ptr;
    R result = fp();
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(void);
template<class C>
struct ClassBinder<C* (*)(void)> {
  static const int NPARAM = 0;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(mrb);(void)(args);(void)(narg);
    C* (*ctor)(void) = (C* (*)(void))new_func_ptr;
    C* instance = ctor();
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(void) };
template<class C>
struct ClassBinder<void (C::*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(mrb);(void)(args);(void)(narg);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(void);
    M mp = *(M*)method_pptr;
    (instance->*mp)();
    return mrb_nil_value();
  }
};

// class C { R f(void) };
template<class C, class R>
struct ClassBinder<R (C::*)(void)> {
  static const int NPARAM = 0;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(mrb);(void)(args);(void)(narg);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(void);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)();
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0);
template<class P0>
struct Binder<void (*)(P0)> {
  static const int NPARAM = 1;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0);
    void (*fp)(P0) = (void (*)(P0))func_ptr;
    fp(ARG(0));
    return mrb_nil_value();
  }
};

// R f(P0);
template<class R, class P0>
struct Binder<R (*)(P0)> {
  static const int NPARAM = 1;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0);
    R (*fp)(P0) = (R (*)(P0))func_ptr;
    R result = fp(ARG(0));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0);
template<class C, class P0>
struct ClassBinder<C* (*)(P0)> {
  static const int NPARAM = 1;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0);
    C* (*ctor)(P0) = (C* (*)(P0))new_func_ptr;
    C* instance = ctor(ARG(0));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0) };
template<class C, class P0>
struct ClassBinder<void (C::*)(P0)> {
  static const int NPARAM = 1;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0));
    return mrb_nil_value();
  }
};

// class C { R f(P0) };
template<class C, class R, class P0>
struct ClassBinder<R (C::*)(P0)> {
  static const int NPARAM = 1;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1);
template<class P0, class P1>
struct Binder<void (*)(P0, P1)> {
  static const int NPARAM = 2;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1);
    void (*fp)(P0, P1) = (void (*)(P0, P1))func_ptr;
    fp(ARG(0), ARG(1));
    return mrb_nil_value();
  }
};

// R f(P0, P1);
template<class R, class P0, class P1>
struct Binder<R (*)(P0, P1)> {
  static const int NPARAM = 2;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1);
    R (*fp)(P0, P1) = (R (*)(P0, P1))func_ptr;
    R result = fp(ARG(0), ARG(1));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1);
template<class C, class P0, class P1>
struct ClassBinder<C* (*)(P0, P1)> {
  static const int NPARAM = 2;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1);
    C* (*ctor)(P0, P1) = (C* (*)(P0, P1))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1) };
template<class C, class P0, class P1>
struct ClassBinder<void (C::*)(P0, P1)> {
  static const int NPARAM = 2;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1) };
template<class C, class R, class P0, class P1>
struct ClassBinder<R (C::*)(P0, P1)> {
  static const int NPARAM = 2;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2);
template<class P0, class P1, class P2>
struct Binder<void (*)(P0, P1, P2)> {
  static const int NPARAM = 3;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2);
    void (*fp)(P0, P1, P2) = (void (*)(P0, P1, P2))func_ptr;
    fp(ARG(0), ARG(1), ARG(2));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2);
template<class R, class P0, class P1, class P2>
struct Binder<R (*)(P0, P1, P2)> {
  static const int NPARAM = 3;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2);
    R (*fp)(P0, P1, P2) = (R (*)(P0, P1, P2))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2);
template<class C, class P0, class P1, class P2>
struct ClassBinder<C* (*)(P0, P1, P2)> {
  static const int NPARAM = 3;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2);
    C* (*ctor)(P0, P1, P2) = (C* (*)(P0, P1, P2))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2) };
template<class C, class P0, class P1, class P2>
struct ClassBinder<void (C::*)(P0, P1, P2)> {
  static const int NPARAM = 3;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2) };
template<class C, class R, class P0, class P1, class P2>
struct ClassBinder<R (C::*)(P0, P1, P2)> {
  static const int NPARAM = 3;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3);
template<class P0, class P1, class P2, class P3>
struct Binder<void (*)(P0, P1, P2, P3)> {
  static const int NPARAM = 4;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3);
    void (*fp)(P0, P1, P2, P3) = (void (*)(P0, P1, P2, P3))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3);
template<class R, class P0, class P1, class P2, class P3>
struct Binder<R (*)(P0, P1, P2, P3)> {
  static const int NPARAM = 4;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3);
    R (*fp)(P0, P1, P2, P3) = (R (*)(P0, P1, P2, P3))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3);
template<class C, class P0, class P1, class P2, class P3>
struct ClassBinder<C* (*)(P0, P1, P2, P3)> {
  static const int NPARAM = 4;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3);
    C* (*ctor)(P0, P1, P2, P3) = (C* (*)(P0, P1, P2, P3))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3) };
template<class C, class P0, class P1, class P2, class P3>
struct ClassBinder<void (C::*)(P0, P1, P2, P3)> {
  static const int NPARAM = 4;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3) };
template<class C, class R, class P0, class P1, class P2, class P3>
struct ClassBinder<R (C::*)(P0, P1, P2, P3)> {
  static const int NPARAM = 4;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4);
template<class P0, class P1, class P2, class P3, class P4>
struct Binder<void (*)(P0, P1, P2, P3, P4)> {
  static const int NPARAM = 5;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4);
    void (*fp)(P0, P1, P2, P3, P4) = (void (*)(P0, P1, P2, P3, P4))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4);
template<class R, class P0, class P1, class P2, class P3, class P4>
struct Binder<R (*)(P0, P1, P2, P3, P4)> {
  static const int NPARAM = 5;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4);
    R (*fp)(P0, P1, P2, P3, P4) = (R (*)(P0, P1, P2, P3, P4))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3, P4);
template<class C, class P0, class P1, class P2, class P3, class P4>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4)> {
  static const int NPARAM = 5;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4);
    C* (*ctor)(P0, P1, P2, P3, P4) = (C* (*)(P0, P1, P2, P3, P4))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3, P4) };
template<class C, class P0, class P1, class P2, class P3, class P4>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4)> {
  static const int NPARAM = 5;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4)> {
  static const int NPARAM = 5;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4, P5);
template<class P0, class P1, class P2, class P3, class P4, class P5>
struct Binder<void (*)(P0, P1, P2, P3, P4, P5)> {
  static const int NPARAM = 6;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5);
    void (*fp)(P0, P1, P2, P3, P4, P5) = (void (*)(P0, P1, P2, P3, P4, P5))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4, P5);
template<class R, class P0, class P1, class P2, class P3, class P4, class P5>
struct Binder<R (*)(P0, P1, P2, P3, P4, P5)> {
  static const int NPARAM = 6;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5);
    R (*fp)(P0, P1, P2, P3, P4, P5) = (R (*)(P0, P1, P2, P3, P4, P5))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3, P4, P5);
template<class C, class P0, class P1, class P2, class P3, class P4, class P5>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4, P5)> {
  static const int NPARAM = 6;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5);
    C* (*ctor)(P0, P1, P2, P3, P4, P5) = (C* (*)(P0, P1, P2, P3, P4, P5))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3, P4, P5) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4, P5)> {
  static const int NPARAM = 6;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4, P5) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4, P5)> {
  static const int NPARAM = 6;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4, P5, P6);
template<class P0, class P1, class P2, class P3, class P4, class P5, class P6>
struct Binder<void (*)(P0, P1, P2, P3, P4, P5, P6)> {
  static const int NPARAM = 7;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6);
    void (*fp)(P0, P1, P2, P3, P4, P5, P6) = (void (*)(P0, P1, P2, P3, P4, P5, P6))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4, P5, P6);
template<class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6>
struct Binder<R (*)(P0, P1, P2, P3, P4, P5, P6)> {
  static const int NPARAM = 7;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6);
    R (*fp)(P0, P1, P2, P3, P4, P5, P6) = (R (*)(P0, P1, P2, P3, P4, P5, P6))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3, P4, P5, P6);
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4, P5, P6)> {
  static const int NPARAM = 7;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6);
    C* (*ctor)(P0, P1, P2, P3, P4, P5, P6) = (C* (*)(P0, P1, P2, P3, P4, P5, P6))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3, P4, P5, P6) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4, P5, P6)> {
  static const int NPARAM = 7;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5, P6);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4, P5, P6) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4, P5, P6)> {
  static const int NPARAM = 7;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5, P6);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4, P5, P6, P7);
template<class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
struct Binder<void (*)(P0, P1, P2, P3, P4, P5, P6, P7)> {
  static const int NPARAM = 8;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7);
    void (*fp)(P0, P1, P2, P3, P4, P5, P6, P7) = (void (*)(P0, P1, P2, P3, P4, P5, P6, P7))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4, P5, P6, P7);
template<class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
struct Binder<R (*)(P0, P1, P2, P3, P4, P5, P6, P7)> {
  static const int NPARAM = 8;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7);
    R (*fp)(P0, P1, P2, P3, P4, P5, P6, P7) = (R (*)(P0, P1, P2, P3, P4, P5, P6, P7))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3, P4, P5, P6, P7);
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4, P5, P6, P7)> {
  static const int NPARAM = 8;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7);
    C* (*ctor)(P0, P1, P2, P3, P4, P5, P6, P7) = (C* (*)(P0, P1, P2, P3, P4, P5, P6, P7))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3, P4, P5, P6, P7) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4, P5, P6, P7)> {
  static const int NPARAM = 8;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5, P6, P7);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4, P5, P6, P7) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4, P5, P6, P7)> {
  static const int NPARAM = 8;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5, P6, P7);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4, P5, P6, P7, P8);
template<class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
struct Binder<void (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)> {
  static const int NPARAM = 9;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8);
    void (*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8) = (void (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4, P5, P6, P7, P8);
template<class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
struct Binder<R (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)> {
  static const int NPARAM = 9;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8);
    R (*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8) = (R (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3, P4, P5, P6, P7, P8);
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)> {
  static const int NPARAM = 9;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8);
    C* (*ctor)(P0, P1, P2, P3, P4, P5, P6, P7, P8) = (C* (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3, P4, P5, P6, P7, P8) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)> {
  static const int NPARAM = 9;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5, P6, P7, P8);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4, P5, P6, P7, P8) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8)> {
  static const int NPARAM = 9;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5, P6, P7, P8);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8));
    return Type<R>::ret(mrb, result);
  }
};

// void f(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
template<class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
struct Binder<void (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> {
  static const int NPARAM = 10;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8); (void)(narg); CHECK(9);
    void (*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) = (void (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9))func_ptr;
    fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8), ARG(9));
    return mrb_nil_value();
  }
};

// R f(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
template<class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
struct Binder<R (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> {
  static const int NPARAM = 10;
  static mrb_value call(mrb_state* mrb, void* func_ptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8); (void)(narg); CHECK(9);
    R (*fp)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) = (R (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9))func_ptr;
    R result = fp(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8), ARG(9));
    return Type<R>::ret(mrb, result);
  }
};

// C* ctor(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
struct ClassBinder<C* (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> {
  static const int NPARAM = 10;
  static mrb_value ctor(mrb_state* mrb, mrb_value self, void* new_func_ptr, mrb_value* args, int narg) {
    DATA_TYPE(self) = &ClassBinder<C>::type_info;
    DATA_PTR(self) = NULL;
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8); (void)(narg); CHECK(9);
    C* (*ctor)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) = (C* (*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9))new_func_ptr;
    C* instance = ctor(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8), ARG(9));
    DATA_PTR(self) = instance;
    return self;
  }
};

// class C { void f(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) };
template<class C, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
struct ClassBinder<void (C::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> {
  static const int NPARAM = 10;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8); (void)(narg); CHECK(9);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef void (C::*M)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
    M mp = *(M*)method_pptr;
    (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8), ARG(9));
    return mrb_nil_value();
  }
};

// class C { R f(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9) };
template<class C, class R, class P0, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
struct ClassBinder<R (C::*)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)> {
  static const int NPARAM = 10;
  static mrb_value call(mrb_state* mrb, mrb_value self, void* method_pptr, mrb_value* args, int narg) {
    (void)(narg); CHECK(0); (void)(narg); CHECK(1); (void)(narg); CHECK(2); (void)(narg); CHECK(3); (void)(narg); CHECK(4); (void)(narg); CHECK(5); (void)(narg); CHECK(6); (void)(narg); CHECK(7); (void)(narg); CHECK(8); (void)(narg); CHECK(9);
    C* instance = static_cast<C*>(mrb_get_datatype(mrb, self, &ClassBinder<C>::type_info));
    typedef R (C::*M)(P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
    M mp = *(M*)method_pptr;
    R result = (instance->*mp)(ARG(0), ARG(1), ARG(2), ARG(3), ARG(4), ARG(5), ARG(6), ARG(7), ARG(8), ARG(9));
    return Type<R>::ret(mrb, result);
  }
};

#undef ARG
#undef CHECK
