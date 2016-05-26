#include "Drawables/SolidDrawable.h"

using namespace LightFx;
using namespace LightFx::Drawables;

void SolidDrawable::SetPosition(int64_t x, int64_t y, int64_t height, int64_t width)
{
    m_x = x;
    m_y = y;
    m_height = height;
    m_width = width;
}

// Called when the drawable should draw it's self.
void SolidDrawable::OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
{
    Pixel pixel = GetColor();
    m_bitmap->FillRect(pixel, m_y, m_x, m_x + m_width, m_y + m_height);
}
