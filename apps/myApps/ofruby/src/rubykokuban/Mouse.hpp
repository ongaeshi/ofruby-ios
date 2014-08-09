#pragma once

//------------------------------------------------------------
namespace rubykokuban {
class Mouse {
public:
    enum ButtonCode {
        L_BUTTON,
        M_BUTTON,
        R_BUTTON,
        BUTTON_TERM
    };
    
    Mouse();

    void setInternalPos(int aX, int aY);
    void setInternalPress(int aCode);
    void setInternalRelease(int aCode);
    
    void update();

    int x() const { return mX; }
    int y() const { return mY; }

    bool isPress(int aCode) const;
    bool isDown(int aCode) const;
    bool isRelease(int aCode) const;

private:
    class Buttons {
    public:
        Buttons()
        {
            for (int i = 0; i < BUTTON_TERM; ++i)
                mButtons[i] = false;
        }

        bool get(int aCode) const { return mButtons[aCode]; }
        void set(int aCode, bool aValue) { mButtons[aCode] = aValue; }

    private:
        bool mButtons[BUTTON_TERM];
    };
        
    struct Internal {
        Internal()
        : x(0)
        , y(0)
        , buttons()
        {}
            
        int x;
        int y;
        Buttons buttons;
    };

    bool isValidate(int aCode) const;

    Internal mInternal;
    int mX;
    int mY;
    Buttons mCurrent;
    Buttons mPrev;
};

}
