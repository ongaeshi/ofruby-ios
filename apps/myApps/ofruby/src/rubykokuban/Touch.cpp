#include "rubykokuban/Touch.hpp"

namespace rubykokuban {
//------------------------------------------------------------
Touch::Touch()
: mPoints()
{
}

//------------------------------------------------------------
const TouchPoint& Touch::point(int aIndex) const
{
    // TODO: assert
    return mPoints[aIndex];
}

//------------------------------------------------------------
void Touch::touchDown(ofTouchEventArgs & touch)
{
    mPoints[touch.id].update(touch.x, touch.y);
}

//------------------------------------------------------------
void Touch::touchMoved(ofTouchEventArgs & touch)
{
    mPoints[touch.id].update(touch.x, touch.y);
}

//------------------------------------------------------------
void Touch::touchUp(ofTouchEventArgs & touch)
{
    mPoints[touch.id].clear();
}

}







