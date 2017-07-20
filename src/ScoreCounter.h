
#pragma once

#include "Entity/EntityBase.h"
#include "Events/EventFwd.h"
#include "EventHandler/EventToken.h"
#include <string>

namespace game
{
    struct ScoreEvent;
    
    // Keeps track of current score, also draws the score
    class ScoreCounter : public mono::EntityBase
    {
    public:
        
        //! ScoreCounter constructor
        //! @param[in] position Where the score counter should be positioned
        ScoreCounter(const math::Vector& position, mono::EventHandler& handler);
        virtual ~ScoreCounter();
        
    private:
        
        bool OnScoreEvent(const game::ScoreEvent& event);
        
        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);
        
        mono::EventHandler& mEventHandler;

        int mScore;
        std::string mText;
        
        mono::EventToken<game::ScoreEvent> mScoreEventToken;
    };
}
