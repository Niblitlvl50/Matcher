
#include "ScaleAction.h"
#include <algorithm>

using namespace game;

ScaleAction::ScaleAction(math::Vector& scale, unsigned int duration)
    : mScale(scale),
      mTargetScale(scale),
      mDuration(duration),
      mCounter(0)
{ }

void ScaleAction::Update(unsigned int delta)
{
    mCounter += delta;
    mCounter = std::min(mCounter, mDuration);
    const float scale = float(mCounter) / float(mDuration);
    mScale = mTargetScale * scale;
}
    
bool ScaleAction::Finished() const
{
    return (mCounter >= mDuration);
}
    
