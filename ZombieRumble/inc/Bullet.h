#include <SFML/Graphics/RectangleShape.hpp>

#ifndef BULLET_CLASS_H_
#define BULLET_CLASS_H_

namespace game {
	using namespace sf;

	struct BulletData
	{
		RectangleShape sBulletShape;
		Vector2f sPosition;
		bool sInFlight = false;
		float sBulletSpeed = 1000.f;
	};

	class Bullet
	{

	};

} // namespace game

#endif // !BULLET_CLASS_H_
