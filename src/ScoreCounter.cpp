
#include "ScoreCounter.h"
#include "Math/Quad.h"
#include "EventHandler/EventHandler.h"
#include "ScoreEvent.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Color.h"

#include <sstream>

using namespace game;

ScoreCounter::ScoreCounter(const math::Vector& position, mono::EventHandler& handler)
    : mEventHandler(handler),
      mScore(0),
      mText("Score: 0")
{
    m_position = position;
    
    using namespace std::placeholders;
    
    const std::function<bool (const game::ScoreEvent&)> scoreFunc = std::bind(&ScoreCounter::OnScoreEvent, this, _1);
    mScoreEventToken = mEventHandler.AddListener(scoreFunc);
}

ScoreCounter::~ScoreCounter()
{
    mEventHandler.RemoveListener(mScoreEventToken);
}

bool ScoreCounter::OnScoreEvent(const game::ScoreEvent& event)
{
    ++mScore;
    std::stringstream stream;
    stream << "Score: " << mScore;
    
    mText = stream.str();

    return false;
}

void ScoreCounter::Draw(mono::IRenderer& renderer) const
{
    constexpr math::Quad quad(math::Vector(-10, -10), math::Vector(200, 25));
    constexpr mono::Color::RGBA red(1, 0, 0, 1);
    constexpr mono::Color::RGBA black(0, 0, 0, 1);
    
    renderer.DrawQuad(quad, red, 3.0f);
    renderer.DrawQuad(quad, black, 2.0f);

    renderer.DrawText(0, mText.c_str(), math::zeroVec, false, black);
}

void ScoreCounter::Update(unsigned int delta)
{ }

