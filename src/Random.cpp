#include "../include/Random.hpp"
#include <time.h>


std::random_device Random::_rand_dev;
std::mt19937 Random::_rng(Random::_rand_dev());

void Random::setSeed()
{
	_rng.seed((unsigned)(time(0)));
}

const double Random::randdouble(double min, double max)
{
	std::uniform_real_distribution<double> randdouble(min, max);
	return randdouble(_rng);
}

const int Random::randint(int min, int max)
{
	std::uniform_int_distribution<int> randint(min, max);
	return randint(_rng);
}