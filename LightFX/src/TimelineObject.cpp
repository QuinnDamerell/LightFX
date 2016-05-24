#include "TimelineObject.h"

using namespace LightFx;


void TimelineObject::OnTick(uint64_t tick, milliseconds elapsedTime)
{
    // If we have no remaining time we are done.
    if (m_remaining.count() <= 0)
    {
        return;
    }

    // Check the tick count to make sure we aren't updating twice.
    // This can happen if the same fade is held by two different objects
    if (tick != m_lastUpdateTickCount)
    {
        m_lastUpdateTickCount = tick;
        m_remaining -= elapsedTime;
    }

    // Check if we are finished
    if (m_remaining.count() <= 0)
    {
        SetFinished(true);
    }
}

// Returns the progress.
double TimelineObject::GetProgress()
{
    double progress;
    if (m_duration.count() == 0)
    {
        progress = 1.0;
    }
    else
    {
        progress = (static_cast<double>(m_remaining.count()) / static_cast<double>(m_duration.count()));
    }
    return progress > 1 ? 1 : (progress < 0 ? 0 : progress);
}

// Returns an interpolated value between from and to based on progress.
double TimelineObject::InterpolateValue(double from, double to)
{
    return to - (to - from) * GetProgress();
}

// Called by the base class to set the duration.
void TimelineObject::SetDuration(milliseconds duration)
{
    m_duration = duration;
    m_remaining = m_duration;
}

// Callable by the base class to report it is done.
void TimelineObject::SetFinished(bool finished)
{
    m_remaining = milliseconds(0);

    // Fire the callback.
    FireFinishedCallback();
}

// Fires the callback if it is there.
void TimelineObject::FireFinishedCallback()
{
    if (auto callback = m_finishedCallback.lock())
    {
        callback->OnTimelineFinished(GetSharedPtr<ITimelineObject>());
    }
}