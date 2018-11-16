
#pragma once

#include "Entity/EntityBase.h"
#include "Rendering/RenderPtrFwd.h"

namespace game
{
    //! This class will draw the background
    class Background : public mono::EntityBase
    {
    public:
        
        Background();
        ~Background();
        
    private:
        
        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);
        
        mono::ISpritePtr mSprite;
    };
}
