#ifndef MOCKRANDOM_H_
#define MOCKRANDOM_H_

#include "Random.h"

#include <deque>

// TODO user23: comment all
class MockRandom: public Random
{
  private:
    std::deque<int> queue_;

  public:
    MockRandom() :
      Random()
    {
    }

    virtual void seed(int seed)
    {
      queue_.push_back(seed);
    }

    virtual void seedNormal(double normal)
    {
      seed(normal * getRandomMax());
    }

    virtual int random()
    {
      if (!queue_.empty()) {
        int random = queue_.front();
        queue_.pop_front();
        return random;
      }
      else {
        return Random::random();
      }
    }

};

#endif /* MOCKRANDOM_H_ */
