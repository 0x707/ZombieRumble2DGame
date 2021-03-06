#include "pch.h"
#include "Player.h"

namespace game {

	Player::Player()
	{
		pData_.sTexture.loadFromFile("graphics/player.png");
		pData_.sSprite.setTexture(pData_.sTexture);
		pData_.sSprite.setOrigin(25, 25);
	}

	void Player::spawn(IntRect const& arena,
		Vector2f const& resolution, int tileSize)
	{
		pData_.sPosition.x = static_cast<float>(arena.width / 2);
		pData_.sPosition.y = static_cast<float>(arena.height / 2);

		sData_.sArena = arena;
		sData_.sTileSize = tileSize;
		sData_.sResolution = resolution;
	}

	void Player::resetPlayerStats()
	{
		pData_.sSpeed = pData_.START_SPEED;
		pData_.sHealth = static_cast<int>(pData_.START_HEALTH);
		pData_.sMaxHealth_ = static_cast<int>(pData_.START_HEALTH);
	}

	bool Player::hit(Time timeHit)
	{
		if (timeHit.asMilliseconds() - pData_.sLastHit.asMilliseconds() > 200) {
			pData_.sLastHit = timeHit;
			pData_.sHealth -= 10;
			return true;
		}
		return false;
	}

	void Player::update(float elapsedTime, Vector2i mousePosition)
	{
		if (controls_.sLeftPressed)
			pData_.sPosition.x -= elapsedTime * pData_.sSpeed;
		if (controls_.sRightPressed)
			pData_.sPosition.x += elapsedTime * pData_.sSpeed;
		if (controls_.sUpPressed)
			pData_.sPosition.y -= elapsedTime * pData_.sSpeed;
		if (controls_.sDownPressed)
			pData_.sPosition.y += elapsedTime * pData_.sSpeed;
		pData_.sSprite.setPosition(pData_.sPosition);
		
		AssignIfLesser(pData_.sPosition.x, sData_.sArena.left + sData_.sTileSize);
		AssignIfGreater(pData_.sPosition.x, sData_.sArena.width - sData_.sTileSize);
		AssignIfLesser(pData_.sPosition.y, sData_.sArena.top + sData_.sTileSize);
		AssignIfGreater(pData_.sPosition.y, sData_.sArena.height - sData_.sTileSize);

		float angle = static_cast<float>((atan2(mousePosition.y - sData_.sResolution.y / 2,
			mousePosition.x - sData_.sResolution.x / 2) * 180) / 3.141);
		pData_.sSprite.setRotation(angle);
	}

	void Player::increadeHealthLevel(int amount)
	{
		if (pData_.sHealth + amount > pData_.START_HEALTH)
			pData_.sHealth = static_cast<int>(pData_.START_HEALTH);
		else
			pData_.sHealth += amount;
	}


} // namespace game
