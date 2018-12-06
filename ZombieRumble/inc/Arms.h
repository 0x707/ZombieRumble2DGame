#include "Bullet.h"
#include "SimpleQueue.h"
#include <SFML/System/Time.hpp>

#ifndef ARMS_CLASS_H_
#define ARMS_CLASS_H_

namespace game {
namespace arms {
	using sim_queue = scds::SimpleQueue<Bullet>;

	constexpr int MAX_CAP = 6;
	constexpr int MAX_BULLETS = MAX_CAP * 7;

	struct BoxGun
	{
		int sBulletsLeft = MAX_BULLETS;
		int sMainClip = MAX_CAP;
		float sFireRate = 2.f;
		Time sReloadLock = Time::Zero;
		Time sFormerShot = Time::Zero;
		sim_queue sBullets{ MAX_CAP + 1 };
	};

	class Gun
	{
	public:
		Gun() {}

		Bullet* const operator[](int index) { return box_.sBullets[index]; }
		Bullet const* const operator[](int index) const { return box_.sBullets[index]; }

		void reload(Time const&);
		void shot(Time const&, Vector2f const& playerPos,
			Vector2f const& mousePos);
		sim_queue& bullets() { return box_.sBullets; }
		sim_queue const& bullets() const { return box_.sBullets; }
		void add_bullets(int amount) { box_.sBulletsLeft += amount; }
		BoxGun const& get_clip() const { return box_; }

		void increase_fire_rate(float amount) { box_.sFireRate += amount; }
		void increase_clip_size() { box_.sMainClip += MAX_CAP; }
		void reset_gun_stats();
	private:
		BoxGun box_;
	};

} // namespace arms
} // namespace games

#endif // !ARMS_CLASS_H_
