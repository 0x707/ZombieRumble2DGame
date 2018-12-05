#include <SFML/Graphics/Sprite.hpp>

#ifndef ZOMBIE_CLASS_H_
#define ZOMBIE_CLASS_H_

namespace game {
	using namespace sf;

	class ZombieBase
	{
	public:
		bool hit();
		void update(float elapsedTime, Vector2f const& playerPos);

		FloatRect get_position() const;// { return sprite_.getGlobalBounds(); }
		Sprite const& get_sprite() const { return sprite_; }
		bool is_alive() const { return alive_; }
	protected:
		ZombieBase(char const*, Vector2f const&, float, int);
	private:
		Sprite sprite_;
		Vector2f position_;
		float speed_;
		int health_;
		bool alive_ = true;
	};

	class Bloater : public ZombieBase
	{
	public:
		Bloater(Vector2f const&);
	};

	class Chaser : public ZombieBase
	{
	public:
		Chaser(Vector2f const&);
	};

	class Crawler : public ZombieBase
	{
	public:
		Crawler(Vector2f const&);
	};

} // namespace game

#endif // !ZOMBIE_CLASS_H_