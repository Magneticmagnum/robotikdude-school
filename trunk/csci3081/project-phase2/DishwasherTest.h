#ifndef DISHWASHERTEST_H_
#define DISHWASHERTEST_H_

#include <cxxtest/TestSuite.h>
#include "Dishwasher.h"

#include <string>
#include <fstream>

class DishwasherTest: public CxxTest::TestSuite
{
  public:

    /*
     * Test the dishwasher's constructor method
     */
    void test_constructor()
    {

      Dishwasher testDishwasher = Dishwasher();

      TS_ASSERT_EQUALS(testDishwasher.isRunning(), false);
      TS_ASSERT_EQUALS(testDishwasher.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 0.0);
    }

    /*
     * Test the dishwasher's tick method.  Ensure that total energy
     * used increases appropriately, that the cycle decrements
     * appropriately, etc.
     */
    //    void test_tick()
    //    {
    //      Dishwasher testWasher = Dishwasher();
    //    }

    /**
     * Test what happens when the dishwasher is turned
     * on:  the instantaneous power usage goes up to 2000,
     * the dishwasher reports that it is on (not off), etc.
     */
    void test_turnOn()
    {

      Dishwasher testDishwasher = Dishwasher();
      double i;

      testDishwasher.turnOn();

      TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
      TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), 45.0);
      TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 20.0);

      for (i = 45.0; i > 25.0; i--) {
        TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
        TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), i);
        TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), i - 25.0);
        testDishwasher.tick();
      }

      for (i; i > 0; i--) {
        TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
        TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), i);
        TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 0.0);
        testDishwasher.tick();
      }

      TS_ASSERT_EQUALS(testDishwasher.isRunning(), false);

      testDishwasher.turnOn();
      TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
      TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), 45.0);
      TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 20.0);
      testDishwasher.tick();
      testDishwasher.turnOn();
      TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
      TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), 44.0);
      TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 19.0);
    }

    /*
     * Test whether the dishwasher correctly tracks it's energy usage.
     */
    void test_getEnergy()
    {

      Dishwasher testWasher = Dishwasher();

      TS_ASSERT_EQUALS(testWasher.getEnergy(), 0.0);

      testWasher.tick();

      TS_ASSERT_EQUALS(testWasher.getEnergy(), 4.0);

      testWasher.turnOn();
      testWasher.tick();

      TS_ASSERT_EQUALS(testWasher.getEnergy(), 2004.0);

      testWasher.tick();

      TS_ASSERT_EQUALS(testWasher.getEnergy(), 4004.0);
    }

    /*
     * Test of the getPower() function
     */
    void test_getPower()
    {

      Dishwasher testWasher = Dishwasher();

      TS_ASSERT_EQUALS(testWasher.getPower(), 4.0);

      testWasher.turnOn();
      testWasher.tick();

      TS_ASSERT_EQUALS(testWasher.getPower(), 2000.0);
    }

    /*
     * Test that isRunning() returns the appropriate value
     */
    void test_isRunning()
    {
      Dishwasher testWasher = Dishwasher();

      TS_ASSERT_EQUALS(testWasher.isRunning(), false);

      testWasher.turnOn();

      for (int i = 0; i < 45; i++) {
        TS_ASSERT_EQUALS(testWasher.isRunning(), true);
        testWasher.tick();
      }

      TS_ASSERT_EQUALS(testWasher.isRunning(), false);
    }

    /*
     * Test that the dishwasher correctly tracks its cycle.
     */
    void test_cycleTimeLeft()
    {
      Dishwasher testWasher = Dishwasher();

      TS_ASSERT_EQUALS(testWasher.getRunningTimeLeft(), 0.0);
      TS_ASSERT_EQUALS(testWasher.getWaterTimeLeft(), 0.0);

      testWasher.turnOn();

      TS_ASSERT_EQUALS(testWasher.getRunningTimeLeft(), 45.0);
      TS_ASSERT_EQUALS(testWasher.getWaterTimeLeft(), 20.0);

      for (int i = 20.0; i > 0.0; i--) {
        TS_ASSERT_EQUALS(testWasher.getWaterTimeLeft(), i);
        testWasher.tick();
      }

      for (int i = 25.0; i >= 0.0; i--) {
        TS_ASSERT_EQUALS(testWasher.getRunningTimeLeft(), i);
        testWasher.tick();
      }
    }
};

#endif /* DISHWASHERTEST_H_ */
