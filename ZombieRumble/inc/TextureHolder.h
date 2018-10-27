#include <SFML/Graphics/Texture.hpp>
#include <map>

#ifndef TEXTURE_HOLDER_CLASS_H_
#define TEXTURE_HOLDER_CLASS_H_

namespace game {

    class TextureHolder
    {
    public:
        TextureHolder(TextureHolder const&) = delete;
        TextureHolder& operator=(TextureHolder const&) = delete;

        static TextureHolder& get_instance();
        sf::Texture texture(char const*);
    private:
        TextureHolder() {}
        std::map<char const*, sf::Texture> textures_;
    };

    TextureHolder& TextureHolder::get_instance()
    {
        static TextureHolder th;
        return th;
    }

    sf::Texture TextureHolder::texture(char const* path)
    {
        if (auto it{textures_.find(path)}; it == textures_.end())
            textures_[path].loadFromFile(path);
        return textures_[path];
    }

} // namespace game

#endif // !TEXTURE_HOLDER_CLASS_H_