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
    void testConstructor() {

       Dishwasher testDishwasher = Dishwasher();

       TS_ASSERT_EQUALS(testDishwasher.isRunning(), false);
       TS_ASSERT_EQUALS(testDishwasher.getEnergy(), 0.0);
       TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), 0.0);
       TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 0.0);
    }

//    /*
//     * Test the dishwasher's tick method.  Ensure that total energy
//     * used increases appropriately, that the cycle decrements
//     * appropriately, etc.
//     */
//    void testTick() {
//
//      Dishwasher testWasher = Dishwasher();
//
//
//    }

    /**
     * Test what happens when the dishwasher is turned
     * on:  the instantaneous power usage goes up to 2000,
     * the dishwasher reports that it is on (not off), etc.
     */
    void testTurnOn() {

      Dishwasher testDishwasher = Dishwasher();
      double i;

      testDishwasher.turnOn();

      TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
      TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), 45.0);
      TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 20.0);

      for(i = 45.0; i > 25.0; i--) {
        testDishwasher.tick();
        TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
        TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), i - 1.0);
        TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), i - 1.0);
      }

      for(i; i > 0; i--) {
        testDishwasher.tick();
        TS_ASSERT_EQUALS(testDishwasher.isRunning(), true);
        TS_ASSERT_EQUALS(testDishwasher.getRunningTimeLeft(), i - 1.0);
        TS_ASSERT_EQUALS(testDishwasher.getWaterTimeLeft(), 0.0);
      }

      TS_ASSERT_EQUALS(testDishwasher.isRunning(), false);
    }

    /*
     * Test whether the dishwasher correctly tracks it's energy usage.
     */
    void testGetEnergy() {

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
    void testGetPpower() {

      Dishwasher testWasher = Dishwasher();

      TS_ASSERT_EQUALS(testWasher.getPower(), 4.0);

      testWasher.turnOn();
      testWasher.tick();

      TS_ASSERT_EQUALS(testWasher.getPower(), 2000.0);
    }

    /*
     * Test that isRunning() returns the appropriate value
     */
    void testIsRunning() {

    }

    /*
     * Test that the dishwasher correctly tracks its cycle.
     */
    void test_CycleTimeLeft() {

    }
};

#endif /* DISHWASHERTEST_H_ */
