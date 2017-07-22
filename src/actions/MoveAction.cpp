
#include "MoveAction.h"
#include "Entity/IEntity.h"
#include <algorithm>

using namespace game;

MoveAction::MoveAction(mono::IEntityPtr entity, const math::Vector& target, unsigned int duration)
    : mEntity(entity),
      mTarget(target),
      mDuration(duration),
      mCounter(0),
      mDoOnce(true)
{ }

void MoveAction::Update(unsigned int delta)
{
    if(mDoOnce)
    {
        mPosition = mEntity->Position();
        mVector = mTarget - mPosition;
        mDoOnce = false;
    }
    
    mCounter += delta;
    mCounter = std::min(mCounter, mDuration);
    const float percent = float(mCounter) / float(mDuration);
    const math::Vector position = mPosition + (mVector * percent);

    mEntity->SetPosition(position);
    
    // Call the callback if there is one
    const bool finished = (mCounter >= mDuration);
    if(finished && mCallback)
        mCallback(mEntity);
}

bool MoveAction::Finished() const
{
    return (mCounter >= mDuration);
}

void MoveAction::SetCallback(const std::function<void (mono::IEntityPtr)>& callback)
{
    mCallback = callback;
}
