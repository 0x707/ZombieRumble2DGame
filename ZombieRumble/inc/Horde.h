#include "Zombie.h"

#ifndef HORDE_CLASS_H_
#define HORDE_CLASS_H_

namespace game {
	unsigned constexpr MAX_NO_ZOMBIE = 100;

	class ZombieHorde
	{
	public:
		ZombieHorde(int);
		~ZombieHorde();

		ZombieHorde(ZombieHorde const&) = delete;
		ZombieHorde(ZombieHorde&&) = delete;
		ZombieHorde& operator=(ZombieHorde const&) = delete;
		ZombieHorde& operator=(ZombieHorde&&) = delete;

		ZombieBase* operator[](int);
		ZombieBase const* operator[](int) const;

		void prepare_horde(IntRect const&);
		ZombieBase const* const* get_horde() { return theHorde_; }
		int zombie_counter() const { return zombieCounter_; }
		int kill_zombie() { return --zombiesAlive_; }

		void release_mem();
	private:
		ZombieBase* theHorde_[MAX_NO_ZOMBIE];
		int zombieCounter_;
		int zombiesAlive_;
	};

} // namespace game

#endif // !HORDE_CLASS_H_
