#include "Drawings.h"
#include "TextureHolder.h"

namespace hud {
    HudFont HudText::font_{};

    HudSprite::HudSprite(char const* path, float x, float y)
        : sprite_{game::TextureHolder::get_instance().texture(path)}
    {
        sprite_.setPosition(x,y);
    }

    HudText::HudText(int sz, Vector2f const& pos, char const* str, Color c)
    {
        text_.setFont(font_.sFont);
        text_.setCharacterSize(sz);
        text_.setPosition(pos);
        text_.setFillColor(c);
        text_.setString(str);
    }

} // namespace hud