#ifndef TELEVISIONTEST_H_
#define TELEVISIONTEST_H_

#include <cxxtest/TestSuite.h>

#include "Television.h"

class TelevisionTest: public CxxTest::TestSuite
{
  public:
    // test default constructor
    void test_contructor()
    {
      Television tv = Television();

      // checks that tv is off when created
      TS_ASSERT_EQUALS(tv.isOn(), false);

      // checks that ticks on counter starts at zero
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 0);

      // checks that ticks off counter starts at zero
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 0);

      // checks that ticks counter starts at zero
      TS_ASSERT_EQUALS(tv.getTotalTicks(), 0);
    }

    // test tick counter is incremented with every call to tick()
    void test_tick_counter()
    {
      Television tv = Television();

      tv.tick();

      // after one call to tick(), tick counter should be 1
      TS_ASSERT_EQUALS(tv.getTotalTicks(), 1);

      tv.tick();
      tv.tick();
      tv.tick();
      tv.tick();
      tv.tick();

      TS_ASSERT_EQUALS(tv.getTotalTicks(), 6);
    }

    // tests the on and off state switches
    void test_on_and_off()
    {
      Television tv = Television();

      tv.turnOff(); // tv is already off so shouldn't change the state
      TS_ASSERT_EQUALS(tv.isOn(), false);

      tv.turnOn(); // should turn tv on
      TS_ASSERT_EQUALS(tv.isOn(), true);

      tv.turnOn(); // tv is already on so shouldn't change the state
      TS_ASSERT_EQUALS(tv.isOn(), true);

      tv.turnOff(); // tv should turn off
      TS_ASSERT_EQUALS(tv.isOn(), false);
    }

    // tests that totalTimeOff_ is incremented when television is off
    // and that TotalTimeOn_ is not changed.
    void test_time_off()
    {
      Television tv = Television();

      tv.tick();
      tv.tick();
      tv.tick();

      // total time on should be zero
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 0);

      // total time off should be 3
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 3);
    }

    // tests that totalTimeOn_ is incremented when television is on
    // and that TotalTimeOff_ is not changed.
    void test_time_on()
    {
      Television tv = Television();
      tv.turnOn();

      tv.tick();
      tv.tick();
      tv.tick();

      // total time off should be zero
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 0);

      // total time on should be 3
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 3);
    }

    // tests for energy usage
    void test_energy()
    {
      Television tv = Television();
      tv.turnOn();
      for (int i = 0; i < 5; i++) {
        tv.tick();
      }

      TS_ASSERT_EQUALS(tv.getEnergy(), 5 * TELEVISION_ON_POWER);

      tv.turnOff();
      for (int i = 0; i < 5; i++) {
        tv.tick();
      }

      TS_ASSERT_EQUALS(tv.getEnergy(), 5 * TELEVISION_ON_POWER + 5 * TELEVISION_OFF_POWER);
    }

    // tests get power; should simply return 0 since I don't use it
    void test_get_power()
    {
      Television tv = Television();
      TS_ASSERT_EQUALS(tv.getPower(), 0);
    }
};

#endif /* TELEVISIONTEST_H_ */
