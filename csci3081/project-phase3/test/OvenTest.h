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
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_constructor()");
      MockScheduler sch = MockScheduler();
      Oven oven = Oven(0, &sch);

      // oven should be off when created
      TS_ASSERT_EQUALS(oven.isRunning(), false);
      // total preheating ticks should start at zero
      TS_ASSERT_EQUALS(oven.getPreheatTicks(), 0);
      // total baking ticks should start at zero
      TS_ASSERT_EQUALS(oven.getBakingTicks(), 0);
      // no given bake time (ConfigMap* == 0) so default value should be used
      TS_ASSERT_EQUALS(oven.getBakeTime(), OVEN_DEFAULT_BAKE_TIME);
      // scheduler* stored should be the same as one given
      TS_ASSERT(oven.getScheduler() == &sch);

      LOG4CXX_DEBUG(log, "<-- OvenTest::test_constructor()");
    }

    // test initialization from config file
    void test_config()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_config()");

      ConfigMap* config = Model::parseConfiguration("unittest.config", OVEN, "oven");
      MockScheduler sch = MockScheduler();
      Oven oven = Oven(config, &sch);

      TS_ASSERT_EQUALS(oven.getBakeTime(), 40);

      ConfigMap* config2 = Model::parseConfiguration("unittest.config", OVEN, "fail-oven");
      Oven oven2 = Oven(config2, &sch);

      TS_ASSERT_EQUALS(oven2.getBakeTime(), OVEN_DEFAULT_BAKE_TIME);

      LOG4CXX_DEBUG(log, "--> OvenTest::test_config()");
    }

    // test for turning the oven on and off using action
    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_action()");

      MockScheduler sch = MockScheduler();
      Oven oven = Oven(0, &sch);

      // turn oven on
      bool noError = oven.action(OVEN_START);
      TS_ASSERT(noError);
      TS_ASSERT(oven.isRunning());

      LOG4CXX_DEBUG(log, "<-- OvenTest::test_action()");
    }

    void test_bad_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_bad_action()");

      MockScheduler sch = MockScheduler();
      Oven oven = Oven(0, &sch);

      // use bad action argument
      bool noError = oven.action("stop");
      // should return false
      TS_ASSERT(!noError);
      // Oven should not have turned on
      TS_ASSERT(!oven.isRunning());

      // use too many arguments
      noError = oven.action("start 0");
      // should return false
      TS_ASSERT(!noError);
      // Oven should not have turned on
      TS_ASSERT(!oven.isRunning());

      // turn oven on
      oven.action(OVEN_START);
      // try to turn on again
      noError = oven.action(OVEN_START);
      // should return false
      TS_ASSERT(!noError);
      // oven should still be on
      TS_ASSERT(oven.isRunning());

      LOG4CXX_DEBUG(log, "<-- OvenTest::test_bad_action()");
    }

    // test for tick()
    void test_tick()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_tick()");

      MockScheduler sch = MockScheduler();
      Oven oven = Oven(0, &sch);

      // test tick() when oven is off
      oven.tick();
      // total baking and preheating ticks should be 0
      TS_ASSERT_EQUALS(oven.getPreheatTicks(), 0);
      TS_ASSERT_EQUALS(oven.getBakingTicks(), 0);
      for (int i = 0; i < 100; i++) {
        oven.tick();
      }
      // total baking and preheating ticks should still be 0
      TS_ASSERT_EQUALS(oven.getPreheatTicks(), 0);
      TS_ASSERT_EQUALS(oven.getBakingTicks(), 0);

      // test preheat cycle
      oven.action(OVEN_START);
      TS_ASSERT(!oven.isPreheated());
      for (int i = 0; i < OVEN_PREHEAT_TIME; i++) {
        oven.tick();
      }
      // oven should be done preheating
      TS_ASSERT(oven.isPreheated());
      // oven should still be on
      TS_ASSERT(oven.isRunning());
      // total preheating ticks should be the time for the
      // whole preheating cycle (10)
      TS_ASSERT_EQUALS(oven.getPreheatTicks(), OVEN_PREHEAT_TIME);
      // total baking ticks should still be 0
      TS_ASSERT_EQUALS(oven.getBakingTicks(), 0);

      // test bake cycle
      for (int i = 0; i < OVEN_DEFAULT_BAKE_TIME; i++) {
        oven.tick();
      }
      // oven should have turned off
      TS_ASSERT(!oven.isRunning());
      // preheating ticks should not have changed
      TS_ASSERT_EQUALS(oven.getPreheatTicks(), 10);
      // baking ticks should be equal to the baking time specified during
      // object construction
      TS_ASSERT_EQUALS(oven.getBakingTicks(), OVEN_DEFAULT_BAKE_TIME);

      LOG4CXX_DEBUG(log, "<-- OvenTest::test_tick()");
    }

    // test for getEnergy()
    void test_get_energy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_get_energy()");

      MockScheduler sch = MockScheduler();
      Oven oven = Oven(0, &sch);

      // start oven and go through preheat cycle
      oven.action(OVEN_START);
      for (int i = 0; i < OVEN_PREHEAT_TIME; i++) {
        oven.tick();
      }
      // total energy used should be the total energy used for the entire
      // preheating cycle
      TS_ASSERT_DELTA(oven.getEnergy(), 4500000, 0.1);

      // baking cycle
      for (int i = 0; i < OVEN_DEFAULT_BAKE_TIME; i++) {
        oven.tick();
      }
      // the energy used during baking cycle should be added to the energy
      // that was already used during preheating cycle
      TS_ASSERT_DELTA(oven.getEnergy(), 9000000, 0.1);

      LOG4CXX_DEBUG(log, "<-- OvenTest::test_get_energy()");
    }

    // test for getPower()
    void test_get_power()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("OvenTest"));
      LOG4CXX_DEBUG(log, "--> OvenTest::test_get_power()");

      MockScheduler sch = MockScheduler();
      Oven oven = Oven(0, &sch);

      // when oven is off, power use should be 0.0
      TS_ASSERT_EQUALS(oven.getPower(), 0.0);
      oven.action(OVEN_START);
      // power use should be the power for preheating oven
      TS_ASSERT_EQUALS(oven.getPower(), OVEN_PREHEATING_POWER);
      for (int i = 0; i < OVEN_PREHEAT_TIME; i++) {
        oven.tick();
      }
      // power used should be the power for baking
      TS_ASSERT_EQUALS(oven.getPower(), OVEN_BAKING_POWER);

      LOG4CXX_DEBUG(log, "<-- OvenTest::test_get_power()");
    }
};

#endif /* OVENTEST_H_ */
