#include "Arms.h"
#include "Audio.h"

namespace game {
namespace arms {

	void Gun::reload(Time const& gameTime)
	{
		if (gameTime.asMilliseconds() - box_.sReloadLock.asMilliseconds() > 1500.f) {
			int* bLeft = &box_.sBulletsLeft;
			if (*bLeft >= MAX_CAP) {
				*bLeft -= box_.sMainClip = MAX_CAP;
				Sounds::get_instance()[AUDIO_BUFFER::RELOAD].play();
			}
			else if (*bLeft > 0) {
				box_.sMainClip = *bLeft;
				*bLeft = 0;
				Sounds::get_instance()[AUDIO_BUFFER::RELOAD].play();
			}
			else
				Sounds::get_instance()[AUDIO_BUFFER::RELOAD_FAILED].play();
			box_.sReloadLock = gameTime;
		}
		else
			Sounds::get_instance()[AUDIO_BUFFER::RELOAD_FAILED].play();
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

				Sounds::get_instance()[AUDIO_BUFFER::SHOOT].play();
			}
		}
	}

	void Gun::reset_gun_stats()
	{
		box_.sBulletsLeft = MAX_BULLETS;
		box_.sMainClip = MAX_CAP;
		box_.sFireRate = 2.0f;
	}

} // namespace arms
} // namespace game