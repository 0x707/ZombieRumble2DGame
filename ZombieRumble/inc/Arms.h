#include "Bullet.h"
#include <SFML/System/Time.hpp>

#ifndef ARMS_CLASS_H_
#define ARMS_CLASS_H_

namespace game {
namespace arms {

	constexpr int MAX_CAP = 6;
	constexpr int MAX_BULLETS = 100;

	struct BoxGun
	{
		int sBulletsLeft = MAX_BULLETS;
		int sMainClip = MAX_CAP;
		float sFireRate_ = 1.f;
		Time sFormerShot = Time::Zero;
		Bullet sBullets[MAX_BULLETS];
		int sCurrentBullet = -1;
	};

	class Gun
	{
	public:
		Gun() {}

		void reload();
		void shot(Time const&, Vector2f const& playerPos,
			Vector2f const& mousePos);
		Bullet& get_bullet(int index) { return box_.sBullets[index]; }
		Bullet const& get_bullet(int index) const { return box_.sBullets[index]; }
	private:
		BoxGun box_;
	};

} // namespace arms
} // namespace games

#endif // !ARMS_CLASS_H_
