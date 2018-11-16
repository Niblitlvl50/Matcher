
#pragma once

#include "Zone/ZoneBase.h"
#include "Events/EventFwd.h"
#include "EventHandler/EventToken.h"
#include "Globals.h"
#include "Math/Point.h"

namespace game
{
    class ActionManager;
    class GemGrid;
    struct CountdownEvent;
    
    //! This is the zone/scene for the entire game
    class MiningZone : public mono::ZoneBase
    {
    public:
        
        MiningZone(mono::EventHandler& eventHandler);
        virtual ~MiningZone();

        virtual void OnLoad(mono::ICameraPtr& camera);
        virtual int OnUnload();
        
    private:
                
        bool OnCountdown(const game::CountdownEvent& event);
        bool OnMouseDown(const event::MouseDownEvent& event);
        bool OnMouseUp(const event::MouseUpEvent& event);
        bool OnKeyUp(const event::KeyUpEvent& event);
        
        void DoSwap(const math::Point& selected_cell, const math::Point& cell);
        
        mono::EventHandler& mEventHandler;
        
        mono::EventToken<event::MouseDownEvent> mMouseDownToken;
        mono::EventToken<event::MouseUpEvent> mMouseUpToken;
        mono::EventToken<event::KeyUpEvent> mKeyUpToken;
        mono::EventToken<game::CountdownEvent> mCountdownToken;
    
        std::shared_ptr<ActionManager> mActionManager;
        std::shared_ptr<GemGrid> mGemGrid;
        GemMatrix mMatrix;
        
        bool mHasSelectedGem;
        math::Point mSelectedCell;
    };
}
