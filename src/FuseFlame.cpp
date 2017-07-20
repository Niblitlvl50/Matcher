
#include "FuseFlame.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Sprite/ISprite.h"
#include "Rendering/Sprite/SpriteFactory.h"
#include "Paths/PathFactory.h"

using namespace game;

FuseFlame::FuseFlame(const math::Vector& position)
    : mElapsedTime(0.0f)
{
    m_scale = math::Vector(20, 20);
    mBasePosition = position;

    mSprite = mono::CreateSprite("res/explosion.sprite");
    mPath = mono::CreatePath("res/fuse_path.path");
}

void FuseFlame::Draw(mono::IRenderer& renderer) const
{
    renderer.DrawSprite(*mSprite);
}

void FuseFlame::Update(unsigned int delta)
{
    mSprite->doUpdate(delta);

    mElapsedTime += delta;

    // 60000 == 60 seconds
    const float duration = 60000.0f;
    const float time = mElapsedTime / duration;
    const float position = mPath->Length() * time;

    m_position = mPath->GetPositionByLength(position) + mBasePosition;
}
