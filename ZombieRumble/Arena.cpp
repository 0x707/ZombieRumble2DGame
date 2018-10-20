#include "pch.h"
#include "Arena.h"
#include <random>
#include <ctime>

namespace {

	int random_tile(int seed)
	{
		srand(int(time(0) + seed));
		return rand() % game::TILE_TYPES;
	}

	float cast_float(int v)
	{
		return static_cast<float>(v);
	}

} //anonymous namespace

namespace game {

	int game::Background::create(IntRect const & arena)
	{
		int arenaWidth{ arena.width / TILE_SIZE };
		int arenaHeight{ arena.height / TILE_SIZE };

		bcg_.resize(arenaWidth * arenaHeight * VERTS_IN_QUADS);
		make_grid(arenaWidth, arenaHeight);
		return TILE_SIZE;
	}

	// private functions

	void Background::make_grid(int arenaWidth, int arenaHeight)
	{
		int currentVertex{ -1 };

		for (int w = 0; w < arenaWidth; ++w) {
			for (int h = 0; h < arenaHeight; ++h) {
				place_tiles(currentVertex, w, h);

				if (h == 0 || h == arenaHeight - 1 ||
					w == 0 || w == arenaWidth - 1)
					set_tile_texture(currentVertex, TILE_TYPES);
				else {
					int morg = random_tile(h * w - h);
					set_tile_texture(currentVertex, morg);
				}

				currentVertex += VERTS_IN_QUADS;
			}
		}
	}

	void Background::place_tiles(int cv, int w, int h)
	{
		// Yes, i do really like casting ints to floats :)
		bcg_[++cv].position = Vector2f{
			static_cast<float>(w * TILE_SIZE), static_cast<float>(h * TILE_SIZE) };
		bcg_[++cv].position = Vector2f{
			static_cast<float>(w * TILE_SIZE + 50), static_cast<float>(h * TILE_SIZE) };
		bcg_[++cv].position = Vector2f{
			static_cast<float>(w * TILE_SIZE + 50), static_cast<float>(h * TILE_SIZE + 50) };
		bcg_[++cv].position = Vector2f{
			static_cast<float>(w * TILE_SIZE), static_cast<float>(h * TILE_SIZE + 50) };
	}

	void Background::set_tile_texture(int cv, int offset)
	{
		const float TILE_SIZE_F = static_cast<float>(TILE_SIZE);
		float verticalOffset{ TILE_SIZE * static_cast<float>(offset) };
		bcg_[++cv].texCoords = Vector2f{ 0, verticalOffset};
		bcg_[++cv].texCoords = Vector2f{ TILE_SIZE_F, verticalOffset };
		bcg_[++cv].texCoords = Vector2f{ TILE_SIZE_F, verticalOffset + TILE_SIZE_F };
		bcg_[++cv].texCoords = Vector2f{ 0, verticalOffset + TILE_SIZE_F };
	}

} // namespace game
