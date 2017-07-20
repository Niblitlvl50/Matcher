
#pragma once

#include "Entity/EntityBase.h"
#include "WaitTimer.h"
#include "Math/MathFwd.h"
#include <string>

namespace game
{
    class CountdownTimer : public mono::EntityBase
    {
    public:
        
        //! A graphical count down timer, will send an event when the time is up
        //! @param[in] second How many seconds to count down
        //! @param[in] position Position of the timer, in world coordinates
        CountdownTimer(int seconds, const math::Vector& position, mono::EventHandler& handler);
        
    private:
        
        void UpdateText();
        
        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);
    
        int mSeconds;
        mono::EventHandler& mEventHandler;
        WaitTimer mTimer;
        std::string mText;
    };
}
