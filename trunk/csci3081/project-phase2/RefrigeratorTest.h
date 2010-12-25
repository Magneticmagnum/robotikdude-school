#ifndef REFRIGERATORTEST_H_
#define REFRIGERATORTEST_H_

#include <cxxtest/TestSuite.h>
#include "Refrigerator.h"
#include "Scheduler.h"

#include <cstdlib>

class RefrigeratorTest: public CxxTest::TestSuite
{
  public:

    /**
     * Test that the refrigerator is in a random state when created.
     */
    void test_initialConditions()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_initialConditions()");

      srand(0);
      Refrigerator r = Refrigerator();

      // LOG4CXX_DEBUG(log, "    Testing refrigerator is not running when first created.");

      TS_ASSERT(!r.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_initialConditions()");
    }

    /**
     * Test that the refrigerator turns off after being on for three ticks.
     */
    void test_turningOff()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_turningOff()");

      srand(0);
      Refrigerator r = Refrigerator();
      // refrigerator should be off when seeded with a 0
      TS_ASSERT(!r.isRunning());
      r.tick();
      // and turn on after one tick
      TS_ASSERT(r.isRunning());
      r.tick(); // 1
      TS_ASSERT(r.isRunning());
      r.tick(); // 2
      TS_ASSERT(r.isRunning());
      r.tick(); // 3
      // refrigerator should turn of
      TS_ASSERT(!r.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_turningOff()");
    }

    /**
     * Test that the refrigerator turns on after being off for nine ticks.
     */
    void test_turningOn()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_turningOn()");

      srand(0);
      Refrigerator r = Refrigerator();
      r.tick();
      r.tick();
      r.tick();
      r.tick();
      // refrigerator should turn off
      TS_ASSERT(!r.isRunning());
      r.tick(); // 1
      TS_ASSERT(!r.isRunning());
      r.tick(); // 2
      TS_ASSERT(!r.isRunning());
      r.tick(); // 3
      TS_ASSERT(!r.isRunning());
      r.tick(); // 4
      TS_ASSERT(!r.isRunning());
      r.tick(); // 5
      TS_ASSERT(!r.isRunning());
      r.tick(); // 6
      TS_ASSERT(!r.isRunning());
      r.tick(); // 7
      // refrigerator should turn on
      TS_ASSERT(r.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_turningOn()");
    }

    /**
     * Test that the refrigerator uses 150 watts of power.
     */
    void test_power()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_power()");

      srand(0);
      Refrigerator r = Refrigerator();
      r.tick();
      TS_ASSERT_EQUALS(r.getPower(), 150.0);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_power()");
    }

    /**
     * Test that the refrigerator uses 450 joules of energy after one
     * off/on/off cycle.
     */
    void test_energy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_energy()");

      srand(0);
      Refrigerator r = Refrigerator();
      // refrigerator should be on

      r.tick(); // tick: 1, energy: 0
      r.tick(); // tick: 2 (1), energy: 150
      TS_ASSERT_EQUALS(r.getEnergy(), 150.0);
      r.tick(); // tick: 3 (2), energy: 300
      TS_ASSERT_EQUALS(r.getEnergy(), 300.0);
      r.tick(); // tick: 4 (3), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      // refrigerator should turn off

      r.tick(); // tick: 5 (1), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 6 (2), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 7 (3), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 8 (4), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 9 (5), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 10 (6), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 11 (7), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      // refrigerator should turn on

      r.tick(); // tick: 14 (1), energy: 600
      TS_ASSERT_EQUALS(r.getEnergy(), 600.0);
      r.tick(); // tick: 15 (2), energy: 750
      TS_ASSERT_EQUALS(r.getEnergy(), 750.0);
      r.tick(); // tick: 16 (3), energy: 900
      TS_ASSERT_EQUALS(r.getEnergy(), 900.0);
      // refrigerator should turn off

      r.tick(); // tick: 17 (1), energy: 900
      TS_ASSERT_EQUALS(r.getEnergy(), 900.0);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_energy()");
    }

    void test_inUse()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_inUse()");

      srand(0);
      Refrigerator r = Refrigerator();
      // one tick to get it to the beginning (just starting to run)
      r.tick();
      r.setInUse(true);

      TS_ASSERT(r.isRunning());
      r.tick(); // 1
      TS_ASSERT(r.isRunning());
      r.tick(); // 2
      TS_ASSERT(r.isRunning());
      r.tick(); // 3
      // refrigerator should turn off
      TS_ASSERT(!r.isRunning());
      r.tick(); // 1
      TS_ASSERT(!r.isRunning());
      r.tick(); // 2
      TS_ASSERT(!r.isRunning());
      r.tick(); // 3
      // refrigerator should turn on
      TS_ASSERT(r.isRunning());
      r.tick(); // 1
      TS_ASSERT(r.isRunning());
      r.tick(); // 2
      TS_ASSERT(r.isRunning());
      r.tick(); // 3
      // refrigerator should turn off
      TS_ASSERT(!r.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_inUse()");
    }

};

#endif /* REFRIGERATORTEST_H_ */
