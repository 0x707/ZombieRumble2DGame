#include "HUD.h"
#include "Score.h"

namespace hud {

	// BoxHUD

	char const* BoxHUD::get_level_up_string()
	{
		return "1 - Increased fire rate\n"
			"2 - Increased clip size\n"
			"3 - Increased max health\n"
			"4 - Increased run speed\n"
			"5 - Better health supplies\n"
			"6 - Better ammo supplies";
	}

	// !BoxHUD

	// HUD

	HUD& HUD::get_instance()
	{
		static HUD instance;
		return instance;
	}

	void HUD::update(Player const& player, Gun const& gun,
		ZombieHorde const& horde)
	{
		box_.hpBar.update_hpbar(player);

		if (++lastUpdateFrames_ > fpsInterval_) {
			update_ammo_HUD(ss_, box_.ammoText, gun);
			update_scores_HUD(ss_, box_.scoreText, box_.hiscrText);
			update_wave_HUD(ss_, box_.waveremainText, wave_);
			update_horde_HUD(ss_, box_.zmbiermainText, horde);
			lastUpdateFrames_ = 0;
		}
	}

	// !HUD

	// UPDATE FUNCTIONS

	void update_ammo_HUD(std::stringstream& ss, HudText& t, Gun const& gun)
	{
		ss << gun.get_clip().sMainClip << " / "
			<< gun.get_clip().sBulletsLeft;
		t.set_string( ss.str().data());
		ss.str({});
	}

	void update_scores_HUD(std::stringstream& ss, HudText& t, HudText& t2)
	{
		ss << "Score: " << Score::get_instance().get_score();
		t.set_string(ss.str().data());
		ss.str({});

		ss << "High Score: " << Score::get_instance().get_score();
		t2.set_string(ss.str().data());
		ss.str({});
	}

	void update_wave_HUD(std::stringstream& ss, HudText& t, int& wave)
	{
		ss << "Wave: " << wave;
		t.set_string(ss.str().data());
		ss.str({});
	}

	void update_horde_HUD(std::stringstream& ss, HudText& t,
		ZombieHorde const& horde)
	{
		ss << "Zombies alive: " << horde.zombies_alive();
		t.set_string(ss.str().data());
		ss.str({});
	}

} // namepsace game