#ifndef RANDOMTEST_H_
#define RANDOMTEST_H_

#include "Random.h"

#include <cxxtest/TestSuite.h>

// TODO user23: find common seed
class RandomTest: public CxxTest::TestSuite
{
  public:
    void test_seed()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RandomTest"));
      LOG4CXX_DEBUG(log, "--> RandomTest::test_seed()");

      Random* random = new Random();
      random->seed(42);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);

      LOG4CXX_DEBUG(log, "<-- RandomTest::test_seed()");
    }

    void test_random()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RandomTest"));
      LOG4CXX_DEBUG(log, "--> RandomTest::test_random()");

      Random* random = new Random();

      random->seed(42);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);

      random->seed(42);
      random->random();
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);
      //      TS_ASSERT_EQUALS(random->random(), 0);

      delete (random);

      LOG4CXX_DEBUG(log, "<-- RandomTest::test_random()");
    }

    void test_normal()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RandomTest"));
      LOG4CXX_DEBUG(log, "--> RandomTest::test_normal()");

      Random* random = new Random();

      random->seed(42);
      random->normal();
      //      TS_ASSERT_DELTA(random->normal(), 0, 0.001);
      //      TS_ASSERT_DELTA(random->normal(), 0, 0.001);
      //      TS_ASSERT_DELTA(random->normal(), 0, 0.001);
      //      TS_ASSERT_DELTA(random->normal(), 0, 0.001);

      delete (random);

      LOG4CXX_DEBUG(log, "<-- RandomTest::test_normal()");
    }

    void test_getRandomMax()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RandomTest"));
      LOG4CXX_DEBUG(log, "--> RandomTest::test_getRandomMax()");

      Random* random = new Random();
      TS_ASSERT_EQUALS(random->getRandomMax(), RAND_MAX);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- RandomTest::test_getRandomMax()");
    }
};

#endif /* RANDOMTEST_H_ */
