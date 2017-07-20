
#include "System/System.h"
#include "Audio/AudioSystem.h"
#include "Rendering/RenderSystem.h"

#include "Rendering/Text/TextFunctions.h"

#include "Engine.h"
#include "Math/Vector.h"
#include "EventHandler/EventHandler.h"
#include "Camera/TraceCamera.h"

#include "StartZone.h"
#include "MiningZone.h"

#include <memory>

namespace
{
    enum class GameFlow
    {
        START_ZONE,
        MINING_ZONE,
        EXIT
    };
}

int main()
{
    System::Initialize();
    mono::InitializeAudio();
    mono::InitializeRender();

    constexpr math::Vector size(640, 1136);

    std::unique_ptr<System::IWindow> window(System::CreateWindow("Mega Miner!", size.x, size.y, false));

    mono::LoadFont(0, "res/fonts/pixelette.ttf", 35.0f);

    mono::ICameraPtr camera = std::make_shared<mono::TraceCamera>(size.x, size.y);
    mono::EventHandler eventHandler;

    mono::Engine engine(window.get(), camera, eventHandler);
    
    GameFlow flow = GameFlow::START_ZONE;

    while(flow != GameFlow::EXIT)
    {
        if(flow == GameFlow::START_ZONE)
        {
            std::shared_ptr<game::StartZone> zone = std::make_shared<game::StartZone>(eventHandler);
            engine.Run(zone);

            const bool quit = zone->Quit();
            flow = quit ? GameFlow::EXIT : GameFlow::MINING_ZONE;
        }
        else if(flow == GameFlow::MINING_ZONE)
        {
            engine.Run(std::make_shared<game::MiningZone>(eventHandler));
            flow = GameFlow::START_ZONE;
        }
    }

    mono::ShutdownRender();
    mono::ShutdownAudio();
    System::Shutdown();

    return 0;
}
