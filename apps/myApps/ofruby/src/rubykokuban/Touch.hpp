#pragma once

#include "rubykokuban/TouchPoint.hpp"

//------------------------------------------------------------
namespace rubykokuban {

class Touch {
public:
    Touch();
        
private:
    static const int TOUCH_POINT_MAX = 5;

    class Internal {
         TouchPoint mPoints[TOUCH_POINT_MAX];
    };

    Internal mInternal;
};

}
