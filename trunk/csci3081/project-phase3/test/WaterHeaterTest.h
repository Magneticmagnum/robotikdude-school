#ifndef WATERHEATERTEST_H_
#define WATERHEATERTEST_H_

#include "WaterHeater.h"
#include "MockScheduler.h"

#include <cxxtest/TestSuite.h>

class WaterHeaterTest: public CxxTest::TestSuite
{
  public:
    void test_constructor()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_constructors()");

      MockScheduler* scheduler = new MockScheduler();

      WaterHeater wh1 = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh1.getWaterTemperature(), 50);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- WaterHeaterTest::test_constructors()");
    }

    void test_configuration()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_configuration()");

      MockScheduler* scheduler = new MockScheduler();
      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    WATERHEATER, "waterheater");

      WaterHeater wh = WaterHeater(config, scheduler);
      TS_ASSERT(!wh.isRunning());
      TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      for (int i = 0; i < 300; i++) {
        wh.tick();
        TS_ASSERT(!wh.isRunning());
        TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      }
      for (int i = 0; i < 31; i++) {
        wh.tick();
        TS_ASSERT(wh.isRunning());
        TS_ASSERT_EQUALS(wh.getPower(), 6000.0);
      }
      wh.tick();
      TS_ASSERT(!wh.isRunning());
      TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", WATERHEATER,
                                         "fail-heater1");
      wh = WaterHeater(config, scheduler);
      TS_ASSERT(!wh.isRunning());
      TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      for (int i = 0; i < 345; i++) {
        wh.tick();
        TS_ASSERT(!wh.isRunning());
        TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      }
      for (int i = 0; i < 5; i++) {
        wh.tick();
        TS_ASSERT(wh.isRunning());
        TS_ASSERT_EQUALS(wh.getPower(), 4500.0);
      }
      wh.tick();
      TS_ASSERT(!wh.isRunning());
      TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      Model::deleteConfiguration(config);

      config = Model::parseConfiguration("unittest.config", WATERHEATER,
                                         "fail-heater2");
      wh = WaterHeater(config, scheduler);
      TS_ASSERT(!wh.isRunning());
      TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      for (int i = 0; i < 345; i++) {
        wh.tick();
        TS_ASSERT(!wh.isRunning());
        TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      }
      for (int i = 0; i < 5; i++) {
        wh.tick();
        TS_ASSERT(wh.isRunning());
        TS_ASSERT_EQUALS(wh.getPower(), 4500.0);
      }
      wh.tick();
      TS_ASSERT(!wh.isRunning());
      TS_ASSERT_EQUALS(wh.getPower(), 0.0);
      Model::deleteConfiguration(config);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- RefrigeratorTest::test_configuration()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("RefrigeratorTest"));
      LOG4CXX_DEBUG(log, "--> RefrigeratorTest::action()");

      MockScheduler* scheduler = new MockScheduler();
      WaterHeater wh = WaterHeater(0, scheduler);

      TS_ASSERT_EQUALS(wh.action("start"), true);
      TS_ASSERT_EQUALS(wh.action("stop blah blah blah kajsd;lkfja;slkdjfl;"), true);
      TS_ASSERT_EQUALS(wh.action(""), true);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- RefrigeratorTest::action()");
    }

    void test_getPower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_getPower()");

      MockScheduler* scheduler = new MockScheduler();

      WaterHeater wh = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh.getPower(), 0);
      for (int i = 0; i < 346; i++) {
        wh.tick();
      }
      TS_ASSERT_EQUALS(wh.getPower(), 4500);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- WaterHeaterTest::test_getPower()");
    }

    void test_getEnergy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_getEnergy()");

      MockScheduler* scheduler = new MockScheduler();

      WaterHeater wh = WaterHeater(0, scheduler);
      // double waterHeat = WATERHEATER_TEMP_OFF;
      TS_ASSERT_EQUALS(wh.getEnergy(), 0);
      for (int i = 0; i < 345; i++) {
        wh.tick();
        // waterHeat -= WATERHEATER_HEAT_LOSS;
        TS_ASSERT_EQUALS(wh.getEnergy(), 0);
      }
      wh.tick();
      TS_ASSERT_DELTA(wh.getEnergy(), 270000.0, 0.1);
      wh.tick();
      TS_ASSERT_DELTA(wh.getEnergy(), 540000.0, 0.1);
      wh.tick();
      TS_ASSERT_DELTA(wh.getEnergy(), 810000.0, 0.1);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- WaterHeaterTest::test_getEnergy()");
    }

    void test_getWater()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_getWater()");

      MockScheduler* scheduler = new MockScheduler();

      WaterHeater wh = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh.getWater(100.0, 40.0), 40.0);

      wh = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh.getWater(100.0, 50.0), 50.0);

      wh = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh.getWater(100.0, 60.0), 50.0);

      wh = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh.getWater(200.0, 50.0), 50.0);

      wh = WaterHeater(0, scheduler);
      TS_ASSERT_EQUALS(wh.getWater(300.0, 50.0), (200.0 * 50.0 + 100.0 * 7.0) / 300.0);

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- WaterHeaterTest::test_getWater()");
    }

    void test_getWaterTemperature()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_getWaterTemperature()");

      MockScheduler* scheduler = new MockScheduler();

      WaterHeater wh = WaterHeater(0, scheduler);
      double waterTemp = WATERHEATER_DEFAULT_TEMP_OFF;
      TS_ASSERT_EQUALS(wh.getEnergy(), 0);
      for (int i = 0; i < 345; i++) {
        wh.tick();
        waterTemp -= WATERHEATER_DEFAULT_HEAT_LOSS;
        TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      }
      wh.tick();
      waterTemp += WATERHEATER_DEFAULT_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_DEFAULT_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_DEFAULT_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_DEFAULT_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_DEFAULT_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      for (int i = 0; i < 100; i++) {
        wh.tick();
        waterTemp -= WATERHEATER_DEFAULT_HEAT_LOSS;
        TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      }

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- WaterHeaterTest::test_getWaterTemperature()");
    }

    void test_isRunning()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> WaterHeaterTest::test_isRunning()");

      MockScheduler* scheduler = new MockScheduler();

      WaterHeater wh = WaterHeater(0, scheduler);
      TS_ASSERT(!wh.isRunning());
      for (int i = 0; i < 345; i++) {
        wh.tick();
        TS_ASSERT(!wh.isRunning());
      }
      wh.tick();
      TS_ASSERT(wh.isRunning());
      wh.tick();
      TS_ASSERT(wh.isRunning());
      wh.tick();
      TS_ASSERT(wh.isRunning());
      wh.tick();
      TS_ASSERT(wh.isRunning());
      wh.tick();
      TS_ASSERT(wh.isRunning());
      for (int i = 0; i < 100; i++) {
        wh.tick();
        TS_ASSERT(!wh.isRunning());
      }

      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- WaterHeaterTest::test_isRunning()");
    }

};

#endif /* WATERHEATERTEST_H_ */
