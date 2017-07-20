
#include "TextObject.h"
#include "Rendering/IRenderer.h"
#include "Rendering/Text/TextFunctions.h"
#include "Math/Vector.h"
#include "Math/Quad.h"

using namespace game;

TextObject::TextObject(const std::string& text, const mono::Color::RGBA& color, const math::Vector& position)
{
    mQuad.mA = position;

    SetText(text);
    SetColor(color);
}

void TextObject::SetColor(const mono::Color::RGBA& color)
{
    mColor = color;
}

void TextObject::SetText(const std::string& text)
{
    mText = text;

    const math::Vector& text_size = mono::MeasureString(0, mText.c_str());

    mQuad.mA.x -= (text_size.x / 2.0f);
    mQuad.mB = mQuad.mA + text_size;
}

void TextObject::doDraw(mono::IRenderer& renderer) const
{
    renderer.DrawText(0, mText.c_str(), mQuad.mA, false, mColor);
}

math::Quad TextObject::BoundingBox() const
{
    return mQuad;
}
