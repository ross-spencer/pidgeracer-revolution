//random.cpp

#include "random.h"

/**********************************************************************
*
*  Name:    
*
*  Author:  
*
*  Purpose: 
*
**********************************************************************/
int Random::GenerateRandom(int R1, int R2)
{
	static boost::mt19937 rng(static_cast<unsigned> (time(0)));		//seeded marsenne twister

	boost::uniform_int<> six(R1,R2);      // distribution that maps to 1..6

	boost::variate_generator<boost::mt19937&, boost::uniform_int<> >uniform_sampler(rng, six);	// glues randomness with mapping

	return uniform_sampler();
}

/**********************************************************************
*
*  Name:    
*
*  Author:  
*
*  Purpose: 
*
**********************************************************************/
bool Random::GenerateBernoulli()
{
	static boost::mt19937 rng(static_cast<unsigned> (time(0)));		//seeded marsenne twister

	boost::bernoulli_distribution<> six;

	boost::variate_generator<boost::mt19937&, boost::bernoulli_distribution<> >bernoulli_sampler(rng, six);	// glues randomness with mapping

	return bernoulli_sampler();
}
