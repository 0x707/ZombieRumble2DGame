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
		box_.sTillRespawn = SPAWN_TIME;
		set_spawn_coords();	
	}

	void Supply::set_spawn_coords()
	{
		utils::RandFloatMT rfX{ static_cast<float>(box_.sArena.left),
								static_cast<float>(box_.sArena.width) };
		utils::RandFloatMT rfY{ static_cast<float>(box_.sArena.top),
								static_cast<float>(box_.sArena.height) };

		box_.sSprite.setPosition(rfX(), rfY());
		box_.sLastSpawn = 0;
		box_.sSpawned = true;
	}

} // namespace pickup
} // namespace game