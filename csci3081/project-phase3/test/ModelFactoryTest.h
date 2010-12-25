#ifndef MODELFACTORYTEST_H_
#define MODELFACTORYTEST_H_

#include "ModelFactory.h"
#include "MockScheduler.h"

#include <cxxtest/TestSuite.h>

class ModelFactoryTest: public CxxTest::TestSuite
{
  public:
    void test_Model()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Model()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getModel("blah") == 0);
      TS_ASSERT(factory->createModel("type", "blah", "", 0) == 0);
      TS_ASSERT(factory->getModel("blah") == 0);

      TS_ASSERT(factory->getModel("house") == 0);
      TS_ASSERT(factory->createModel("House", "house", "", 0) != 0);
      TS_ASSERT(factory->getModel("house") != 0);

      TS_ASSERT(factory->getModel("bath") == 0);
      TS_ASSERT(factory->createModel("Bath", "bath", "", 0) != 0);
      TS_ASSERT(factory->getModel("bath") != 0);

      TS_ASSERT(factory->getModel("dishwasher") == 0);
      TS_ASSERT(factory->createModel("Dishwasher", "dishwasher", "", 0) != 0);
      TS_ASSERT(factory->getModel("dishwasher") != 0);

      TS_ASSERT(factory->getModel("microwave") == 0);
      TS_ASSERT(factory->createModel("Microwave", "microwave", "", 0) != 0);
      TS_ASSERT(factory->getModel("microwave") != 0);

      TS_ASSERT(factory->getModel("oven") == 0);
      TS_ASSERT(factory->createModel("Oven", "oven", "", 0) != 0);
      TS_ASSERT(factory->getModel("oven") != 0);

      TS_ASSERT(factory->getModel("person") == 0);
      TS_ASSERT(factory->createModel("Person", "person", "", 0) != 0);
      TS_ASSERT(factory->getModel("person") != 0);

      TS_ASSERT(factory->getModel("refrigerator") == 0);
      TS_ASSERT(factory->createModel("Refrigerator", "refrigerator", "", 0) != 0);
      TS_ASSERT(factory->getModel("refrigerator") != 0);

      TS_ASSERT(factory->getModel("shower") == 0);
      TS_ASSERT(factory->createModel("Shower", "shower", "", 0) != 0);
      TS_ASSERT(factory->getModel("shower") != 0);

      TS_ASSERT(factory->getModel("stove") == 0);
      TS_ASSERT(factory->createModel("Stove", "stove", "", 0) != 0);
      TS_ASSERT(factory->getModel("stove") != 0);

      TS_ASSERT(factory->getModel("television") == 0);
      TS_ASSERT(factory->createModel("Television", "television", "", 0) != 0);
      TS_ASSERT(factory->getModel("television") != 0);

      TS_ASSERT(factory->getModel("toaster") == 0);
      TS_ASSERT(factory->createModel("Toaster", "toaster", "", 0) != 0);
      TS_ASSERT(factory->getModel("toaster") != 0);

      TS_ASSERT(factory->getModel("waterheater") == 0);
      TS_ASSERT(factory->createModel("WaterHeater", "waterheater", "", 0) != 0);
      TS_ASSERT(factory->getModel("waterheater") != 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Model()");
    }

    void test_House()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_House()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getHouse("blah") == 0);
      TS_ASSERT(factory->createHouse("house", "") != 0);
      TS_ASSERT(factory->getHouse("house") != 0);
      TS_ASSERT(factory->getHouse("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_House()");
    }

    void test_Bath()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Bath()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getBath("blah") == 0);
      TS_ASSERT(factory->createBath("bath", "", 0) != 0);
      TS_ASSERT(factory->getBath("bath") != 0);
      TS_ASSERT(factory->getBath("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Bath()");
    }

    void test_Dishwasher()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Dishwasher()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getDishwasher("blah") == 0);
      TS_ASSERT(factory->createDishwasher("dishwasher", "", 0) != 0);
      TS_ASSERT(factory->getDishwasher("dishwasher") != 0);
      TS_ASSERT(factory->getDishwasher("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Dishwasher()");
    }

    void test_Microwave()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Microwave()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getMicrowave("blah") == 0);
      TS_ASSERT(factory->createMicrowave("microwave", "", 0) != 0);
      TS_ASSERT(factory->getMicrowave("microwave") != 0);
      TS_ASSERT(factory->getMicrowave("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Microwave()");
    }

    void test_Oven()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Oven()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getOven("blah") == 0);
      TS_ASSERT(factory->createOven("oven", "", 0) != 0);
      TS_ASSERT(factory->getOven("oven") != 0);
      TS_ASSERT(factory->getOven("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Oven()");
    }

    void test_Person()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Person()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getPerson("blah") == 0);
      TS_ASSERT(factory->createPerson("person", "", 0) != 0);
      TS_ASSERT(factory->getPerson("person") != 0);
      TS_ASSERT(factory->getPerson("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Person()");
    }

    void test_Refrigerator()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_getRefrigerator()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getRefrigerator("blah") == 0);
      TS_ASSERT(factory->createRefrigerator("refrigerator", "", 0) != 0);
      TS_ASSERT(factory->getRefrigerator("refrigerator") != 0);
      TS_ASSERT(factory->getRefrigerator("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_getRefrigerator()");
    }

    void test_Shower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Shower()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getShower("blah") == 0);
      TS_ASSERT(factory->createShower("shower", "", 0) != 0);
      TS_ASSERT(factory->getShower("shower") != 0);
      TS_ASSERT(factory->getShower("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Shower()");
    }

    void test_Stove()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Stove()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getStove("blah") == 0);
      TS_ASSERT(factory->createStove("stove", "", 0) != 0);
      TS_ASSERT(factory->getStove("stove") != 0);
      TS_ASSERT(factory->getStove("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Stove()");
    }

    void test_Television()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Television()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getTelevision("blah") == 0);
      TS_ASSERT(factory->createTelevision("television", "", 0) != 0);
      TS_ASSERT(factory->getTelevision("television") != 0);
      TS_ASSERT(factory->getTelevision("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Television()");
    }

    void test_Toaster()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_Toaster()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getToaster("blah") == 0);
      TS_ASSERT(factory->createToaster("toaster", "", 0) != 0);
      TS_ASSERT(factory->getToaster("toaster") != 0);
      TS_ASSERT(factory->getToaster("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_Toaster()");
    }

    void test_WaterHeater()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelFactoryTest"));
      LOG4CXX_DEBUG(log, "--> ModelFactoryTest::test_WaterHeater()");

      MockScheduler* scheduler = new MockScheduler();
      ModelFactory* factory = new ModelFactory(scheduler);

      TS_ASSERT(factory->getWaterHeater("blah") == 0);
      TS_ASSERT(factory->createWaterHeater("waterheater", "", 0) != 0);
      TS_ASSERT(factory->getWaterHeater("waterheater") != 0);
      TS_ASSERT(factory->getWaterHeater("blah") == 0);

      delete (scheduler);
      delete (factory);

      LOG4CXX_DEBUG(log, "<-- ModelFactoryTest::test_WaterHeater()");
    }
};

#endif /* MODELFACTORYTEST_H_ */
