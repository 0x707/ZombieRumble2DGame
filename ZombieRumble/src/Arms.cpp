#include "Arms.h"

namespace game {
namespace arms {

	void Gun::reload()
	{
		int* bLeft = &box_.sBulletsLeft;
		if (*bLeft >= MAX_CAP)
			*bLeft -= box_.sMainClip = MAX_CAP;
		else if (*bLeft > 0) {
			box_.sMainClip = *bLeft;
			*bLeft = 0;
		}
		else {
			// TODO: here game will be playing audio soon
		}
	}

	void Gun::shot(Time const& gameTime, Vector2f const& playerPos,
		Vector2f const& mousePos)
	{
		if (gameTime.asMilliseconds() - box_.sFormerShot.asMilliseconds()
			> 1000.f / box_.sFireRate_ && box_.sMainClip > 0) {
			box_.sBullets[++box_.sCurrentBullet].shoot(
				playerPos, mousePos );
			if (box_.sCurrentBullet == MAX_BULLETS)
				box_.sCurrentBullet = -1;
			box_.sFormerShot = gameTime;
			--box_.sMainClip;
		}
	}

} // namespace arms
} // namespace game