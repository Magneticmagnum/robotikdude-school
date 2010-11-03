#ifndef REFRIGERATORTEST_H_
#define REFRIGERATORTEST_H_

#include <cxxtest/TestSuite.h>
#include "Refrigerator.h"
#include "Scheduler.h"

#include <string>
#include <fstream>

class RefrigeratorTest: public CxxTest::TestSuite
{
  public:

    /**
     * Test that the refrigerator is on when created.
     */
    void test_initialConditions()
    {
      Refrigerator r = Refrigerator();
      TS_ASSERT(r.isRunning());
    }

    /**
     * Test that the refrigerator turns off after being on for three ticks.
     */
    void test_turningOff()
    {
      Refrigerator r = Refrigerator();
      // refrigerator should be on
      TS_ASSERT(r.isRunning());
      r.tick(); // 1
      TS_ASSERT(r.isRunning());
      r.tick(); // 2
      TS_ASSERT(r.isRunning());
      r.tick(); // 3
      // refrigerator should turn off
      TS_ASSERT(!r.isRunning());
    }

    /**
     * Test that the refrigerator turns on after being off for nine ticks.
     */
    void test_turningOn()
    {
      Refrigerator r = Refrigerator();
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
      TS_ASSERT(!r.isRunning());
      r.tick(); // 8
      TS_ASSERT(!r.isRunning());
      r.tick(); // 9
      // refrigerator should turn on
      TS_ASSERT(r.isRunning());
    }

    /**
     * Test that the refrigerator uses 150 watts of power.
     */
    void test_power()
    {
      Refrigerator r = Refrigerator();
      TS_ASSERT_EQUALS(r.getPower(), 150.0);
    }

    /**
     * Test that the refrigerator uses 450 joules of energy after one
     * off/on/off cycle.
     */
    void test_energy()
    {
      Refrigerator r = Refrigerator();
      // refrigerator should be on

      r.tick(); // tick: 1, energy: 150
      TS_ASSERT_EQUALS(r.getEnergy(), 150.0);
      r.tick(); // tick: 2, energy: 300
      TS_ASSERT_EQUALS(r.getEnergy(), 300.0);
      r.tick(); // tick: 3, energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      // refrigerator should turn off

      r.tick(); // tick: 4 (1), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 5 (2), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 6 (3), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 7 (4), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 8 (5), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 9 (6), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 10 (7), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 11 (8), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      r.tick(); // tick: 12 (9), energy: 450
      TS_ASSERT_EQUALS(r.getEnergy(), 450.0);
      // refrigerator should turn on

      r.tick(); // tick: 13 (1), energy: 600
      TS_ASSERT_EQUALS(r.getEnergy(), 600.0);
      r.tick(); // tick: 14 (2), energy: 750
      TS_ASSERT_EQUALS(r.getEnergy(), 750.0);
      r.tick(); // tick: 15 (3), energy: 900
      TS_ASSERT_EQUALS(r.getEnergy(), 900.0);
      // refrigerator should turn off

      r.tick(); // tick: 16 (1), energy: 900
      TS_ASSERT_EQUALS(r.getEnergy(), 900.0);
    }

};

#endif /* REFRIGERATORTEST_H_ */
