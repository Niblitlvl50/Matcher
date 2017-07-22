
#include "Gem.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Sprite/SpriteFactory.h"
#include "Rendering/Sprite/ISprite.h"
#include "Rendering/Color.h"
#include "Random.h"

using namespace game;

class SpriteEntity : public mono::EntityBase
{
public:

    SpriteEntity(const char* sprite_file)
    {
        sprite = mono::CreateSprite(sprite_file);
    }

    void Draw(mono::IRenderer& renderer) const
    {
        renderer.DrawSprite(*sprite);
    }

    void Update(unsigned int delta)
    {
        sprite->doUpdate(delta);
    }

    mono::ISpritePtr sprite;        
};

Gem::Gem(const GemSetup& data)
    : mType(data.type),
      mSelected(false)
{
    m_scale = math::Vector(35, 35);

    auto shadow = std::make_shared<SpriteEntity>("res/shadow.sprite");
    shadow->SetPosition(math::Vector(0.0f, -0.3f));
    shadow->SetScale(math::Vector(1.1f, 0.6f));

    m_face = std::make_shared<SpriteEntity>("res/face.sprite");
    m_face->SetScale(math::Vector(0.85f, 0.3f));
    m_face->SetPosition(math::Vector(0.0f, -0.25f));

    m_face->sprite->SetAnimation(data.animation);

    auto body = std::make_shared<SpriteEntity>(data.body_sprite);

    AddChild(shadow);
    AddChild(body);
    AddChild(m_face);

    const int tree_to_sixty = mono::RandomInt(3000, 60000);
    m_timer.SetTimeout(tree_to_sixty);
}

void Gem::Draw(mono::IRenderer& renderer) const
{
    if(mSelected)
    {
        constexpr mono::Color::RGBA color(1, 1, 1, 1);
        renderer.DrawCircle(math::Vector(0, 0), 0.55, 20, 2.0f, color);
    }
}

void Gem::Update(unsigned int delta)
{
    m_timer.doUpdate(delta);

    const bool signal = m_timer.IsSignaled();
    if(signal)
    {
        const auto callback = [this]() {
            m_face->sprite->SetAnimation("brown_eyes");
        };

        m_face->sprite->SetAnimation("blink1", callback);
    }
}

GemType Gem::GetType() const
{
    return mType;
}

void Gem::SetSelected(bool selected)
{
    mSelected = selected;
}

std::shared_ptr<game::Gem> game::CreateRandomGem(const math::Vector& position)
{
    constexpr GemSetup data_table[] = {
        { "res/body_red.sprite",    "green_eyes",     GemType::RED    },
        { "res/body_green.sprite",  "brown_eyes",     GemType::GREEN  },
        { "res/body_blue.sprite",   "green_eyes",     GemType::BLUE   },
        { "res/body_yellow.sprite", "blue_eyes",      GemType::YELLOW },
        { "res/body_purple.sprite", "brown_eyes",     GemType::PURPLE },
        { "res/body_black.sprite",  "res/eye.sprite", GemType::BLACK  },
    };

    const int random_int = mono::RandomInt(0, 4);
    
    std::shared_ptr<Gem> gem = std::make_shared<Gem>(data_table[random_int]);
    gem->SetPosition(position);
    
    return gem;
}
