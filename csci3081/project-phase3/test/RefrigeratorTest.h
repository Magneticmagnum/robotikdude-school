#ifndef REFRIGERATORTEST_H_
#define REFRIGERATORTEST_H_

#include "Refrigerator.h"
#include "MockScheduler.h"
#include "MockRandom.h"

#include <cxxtest/TestSuite.h>

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

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.4);
      Refrigerator r = Refrigerator(0, scheduler, random);
      TS_ASSERT(!r.isRunning());

      random->seedNormal(0.6);
      r = Refrigerator(0, scheduler, random);
      TS_ASSERT(r.isRunning());

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_initialConditions()");
    }

    void test_configuration()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_configuration()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();
      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    REFRIGERATOR,
                                                    "refrigerator");

      random->seedNormal(0.6);
      random->seedNormal(0.0);
      Refrigerator r = Refrigerator(config, scheduler, random);

      // refrigerator should start on
      TS_ASSERT(r.isRunning());
      TS_ASSERT_EQUALS(r.getPower(), 200);

      r.tick(); // 1
      TS_ASSERT(r.isRunning());
      r.tick(); // 2
      TS_ASSERT(r.isRunning());
      r.tick(); // 3
      TS_ASSERT(r.isRunning());
      r.tick(); // 4
      TS_ASSERT(r.isRunning());
      r.tick(); // 5
      // refrigerator should turn off
      TS_ASSERT(!r.isRunning());
      r.tick(); // 1 (6)
      TS_ASSERT(!r.isRunning());
      r.tick(); // 2 (7)
      TS_ASSERT(!r.isRunning());
      r.tick(); // 3 (8)
      TS_ASSERT(!r.isRunning());
      r.tick(); // 4 (9)
      TS_ASSERT(!r.isRunning());
      r.tick(); // 5 (10)
      // refrigerator should turn on again
      TS_ASSERT(r.isRunning());

      r.setInUse(true);

      // should stay running as long as in use.
      for (int i = 0; i < 20; i++) {
        r.tick();
        TS_ASSERT(r.isRunning());
      }

      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", REFRIGERATOR,
                                         "fail-frige1");
      random->seedNormal(0.6);
      r = Refrigerator(config, scheduler, random);
      TS_ASSERT(r.isRunning());
      TS_ASSERT_EQUALS(r.getPower(), REFRIGERATOR_DEFAULT_POWER);
      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", REFRIGERATOR,
                                         "fail-frige2");
      random->seedNormal(0.6);
      r = Refrigerator(config, scheduler, random);
      TS_ASSERT(r.isRunning());
      TS_ASSERT_EQUALS(r.getPower(), REFRIGERATOR_DEFAULT_POWER);
      Model::deleteConfiguration(config);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_configuration()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::action()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.6);
      random->seedNormal(0.0);
      Refrigerator r = Refrigerator(0, scheduler, random);

      TS_ASSERT_EQUALS(r.action("start"), true);

      TS_ASSERT_EQUALS(r.action("stop"), true);

      TS_ASSERT_EQUALS(r.action(""), false);

      TS_ASSERT_EQUALS(r.action("start and stop"), false);

      TS_ASSERT_EQUALS(r.action("fail"), false);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::action()");
    }

    /**
     * Test that the refrigerator turns off after being on for three ticks.
     */
    void test_turningOff()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_turningOff()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.4);
      random->seedNormal(1.0);
      Refrigerator r = Refrigerator(0, scheduler, random);
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

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_turningOff()");
    }

    /**
     * Test that the refrigerator turns on after being off for nine ticks.
     */
    void test_turningOn()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_turningOn()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.4);
      random->seedNormal(1.0);
      Refrigerator r = Refrigerator(0, scheduler, random);
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

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_turningOn()");
    }

    /**
     * Test that the refrigerator uses 150 watts of power.
     */
    void test_power()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_power()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.4);
      random->seedNormal(1.0);
      Refrigerator r = Refrigerator(0, scheduler, random);
      r.tick();
      TS_ASSERT_EQUALS(r.getPower(), 150.0);

      delete (random);
      delete (scheduler);

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

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.4);
      random->seedNormal(1.0);
      Refrigerator r = Refrigerator(0, scheduler, random);
      // refrigerator should be on

      r.tick(); // tick: 1, energy: 0
      r.tick(); // tick: 2 (1), energy: 9000
      TS_ASSERT_EQUALS(r.getEnergy(), 9000.0);
      r.tick(); // tick: 3 (2), energy: 18000
      TS_ASSERT_EQUALS(r.getEnergy(), 18000.0);
      r.tick(); // tick: 4 (3), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      // refrigerator should turn off

      r.tick(); // tick: 5 (1), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      r.tick(); // tick: 6 (2), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      r.tick(); // tick: 7 (3), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      r.tick(); // tick: 8 (4), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      r.tick(); // tick: 9 (5), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      r.tick(); // tick: 10 (6), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      r.tick(); // tick: 11 (7), energy: 27000
      TS_ASSERT_EQUALS(r.getEnergy(), 27000.0);
      // refrigerator should turn on

      r.tick(); // tick: 12 (1), energy: 36000
      TS_ASSERT_EQUALS(r.getEnergy(), 36000.0);
      r.tick(); // tick: 13 (2), energy: 45000
      TS_ASSERT_EQUALS(r.getEnergy(), 45000.0);
      r.tick(); // tick: 14 (3), energy: 54000
      TS_ASSERT_EQUALS(r.getEnergy(), 54000.0);
      // refrigerator should turn off

      r.tick(); // tick: 15 (1), energy: 54000
      TS_ASSERT_EQUALS(r.getEnergy(), 54000.0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_energy()");
    }

    void test_inUse()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_inUse()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      random->seedNormal(0.4);
      random->seedNormal(1.0);
      Refrigerator r = Refrigerator(0, scheduler, random);
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

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_inUse()");
    }

};

#endif /* REFRIGERATORTEST_H_ */
