#ifndef OVENTEST_H_
#define OVENTEST_H_

#include <cxxtest/TestSuite.h>

#include "Oven.h"

class OvenTest: public CxxTest::TestSuite
{
  public:
    // test for constructor, checking if variables are initialized correctly.
    void test_constructor()
    {
      Oven testOven = Oven();

      // oven should be off when created
      TS_ASSERT_EQUALS(testOven.isOn(), false);

      // total ticks should start at zero
      TS_ASSERT_EQUALS(testOven.getTicks(), 0);

      // total preheating ticks should start at zero
      TS_ASSERT_EQUALS(testOven.getPreheatTicks(), 0);

      // total baking ticks should start at zero
      TS_ASSERT_EQUALS(testOven.getBakingTicks(), 0);
    }

    // test for turning the oven on
    void test_turnOn()
    {
      Oven testOven = Oven();
      testOven.turnOn();

      // oven should now be on
      TS_ASSERT_EQUALS(testOven.isOn(), true);

      // counter should be set to zero
      TS_ASSERT_EQUALS(testOven.getCounter(), 0);
    }

    // test for tick()
    void test_tick()
    {
      Oven testOven = Oven();
      testOven.tick();

      // ticks should be 1
      TS_ASSERT_EQUALS(testOven.getTicks(), 1);

      // total baking and preheating ticks should still be 0
      TS_ASSERT_EQUALS(testOven.getPreheatTicks(), 0);
      TS_ASSERT_EQUALS(testOven.getBakingTicks(), 0);

      // oven should still be off
      TS_ASSERT_EQUALS(testOven.isOn(), 0);

      testOven.turnOn();
      // test preheat cycle
      for (int i = 1; i <= 10; i++) {
        testOven.tick();
        // ticks should equal (i + 1)
        TS_ASSERT_EQUALS(testOven.getTicks(), i + 1);
        // counter should be equal to i
        TS_ASSERT_EQUALS(testOven.getCounter(), i);
        // preheat ticks should equal i
        TS_ASSERT_EQUALS(testOven.getPreheatTicks(), i);
        // baking ticks should remain 0
        TS_ASSERT_EQUALS(testOven.getBakingTicks(), 0);
      }
      // test baking cycle
      for (int i = 11; i <= 40; i++) {
        testOven.tick();
        // number of ticks should be (i + 1)
        TS_ASSERT_EQUALS(testOven.getTicks(), i + 1);
        // preheat ticks should remain at 10
        TS_ASSERT_EQUALS(testOven.getPreheatTicks(), 10);
        // counter should be equal to i
        TS_ASSERT_EQUALS(testOven.getCounter(), i);
        // baking ticks should be equal to (i - 10)
        TS_ASSERT_EQUALS(testOven.getBakingTicks(), i - 10);
      }
      // oven cycle is over, next tick should turn off oven
      testOven.tick();
      TS_ASSERT_EQUALS(testOven.isOn(), false);
      // preheat ticks should remain at 10
      TS_ASSERT_EQUALS(testOven.getPreheatTicks(), 10);
      // baking ticks should remain at 30
      TS_ASSERT_EQUALS(testOven.getBakingTicks(), 30);

      // additional ticks after cycle has completed
      for (int i = 0; i < 5; i++) {
        testOven.tick();
      }
      // oven should still be off
      TS_ASSERT_EQUALS(testOven.isOn(), false);
      // ticks should have increased by 5
      TS_ASSERT_EQUALS(testOven.getTicks(), 47);
      // preheat ticks should have remained 10
      TS_ASSERT_EQUALS(testOven.getPreheatTicks(), 10);
      // baking ticks should have remained at 30
      TS_ASSERT_EQUALS(testOven.getBakingTicks(), 30);
    }

    // test for getEnergy()
    void test_getEnergy()
    {
      Oven testOven = Oven();
      // total energy used by oven should be zero when it is created
      TS_ASSERT_EQUALS(testOven.getEnergy(), 0);

      for (int i = 0; i < 5; i++) {
        testOven.tick();
        // total energy used by oven should remain zero while oven is off.
        TS_ASSERT_EQUALS(testOven.getEnergy(), 0);
      }

      testOven.turnOn();
      // preheat-bake cycle
      for (int i = 0; i < 40; i++) {
        testOven.tick();
      }
      // total energy used should equal 10 * 7500 kW + 30 * 2500 kW
      TS_ASSERT_EQUALS(testOven.getEnergy(), 10 * PREHEATING_POWER + 30 * BAKING_POWER);
    }

    // test for getPower()
    void test_getPower()
    {
      Oven testOven = Oven();
      TS_ASSERT_EQUALS(testOven.getPower(), 0);
    }
};

#endif /* OVENTEST_H_ */
