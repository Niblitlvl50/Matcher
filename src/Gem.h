
#pragma once

#include "Entity/EntityBase.h"
#include "Rendering/RenderPtrFwd.h"

#include "WaitTimer.h"

class SpriteEntity;

namespace game
{
    //! The different types of gems
    enum class GemType
    {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        PURPLE,
        BLACK
    };

    struct GemSetup
    {
        const char* body_sprite;
        const char* animation;
        GemType type;
    };
    
    class Gem : public mono::EntityBase
    {
    public:
        
        //! Gem constructor
        //! @param[in] sprite A filepath to a sprite file
        //! @param[in] type The gemtype
        Gem(const GemSetup& data);
        
        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);
        
        //! Get the type of gem
        //! @return GemType Returns the type of the gem
        GemType GetType() const;
        
        //! Set the gem selected or not
        //! @param[in] selected True if selected, false otherwise
        void SetSelected(bool selected);
        
    private:

        GemType mType;
        bool mSelected;

        std::shared_ptr<SpriteEntity> m_face;
        WaitTimer m_timer;
    };
    
    //! Create a random Gem at x, y position
    //! @param[in] position The position
    //! @return std::shared_ptr<Gem> A gem pointer
    std::shared_ptr<Gem> CreateRandomGem(const math::Vector& position);
}
