#include <SFML/Graphics/Sprite.hpp>

#ifndef PICKUP_CLASS_H_
#define PICKUP_CLASS_H_

namespace game {
	using namespace sf;
namespace pickup {

	constexpr int HEALTH_CAP = 50;
	constexpr int AMMO_CAP = 12;
	constexpr int LIFESPAN = 10;

	struct BoxSupply
	{
		Sprite sSprite;
		IntRect sArena;
		float sPickupValue;
		bool sSpawned;
		float sSpawnTime = 0.f;
	};

	class Supply
	{
	public:
		void set_spawn_coords();
		FloatRect get_position() const { return box_.sSprite.getGlobalBounds(); }
		Sprite const& get_sprite() const { return box_.sSprite; }
		bool is_spawned() const { return box_.sSpawned; }
		void update(float elapsedTime);
		void upgrade(int upgradeWhat);
	protected:
		Supply(IntRect const&, char const*);
	private:
		BoxSupply box_;
	};

	class AmmoSupply : public Supply
	{
	public:
		AmmoSupply(IntRect const&);
		void upgrade();
	};

	class HealthSupply : public Supply
	{
	public:
		HealthSupply(IntRect const&);
		void upgrade();
	};

} // namespace pickup
} // namespace game

#endif // !PICKUP_CLASS_H_
