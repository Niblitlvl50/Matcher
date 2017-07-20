
#include "Background.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Sprite/SpriteFactory.h"

using namespace game;

Background::Background()
{
    m_position = math::Vector(0.5, 0.5);
    m_scale = math::Vector(640, 1136);
    mSprite = mono::CreateSprite("res/bg.sprite");
}

void Background::Draw(mono::IRenderer& renderer) const
{
    renderer.DrawSprite(*mSprite);
}

void Background::Update(unsigned int delta)
{ }
