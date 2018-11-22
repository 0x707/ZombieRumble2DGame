#include "Bullet.h"

namespace game {
namespace arms {

	void Bullet::shoot(Vector2f const& startPos, Vector2f const& targetPos)
	{
		bData_.sInFlight = true;
		bData_.sPosition = startPos;

		float gradient = (startPos.x - targetPos.x) /
			(startPos.y - targetPos.y);  // WHAT IF startPos.y == targetPos.y? dividing by 0!

		float ratioXY = bData_.sBulletSpeed / (1 + std::abs(gradient));
		bData_.sBulletDist.y = ratioXY;
		bData_.sBulletDist.x = ratioXY * std::abs(gradient);
		if (startPos.x > targetPos.x)
			bData_.sBulletDist.x *= -1;
		if (startPos.y > targetPos.y)
			bData_.sBulletDist.y *= -1;

		float range = 1000.f;
		bData_.sBulletRange = { startPos.x + range,  startPos.x - range,
			startPos.y + range, startPos.y - range };

		bData_.set_position();
	}

	bool Bullet::update(float elapsedTime)
	{
		bData_.sPosition.x += bData_.sBulletDist.x * elapsedTime;
		bData_.sPosition.y += bData_.sBulletDist.y * elapsedTime;

		bData_.set_position();

		if (bData_.sPosition.x > bData_.sBulletRange.sXMax ||
			bData_.sPosition.x < bData_.sBulletRange.sXMin ||
			bData_.sPosition.y > bData_.sBulletRange.sYMax ||
			bData_.sPosition.y < bData_.sBulletRange.sYMin)
			bData_.sInFlight = false;
		return bData_.sInFlight;
	}

} // namespace arms
} // namespace game