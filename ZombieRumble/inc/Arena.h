#pragma once
#ifndef ARENA_CLASS_H_
#define ARENA_CLASS_H_

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/VertexArray.hpp>
using namespace sf;

namespace game {
	constexpr int TILE_SIZE{ 50 };
	constexpr int TILE_TYPES{ 3 };
	constexpr int VERTS_IN_QUADS{ 4 };

	struct Background
	{
		Background(char const* path)
			: bcg_{ Quads }
		{
			texture_.loadFromFile(path);

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
