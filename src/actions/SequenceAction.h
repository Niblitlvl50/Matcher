
#pragma once

#include "IAction.h"
#include "MonoPtrFwd.h"
#include <queue>

namespace game
{
    //! This class will handle a sequence of actions
    class SequenceAction : public IAction
    {
    public:
        
        //! Adds an action to the sequence
        //! @param[in] action A action
        void AddAction(IActionPtr action);
        
    private:
        
        virtual void Update(unsigned int delta);
        virtual bool Finished() const;
        
        std::queue<IActionPtr> mActions;
    };
}
