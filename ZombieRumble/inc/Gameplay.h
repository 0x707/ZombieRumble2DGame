#include "Player.h"
#include "Horde.h"
#include "Arms.h"
#include "Pickup.h"

#ifndef GAMEPLAY_CLASS_H_
#define GAMEPLAY_CLASS_H_

namespace game {

	enum class game_state {
		PAUSED, LEVELING, GAME_OVER, PLAYING
	};

	// this class needs some refactor to become easier to read
	struct GameTime
	{
		static Time clock_restart() { return s_sClock.restart(); }
		float delta_asSeconds() const { return sDeltaTime.asSeconds(); }
		Time const& get_total_game_time() const { return sGameTotalTime; }
		void set_delta_time() { sDeltaTime = GameTime::clock_restart(); }
		void update_total_game_time() { sGameTotalTime += sDeltaTime; }

	private:
		Time sGameTotalTime = sf::Time::Zero;
		Time sDeltaTime = sf::Time::Zero;
		static Clock s_sClock;
	};

	struct GameScreen
	{
		GameScreen(Vector2f const& res, char const* title, Uint32 style);
		void set_main_view() { sWindow.setView(sViewMain); }

		Vector2f sResolution;
		RenderWindow sWindow;
		View sViewMain;
	};

	struct GameCursor
	{
		GameCursor();
		void set_cursor_to_corsshair();

		Sprite crosshair;
		Vector2f mouseWorldPosition_;
		Vector2i mouseScreenPosition_;
	};

	struct Supplies
	{
		Supplies(IntRect const&);

		pickup::AmmoSupply ammo_pack;
		pickup::HealthSupply health_pack;
	};

	class Game
	{
	public:
		Game(int, int);

		game_state const& get_state() const { return state_; }
		bool game_over() const { return state_ == game_state::GAME_OVER; }
		bool paused() const { return state_ == game_state::PAUSED; }
		bool playing() const { return state_ == game_state::PLAYING; }
		bool leveling() const { return state_ == game_state::LEVELING; }
		void set_gameOver() { state_ = game_state::GAME_OVER; }
		void set_paused() { state_ = game_state::PAUSED; }
		void set_playing() { state_ = game_state::PLAYING; }
		void set_leveling() { state_ = game_state::LEVELING; }

		Vector2f const& get_mouse_world_pos() const { return cursor_.mouseWorldPosition_; }
		Sprite const& get_cursor_sprite() const { return cursor_.crosshair; }
		IntRect const& get_arena() const { return arena_; }
		void set_arena(int widht, int height) { arena_ = { 0,0,widht,height }; }

		Supplies const& get_supplies() const { return supplies_; }

		void update(GameTime& time, GameScreen& screen, Player& player,
			ZombieHorde& horde, arms::Gun& gun);
	private:
		game_state state_{ game_state::GAME_OVER };
		IntRect arena_;
		GameCursor cursor_;
		Supplies supplies_;
	};

} // namespace game

#endif // !GAMEPLAY_CLASS_H_

