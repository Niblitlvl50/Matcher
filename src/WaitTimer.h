
#pragma once

#include "IUpdatable.h"

namespace game
{
    class WaitTimer : public mono::IUpdatable
    {
    public:
        
        //! A timer that you wait on
        //! @param[in] wait Milliseconds before the timer will signal
        WaitTimer(unsigned int wait);
        
        //! Check if it has timed out yet
        //! @return bool True if timed out, else false
        bool IsSignaled() const;
                
        virtual void doUpdate(unsigned int delta);

    private:
        
        const unsigned int mWait;
        unsigned int mCounter;
        mutable bool mSignal;
    };
}
