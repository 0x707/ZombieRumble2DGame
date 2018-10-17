#pragma once
#include "pch.h"
#include "Player.h"

namespace game {

	enum class game_state {
		PAUSED, LEVELING, GAME_OVER, PLAYING
	};

	struct GameTime
	{
		void clock_restart() { sClock.restart(); }

		Time sGameTotalTime;
		Clock sClock;
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
	private:
		game_state state_{ game_state::GAME_OVER };
		IntRect arena_;
		Vector2f mouseWorldPosition;
		Vector2i mouseScreenPosition;
	};


} // namespace game