#include "Panel.h"

using namespace LightFx;
using namespace LightFx::Drawables;

Panel::Panel(int64_t height, int64_t width)
{
    // Make the back buffer
    m_backBuffer = std::make_shared<Bitmap>(height, width);

    // Set our size.
    SetSize(height, width);
}

void Panel::OnTick(uint64_t tick, milliseconds elapsedTime)
{
    // Clear the buffer
    m_backBuffer->Clear();

    // Kick off the drawing
    OnDraw(tick, elapsedTime, m_backBuffer);

    // Now that we have drawn, report that we have an update to the panel
    if (auto callback = m_renderedCallback.lock())
    {
        callback->OnPanelRendered();
    }
}

