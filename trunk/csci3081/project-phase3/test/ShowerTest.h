#ifndef SHOWERTEST_H_
#define SHOWERTEST_H_

#include "MockScheduler.h"
#include "House.h"
#include "Shower.h"
#include "WaterHeater.h"

#include <cxxtest/TestSuite.h>

class ShowerTest: public CxxTest::TestSuite
{
  public:

    void test_constructor()
    {
      log4cxx::LoggerPtr
          log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_constructor()");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, 0);
      house.addModel("waterheater", &wh);
      Shower test = Shower(0, &scheduler, &house);

      TS_ASSERT(&scheduler == test.getScheduler());
      TS_ASSERT(test.getHouse() == &house);

      // default values should have been loaded

      // shower should not be initially running
      TS_ASSERT_EQUALS(false, test.isRunning());
      TS_ASSERT_EQUALS(0.0, test.getDraw());
      TS_ASSERT_EQUALS(0.0, test.getTemp());
      TS_ASSERT_EQUALS(0.0, test.getTotalWater());

      TS_ASSERT(test.getWHName().compare("waterheater") == 0);
      TS_ASSERT(test.getWHModel() == &wh);

      ConfigMap* cm = new ConfigMap();

      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_constructor()");
    }

    void test_config()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_config()");

      ConfigMap* config = Model::parseConfiguration("unittest.config", SHOWER, "shower");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, 0);
      house.addModel("wh", &wh);
      Shower shower = Shower(config, &scheduler, &house);

      TS_ASSERT(shower.getWHName().compare("wh") == 0);

      ConfigMap* config2 = Model::parseConfiguration("unittest.config", SHOWER, "fail-shower");
      Shower shower2 = Shower(config2, &scheduler, &house);

      TS_ASSERT(shower2.getWHName().compare("waterheater") == 0);

      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_config()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr
          log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_action()");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, 0);
      house.addModel("waterheater", &wh);
      Shower shower = Shower(0, &scheduler, &house);

      TS_ASSERT(!shower.isRunning());
      bool noError = shower.action("start 7.0 18.0");
      TS_ASSERT(noError);
      TS_ASSERT(shower.isRunning());
      TS_ASSERT_EQUALS(shower.getDraw(), 7.0);
      TS_ASSERT_EQUALS(shower.getTemp(), 18.0);

      noError = shower.action("stop");
      TS_ASSERT(noError);
      TS_ASSERT(!shower.isRunning());
      TS_ASSERT_EQUALS(shower.getDraw(), 0.0);
      TS_ASSERT_EQUALS(shower.getTemp(), 0.0);

      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_action()");
    }

    void test_bad_action()
    {
      log4cxx::LoggerPtr
          log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_bad_action()");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, 0);
      house.addModel("waterheater", &wh);
      Shower shower = Shower(0, &scheduler, &house);

      TS_ASSERT(!shower.isRunning());
      bool noError = shower.action("stop");
      TS_ASSERT(!noError);
      TS_ASSERT(!shower.isRunning());

      noError = shower.action("stop 9.0");
      TS_ASSERT(!noError);
      TS_ASSERT(!shower.isRunning());

      noError = shower.action("start 9.0");
      TS_ASSERT(!noError);
      TS_ASSERT(!shower.isRunning());

      shower.action("start 9.0 70.0");

      noError = shower.action("start 8.0 12.0");
      TS_ASSERT(!noError);
      TS_ASSERT(shower.isRunning());
      TS_ASSERT_EQUALS(shower.getDraw(), 9.0);
      TS_ASSERT_EQUALS(shower.getTemp(), 70.0);

      noError = shower.action("blarm");
      TS_ASSERT(!noError);

      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_bad_action()");
    }

    void test_tick()
    {
      log4cxx::LoggerPtr
          log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_tick()");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, 0);
      house.addModel("waterheater", &wh);
      Shower shower = Shower(0, &scheduler, &house);

      shower.tick();
      TS_ASSERT_EQUALS(0.0, shower.getTotalWater());

      shower.action("start 10.0 70.0");
      shower.tick();
      TS_ASSERT_EQUALS(10.0, shower.getTotalWater());
      for (int i = 0; i < 10; i++) {
        shower.tick();
      }
      TS_ASSERT_EQUALS(110.0, shower.getTotalWater());

      shower.action("stop");
      for (int i = 0; i < 100; i++) {
        shower.tick();
      }
      TS_ASSERT_EQUALS(110.0, shower.getTotalWater());

      house.removeModel("waterheater");
      shower.tick();
      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_tick()");
    }

    void test_getEnergy()
    {
      log4cxx::LoggerPtr
          log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_getEnergy()");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, &scheduler);
      house.addModel("waterheater", &wh);
      Shower shower = Shower(0, &scheduler, &house);

      TS_ASSERT_EQUALS(0.0, shower.getEnergy());
      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_getEnerg()");
    }

    void test_getPower()
    {
      log4cxx::LoggerPtr
          log(log4cxx::Logger::getLogger("ShowerTest"));
      LOG4CXX_DEBUG(log, "--> ShowerTest::test_getPower()");

      MockScheduler scheduler = MockScheduler();
      WaterHeater wh = WaterHeater(0, &scheduler);
      House house = House(0, &scheduler);
      house.addModel("waterheater", &wh);
      Shower shower = Shower(0, &scheduler, &house);

      TS_ASSERT_EQUALS(0.0, shower.getPower());
      LOG4CXX_DEBUG(log, "<-- ShowerTest::test_getPower()");
    }


};

#endif /* SHOWERTEST_H_ */
