#include "rubykokuban/Input.hpp"

namespace rubykokuban {
//------------------------------------------------------------
Input::Input()
: mMouse()
{
}

//------------------------------------------------------------
void Input::update()
{
    mMouse.update();
}

}
