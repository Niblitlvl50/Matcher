
#include "StartZone.h"
#include "Rendering/IRenderer.h"
#include "Rendering/ICamera.h"
#include "Rendering/IDrawable.h"
#include "Math/Vector.h"
#include "Math/MathFunctions.h"
#include "IUpdater.h"

#include "Background.h"
#include "TextObject.h"
#include "Gem.h"
#include "RenderLayers.h"

#include "EventHandler/EventHandler.h"
#include "Events/EventFuncFwd.h"
#include "Events/MouseEvent.h"
#include "Events/MouseEvent.h"
#include "Events/QuitEvent.h"


using namespace game;

StartZone::StartZone(mono::EventHandler& eventHandler)
    : mEventHandler(eventHandler),
      mQuit(false)
{ }

void StartZone::AddListeners()
{
    using namespace std::placeholders;
    
    const event::MouseMotionEventFunc mouseMotionFunc = std::bind(&StartZone::OnMouseMotion, this, _1);
    mMouseMotionToken = mEventHandler.AddListener(mouseMotionFunc);
    
    const event::MouseUpEventFunc mouseUpFunc = std::bind(&StartZone::OnMouseUp, this, _1);
    mMouseUpToken = mEventHandler.AddListener(mouseUpFunc);
}

void StartZone::RemoveListeners()
{
    mEventHandler.RemoveListener(mMouseMotionToken);
    mEventHandler.RemoveListener(mMouseUpToken);
}

void StartZone::OnLoad(mono::ICameraPtr& camera)
{
    AddListeners();    
    camera->SetPosition(math::Vector(0, 0));
    
    auto title_text = std::make_shared<TextObject>("Mega Miner!", mono::Color::RGBA(1, 1, 1, 1), math::Vector(0, 150));
    mStartText = std::make_shared<TextObject>("Start mining!", mono::Color::RGBA(1, 0, 0, 1), math::Vector(0, 50));
    mExitText = std::make_shared<TextObject>("Exit", mono::Color::RGBA(1, 0, 0, 1), math::Vector(0, 0));
    
    auto mGemLeft = game::CreateRandomGem(math::Vector(-185, 160));
    auto mGemRight = game::CreateRandomGem(math::Vector(185, 160));

    mGemLeft->SetScale(math::Vector(100.0f, 100.0f));
    mGemRight->SetScale(math::Vector(100.0f, 100.0f));

    AddEntity(std::make_shared<Background>(), BACKGROUND);
    AddEntity(mGemLeft, MIDDLEGROUND);
    AddEntity(mGemRight, MIDDLEGROUND);
    AddDrawable(title_text, FOREGROUND);
    AddDrawable(mStartText, FOREGROUND);
    AddDrawable(mExitText, FOREGROUND);
}

void StartZone::OnUnload()
{
    RemoveListeners();
}

bool StartZone::Quit() const
{
    return mQuit;
}

bool StartZone::OnMouseMotion(const event::MouseMotionEvent& event)
{
    const math::Vector point(event.worldX, event.worldY);
    
    const math::Quad startBB = mStartText->BoundingBox();
    const math::Quad exitBB = mExitText->BoundingBox();
    
    const bool insideStart = math::PointInsideQuad(point, startBB);
    const bool insideExit = math::PointInsideQuad(point, exitBB);
    
    const mono::Color::RGBA red(1, 0, 0, 1);
    const mono::Color::RGBA green(0, 1, 0, 1);
    
    const mono::Color::RGBA startColor = insideStart ? green : red;
    const mono::Color::RGBA exitColor = insideExit ? green : red;
    
    mStartText->SetColor(startColor);
    mExitText->SetColor(exitColor);

    return false;
}

bool StartZone::OnMouseUp(const event::MouseUpEvent& event)
{
    const math::Vector point(event.worldX, event.worldY);
    
    const math::Quad startBB = mStartText->BoundingBox();
    const math::Quad exitBB = mExitText->BoundingBox();
    
    const bool insideStart = math::PointInsideQuad(point, startBB);
    const bool insideExit = math::PointInsideQuad(point, exitBB);

    mQuit = insideExit;
    if(insideStart || insideExit)
        mEventHandler.DispatchEvent(event::QuitEvent());

    return false;
}

