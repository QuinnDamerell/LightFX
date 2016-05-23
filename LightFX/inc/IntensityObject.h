#pragma once

#include "Common.h"
#include "IIntensityObject.h"
#include "Fadables/IFader.h"

namespace LightFx
{
    DECLARE_SMARTPOINTER(IntensityObject);
    class IntensityObject :
        public IIntensityObject,
        public std::enable_shared_from_this<IntensityObject>
    {
    public:
        IntensityObject() :
            IntensityObject(1)
        {}

        IntensityObject(double intensity) :
            m_intensity(intensity)
        { }

        // Gets the intensity
        virtual double GetIntensity() 
        {
            return m_intensity;
        }

        // Sets the intensity
        virtual void SetIntensity(double intensity)
        {
            m_intensity = intensity;
        }

        // Sets a fader object on this object
        virtual void SetFader(Fadables::IFaderPtr fader)
        {
            if (m_fader)
            {
                // If we had a fader remove ourselves.
                m_fader->RemoveFadingDrawable(shared_from_this());
            }

            m_fader = fader;

            if (m_fader)
            {
                // If we have a fader send register ourselves
                m_fader->AddFadingDrawable(shared_from_this());
            }
        }

        // Sets a fader object on this object
        virtual Fadables::IFaderPtr GetFader()
        {
            return m_fader;
        }

    private:
        double m_intensity;
        Fadables::IFaderPtr m_fader;
    };
}
