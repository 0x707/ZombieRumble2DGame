#include "Player.h"

#ifndef DRAWINGS_CLASS_H_
#define DRAWINGS_CLASS_H_

namespace hud {
    using namespace sf;


    struct HudFont {
        HudFont() : sFont{}
        { sFont.loadFromFile("fonts/zombiecontrol.ttf"); }
        Font sFont;
    };

    struct HealthBar
    {
    public:
        HealthBar();
		void update_hpbar(game::Player const&);
		RectangleShape const& bar() const { return bar_; }
    private:
        RectangleShape bar_;
    };

    class HudSprite
    {
    public:
        HudSprite(char const*, float, float);
        Sprite const& sprite() const { return sprite_; }
        Sprite& sprite() { return sprite_; }
    private:
        Sprite sprite_;
    };

    class HudText
    {
    public:
        HudText(unsigned, Vector2f const&, Color, char const* = nullptr);
		void set_string(char const* str) { text_.setString(str); }
		Text const& text() const { return text_; }
    private:
        static HudFont font_;
        Text text_;
    };


} // namespace hud

#endif // !DRAWINGS_CLASS_H_