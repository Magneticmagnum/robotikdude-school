#ifndef WATERHEATERTEST_H_
#define WATERHEATERTEST_H_

#include "WaterHeater.h"

#include <cxxtest/TestSuite.h>

class WaterHeaterTest: public CxxTest::TestSuite
{
  public:
    void test_constructors()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> Entering WaterHeaterTest::test_constructors()");

      WaterHeater wh1 = WaterHeater();
      TS_ASSERT_EQUALS(wh1.getWaterTemperature(), 50);

      WaterHeater wh2 = WaterHeater(7.0);
      TS_ASSERT_EQUALS(wh2.getWaterTemperature(), 7.0);

      LOG4CXX_DEBUG(log, "<-- Exiting WaterHeaterTest::test_constructors()");
    }

    void test_getPower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> Entering WaterHeaterTest::test_getPower()");

      WaterHeater wh = WaterHeater();
      TS_ASSERT_EQUALS(wh.getPower(), 3000);

      LOG4CXX_DEBUG(log, "<-- Exiting WaterHeaterTest::test_getPower()");
    }

    void test_getEnergy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> Entering WaterHeaterTest::test_getEnergy()");

      WaterHeater wh = WaterHeater();
      // double waterHeat = WATERHEATER_TEMP_OFF;
      TS_ASSERT_EQUALS(wh.getEnergy(), 0);
      for (int i = 0; i < 345; i++) {
        wh.tick();
        // waterHeat -= WATERHEATER_HEAT_LOSS;
        TS_ASSERT_EQUALS(wh.getEnergy(), 0);
      }
      wh.tick();
      TS_ASSERT_EQUALS(wh.getEnergy(), 3000.0);
      wh.tick();
      TS_ASSERT_EQUALS(wh.getEnergy(), 6000.0);
      wh.tick();
      TS_ASSERT_EQUALS(wh.getEnergy(), 9000.0);

      LOG4CXX_DEBUG(log, "<-- Exiting WaterHeaterTest::test_getEnergy()");
    }

    void test_getWater()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> Entering WaterHeaterTest::test_getWater()");

      WaterHeater wh = WaterHeater();
      TS_ASSERT_EQUALS(wh.getWater(100.0, 40.0), 40.0);

      wh = WaterHeater();
      TS_ASSERT_EQUALS(wh.getWater(100.0, 50.0), 50.0);

      wh = WaterHeater();
      TS_ASSERT_EQUALS(wh.getWater(100.0, 60.0), 50.0);

      wh = WaterHeater();
      TS_ASSERT_EQUALS(wh.getWater(200.0, 50.0), 50.0);

      wh = WaterHeater();
      TS_ASSERT_EQUALS(wh.getWater(300.0, 50.0), (200.0 * 50.0 + 100.0 * 7.0) / 300.0);

      LOG4CXX_DEBUG(log, "<-- Exiting WaterHeaterTest::test_getWater()");
    }

    void test_getWaterTemperature()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> Entering WaterHeaterTest::test_getWaterTemperature()");

      WaterHeater wh = WaterHeater();
      double waterTemp = WATERHEATER_TEMP_OFF;
      TS_ASSERT_EQUALS(wh.getEnergy(), 0);
      for (int i = 0; i < 345; i++) {
        wh.tick();
        waterTemp -= WATERHEATER_HEAT_LOSS;
        TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      }
      wh.tick();
      waterTemp += WATERHEATER_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      wh.tick();
      waterTemp += WATERHEATER_HEAT_GAIN;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      for (int i = 0; i < 100; i++) {
        wh.tick();
        waterTemp -= WATERHEATER_HEAT_LOSS;
        TS_ASSERT_EQUALS(wh.getWaterTemperature(), waterTemp);
      }

      LOG4CXX_DEBUG(log, "<-- Exiting WaterHeaterTest::test_getWaterTemperature()");
    }

    void test_isRunning()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("WaterHeaterTest"));
      LOG4CXX_DEBUG(log, "--> Entering WaterHeaterTest::test_isRunning()");

      WaterHeater wh = WaterHeater();
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

      LOG4CXX_DEBUG(log, "<-- Exiting WaterHeaterTest::test_isRunning()");
    }

};

#endif /* WATERHEATERTEST_H_ */
