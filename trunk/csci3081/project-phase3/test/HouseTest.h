#ifndef HOUSETEST_H_
#define HOUSETEST_H_

#include "House.h"
#include "Scheduler.h"
#include "MockScheduler.h"
#include "ModelFactory.h"
#include "Toaster.h"
#include "Stove.h"
#include "Oven.h"
#include "WaterHeater.h"
#include "Dishwasher.h"

#include <string>
#include <fstream>

#include <cxxtest/TestSuite.h>

class HouseTest: public CxxTest::TestSuite
{
  public:

  /*
   * Tests that the house's constructor method works correctly.
   */
  void test_constructor()
  {
    log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("HouseTest"));
    LOG4CXX_DEBUG(log, "--> HouseTest::test_constructor()");

    Scheduler* scheduler = new MockScheduler();
    ModelFactory* modelFactory = new ModelFactory(scheduler);
    House* testHouse = modelFactory->createHouse(HOUSE, "unittest.config");
    Stove* stove = modelFactory->createStove(STOVE, "unittest.config", testHouse);
    Oven* oven = modelFactory->createOven(OVEN, "unittest.config", testHouse);

    ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                  HOUSE,
                                                  "house");


    scheduler->registerModel(testHouse);
    scheduler->registerModel(stove);
    scheduler->registerModel(oven);

    TS_ASSERT_EQUALS(testHouse->getPower(), 0.0);
    TS_ASSERT_EQUALS(testHouse->getEnergy(), 0.0);

    TS_ASSERT(!testHouse->getModel("stove"));

    LOG4CXX_DEBUG(log, "<-- HouseTest::test_constructor()");
  }

  /*
   * Make sure that it is possible to add and remove models from
   * the house object.  A house should maintain a list of the appliances
   * it contains; this list should be manipulable.
   */
  void test_addRemoveModels()
  {
    log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("HouseTest"));
    LOG4CXX_DEBUG(log, "--> HouseTest::test_addRemoveModels()");

    Scheduler* scheduler = new MockScheduler();
    ModelFactory* modelFactory = new ModelFactory(scheduler);
    House* testHouse = modelFactory->createHouse(HOUSE, "unittest.config");
    Stove* stove = modelFactory->createStove(STOVE, "unittest.config", testHouse);
    Oven* oven = modelFactory->createOven(OVEN, "unittest.config", testHouse);

    ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                  HOUSE,
                                                  "house");


    scheduler->registerModel(testHouse);
    scheduler->registerModel(stove);
    scheduler->registerModel(oven);

    TS_ASSERT(!testHouse->getModel("stove"));

    testHouse->addModel("stove", stove);
    testHouse->addModel("oven", oven);

    TS_ASSERT(testHouse->getModel("stove"));
    TS_ASSERT(testHouse->getModel("oven"));

    TS_ASSERT(!testHouse->addModel("stove", stove));
    TS_ASSERT(!testHouse->addModel("oven", oven));

    testHouse->removeModel("stove");
    testHouse->removeModel("oven");

    TS_ASSERT(!testHouse->getModel("stove"));
    TS_ASSERT(!testHouse->getModel("oven"));

    TS_ASSERT(!testHouse->removeModel("stove"));

    LOG4CXX_DEBUG(log, "<-- HouseTest::test_addRemoveModels()");
  }

  /*
   * Test that the houses getPower() and getEnergy() functions
   * properly aggregate the power and energy use of the appliances
   * it contains.
   */
  void test_getPowerAndEnergy()
  {
    log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("HouseTest"));
    LOG4CXX_DEBUG(log, "--> HouseTest::test_getPowerAndEnergy()");

    Scheduler* scheduler = new MockScheduler();
    ModelFactory* modelFactory = new ModelFactory(scheduler);
    House* testHouse = modelFactory->createHouse(HOUSE, "unittest.config");
    Stove* stove = modelFactory->createStove(STOVE, "unittest.config", testHouse);
    //Toaster* toaster = modelFactory->createToaster(TOASTER, "unittest.config", testHouse);

    ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                  HOUSE,
                                                  "house");


    scheduler->registerModel(testHouse);
    scheduler->registerModel(stove);
   // scheduler->registerModel(toaster);

    TS_ASSERT(!testHouse->getModel("stove"));

    testHouse->addModel("stove", stove);
    //testHouse->addModel("oven", oven);

    TS_ASSERT_EQUALS(testHouse->getPower(), 0.0);
    TS_ASSERT_EQUALS(testHouse->getEnergy(), 0.0);

    stove->turnOnBurner(1,1);
    //toaster->turnOn();

    TS_ASSERT_EQUALS(testHouse->getPower(), 350.0);
    TS_ASSERT_EQUALS(testHouse->getEnergy(), 0.0);

    testHouse->tick();

    TS_ASSERT_EQUALS(testHouse->getPower(), 0.0);
    TS_ASSERT_DELTA(testHouse->getEnergy(), 21000.0, 0.1);

    LOG4CXX_DEBUG(log, "<-- HouseTest::test_getPowerAndEnergy()");
  }

  /*
     * The isRunning() function in House should return true if
     * any appliance in the house is currently running.  This
     * function checks that this is true.
     */
    void test_isRunning()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("HouseTest"));
      LOG4CXX_DEBUG(log, "--> HouseTest::test_isRunning()");

      Scheduler* scheduler = new MockScheduler();
      ModelFactory* modelFactory = new ModelFactory(scheduler);
      House* testHouse = modelFactory->createHouse(HOUSE, "unittest.config");
      Stove* stove = modelFactory->createStove(STOVE, "unittest.config", testHouse);
      Oven* oven = modelFactory->createOven(OVEN, "unittest.config", testHouse);

      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    HOUSE,
                                                    "house");


      scheduler->registerModel(testHouse);
      scheduler->registerModel(stove);
      scheduler->registerModel(oven);

      TS_ASSERT(!testHouse->getModel("stove"));

      testHouse->addModel("stove", stove);
      testHouse->addModel("oven", oven);

      TS_ASSERT(!testHouse->isRunning());

      stove->turnOnBurner(1,1);

      TS_ASSERT(testHouse->isRunning());

      testHouse->tick();

      TS_ASSERT(!testHouse->isRunning());

      stove->turnOnBurner(1,1);
 //     oven->action("turnOn");

      TS_ASSERT(testHouse->isRunning());

      testHouse->tick();
      testHouse->tick();
      testHouse->tick();

      TS_ASSERT(!testHouse->isRunning());

      LOG4CXX_DEBUG(log, "<-- HouseTest::test_isRunning()");
    }

    /*
     * Test the unused action() function inherited from Model.
     * It should always return true.
     */
    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("HouseTest"));
      LOG4CXX_DEBUG(log, "--> HouseTest::test_action()");

      Scheduler* scheduler = new MockScheduler();
      ModelFactory* modelFactory = new ModelFactory(scheduler);
      House* testHouse = modelFactory->createHouse(HOUSE, "unittest.config");
      Stove* stove = modelFactory->createStove(STOVE, "unittest.config", testHouse);
      Oven* oven = modelFactory->createOven(OVEN, "unittest.config", testHouse);

      ConfigMap* config = Model::parseConfiguration("unittest.config",
                                                    HOUSE,
                                                    "house");


      scheduler->registerModel(testHouse);
      scheduler->registerModel(stove);
      scheduler->registerModel(oven);

      TS_ASSERT(testHouse->action("turnOn"));
      TS_ASSERT(testHouse->action(""));

      LOG4CXX_DEBUG(log, "<-- HouseTest::test_action()");
    }
};


#endif /* HOUSETEST_H_ */
