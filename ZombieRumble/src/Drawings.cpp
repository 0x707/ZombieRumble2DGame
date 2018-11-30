#include "Drawings.h"
#include "TextureHolder.h"

namespace hud {
    HudFont HudText::font_{};

    HudSprite::HudSprite(char const* path, float x, float y)
        : sprite_{game::TextureHolder::get_instance().texture(path)}
    {
        sprite_.setPosition(x,y);
    }

    HudText::HudText(unsigned sz, Vector2f const& pos, Color c, char const* str)
        : text_{str, font_.sFont, sz}
    {
        text_.setPosition(pos);
        text_.setFillColor(c);
    }

    HealthBar::HealthBar()
    {
        bar_.setPosition(450, 980);
        bar_.setFillColor(Color::Red);
    } 

} // namespace hud