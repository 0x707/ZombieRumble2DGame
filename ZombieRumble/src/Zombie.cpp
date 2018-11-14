#include "Zombie.h"
#include "TextureHolder.h"
#include "RandomGen.h"

namespace game {

	namespace {
		constexpr unsigned MAX_VARIANCE = 100;
		constexpr unsigned OFFSET = MAX_VARIANCE - 20;
		utils::RandInt ri{ OFFSET, MAX_VARIANCE };

	} // anonymous namespace

	ZombieBase::ZombieBase(char const* path, Vector2f const& pos,
		float speed, int hp)
		: sprite_{ TextureHolder::get_instance().texture(path) }
		, position_{ pos }
		, speed_{ speed * (static_cast<float>(ri()) / 100) }, health_{ hp }
	{
		sprite_.setOrigin(25, 25);
		sprite_.setPosition(position_);
	}

	bool ZombieBase::hit()
	{
		if (--health_ <= 0) {
			alive_ = false;
			sprite_.setTexture(TextureHolder::get_instance().
				texture("graphics/blood.png"));
			return true;
		}
		return false;
	}

	void ZombieBase::update(float elapsedTime, Vector2f const& playerPos)
	{
		float xPos = playerPos.x;
		float yPos = playerPos.y;

		if (xPos > position_.x)
			position_.x += elapsedTime * speed_;
		if (yPos > position_.y)
			position_.y += elapsedTime * speed_;
		if (xPos < position_.x)
			position_.x -= elapsedTime * speed_;
		if (yPos < position_.y)
			position_.y -= elapsedTime * speed_;
		sprite_.setPosition(position_);

		sprite_.setRotation(static_cast<float>((atan2(yPos - position_.y,
			xPos - position_.x) * 180) / 3.141));
	}

	// BLOATER ======================================================================

	Bloater::Bloater(Vector2f const& pos)
		: ZombieBase{ "graphics/bloater.png", pos, 35, 5 }
	{
	}

	// CHASER  ======================================================================

	Chaser::Chaser(Vector2f const& pos)
		: ZombieBase{ "graphics/chaser.png" , pos, 70, 2 }
	{
	}

	// CRAWLER ======================================================================

	Crawler::Crawler(Vector2f const& pos)
		: ZombieBase{ "graphics/crawler.png", pos, 20, 4 }
	{
	}

} // namespace game