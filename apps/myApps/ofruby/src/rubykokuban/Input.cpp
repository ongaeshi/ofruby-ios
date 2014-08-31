#include "rubykokuban/Input.hpp"

namespace rubykokuban {
//------------------------------------------------------------
Input::Input()
: mMouse()
, mTouch()
{
}

//------------------------------------------------------------
void Input::update()
{
    mMouse.update();
    mTouch.update();
}

}
