
#pragma once

#include "Zone/ZoneBase.h"
#include "Events/EventFwd.h"
#include "EventHandler/EventToken.h"

namespace game
{
    class TextObject;
    
    class StartZone : public mono::ZoneBase
    {
    public:

        StartZone(mono::EventHandler& eventHandler);
                
        virtual void OnLoad(mono::ICameraPtr& camera);
        virtual void OnUnload();
        
        bool Quit() const;
        
    private:
        
        bool OnMouseMotion(const event::MouseMotionEvent& event);
        bool OnMouseUp(const event::MouseUpEvent& event);
        
        void AddListeners();
        void RemoveListeners();

        mono::EventHandler& mEventHandler;        
        mono::EventToken<event::MouseMotionEvent> mMouseMotionToken;
        mono::EventToken<event::MouseUpEvent> mMouseUpToken;
        
        std::shared_ptr<TextObject> mStartText;
        std::shared_ptr<TextObject> mExitText;

        bool mQuit;
    };
}
