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
		std::uniform_int_distribution<> dist; // TODO rewrite it with mt19937
	};

	class RandFloatMT
	{
	public:
		RandFloatMT(float low, float high)
			: re{ std::random_device{}() }
			, dist{ low,high } {}
		float operator()() { return dist(re); }
	private:
		std::uniform_real_distribution<float> dist;
		std::mt19937_64 re;
	};

} // namespace utils

#endif // ! RANDOM_INT_GEN_CLASS_H_