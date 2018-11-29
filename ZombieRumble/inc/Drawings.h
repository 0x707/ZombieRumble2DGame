#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#ifndef DRAWINGS_CLASS_H_
#define DRAWINGS_CLASS_H_

namespace hud {
    using namespace sf;

    class HudSprite
    {
    public:
        HudSprite(char const*, float, float);
        Sprite const& sprite() const { return sprite_; }
        Sprite& sprite() { return sprite_; }
    private:
        Sprite sprite_;
    };

    struct HudFont {
        HudFont() : sFont{}
        { sFont.loadFromFile("fonts/zombiecontrol.ttf"); }
        Font sFont;
    };

    class HudText
    {
    public:
        HudText(int, Vector2f const&, Color, char const* = nullptr);

		void add_num_to_str(int);
    private:
        static HudFont font_;
        Text text_;
    };

} // namespace hud

#endif // !DRAWINGS_CLASS_H_