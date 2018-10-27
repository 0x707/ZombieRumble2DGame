#pragma once
#include <SFML/Graphics.hpp>

#ifndef PLAYER_CLASS_H_
#define PLAYER_CLASS_H_

namespace {

	// This namespace holds all information that Player class needs to maitain its functionality.
	using namespace sf;

	struct ScreenSpaceData
	{
		Vector2f sResolution;
		IntRect sArena;
		int sTileSize;
	};

	struct Controls
	{
		bool sUpPressed;
		bool sDownPressed;
		bool sLeftPressed;
		bool sRightPressed;
	};

	struct PlayerData
	{
		float const START_SPEED = 200;
		float const START_HEALTH = 100;
		int  sHealth = static_cast<int>(START_HEALTH);
		int sMaxHealth_ = static_cast<int>(START_HEALTH);
		float sSpeed = START_SPEED;
		Vector2f sPosition;
		Sprite sSprite;
		Texture sTexture;
		Time sLastHit;
	};
} // anonymous namespace

namespace game {

	class Player
	{
	public:
		Player();
		
		void spawn(IntRect const& arena,
			Vector2f const&  resolution, int tileSize);
		void resetPlayerStats();
		bool hit(Time timeHit);

		Time getLastHitTime() const { return pData_.sLastHit; }
		FloatRect getPosition() const { return pData_.sSprite.getGlobalBounds(); }
		Vector2f getCenter() const { return pData_.sPosition; }
		float getRotation() const { return pData_.sSprite.getRotation(); }
		Sprite getSprite() const { return pData_.sSprite; }
		int getHealth() const { return pData_.sHealth; }

		void moveLeft() { controls_.sLeftPressed = true; }
		void moveRight() { controls_.sRightPressed = true;  }
		void moveUp() { controls_.sUpPressed = true; }
		void moveDown() { controls_.sDownPressed = true; }
		void stopLeft() { controls_.sLeftPressed = false; }
		void stopRight() { controls_.sRightPressed = false; }
		void stopUp() { controls_.sUpPressed = false; }
		void stopDown() { controls_.sDownPressed = false; }

		void update(float elapsedTime, Vector2i mousePosition);
		void upgradeSpeed() { pData_.sSpeed += static_cast<int>(pData_.START_SPEED * 0.2f); }
		void upgradeHealth() { pData_.sHealth += static_cast<int>(pData_.START_HEALTH * 0.2f); }
		void increaseHealthLevel(int amount);
	private:
		PlayerData pData_;
		ScreenSpaceData sData_;
		Controls controls_;
	};

	template<typename P, typename Q>
	void AssignIfLesser(P& first, Q&& second)
	{
		if (first < second)
			first = static_cast<P>(second);
	}

	template<typename P, typename Q>
	void AssignIfGreater(P& first, Q&& second)
	{
		if (first > second)
			first = static_cast<P>(second);
	}

} // namespace game

#endif // !PLAYER_CLASS_H_

