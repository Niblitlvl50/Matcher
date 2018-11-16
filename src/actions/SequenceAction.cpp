
#include "SequenceAction.h"

using namespace game;

void SequenceAction::AddAction(IActionPtr action)
{
    mActions.push(action);
}

void SequenceAction::Update(unsigned int delta)
{
    if(mActions.empty())
        return;
    
    IActionPtr action = mActions.front();
    action->Update(delta);
    
    if(action->Finished())
        mActions.pop();
}

bool SequenceAction::Finished() const
{
    return mActions.empty();
}
