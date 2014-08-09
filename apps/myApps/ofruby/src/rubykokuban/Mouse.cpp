#include "rubykokuban/Mouse.hpp"

namespace rubykokuban {
//------------------------------------------------------------
Mouse::Mouse()
: mInternal()
, mX(0)
, mY(0)
, mCurrent()
, mPrev()
{
}

//------------------------------------------------------------
void Mouse::setInternalPos(int aX, int aY)
{
    mInternal.x = aX;
    mInternal.y = aY;
}

//------------------------------------------------------------
void Mouse::setInternalPress(int aCode)
{
    if (isValidate(aCode))
        mInternal.buttons.set(aCode, true);
}
 
//------------------------------------------------------------
void Mouse::setInternalRelease(int aCode)
{
    if (isValidate(aCode))
        mInternal.buttons.set(aCode, false);
}
 
//------------------------------------------------------------
void Mouse::update()
{
    mX = mInternal.x;
    mY = mInternal.y;
    mPrev = mCurrent;
    mCurrent = mInternal.buttons;
    // printf("x: %d, y: %d\n", mX, mY);
}

//------------------------------------------------------------
bool Mouse::isPress(int aCode) const
{
    if (!isValidate(aCode))
        return false;

    return !mPrev.get(aCode) && mCurrent.get(aCode);
}

//------------------------------------------------------------
bool Mouse::isDown(int aCode) const
{
    if (!isValidate(aCode))
        return false;

    return mCurrent.get(aCode);
}

//------------------------------------------------------------
bool Mouse::isRelease(int aCode) const
{
    if (!isValidate(aCode))
        return false;

    return mPrev.get(aCode) && !mCurrent.get(aCode);
}

//------------------------------------------------------------
bool Mouse::isValidate(int aCode) const
{
    return 0 <= aCode && aCode < BUTTON_TERM;
}

}
