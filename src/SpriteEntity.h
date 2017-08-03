
#pragma once

#include "Entity/EntityBase.h"
#include "Rendering/RenderPtrFwd.h"

class SpriteEntity : public mono::EntityBase
{
public:

    SpriteEntity(const char* sprite_file);
    void Draw(mono::IRenderer& renderer) const;
    void Update(unsigned int delta);

    mono::ISpritePtr sprite;        
};
