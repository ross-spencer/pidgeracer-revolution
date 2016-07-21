//random.h

#ifndef RANDOM_H
#define RANDOM_H

#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/bernoulli_distribution.hpp>

class Random
{
	public:

		int GenerateRandom(int R1 = 1, int R2 = 6);

		bool GenerateBernoulli();
};

#endif
