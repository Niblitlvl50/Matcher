
#pragma once

#include "IAction.h"
#include "Math/Vector.h"

namespace game
{
    class ScaleAction : public mono::IAction
    {
    public:
        
        //! A scaling action
        //! @param[in] scale A reference to a scale value, this will be modified
        //! @param[in] duration Time in milliseconds for the action
        ScaleAction(math::Vector& scale, unsigned int duration);
        
    private:
        
        virtual void Update(unsigned int delta);
        virtual bool Finished() const;
        
        math::Vector& mScale;
        const math::Vector mTargetScale;
        const unsigned int mDuration;
        unsigned int mCounter;
    };
}
