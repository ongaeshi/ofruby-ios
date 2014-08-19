#pragma once

//------------------------------------------------------------
namespace rubykokuban {

class TouchPoint {
public:
    TouchPoint()
    : mIsValid(false)
    , mX(0.0f)
    , mY(0.0f)
    {}
  
    void update(float aX, float aY) { mIsValid = true; mX = aX; mY = aY; }
    void clear() { mIsValid = false; }

    bool isValid() const { return mIsValid; }
    float x() const { return mX; }
    float y() const { return mY; }

private:
    bool mIsValid;
    float mX;
    float mY;
};

}
