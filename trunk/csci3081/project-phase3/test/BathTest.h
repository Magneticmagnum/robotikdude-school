#ifndef BATHTEST_H_
#define BATHTEST_H_

#include "MockScheduler.h"
#include "House.h"
#include "Bath.h"
#include "WaterHeater.h"

#include <cxxtest/TestSuite.h>

class BathTest: public CxxTest::TestSuite
{
  public:

    void test_constructor()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("BathTest"));
      LOG4CXX_DEBUG(log, "--> BathTest::test_constructor()");

      MockScheduler* scheduler = new MockScheduler();
      Bath b = Bath(0, scheduler, 0);

      TS_ASSERT_EQUALS(b.getPower(), 0.0);
      TS_ASSERT_EQUALS(b.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(b.getCapacity(), 100.0);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- BathTest::test_constructor()");
    }

    void test_configuration()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> Entering RefrigeratorTest::test_configuration()");

      MockScheduler* scheduler = new MockScheduler();
      ConfigMap* config = Model::parseConfiguration("unittest.config", BATH,
                                                    "bath");
      Bath b = Bath(config, scheduler, 0);
      TS_ASSERT_EQUALS(b.getPower(), 0.0);
      TS_ASSERT_EQUALS(b.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(b.getCapacity(), 200.0);

      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", BATH, "fail-bath1");
      b = Bath(config, scheduler, 0);
      TS_ASSERT_EQUALS(b.getPower(), 0.0);
      TS_ASSERT_EQUALS(b.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(b.getCapacity(), 100.0);

      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", BATH, "fail-bath2");
      b = Bath(config, scheduler, 0);
      TS_ASSERT_EQUALS(b.getPower(), 0.0);
      TS_ASSERT_EQUALS(b.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(b.getCapacity(), 100.0);

      Model::deleteConfiguration(config);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- Exiting RefrigeratorTest::test_configuration()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("BathTest"));
      LOG4CXX_DEBUG(log, "--> BathTest::test_action()");

      MockScheduler* scheduler = new MockScheduler();
      Bath b = Bath(0, scheduler, 0);

      TS_ASSERT_EQUALS(b.action("start 25 42"), true);
      TS_ASSERT_EQUALS(b.action("fail"), false);
      TS_ASSERT_EQUALS(b.action("fail really bad"), false);
      TS_ASSERT_EQUALS(b.action(""), false);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_action()");
    }

    void test_tick()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("BathTest"));
      LOG4CXX_DEBUG(log, "--> BathTest::test_tick()");

      MockScheduler* scheduler = new MockScheduler();
      WaterHeater* wh = new WaterHeater(0, scheduler);
      House* house = new House(0, scheduler);
      Bath b = Bath(0, scheduler, house);

      TS_ASSERT(!b.isRunning());
      b.turnOn(25, 42);
      TS_ASSERT(b.isRunning());
      TS_ASSERT_EQUALS(b.getCurrentLevel(), 0.0);
      TS_ASSERT_EQUALS(b.getTemperature(), 42.0);
      TS_ASSERT_EQUALS(b.getTimeRunning(), 0);

      b.tick();
      TS_ASSERT(b.isRunning());
      TS_ASSERT_EQUALS(b.getCurrentLevel(), 25.0);
      TS_ASSERT_EQUALS(b.getTemperature(), 42.0);
      TS_ASSERT_EQUALS(b.getTimeRunning(), 1);

      b.turnOn(50, 45);
      b.tick();
      TS_ASSERT(b.isRunning());
      TS_ASSERT_EQUALS(b.getCurrentLevel(), 75.0);
      TS_ASSERT_EQUALS(b.getTemperature(), 45.0);
      TS_ASSERT_EQUALS(b.getTimeRunning(), 2);

      b.tick();
      TS_ASSERT(!b.isRunning());

      house->addModel("waterheater", wh);

      b.turnOn(25, 42);
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(b.isRunning());
      b.turnOn(50, 45);
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(!b.isRunning());

      b.turnOn(25, 42);
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(b.isRunning());
      b.tick();
      TS_ASSERT(!b.isRunning());

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- BathTest::test_tick()");
    }

    void test_turnOn()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("BathTest"));
      LOG4CXX_DEBUG(log, "--> BathTest::test_turnOn()");

      MockScheduler* scheduler = new MockScheduler();
      WaterHeater* wh = new WaterHeater(0, scheduler);
      House* house = new House(0, scheduler);
      house->addModel("waterheater", wh);

      Bath b = Bath(0, scheduler, house);

      b.turnOn(25, -1);
      TS_ASSERT(!b.isRunning());

      b.turnOn(-25, 42);
      TS_ASSERT(!b.isRunning());

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- BathTest::test_turnOn()");
    }
};

#endif /* BATHTEST_H_ */
