#include <SFML/Audio.hpp>

#ifndef AUDIO_CLASS_H_
#define AUDIO_CLASS_H_

namespace game {

    enum AUDIO_BUFFER {
        HIT, PICKUP, POWERUP, RELOAD_FAILED,
        RELOAD, SHOOT, SPLAT
    };

    class Sounds
    {
    public:
        static Sounds& get_instace()
        {
            static Sounds sounds{};
            return sounds;
        }

        sf::Sound const& operator[](AUDIO_BUFFER buff) const
        {
            return audio_arr[buff];
        }

    private:
        Sounds() {}
        sf::Sound sound_buffer_factory(char const* path)
        {
            sf::SoundBuffer buffer{};
            buffer.loadFromFile(path);
            return sf::Sound{buffer};
        }

        sf::Sound const audio_arr[7] {
            sound_buffer_factory("../sound/hit.wav"),
            sound_buffer_factory("../sound/pickup.wav"),
            sound_buffer_factory("../sound/powerup.wav"),
            sound_buffer_factory("../sound/reload_failed.wav"),
            sound_buffer_factory("../sound/reload.wav"),
            sound_buffer_factory("../sound/shoot.wav"),
            sound_buffer_factory("../sound/splat.wav")
        };
    };

} // namespace game

#endif // !AUDIO_CLASS_H_