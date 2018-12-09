#include "Horde.h"
#include "RandomGen.h"
#include <cassert>
#include <ctime>

namespace game {

	namespace {
		// constants used to randomly choose type of zombie
		constexpr unsigned MIN = 0;
		constexpr unsigned MAX = 2;

		Vector2f spawn_coords(IntRect const& arena)
		{
			utils::RandInt ri(0, 3); // four sied zombies will spawn at
			auto result{ ri() };

			float xMin = static_cast<float>(arena.left) + 50.f;
			float xMax = static_cast<float>(arena.width) - 50.f;
			float yMin = static_cast<float>(arena.top) + 50.f;
			float yMax = static_cast<float>(arena.height) - 50.f;

			utils::RandFloatMT rfX{ xMin,xMax };
			utils::RandFloatMT rfY{ yMin, yMax };
			
			switch (result) {
			case 0: return { xMin, rfY() };
			case 1: return { rfX(), yMin };
			case 2: return { xMax, rfY() };
			case 3: return { rfX(), yMax };
			}

			assert("Wrong number generated");
			return { 0, 0 };
		}

	} // anonymous namespace

	ZombieHorde::ZombieHorde(int zombies)
		: theHorde_{ nullptr }, zombieCounter_{ zombies }
		, zombiesAlive_{ zombieCounter_ }
	{
		//if (zombieCounter_ > MAX_NO_ZOMBIE)
			assert(zombieCounter_ <= MAX_NO_ZOMBIE);
	}

	void ZombieHorde::prepare_horde(IntRect const& arena)
	{
		//assert(amount > MAX_NO_ZOMBIE);
		//assert(amount <= 0);
		zombieCounter_ = zombiesAlive_;
		utils::RandInt ri{ MIN, MAX };

		for (int i = 0; i < zombieCounter_; ++i) {
			auto zombieType{ ri() };
			auto zombiePos{ spawn_coords(arena) };

			if (zombieType == 0)
				theHorde_[i] = new Bloater{ zombiePos };
			else if (zombieType == 1)
				theHorde_[i] = new Chaser{ zombiePos };
			else
				theHorde_[i] = new Crawler{ zombiePos };
		}
	}

	void ZombieHorde::release_mem()
	{
		if (zombieCounter_ > 0) {
			for (int i = 0; i < zombieCounter_; ++i)
				delete theHorde_[i];
		}
		zombieCounter_ = 0;
	}

	ZombieHorde::~ZombieHorde()
	{
		if (zombieCounter_ > 0)
			release_mem();
	}

	ZombieBase* ZombieHorde::operator[](int index)
	{
		if (index < zombieCounter_)
			return theHorde_[index];
		return nullptr;
	}

	ZombieBase const* ZombieHorde::operator[](int index) const
	{
		if (index < zombieCounter_)
			return theHorde_[index];
		return nullptr;
	}

} // namespace game