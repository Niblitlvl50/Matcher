
#include "CountdownTimer.h"
#include "EventHandler/EventHandler.h"
#include "CountdownEvent.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Color.h"
#include <sstream>

using namespace game;

CountdownTimer::CountdownTimer(int seconds, const math::Vector& position, mono::EventHandler& handler)
    : mSeconds(seconds),
      mEventHandler(handler),
      mTimer(1000)
{
    m_position = position;
    UpdateText();
}

void CountdownTimer::Draw(mono::IRenderer& renderer) const
{
    renderer.DrawText(0, mText.c_str(), math::zeroVec, true, mono::Color::RGBA(0, 0, 0));
}

void CountdownTimer::Update(unsigned int delta)
{
    mTimer.doUpdate(delta);
    
    const bool signal = mTimer.IsSignaled();
    if(signal)
    {
        --mSeconds;
        UpdateText();
    }
    
    if(mSeconds < 0)
        mEventHandler.DispatchEvent(game::CountdownEvent());
}

void CountdownTimer::UpdateText()
{
    std::stringstream stream;
    stream << "Time: " << mSeconds;
    mText = stream.str();
}
