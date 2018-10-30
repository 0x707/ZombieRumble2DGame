#pragma once
#ifndef ARENA_CLASS_H_
#define ARENA_CLASS_H_

#include <SFML/Graphics/VertexArray.hpp>
#include "TextureHolder.h"
using namespace sf;

namespace game {
	constexpr int TILE_SIZE{ 50 };
	constexpr int TILE_TYPES{ 3 };
	constexpr int VERTS_IN_QUADS{ 4 };

	struct Background
	{
		Background()
			: texture_{ TextureHolder::get_instance().texture("graphics/background_sheet.png") }
			, bcg_{ Quads }
		{
		}

		Texture&  operator()() { return texture_; }
		VertexArray const& get_background_VA() const { return bcg_; }
		int create(IntRect const& arena);
	private:
		Texture texture_;
		VertexArray bcg_;

		void make_grid(int, int);
		void place_tiles(int, int, int);
		void set_tile_texture(int, int);
	};

} // namespace game

#endif //! ARENA_CLASS_H_
