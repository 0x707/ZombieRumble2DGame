#include "Arms.h"

namespace game {
namespace arms {

	void Gun::reload(Time const& gameTime)
	{
		if (gameTime.asMilliseconds() - box_.sReloadLock.asMilliseconds() > 1500.f) {
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
				box_.sReloadLock = gameTime;
		}
	}

	void Gun::shot(Time const& gameTime, Vector2f const& playerPos,
		Vector2f const& mousePos)
	{
		if (gameTime.asMilliseconds() - box_.sReloadLock.asMilliseconds() > 1500.f) {
			if (gameTime.asMilliseconds() - box_.sFormerShot.asMilliseconds()
				> 1000.f / box_.sFireRate && box_.sMainClip > 0) {
				box_.sBullets.enqueue();
				box_.sBullets[box_.sBullets.rear()]->shoot(
					playerPos, mousePos);
				box_.sFormerShot = gameTime;
				--box_.sMainClip;
			}
		}
	}

} // namespace arms
} // namespace game