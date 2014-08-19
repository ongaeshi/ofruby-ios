#pragma once

#include "ofEvents.h"
#include "rubykokuban/TouchPoint.hpp"

//------------------------------------------------------------
namespace rubykokuban {

class Touch {
public:
    Touch();

    const TouchPoint& point(int aIndex) const;

    void touchDown(ofTouchEventArgs & touch);
    void touchMoved(ofTouchEventArgs & touch);
    void touchUp(ofTouchEventArgs & touch);
        
private:
    static const int TOUCH_POINT_MAX = 5;
    
    TouchPoint mPoints[TOUCH_POINT_MAX];
};

}
