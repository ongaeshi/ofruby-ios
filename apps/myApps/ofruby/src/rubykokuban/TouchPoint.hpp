#pragma once

//------------------------------------------------------------
namespace rubykokuban {

class TouchPoint {
public:
    TouchPoint()
    : mInternal()
    , mPrev(false)
    , mIsValid(false)
    , mX(0.0f)
    , mY(0.0f)
    {}
  
    void internalUpdate(float aX, float aY)
    {
        mInternal.isValid = true;
        mInternal.x = aX;
        mInternal.y = aY;
    }

    void internalClear()
    {
        mInternal.isValid = false;
    }

    void update()
    {
        mPrev    = mIsValid;
        mIsValid = mInternal.isValid;
        mX       = mInternal.x;
        mY       = mInternal.y;
    }

    bool isValid() const { return mIsValid; }
    float x() const { return mX; }
    float y() const { return mY; }

    bool isPress() const   { return !mPrev && mIsValid; }
    bool isDown() const    { return mIsValid; }
    bool isRelease() const { return mPrev && !mIsValid; }

private:
    struct Internal {
        Internal()
        : isValid()
        , x(0)
        , y(0)
        {}

        bool isValid;
        int x;
        int y;
    };

    Internal  mInternal;
    bool      mPrev;
    bool      mIsValid;
    float     mX;
    float     mY;
};

}
