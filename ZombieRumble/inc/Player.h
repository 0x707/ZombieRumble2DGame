#include <SFML/Graphics.hpp>
#include "TextureHolder.h"

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

	enum class DIRS {DOWN, LEFT, RIGHT, UP}; // order is alphabetic
	struct Controls
	{
		bool operator()(DIRS dir) const { return sDirections[static_cast<int>(dir)]; }
		void operator()(DIRS dir, bool state) {
			sDirections[static_cast<int>(dir)] = state; }
		bool sDirections[4];
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
		Texture sTexture{game::TextureHolder::get_instance().texture(
			"graphics/player.png")};
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

		Time const& getLastHitTime() const { return pData_.sLastHit; }
		FloatRect getPosition() const { return pData_.sSprite.getGlobalBounds(); }
		Vector2f const& getCenter() const { return pData_.sPosition; }
		float getRotation() const { return pData_.sSprite.getRotation(); }
		Sprite const& getSprite() const { return pData_.sSprite; }
		int getHealth() const { return pData_.sHealth; }

		void move(DIRS dir, bool state) { controls_(dir, state); }
		void update(float elapsedTime, Vector2i const& mousePosition);
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

