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
        static Sounds& get_instance()
        {
            static Sounds sounds{};
            return sounds;
        }

        sf::Sound& operator[](AUDIO_BUFFER buff)
        {
            return audio_arr[buff];
        }

    private:
        Sounds() {}

		sf::SoundBuffer buffer_arr[7];

        sf::Sound audio_arr[7] {
            sound_buffer_factory("sound/hit.wav", 0),
            sound_buffer_factory("sound/pickup.wav", 1),
            sound_buffer_factory("sound/powerup.wav", 2),
            sound_buffer_factory("sound/reload_failed.wav", 3),
            sound_buffer_factory("sound/reload.wav", 4),
            sound_buffer_factory("sound/shoot.wav", 5),
            sound_buffer_factory("sound/splat.wav", 6)
        };

        sf::Sound sound_buffer_factory(char const* path, int index)
        {
            buffer_arr[index].loadFromFile(path);
            return sf::Sound{buffer_arr[index]};
        }
    };

} // namespace game

#endif // !AUDIO_CLASS_H_