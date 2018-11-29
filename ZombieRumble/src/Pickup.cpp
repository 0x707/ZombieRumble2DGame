#include "Pickup.h"
#include "TextureHolder.h"
#include "RandomGen.h"

namespace game {
namespace pickup {

namespace {

	IntRect set_arena(IntRect const& arena)
	{
		return IntRect{ arena.left + 50, // 50 is the tile width and height size
		arena.top + 50, arena.width - 50, arena.height - 50 };
	}

} // anonymous namespace

	Supply::Supply(IntRect const& arena, char const* path)
	{
		box_.sArena = set_arena(arena);
		box_.sSprite.setTexture(
			TextureHolder::get_instance().texture(path));
		box_.sSprite.setOrigin(25, 25);
		set_spawn_coords();	
	}

	void Supply::set_spawn_coords()
	{
		utils::RandFloatMT rfX{ static_cast<float>(box_.sArena.left),
								static_cast<float>(box_.sArena.width) };
		utils::RandFloatMT rfY{ static_cast<float>(box_.sArena.top),
								static_cast<float>(box_.sArena.height) };

		box_.sSprite.setPosition(rfX(), rfY());
		box_.sSpawned = true;
	}

	void Supply::update(float elapsedTime)
	{
		if (box_.sSpawnTime < LIFESPAN)
			box_.sSpawnTime += elapsedTime;
		else {
			box_.sSpawnTime = 0;
			if (box_.sSpawned)
				box_.sSpawned = false;
			else
				set_spawn_coords();
		}

	}

	void Supply::upgrade(int upgradeWhat)
	{
		box_.sPickupValue += upgradeWhat / 2;
	}

	int Supply::get_supply(int whichOne)
	{
		box_.sSpawned = false;
		return box_.sPickupValue + whichOne;
	}

	// ammunition supply

	AmmoSupply::AmmoSupply(IntRect const& arena)
		: Supply{ arena, "graphics/ammo_pickup.png" }
	{
	}

	void AmmoSupply::upgrade()
	{
		Supply::upgrade(AMMO_CAP);
	}

	int AmmoSupply::get_supply()
	{
		return Supply::get_supply(AMMO_CAP);
	}

	// health supply

	HealthSupply::HealthSupply(IntRect const& arena)
		: Supply{ arena, "graphics/health_pickup.png" }
	{
	}

	void HealthSupply::upgrade()
	{
		Supply::upgrade(HEALTH_CAP);
	}

	int HealthSupply::get_supply()
	{
		return Supply::get_supply(HEALTH_CAP);
	}

} // namespace pickup
} // namespace game