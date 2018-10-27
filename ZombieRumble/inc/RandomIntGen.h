#include <random>

#ifndef  RANDOM_INT_GEN_CLASS_H_
#define RANDOM_INT_GEN_CLASS_H_

namespace utils {

	class RandInt
	{
	public:
		RandInt(unsigned low, unsigned high) : re{ std::random_device{}() }, dist{ low,high } {}
		unsigned operator()() { return dist(re); }
	private:
		std::default_random_engine re;
		std::uniform_int_distribution<> dist;
	};

} // namespace utils

#endif // ! RANDOM_INT_GEN_CLASS_H_