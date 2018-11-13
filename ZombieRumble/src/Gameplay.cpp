#include "Gameplay.h"

namespace game {
	Clock GameTime::s_sClock{};

	GameScreen::GameScreen(Vector2f const& res, char const* title, Uint32 style)
		: sResolution{ res }
		, sWindow{ VideoMode{static_cast<unsigned>(res.x),
			static_cast<unsigned>(res.y)}, title, style }
		, sViewMain{ {0,0,res.x,res.y} }
	{
		sWindow.setMouseCursorVisible(false);
	}

	GameCursor::GameCursor()
		: crosshair{ TextureHolder::get_instance().texture(
			"graphics/crosshair.png") }
	{
		crosshair.setOrigin(25, 25);
	}

	void GameCursor::set_cursor_to_corsshair() {
		crosshair.setPosition(mouseWorldPosition_);
	}

	// Game update

	void Game::update(GameTime& time, GameScreen& screen, Player& player,
		ZombieHorde& horde, arms::Gun& gun)
	{
		time.set_delta_time();
		time.update_total_game_time();

		cursor_.mouseScreenPosition_ = Mouse::getPosition();
		cursor_.mouseWorldPosition_ = screen.sWindow.mapPixelToCoords(
			Mouse::getPosition(), screen.sViewMain );
		cursor_.set_cursor_to_corsshair();

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
