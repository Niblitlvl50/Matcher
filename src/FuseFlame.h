
#pragma once

#include "Entity/EntityBase.h"
#include "Rendering/RenderPtrFwd.h"
#include "Paths/IPath.h"

namespace game
{
    class FuseFlame : public mono::EntityBase
    {
    public:
        
        FuseFlame(const math::Vector& position);
        
    private:
        
        virtual void Draw(mono::IRenderer& renderer) const;
        virtual void Update(unsigned int delta);
    
        mono::ISpritePtr mSprite;
        std::shared_ptr<mono::IPath> mPath;
        float mElapsedTime;
        math::Vector mBasePosition;
    };
}
