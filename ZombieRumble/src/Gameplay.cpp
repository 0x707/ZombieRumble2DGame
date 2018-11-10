#include "Gameplay.h"

namespace game {
	Clock GameTime::s_sClock{};

	GameScreen::GameScreen(Vector2f const& res, char const* title, Uint32 style)
		: sResolution{ res }
		, sWindow{ VideoMode{static_cast<unsigned>(res.x),
			static_cast<unsigned>(res.y)}, title, style }
		, sViewMain{ {0,0,res.x,res.y} }
	{
	}

	void Game::update(GameTime& time, GameScreen& screen, Player& player,
		ZombieHorde& horde, arms::Gun& gun)
	{
		time.set_delta_time();
		time.update_total_game_time();

		mouseScreenPosition_ = Mouse::getPosition();
		mouseWorldPosition_ = screen.sWindow.mapPixelToCoords(
			Mouse::getPosition(), screen.sViewMain );

		player.update(time.delta_asSeconds(), Mouse::getPosition());
		screen.sViewMain.setCenter(player.getCenter());

		for (unsigned i = 0; i < horde.zombie_counter(); ++i)
			if (horde[i]->is_alive())
				horde[i]->update(time.delta_asSeconds(),
					player.getCenter());

		for (int i = 0; i < arms::MAX_BULLETS; ++i)
			if (gun.get_bullet(i).is_inFlight())
				gun.get_bullet(i).update(time.delta_asSeconds());
	}
} // namespace game
