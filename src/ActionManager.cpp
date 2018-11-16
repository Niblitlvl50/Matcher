
#include "ActionManager.h"

using namespace game;

void ActionManager::AddAction(IActionPtr action)
{
    mActions.push_back(action);
}

bool ActionManager::HasActiveActions() const
{
    return !mActions.empty();
}

void ActionManager::doUpdate(unsigned int delta)
{
    for(IActionPtr action : mActions)
        action->Update(delta);
    
    const auto removeFunc = [](IActionPtr action) {
        return action->Finished();
    };
    
    const auto it = std::remove_if(mActions.begin(), mActions.end(), removeFunc);
    if(it != mActions.end())
        mActions.erase(it, mActions.end());
}
