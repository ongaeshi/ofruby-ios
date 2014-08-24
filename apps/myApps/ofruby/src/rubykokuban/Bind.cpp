#include "rubykokuban/Bind.hpp"

namespace rubykokuban {
    extern void BindApplication(mrb_state* mrb);
    extern void BindGraphics(mrb_state* mrb);
    extern void BindMath(mrb_state* mrb);
}

#include "rubykokuban/BindColor.hpp"
#include "rubykokuban/BindImage.hpp"
#include "rubykokuban/BindInput.hpp"
#include "rubykokuban/BindTouchPoint.hpp"

namespace rubykokuban {

//----------------------------------------------------------
void Bind::All(mrb_state* mrb)
{
    BindApplication(mrb);
    BindColor::Bind(mrb);
    BindGraphics(mrb);
    BindImage::Bind(mrb);
    BindInput::Bind(mrb);
    BindMath(mrb);
}

}
