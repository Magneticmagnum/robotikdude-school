#ifndef MICROWAVETEST_H_
#define MICROWAVETEST_H_

#include "Microwave.h"
#include "MockScheduler.h"
#include "MockRandom.h"

#include <cxxtest/TestSuite.h>

class MicrowaveTest: public CxxTest::TestSuite
{
  public:
    void test_initialConditions()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> MicrowaveTest::test_initialConditions()");

      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      Microwave m = Microwave(0, scheduler, 0, random);
      TS_ASSERT(!m.isRunning());

      delete (scheduler);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- MicrowaveTest::test_initialConditions()");
    }

    void test_configuration()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> RefrigeratorTest::test_configuration()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();
      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    MICROWAVE, "microwave");
      Microwave m = Microwave(config, scheduler, 0, random);
      random->seedNormal(0.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1000.0);
      m.tick();
      m.tick();
      TS_ASSERT_EQUALS(m.getEnergy(), 30000.0);
      random->seedNormal(1.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1000.0);
      m.tick();
      m.tick();
      m.tick();
      m.tick();
      TS_ASSERT_EQUALS(m.getEnergy(), 210000.0);
      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", MICROWAVE,
                                         "fail-wave1");
      m = Microwave(config, scheduler, 0, random);
      random->seedNormal(0.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1500.0);
      m.tick();
      m.tick();
      TS_ASSERT_EQUALS(m.getEnergy(), 60000.0);
      random->seedNormal(1.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1500.0);
      m.tick();
      m.tick();
      m.tick();
      m.tick();
      TS_ASSERT_EQUALS(m.getEnergy(), 240000.0);
      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", MICROWAVE,
                                         "fail-wave2");
      m = Microwave(config, scheduler, 0, random);
      random->seedNormal(0.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1500.0);
      m.tick();
      m.tick();
      TS_ASSERT_EQUALS(m.getEnergy(), 60000.0);
      random->seedNormal(1.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1500.0);
      m.tick();
      m.tick();
      m.tick();
      m.tick();
      TS_ASSERT_EQUALS(m.getEnergy(), 240000.0);
      Model::deleteConfiguration(config);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- RefrigeratorTest::test_configuration()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> RefrigeratorTest::action()");

      MockRandom* random = new MockRandom();
      MockScheduler* scheduler = new MockScheduler();

      Microwave m = Microwave(0, scheduler, 0, random);

      random->seedNormal(0.6);
      random->seedNormal(0.0);

      TS_ASSERT_EQUALS(m.action("start"), true);

      TS_ASSERT_EQUALS(m.action(""), false);

      TS_ASSERT_EQUALS(m.action("start and stop"), false);

      TS_ASSERT_EQUALS(m.action("fail"), false);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- RefrigeratorTest::action()");
    }

    void test_getPower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> MicrowaveTest::test_getPower()");

      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      Microwave m = Microwave(0, scheduler, 0, random);
      TS_ASSERT_EQUALS(m.getPower(), 0.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1500.0);

      delete (scheduler);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- MicrowaveTest::test_getPower()");
    }

    void test_getEnergy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> MicrowaveTest::test_getEnergy()");

      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      Microwave m = Microwave(0, scheduler, 0, random);

      random->seedNormal(0.2);
      m.turnOn();
      TS_ASSERT_DELTA(m.getEnergy(), 0.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 84000.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 84000.0, 0.01);

      random->seedNormal(0.8);
      m.turnOn();
      TS_ASSERT_DELTA(m.getEnergy(), 84000.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 174000.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 240000.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 240000.0, 0.01);

      delete (scheduler);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- MicrowaveTest::test_getEnergy()");
    }

    void test_turnOn()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> MicrowaveTest::test_turnOn()");

      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      Microwave m = Microwave(0, scheduler, 0, random);
      TS_ASSERT(!m.isRunning());
      random->seedNormal(0.2);
      m.turnOn();
      TS_ASSERT(m.isRunning());
      random->seedNormal(0.2);
      m.turnOn();
      TS_ASSERT(m.isRunning());

      delete (scheduler);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- MicrowaveTest::test_turnOn()");
    }

    void test_isRunning()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> MicrowaveTest::test_isRunning()");

      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      Microwave m = Microwave(0, scheduler, 0, random);
      TS_ASSERT(!m.isRunning());
      random->seedNormal(0.2);
      m.turnOn();
      TS_ASSERT(m.isRunning());

      delete (scheduler);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- SMicrowaveTest::test_isRunning()");
    }
};

#endif /* MICROWAVETEST_H_ */
