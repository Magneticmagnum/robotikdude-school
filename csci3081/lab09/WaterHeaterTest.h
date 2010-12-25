#ifndef WATERHEATERTEST_H_
#define WATERHEATERTEST_H_

#include "WaterHeater.h"

#include <cxxtest/TestSuite.h>

class WaterHeaterTest: public CxxTest::TestSuite
{
  public:
    void test_constructors()
    {
      WaterHeater wh1 = WaterHeater();
      TS_ASSERT_EQUALS(wh1.getWaterTemperature(), 50);

      WaterHeater wh2 = WaterHeater(7.0);
      TS_ASSERT_EQUALS(wh2.getWaterTemperature(), 7.0);
    }

    void test_getPower()
    {
      WaterHeater wh = WaterHeater();
      // not running...
      // TS_ASSERT_EQUALS(wh.getPower(), 3000);
    }

    void test_getEnergy()
    {
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
    }

    void test_getWater()
    {
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
    }

    void test_getWaterTemperature()
    {
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
    }

    void test_isRunning()
    {
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
    }

    void test_subtractEquals()
    {
      WaterHeater wh = WaterHeater();
      wh -= 100;
      TS_ASSERT_EQUALS(wh.getWaterTemperature(), (100 * 50 + 100 * 7) / 200.0)
    }

};

#endif /* WATERHEATERTEST_H_ */
