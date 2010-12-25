#ifndef TOASTERTEST_H_
#define TOASTERTEST_H_

#include <cxxtest/TestSuite.h>
#include "Toaster.h"

class ToasterTest: public CxxTest::TestSuite
{
  public:
    /*
     * Create a toaster and check its initial conditions
     */
    void test_initialToasterConditions() {
      Toaster toast1 = Toaster();
      TS_ASSERT_EQUALS(toast1.isRunning(), false);
      TS_ASSERT_EQUALS(toast1.getCycleTime(), 0);
      TS_ASSERT_EQUALS(toast1.getTotalTime(), 0);
      TS_ASSERT_EQUALS(toast1.getLifetime(), 0);
      TS_ASSERT_EQUALS(toast1.getEnergy(), 0);
      TS_ASSERT_EQUALS(toast1.getPower(), 0);
    }

    /*
     * Create a toaster, turn it on, test that it turns off after
     * two ticks.
     */
    void test_toasterCycle() {
      Toaster toast1 = Toaster();

      toast1.turnOn();
      TS_ASSERT_EQUALS(toast1.isRunning(), true);

      toast1.tick();
      TS_ASSERT_EQUALS(toast1.isRunning(), true);
      TS_ASSERT_EQUALS(toast1.getCycleTime(), 1);
      TS_ASSERT_EQUALS(toast1.getTotalTime(), 1);
      TS_ASSERT_EQUALS(toast1.getLifetime(), 1);
      TS_ASSERT_EQUALS(toast1.getEnergy(), 900);

      toast1.tick();
      TS_ASSERT_EQUALS(toast1.isRunning(), false);
      TS_ASSERT_EQUALS(toast1.getCycleTime(), 0);
      TS_ASSERT_EQUALS(toast1.getTotalTime(), 2);
      TS_ASSERT_EQUALS(toast1.getLifetime(), 2);
      TS_ASSERT_EQUALS(toast1.getEnergy(), 1800);


      //Ensure off state and cycle time remain zero when toaster is off.
      toast1.tick();
      TS_ASSERT_EQUALS(toast1.isRunning(), false);
      TS_ASSERT_EQUALS(toast1.getCycleTime(), 0);
      TS_ASSERT_EQUALS(toast1.getTotalTime(), 2);
      TS_ASSERT_EQUALS(toast1.getLifetime(), 3);
      TS_ASSERT_EQUALS(toast1.getEnergy(), 1800);
    }
};
#endif /* TOASTERTEST_H_ */
