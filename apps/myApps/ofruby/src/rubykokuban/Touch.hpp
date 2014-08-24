#pragma once

#include "ofEvents.h"
#include "rubykokuban/TouchPoint.hpp"

//------------------------------------------------------------
namespace rubykokuban {

class Touch {
public:
    static const int TOUCH_POINT_MAX = 5;
    
    Touch();

    TouchPoint& point(int aIndex);
    const TouchPoint& point(int aIndex) const;

    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
        
private:
    TouchPoint mPoints[TOUCH_POINT_MAX];
};

}
