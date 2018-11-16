
#pragma once

#include "IUpdatable.h"
#include "actions/IAction.h"
#include <vector>

namespace game
{
    class ActionManager : public mono::IUpdatable
    {
    public:
        
        //! Add an action that will be performed and tracked
        //! @param[in] action An action
        void AddAction(IActionPtr action);
        
        //! Check if there are any active actions
        //! @return Will return true if there is, else false
        bool HasActiveActions() const;
        
    private:
        
        virtual void doUpdate(unsigned int delta);
        std::vector<IActionPtr> mActions;
    };
}
