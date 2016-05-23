#include "Drawables/SolidDrawable.h"

using namespace LightFx;
using namespace LightFx::Drawables;

void SolidDrawable::SetPosition(uint64_t x, uint64_t y, uint64_t height, uint64_t width)
{
    m_x = x;
    m_y = y;
    m_height = height;
    m_width = width;
}

// Sets the draw color
void SolidDrawable::SetColor(Pixel color)
{
    m_color = color;
}

// Called when the drawable should draw it's self.
void SolidDrawable::OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
{
    m_bitmap->FillRect(m_color, m_y, m_x, m_x + m_width, m_y + m_height);
}
