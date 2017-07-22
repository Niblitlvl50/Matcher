
#pragma once

#include "Rendering/IDrawable.h"
#include "Math/Quad.h"
#include "Rendering/Color.h"
#include <string>

namespace game
{
    class TextObject : public mono::IDrawable
    {
    public:
        
        //! A object that draws a text
        //! @param[in] text The initial text to draw
        //! @param[in] color The initial color of the text
        //! @param[in] position Position of the text
        TextObject(const std::string& text, const mono::Color::RGBA& color, const math::Vector& position);
        
        //! Set text color
        //! @param[in] color The new color
        void SetColor(const mono::Color::RGBA& color);
        
        //! Set text
        //! @param[in] text The new text
        void SetText(const std::string& text);
        
        virtual math::Quad BoundingBox() const;

    private:

        virtual void doDraw(mono::IRenderer& renderer) const;
        
        std::string mText;
        mono::Color::RGBA mColor;
        math::Quad mQuad;
    };
}
