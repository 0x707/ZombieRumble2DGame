#include "Gameplay.h"
#include "Score.h"

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

	// supplies

	Supplies::Supplies(IntRect const& arena)
		: ammo_pack{ arena }, health_pack{ arena }
	{
	}

	// Game class

	Game::Game(int width, int height)
		: arena_{ 0,0,width,height }
		, supplies_{ arena_ }
	{
	}

	void Game::detect_collisions(ZombieHorde& horde, arms::Gun& gun)
	{
		for (int i = gun.bullets().front(), j = gun.bullets().current_length();
			j > 0; ++i %= gun.bullets().size(), --j) {
			for (int z = 0; z < horde.zombie_counter(); ++z) {
				if (horde[z]->is_alive() &&
					gun[i]->get_position().intersects(
					horde[z]->get_position())) {
					gun[i]->stop();
					if (horde[z]->hit()) {
						Score::get_instance() += 10;
						Score::get_instance().update_high_score();
						if (horde.kill_zombie() < 0)
							state_ = game_state::LEVELING;
					}
				}
			}
		}
	}

	void Game::detect_collisions(ZombieHorde const& horde, Player& player,
		GameTime const& time)
	{
		for (int i = 0; i < horde.zombie_counter(); ++i) {
			if (player.get_position().intersects(horde[i]->get_position())
				&& horde[i]->is_alive()) {
				if (player.hit(time.get_total_game_time())) {
					// more here soon
				}
				if (player.getHealth() < -1) {
					state_ = game_state::GAME_OVER;
					Score::get_instance().update_high_score();
				}
			}
		}
	}

	void Game::detect_collisions(Player& player, arms::Gun& gun)
	{
		if (player.get_position().intersects(
			supplies_.health_pack.get_position()) && supplies_.health_pack.is_spawned())
			player.increaseHealthLevel(supplies_.health_pack.get_supply());
		if (player.get_position().intersects(
			supplies_.ammo_pack.get_position()) && supplies_.ammo_pack.is_spawned())
			gun.add_bullets(supplies_.ammo_pack.get_supply());
	}

	void Game::update(GameTime& time, GameScreen& screen, Player& player,
		ZombieHorde& horde, arms::Gun& gun)
	{
		time.set_delta_time();
		time.update_total_game_time();
		
		player.update(time.delta_asSeconds(), Mouse::getPosition());
		screen.sViewMain.setCenter(player.getCenter());

		update_crosshair(cursor_, screen);
		update_horde(horde, player, time.delta_asSeconds());
		update_bullets(gun, time.delta_asSeconds());
		update_supplies(supplies_, time.delta_asSeconds());

		detect_collisions(horde, gun);
		detect_collisions(horde, player, time);
		detect_collisions(player, gun);

		hud::HUD::get_instance().update(player, gun, horde);
	}

	// free functions

	void update_crosshair(GameCursor& cursor, GameScreen& screen)
	{
		cursor.mouseScreenPosition_ = Mouse::getPosition();
		cursor.mouseWorldPosition_ = screen.sWindow.mapPixelToCoords(
			Mouse::getPosition(), screen.sViewMain);
		cursor.set_cursor_to_corsshair();
	}

	void update_horde(ZombieHorde& horde, Player& player,
		float elapsedTime)
	{
		for (int i = 0; i < horde.zombie_counter(); ++i)
			if (horde[i]->is_alive())
				horde[i]->update(elapsedTime, player.getCenter());
	}

	void update_bullets(arms::Gun& gun, float elapsedTime)
	{
		for (int i = gun.bullets().front(),
			j = gun.bullets().current_length();
			j > 0; i = ++i % gun.bullets().size(), --j) {
			if (!gun[i]->update(elapsedTime))
				gun.bullets().dequeue();
		}
	}

	void update_supplies(Supplies& supplies, float elapsedTime)
	{
		supplies.ammo_pack.update(elapsedTime);
		supplies.health_pack.update(elapsedTime);
	}
} // namespace game
