#include <SFML/Graphics/Sprite.hpp>

#ifndef PICKUP_CLASS_H_
#define PICKUP_CLASS_H_

namespace game {
	using namespace sf;
namespace pickup {

	constexpr int HEALTH_CAP = 50;
	constexpr int AMMO_CAP = 12;
	constexpr int SPAWN_TIME = 10;
	constexpr int LIFESPAN = 10;

	struct BoxSupply
	{
		Sprite sSprite;
		IntRect sArena;
		int sPickupValue;
		bool sSpawned;
		float sLastSpawn;
		float sLastDeSpawn;
		float sTillRespawn;
	};

	class Supply
	{
	protected:
		Supply(IntRect const&, char const*);
	private:
		BoxSupply box_;
	};

} // namespace pickup
} // namespace game

#endif // !PICKUP_CLASS_H_
