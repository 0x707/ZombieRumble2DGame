#include "TextureHolder.h"

namespace game {

	TextureHolder& TextureHolder::get_instance()
	{
		static TextureHolder th;
		return th;
	}

	sf::Texture& TextureHolder::texture(char const* path)
	{
		if (auto it{ textures_.find(path) }; it == textures_.end())
			textures_[path].loadFromFile(path);
		return textures_[path];
	}

} // namespace game