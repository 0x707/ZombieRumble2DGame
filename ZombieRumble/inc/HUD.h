#include "Arms.h"
#include "Drawings.h"
#include "Horde.h"
#include <sstream>

#ifndef HUD_CLASS_H_
#define HUD_CLASS_H_

namespace hud {
	using namespace game;
	using namespace arms;

	struct BoxHUD
	{
		char const* get_level_up_string();

		hud::HudSprite gameOver{ "graphics/background.png", 0, 0 };
		hud::HudSprite ammoIcon{ "graphics/ammo_icon.png", 20, 980 };

		hud::HudText pauseText{ 155, {400, 400}, Color::White, "Press Enter \n to continue" };
		hud::HudText goverText{ 128, {250,850}, Color::White, "Press Enter to play" };
		hud::HudText levelText{ 80,{150,250}, Color::White, get_level_up_string() };
		hud::HudText ammoText{ 55,{200,980}, Color::White };
		hud::HudText scoreText{ 55,{20,0},Color::White };
		hud::HudText hiscrText{ 55,{1400,0},Color::White, "High score: " };
		hud::HudText zmbiermainText{ 55, {1500, 980}, Color::White, "Zombies: 100" };
		hud::HudText waveremainText{ 55, {1250, 980}, Color::White, "Wave: 0" };

		hud::HealthBar hpBar;
	};

	class HUD
	{
	public:
		HUD(HUD const&) = delete;
		HUD& operator=(HUD const&) = delete;

		static HUD& get_instance();
		BoxHUD const& get_drawings() const { return box_; }
		void update(Player const&, Gun const&, ZombieHorde const&);
	private:
		HUD() {}

		BoxHUD box_;
		int lastUpdateFrames_;
		int fpsInterval_ = 200;
		int wave_ = 1;
		std::stringstream ss_;
	};

	void update_ammo_HUD(std::stringstream&, HudText&, Gun const&);
	void update_scores_HUD(std::stringstream&, HudText&, HudText&);
	void update_wave_HUD(std::stringstream&, HudText&, int&);
	void update_horde_HUD(std::stringstream&, HudText&,
		ZombieHorde const&);

} // namespace hud

#endif // !HUD_CLASS_H_
