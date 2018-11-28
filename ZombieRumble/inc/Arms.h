#include "Bullet.h"
#include "SimpleQueue.h"
#include <SFML/System/Time.hpp>

#ifndef ARMS_CLASS_H_
#define ARMS_CLASS_H_

namespace game {
namespace arms {
	using sim_queue = scds::SimpleQueue<Bullet>;

	constexpr int MAX_CAP = 23;
	constexpr int MAX_BULLETS = 1000;

	struct BoxGun
	{
		int sBulletsLeft = MAX_BULLETS;
		int sMainClip = MAX_CAP;
		float sFireRate_ = 10.f;
		Time sFormerShot = Time::Zero;
		sim_queue sBullets{ MAX_CAP + 1 };
	};

	class Gun
	{
	public:
		Gun() {}

		Bullet* const operator[](int index) { return box_.sBullets[index]; }
		Bullet const* const operator[](int index) const { return box_.sBullets[index]; }

		void reload();
		void shot(Time const&, Vector2f const& playerPos,
			Vector2f const& mousePos);
		sim_queue& bullets() { return box_.sBullets; }
		sim_queue const& bullets() const { return box_.sBullets; }
		void add_bullets(int amount) { box_.sBulletsLeft += amount; }
	private:
		BoxGun box_;
	};

} // namespace arms
} // namespace games

#endif // !ARMS_CLASS_H_
