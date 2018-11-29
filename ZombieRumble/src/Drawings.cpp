#include "Drawings.h"
#include "TextureHolder.h"
#include <sstream>

namespace hud {
    HudFont HudText::font_{};

    HudSprite::HudSprite(char const* path, float x, float y)
        : sprite_{game::TextureHolder::get_instance().texture(path)}
    {
        sprite_.setPosition(x,y);
    }

    HudText::HudText(int sz, Vector2f const& pos, Color c, char const* str)
    {
        text_.setFont(font_.sFont);
        text_.setCharacterSize(sz);
        text_.setPosition(pos);
        text_.setFillColor(c);
        text_.setString(str);
    }

	void HudText::add_num_to_str(int num)
	{
		std::stringstream s;
		s << static_cast<char const*>(text_.getString()) << num;
	}

} // namespace hud