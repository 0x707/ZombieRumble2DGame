#include "Zombie.h"

#ifndef HORDE_CLASS_H_
#define HORDE_CLASS_H_

namespace game {
	unsigned constexpr MAX_NO_ZOMBIE = 100;

	class ZombieHorde
	{
	public:
		ZombieHorde(unsigned);
		~ZombieHorde();

		ZombieHorde(ZombieHorde const&) = delete;
		ZombieHorde(ZombieHorde&&) = delete;
		ZombieHorde& operator=(ZombieHorde const&) = delete;
		ZombieHorde& operator=(ZombieHorde&&) = delete;

		ZombieBase* operator[](unsigned);
		ZombieBase const* operator[](unsigned) const;

		void prepare_horde(IntRect const&);
		void release_mem();
		ZombieBase const* const* get_horde() { return theHorde_; }
		unsigned zombie_counter() const { return zombieCounter_; }

	private:
		ZombieBase* theHorde_[MAX_NO_ZOMBIE];
		unsigned zombieCounter_;
		unsigned zombiesAlive_;
	};

} // namespace game

#endif // !HORDE_CLASS_H_
