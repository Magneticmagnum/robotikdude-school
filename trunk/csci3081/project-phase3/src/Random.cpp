#include "Random.h"
#include <cstdlib>

Random::Random() :
  randomMax_(RAND_MAX)
{
}

void Random::seed(int seed)
{
  srand(seed);
}

int Random::random()
{
  return rand();
}

double Random::normal()
{
  return random() / randomMax_;
}

double Random::getRandomMax() const
{
  return randomMax_;
}
