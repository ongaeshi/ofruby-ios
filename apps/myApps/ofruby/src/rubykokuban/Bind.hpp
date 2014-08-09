#pragma once

struct mrb_state;

//----------------------------------------------------------
namespace rubykokuban {

class Bind {
public:
    static void All(mrb_state* mrb);
};

}
