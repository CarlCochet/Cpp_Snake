#include "utils.h"

// Taking 2 integers between which we generate a random integer
int randint(int a, int b)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distrib(a, b);
	return distrib(rng);
}
