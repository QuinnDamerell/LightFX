#include "Drawables/ExpandingDrawable.h"
#include "Drawables/SolidDrawable.h"
#include "Fadables/Fader.h"

using namespace LightFx;
using namespace LightFx::Drawables;
using namespace LightFx::Fadables;


ExpandingDrawable::ExpandingDrawable() :
    ExpandingDrawable(false)
{}

ExpandingDrawable::ExpandingDrawable(bool shouldCleanUp) :
    Drawable(shouldCleanUp),
    m_startingX(0),
    m_startingY(0),
    m_currentPosition(0),
    m_timeBetweenDraws(milliseconds(48)),
    m_timeUntilNextDraw(milliseconds(0))
{ }


// Called when the drawable should draw it's self.
void ExpandingDrawable::OnDrawSelf(uint64_t tickCount, milliseconds elapsedTime)
{
    // Check our draw time, return if we don't need to update yet.
    m_timeUntilNextDraw -= elapsedTime;
    if (m_timeUntilNextDraw.count() > 0)
    {
        return;
    }
    else
    {
        m_timeUntilNextDraw = m_timeBetweenDraws;
    }


    // The length we will draw
    uint64_t drawLength = m_currentPosition * 2 + 1;

    // Indicates if they are all done drawing.
    bool allSidesDone = true;

    bool topLeftCorner = false;
    bool topRightCorner = false;
    bool bottomLeftCorner = false;
    bool bottomRightCorner = false;

    // Draw for each side
    for (SquareSide side = SquareSide::Top; side < SquareSide::End;)
    {
        int64_t beginX;
        int64_t beginY;
        int64_t height;
        int64_t width;

        switch (side)
        {
        case SquareSide::Top:
            height = 1;
            width = drawLength;
            beginX = m_startingX - m_currentPosition;
            beginY = m_startingY - m_currentPosition;
            break;
        case SquareSide::Right:
            height = drawLength;
            width = 1;
            beginX = m_startingX + m_currentPosition;
            beginY = m_startingY - m_currentPosition;

            // If the corner has already been draw remove it.
            if (topRightCorner)
            {
                beginY++;
                height--;
            }
            break;
        case SquareSide::Bottom:
            height = 1;
            width = drawLength;
            beginX = m_startingX - m_currentPosition;
            beginY = m_startingY + m_currentPosition;

            // If the corner has already been draw remove it.
            if (bottomRightCorner)
            {
                width--;
            }
            break;
        case SquareSide::Left:
            height = drawLength;
            width = 1;
            beginX = m_startingX - m_currentPosition;
            beginY = m_startingY - m_currentPosition;

            // If the corner has already been draw remove it.
            if (topLeftCorner)
            {
                beginY++;
                height--;
            }
            // If the corner has already been draw remove it.
            if (bottomLeftCorner)
            {
                height--;
            }
            break;
        }

        // Clamp any other values
        if (beginY < 0)
        {
            height += beginY; // This is (-) so it will subtract
            beginY = 0;
        }
        if (beginY + height > static_cast<int64_t>(GetHeight()))
        {
            height = (GetHeight()) - beginY;
        }

        if (beginX < 0)
        {
            width += beginX; // This is (-) so it will subtract
            beginX = 0;
        }
        if (beginX + width > static_cast<int64_t>(GetWitdh()))
        {
            width = (GetWitdh()) - beginX;
        }

        if (height <= 0 || width <= 0)
        {
            // We have nothing to draw
            side = (SquareSide)((int)side + 1);
            continue;
        }
        else
        {
            // If this isn't done clear the flag
            allSidesDone = false;

            switch (side)
            {
            case SquareSide::Top:
                topLeftCorner = true;
                topRightCorner = true;
                break;
            case SquareSide::Right:
                topRightCorner = true;
                bottomRightCorner = true;
                break;
            case SquareSide::Bottom:
                bottomRightCorner = true;
                bottomLeftCorner = true;
                break;
            case SquareSide::Left:
                bottomLeftCorner = true;
                topLeftCorner = true;
                break;
            }
        }

        // Draw the side
        SolidDrawablePtr sideDraw = std::make_shared<SolidDrawable>();
        sideDraw->SetPosition(beginX, beginY, height, width);
        sideDraw->SetColor(GetColor());
        AddDrawable(sideDraw, 100);

        // Make the fader
        FaderPtr fader = std::make_shared<Fader>();
        fader->SetFrom(1);
        fader->SetTo(0);
        fader->SetDuration(milliseconds(400));
        sideDraw->SetFader(fader);

        // Set the last side we added
        m_lastDrawnSide = sideDraw;

        // Add one to side;
        side = (SquareSide)((int)side + 1);
    }
    

    // Update position
    m_currentPosition++;

    if (allSidesDone)
    {
        if (m_lastDrawnSide && m_lastDrawnSide->GetFader())
        {
            if (m_lastDrawnSide->GetFader()->IsComplete())
            {
                // If our last fader is already done clean up now.
                m_forceCleanUp = true;
            }
            else
            {
                // Otherwise attach a listener so when it is done we can clean up.
                m_lastDrawnSide->GetFader()->SetFinishedCallback(GetSharedPtr<ITimelineObjectCallback>());
            }
        }
        else
        {
            // If we don't have a last drawn clean up now
            m_forceCleanUp = true;
        }
    }
}

void ExpandingDrawable::OnTimelineFinished(ITimelineObjectPtr timeline)
{
    // Now that the last fade is done clean up
    m_forceCleanUp = true;
}
