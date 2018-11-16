
#include "SpriteEntity.h"

#include "Rendering/IRenderer.h"
#include "Rendering/Sprite/SpriteFactory.h"
#include "Rendering/Sprite/ISprite.h"

SpriteEntity::SpriteEntity(const char* sprite_file)
{
    sprite = mono::CreateSprite(sprite_file);
}

SpriteEntity::~SpriteEntity()
{ }

void SpriteEntity::Draw(mono::IRenderer& renderer) const
{
    renderer.DrawSprite(*sprite);
}

void SpriteEntity::Update(unsigned int delta)
{
    sprite->doUpdate(delta);
}
