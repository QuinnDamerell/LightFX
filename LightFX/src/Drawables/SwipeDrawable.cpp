#include "Drawables/SwipeDrawable.h"
#include "Drawables/SolidDrawable.h"
#include "Fadables/Fader.h"

using namespace LightFx;
using namespace LightFx::Drawables;
using namespace LightFx::Fadables;


// Called when the drawable should draw it's self.
void SwipeDrawable::OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
{
    SolidDrawablePtr solidDraw = std::make_shared<SolidDrawable>(true);

    bool isFinalPass = false;
    int64_t position;

    switch (m_direction)
    {
    case SwipeDirection::Down:
    case SwipeDirection::Up:

        position = m_currentPosition;
        if (m_direction == SwipeDirection::Up)
        {
            position = (GetHeight() - 1) - position;
        }

        if (position < 0 || position == GetHeight())
        {
            // We are done, leave now. When the fader complete fire we will
            // clean up.
            return;
        }

        // Set if this is the final pass
        isFinalPass = (m_direction == SwipeDirection::Down && m_currentPosition == 0)
            || (m_direction == SwipeDirection::Up && m_currentPosition == GetHeight() - 1);

        solidDraw->SetPosition(0, position, 1, GetWitdh());
        break;
    default:

        position = m_currentPosition;
        if (m_direction == SwipeDirection::Left)
        {
            position = (GetWitdh() - 1) - position;
        }

        if (position < 0 || position == GetWitdh())
        {
            // We are done, leave now. When the fader complete fire we will
            // clean up.
            return;
        }

        // Set if this is the final pass
        isFinalPass = (m_direction == SwipeDirection::Left && m_currentPosition == 0)
            || (m_direction == SwipeDirection::Right && m_currentPosition == GetWitdh() - 1);

        solidDraw->SetPosition(position, 0, GetHeight(), 1);
        break;
    }

    // Iterate the current pos
    m_currentPosition++;

    // Make the fader
    FaderPtr fader = std::make_shared<Fader>();
    fader->SetFrom(1);
    fader->SetTo(0);
    fader->SetDuration(milliseconds(400));
    solidDraw->SetFader(fader);

    // Set the color
    solidDraw->SetColor(GetColor());

    // If this is the last row add a call back so we can clean up.
    if (isFinalPass)
    {
        fader->SetFinishedCallback(std::dynamic_pointer_cast<ITimelineObjectCallback>(shared_from_this()));
    }

    // Finally add the drawable
    AddDrawable(solidDraw, 100);  
}

void SwipeDrawable::OnTimelineFinished(ITimelineObjectPtr timeline)
{
    // We are done, so force our clean up.
	SetCleanupFlag(true);
}
