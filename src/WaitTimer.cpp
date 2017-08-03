
#include "WaitTimer.h"

using namespace game;

WaitTimer::WaitTimer()
{ }

WaitTimer::WaitTimer(unsigned int wait)
    : mWait(wait)
{ }

void WaitTimer::SetTimeout(unsigned int wait)
{
    mWait = wait;
}

bool WaitTimer::IsSignaled() const
{
    const bool signal = mSignal;
    mSignal = false;
    
    return signal;
}

void WaitTimer::doUpdate(unsigned int delta)
{
    mCounter += delta;
    if(mCounter >= mWait)
    {
        mCounter = mCounter - mWait;
        mSignal = true;
    }
}
