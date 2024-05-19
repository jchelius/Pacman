#ifndef RANDOM_H
#define RANDOM_H

#include <random>


class Random
{
private:
	static std::random_device _rand_dev;
	static std::mt19937 _rng;
public:
	static void setSeed();
	static const double randdouble(double min, double max);
	static const int randint(int min, int max);
};

#endif //RANDOM_H