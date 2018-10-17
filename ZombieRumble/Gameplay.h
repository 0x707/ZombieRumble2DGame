#pragma once
#include "pch.h"
#include "Player.h"

namespace game {

	enum class game_state {
		PAUSED, LEVELING, GAME_OVER, PLAYING
	};

	struct GameTime
	{
		static Time clock_restart() { return s_sClock.restart(); }
		float delta_asSeconds() const { return sDeltaTime.asSeconds(); }

		Time sGameTotalTime;
		Time sDeltaTime;
		static Clock s_sClock;
	};

	struct GameScreen
	{
		GameScreen(Vector2f const& res, char const* title, Uint32 style);

		Vector2f sResolution;
		RenderWindow sWindow;
		View sView;
	};

	class Game
	{
	public:
		Game() {}

		game_state const& get_state() const { return state_; }
		bool game_over() const { return state_ == game_state::GAME_OVER; }
		bool paused() const { return state_ == game_state::PAUSED; }
		bool playing() const { return state_ == game_state::PLAYING; }
		bool leveling() const { return state_ == game_state::LEVELING; }
		void set_gameOver() { state_ = game_state::GAME_OVER; }
		void set_paused() { state_ = game_state::PAUSED; }
		void set_playing() { state_ = game_state::PLAYING; }
		void set_leveling() { state_ = game_state::LEVELING; }

		IntRect const& get_arena() const { return arena_; }
		void set_arena(IntRect const& arena) { arena_ = arena; }

		void set_tile_size(int value) { tileSize_ = value; }
		int get_tile_size() const { return tileSize_; }

		void update(GameTime& time, GameScreen& screen, Player& player);
	private:
		game_state state_{ game_state::GAME_OVER };
		IntRect arena_;
		int tileSize_;
		Vector2f mouseWorldPosition_;
		Vector2i mouseScreenPosition_;
	};


} // namespace game