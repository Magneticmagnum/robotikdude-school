#ifndef DISHWASHERTEST_H_
#define DISHWASHERTEST_H_

#include "Model.h"
#include "Scheduler.h"
#include "MockScheduler.h"
#include "ModelFactory.h"
#include "Dishwasher.h"
#include "WaterHeater.h"
#include "House.h"

#include <string>
#include <fstream>

#include <cxxtest/TestSuite.h>

class DishwasherTest: public CxxTest::TestSuite
{
  public:

    /*
     * Test the dishwasher's default constructor method
     */
    void test_default_constructor()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_constructor()");

      Scheduler* scheduler = new MockScheduler();
      ModelFactory* modelFactory = new ModelFactory(scheduler);
      House* house = new House(0, scheduler);

      WaterHeater* waterheater = new WaterHeater(0, scheduler);

      Dishwasher* testDishwasher = new Dishwasher();

      scheduler->registerModel(house);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);
      house->addModel("waterheater", waterheater);
      house->addModel("dishwasher", testDishwasher);

      TS_ASSERT_EQUALS(testDishwasher->isRunning(), false);
      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher->getPower(), 4.0)
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 0.0);

      LOG4CXX_DEBUG(log, "<-- DishwasherTest::test_constructor()");
    }

    // Test the constructor that takes a pointer to a scheduler and
    // a configuration map.  Make sure that the dishwasher is created
    // with the correct settings, even though the passed values are improper
    // (so the defaults should be used.)
    void test_configConstructorBad()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_configConstructorBad()");

      Scheduler* scheduler = new MockScheduler();
      ModelFactory* modelFactory = new ModelFactory(scheduler);
      House* testHouse = modelFactory->createHouse("testHouse",
                                                   "unittest.config");
      WaterHeater* waterheater =
          modelFactory->createWaterHeater("waterheater", "unittest.config",
                                          testHouse);

      //      ConfigMap* config = new ConfigMap();
      //      (*config)["on-power"] = "-4000.0";
      //      (*config)["off-power"] = "5000.0";
      //      (*config)["run-time"] = "-10.0";
      //      (*config)["water-time"] = "300.0";
      //      (*config)["water-temp"] = "-10.0";
      //      (*config)["water-volume"] = "-10.0";
      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    DISHWASHER, "fail-washer1");
      Dishwasher* testDishwasher = new Dishwasher(config, scheduler, testHouse);
      Model::deleteConfiguration(config);

      scheduler->registerModel(testHouse);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);

      testHouse->addModel("waterheater", waterheater);
      testHouse->addModel("dishwasher", testDishwasher);

      TS_ASSERT(!testDishwasher->isRunning());
      TS_ASSERT_EQUALS(testDishwasher->getPower(), 4.0);
      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 0.0);

      testDishwasher->turnOn();
      testDishwasher->tick();

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 2000.0);
      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 120000.0);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 44.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 19.0);

      int tickCount = 1;
      while (testDishwasher->isRunning()) {
        testHouse->tick();
        tickCount++;
      }

      TS_ASSERT(!testDishwasher->isRunning());
      TS_ASSERT_EQUALS(tickCount, 45);

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 4.0);

      testDishwasher->turnOn();

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 2000.0);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 45.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 20.0);

      LOG4CXX_DEBUG(log, "<-- DishwasherTest::test_configConstructorBad()");
    }

    // Test the constructor that takes a pointer to a scheduler and
    // a configuration map.  Make sure that the dishwasher is created
    // with the correct settings.
    void test_configConstructorGood()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_configConstructorGood()");

      Scheduler* scheduler = new MockScheduler();
      ModelFactory* modelFactory = new ModelFactory(scheduler);
      House* testHouse = modelFactory->createHouse("testHouse",
                                                   "unittest.config");
      WaterHeater* waterheater =
          modelFactory->createWaterHeater("waterheater", "unittest.config",
                                          testHouse);

      //      ConfigMap* config = new ConfigMap();
      //      (*config)["on-power"] = "5000.0";
      //      (*config)["off-power"] = "5.0";
      //      (*config)["run-time"] = "50.0";
      //      (*config)["water-time"] = "20.0";
      //      (*config)["water-temp"] = "45.0";
      //      (*config)["water-volume"] = "20.0";
      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    DISHWASHER, "dishwasher");
      Dishwasher* testDishwasher = new Dishwasher(config, scheduler, testHouse);
      Model::deleteConfiguration(config);

      scheduler->registerModel(testHouse);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);

      testHouse->addModel("waterheater", waterheater);
      testHouse->addModel("dishwasher", testDishwasher);

      TS_ASSERT(!testDishwasher->isRunning());
      TS_ASSERT_EQUALS(testDishwasher->getPower(), 5.0);
      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 0.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 0.0);

      testDishwasher->turnOn();
      testDishwasher->tick();

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 5000.0);
      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 300000.0);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 49.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 19.0);

      int tickCount = 1;
      while (testDishwasher->isRunning()) {
        testHouse->tick();
        tickCount++;
      }

      TS_ASSERT(!testDishwasher->isRunning());
      TS_ASSERT_EQUALS(tickCount, 50);

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 5.0);

      testDishwasher->turnOn();

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 5000.0);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 50.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 20.0);

      LOG4CXX_DEBUG(log, "<-- DishwasherTest::test_configConstructorGood()");
    }

    /**
     * Test what happens when the dishwasher is turned
     * on:  the instantaneous power usage goes up to 2000,
     * the dishwasher reports that it is on (not off), etc.
     */
    void test_turnOn()
    {

      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_turnOn()");

      Scheduler* scheduler = new MockScheduler();
      House* house = new House(0, scheduler);
      WaterHeater* waterheater = new WaterHeater(0, scheduler);
      Dishwasher* testDishwasher = new Dishwasher(0, scheduler, house);

      scheduler->registerModel(house);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);
      TS_ASSERT(house->addModel("waterheater", waterheater));
      house->addModel("dishwasher", testDishwasher);

      double i;

      TS_ASSERT(!testDishwasher->isRunning())
      testDishwasher->turnOn();

      TS_ASSERT_EQUALS(testDishwasher->isRunning(), true);
      TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), 45.0);
      TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 20.0);

      for (i = 45.0; i > 25.0; i--) {
        TS_ASSERT_EQUALS(testDishwasher->isRunning(), true);
        TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), i);
        TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), i - 25.0);
        testDishwasher->tick();
      }

      for (i; i > 0; i--) {
        TS_ASSERT_EQUALS(testDishwasher->isRunning(), true);
        TS_ASSERT_EQUALS(testDishwasher->getRunningTimeLeft(), i);
        TS_ASSERT_EQUALS(testDishwasher->getWaterTimeLeft(), 0.0);
        testDishwasher->tick();
      }

      TS_ASSERT_EQUALS(testDishwasher->isRunning(), false);
      LOG4CXX_DEBUG(log, "<-- DishwasherTest::test_turnOn()");
    }

    /*
     * Test whether the dishwasher correctly tracks it's energy usage.
     */
    void test_getEnergy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_getEnergy()");

      Scheduler* scheduler = new MockScheduler();
      House* house = new House(0, scheduler);
      WaterHeater* waterheater = new WaterHeater(0, scheduler);
      Dishwasher* testDishwasher = new Dishwasher(0, scheduler, house);

      scheduler->registerModel(house);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);
      TS_ASSERT(house->addModel("waterheater", waterheater));
      house->addModel("dishwasher", testDishwasher);

      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 0.0);

      testDishwasher->tick();

      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 4.0 * 60.0);

      testDishwasher->turnOn();
      testDishwasher->tick();

      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 4.0 * 60.0 + 2000.0 * 60);

      testDishwasher->tick();

      TS_ASSERT_EQUALS(testDishwasher->getEnergy(), 4.0 * 60.0 + 2000.0 * 60 * 2.0);
      LOG4CXX_DEBUG(log, "<-- DishwasherTest::test_getEnergy()");
    }

    /*
     * Test of the getPower() function
     */
    void test_getPower()
    {

      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_getPower()");

      Scheduler* scheduler = new MockScheduler();
      House* house = new House(0, scheduler);
      WaterHeater* waterheater = new WaterHeater(0, scheduler);
      Dishwasher* testDishwasher = new Dishwasher(0, scheduler, house);

      scheduler->registerModel(house);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);
      TS_ASSERT(house->addModel("waterheater", waterheater));
      house->addModel("dishwasher", testDishwasher);

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 4.0);

      testDishwasher->turnOn();
      testDishwasher->tick();

      TS_ASSERT_EQUALS(testDishwasher->getPower(), 2000.0);
      LOG4CXX_DEBUG(log, "<-- DishwasherTest::test_getPower()");
    }

    /*
     * Test the dishwasher's action method.
     */
    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("DishwasherTest"));
      LOG4CXX_DEBUG(log, "--> DishwasherTest::test_getPower()");

      Scheduler* scheduler = new MockScheduler();
      House* house = new House(0, scheduler);
      WaterHeater* waterheater = new WaterHeater(0, scheduler);
      Dishwasher* testDishwasher = new Dishwasher(0, scheduler, house);

      scheduler->registerModel(house);
      scheduler->registerModel(waterheater);
      scheduler->registerModel(testDishwasher);
      TS_ASSERT(house->addModel("waterheater", waterheater));
      house->addModel("dishwasher", testDishwasher);

      testDishwasher->action("start");

      TS_ASSERT(testDishwasher->isRunning());

      TS_ASSERT(!testDishwasher->action(""));
      TS_ASSERT(!testDishwasher->action("fail"));
      TS_ASSERT(!testDishwasher->action("fail twice"));

      TS_ASSERT(!testDishwasher->action("start"));
    }

};

#endif /* DISHWASHERTEST_H_ */
