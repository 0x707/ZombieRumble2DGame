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
        sf::Texture& texture(char const*);
    private:
        TextureHolder() {}
        std::map<char const*, sf::Texture> textures_;
    };

} // namespace game

#endif // !TEXTURE_HOLDER_CLASS_H_