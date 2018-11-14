#include "Pickup.h"
#include "TextureHolder.h"

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
		box_.sArena = arena;
		box_.sSprite.setTexture(
			TextureHolder::get_instance().texture(path));
		box_.sSprite.setOrigin(25, 25);
		box_.sTillRespawn = SPAWN_TIME;
	
	}

} // namespace pickup
} // namespace game