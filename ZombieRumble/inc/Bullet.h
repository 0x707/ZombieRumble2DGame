#include <SFML/Graphics/RectangleShape.hpp>

#ifndef BULLET_CLASS_H_
#define BULLET_CLASS_H_

namespace game {
	using namespace sf;

	struct BulletData
	{
		void set_position() { sBulletShape.setPosition(sPosition); }

		RectangleShape sBulletShape{ Vector2f{2,2} };
		Vector2f sPosition;
		bool sInFlight = false;
		float sBulletSpeed = 1000.f;
		Vector2f sBulletDist;
		struct BulletRange {
			float sXMax;
			float sXMin;
			float sYMax;
			float sYMin;
		} sBulletRange;
	};

	class Bullet
	{
	public:
		Bullet() {}
		void shoot(Vector2f const&, Vector2f const&);
		void update(float);

		void stop() { bData_.sInFlight = false; }
		bool is_inFlight() const { return bData_.sInFlight; }
		RectangleShape get_shape() const { return bData_.sBulletShape; }
		FloatRect get_position() const { return get_shape().getGlobalBounds(); }

	private:
		BulletData bData_;
	};

} // namespace game

#endif // !BULLET_CLASS_H_
