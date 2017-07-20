
#include "Gem.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Sprite/SpriteFactory.h"
#include "Rendering/Color.h"
#include "Random.h"

using namespace game;

namespace
{
    class SpriteEntity : public mono::EntityBase
    {
    public:

        SpriteEntity(const char* sprite_file)
        {
            m_sprite = mono::CreateSprite(sprite_file);
        }

        void Draw(mono::IRenderer& renderer) const
        {
            renderer.DrawSprite(*m_sprite);
        }

        void Update(unsigned int delta)
        { }

        mono::ISpritePtr m_sprite;        
    };
}

Gem::Gem(const GemData& data)
    : mType(data.type),
      mSelected(false)
{
    m_scale = math::Vector(35, 35);

    auto shadow = std::make_shared<SpriteEntity>("res/shadow.sprite");
    shadow->SetPosition(math::Vector(0.0f, -0.3f));
    shadow->SetScale(math::Vector(1.1f, 0.6f));

    auto face = std::make_shared<SpriteEntity>(data.face_sprite);
    face->SetScale(math::Vector(0.85f, 0.3f));
    face->SetPosition(math::Vector(0.0f, -0.25f));

    auto body = std::make_shared<SpriteEntity>(data.body_sprite);

    AddChild(shadow);
    AddChild(body);
    AddChild(face);
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
{ }

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
    constexpr GemData data_table[] = {
        { "res/body_red.sprite",    "res/face_green.sprite", GemType::RED    },
        { "res/body_green.sprite",  "res/face_brown.sprite", GemType::GREEN  },
        { "res/body_blue.sprite",   "res/face_smile.sprite", GemType::BLUE   },
        { "res/body_yellow.sprite", "res/face_blue.sprite",  GemType::YELLOW },
        { "res/body_purple.sprite", "res/face_blink.sprite", GemType::PURPLE },
        { "res/body_black.sprite",  "res/eye.sprite",        GemType::BLACK  },
    };

    const int random_int = mono::RandomInt(0, 4);
    
    std::shared_ptr<Gem> gem = std::make_shared<Gem>(data_table[random_int]);
    gem->SetPosition(position);
    
    return gem;
}
