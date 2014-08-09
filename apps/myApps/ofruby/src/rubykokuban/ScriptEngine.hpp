#pragma once

#include "mruby.h"
#include <string>

//----------------------------------------------------------
namespace rubykokuban {

class ScriptEngine {
public:
    ScriptEngine(const char* aScriptPath);
    ~ScriptEngine();

    mrb_state* mrb() { return mMrb; }

    void setup();

    // Create need function only
    void funcallIf(const char* aName);
    void funcallIf(mrb_value aModule, const char* aName);
    void funcallIf(const char* aName, mrb_value aArg1, mrb_value aArg2);
    void funcallIf(const char* aName, mrb_value aArg1, mrb_value aArg2, mrb_value aArg3);

    void draw();
    void reload();

private:
    void open();
    void load();
    void close();
    
    struct RClass* kernel_module() { return mMrb->kernel_module; }
    mrb_value      kernel_obj()    { return mrb_obj_value(kernel_module()); }

    bool isExistFunction(mrb_value aSelf, const char* aFuncName);
    void closeOnException();

    const char* mScriptPath;            // Need full path
    mrb_state*  mMrb;
    std::string mErrorMsg;
    struct RClass* mConsoleModule;
};

}
