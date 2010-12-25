#ifndef SCHEDULERTEST_H_
#define SCHEDULERTEST_H_

#include "Scheduler.h"
#include "Refrigerator.h"

#include <cxxtest/TestSuite.h>

#include <cstdlib>

class SchedulerTest: public CxxTest::TestSuite
{
  public:

    /**
     * Test that the initial time and number of models start at zero.
     */
    void test_initialTimeModels()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("SchedulerTest"));
      LOG4CXX_DEBUG(log, "--> Entering SchedulerTest::test_initialTimeModels()");

      Scheduler* s = Scheduler::getInstance();
      s->reset();

      TS_ASSERT_EQUALS(s->getTime(), 0);
      TS_ASSERT_EQUALS(s->getModels(), 0);

      LOG4CXX_DEBUG(log, "<-- Exiting SchedulerTest::test_initialTimeModels()");
    }

    /**
     * Test addition of a model to the scheduler.
     * Checks to ensure number of models is correct as well as
     * the list of models in the scheduler instance.
     */
    void test_addModel()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("SchedulerTest"));
      LOG4CXX_DEBUG(log, "--> Entering SchedulerTest::test_addModel()");

      Scheduler* s = Scheduler::getInstance();
      s->reset();

      Refrigerator fridgeOne = Refrigerator();
      Refrigerator* pFridge = &fridgeOne;

      Refrigerator fridgeTwo = Refrigerator();
      Refrigerator* pFridgeTwo = &fridgeTwo;

      //Add first fridge and check that it was added.
      s->registerModel(pFridge);
      std::vector<Model*> testVector = s->getList();
      TS_ASSERT_EQUALS(s->getModels(), 1);
      TS_ASSERT_EQUALS(testVector.at(0), pFridge);

      //Add second fridge and check that both fridges are in the vector.
      s->registerModel(pFridgeTwo);
      testVector = s->getList();
      TS_ASSERT_EQUALS(s->getModels(), 2);
      TS_ASSERT_EQUALS(testVector.at(0), pFridge);
      TS_ASSERT_EQUALS(testVector.at(1), pFridgeTwo);
      s->reset();

      LOG4CXX_DEBUG(log, "<-- Exiting SchedulerTest::test_addModel()");
    }

    /**
     * Tests a short run of the refrigerator.  Creates a new
     * refrigerator and runs it for a total of 12 ticks to
     * ensure it turns on and off as expected.  Then adds a
     * second refrigerator and runs again, making sure both
     * are getting properly updated.  Also checks to make sure
     * getTime() returns the correct amount of ticks passed.
     */
    void test_runScheduler()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("SchedulerTest"));
      LOG4CXX_DEBUG(log, "--> Entering SchedulerTest::test_runScheduler()");

      Scheduler* s = Scheduler::getInstance();
      s->reset();

      srand(0);
      Refrigerator fridgeOne = Refrigerator();
      fridgeOne.tick();

      //Register fridgeOne and run simulation for 12 ticks.
      s->registerModel(&fridgeOne);
      s->run(3);
      TS_ASSERT(!fridgeOne.isRunning());
      s->run(7);
      TS_ASSERT(fridgeOne.isRunning());
      TS_ASSERT_EQUALS(s->getTime(), 10);

      //Create second fridge.
      srand(0);
      Refrigerator fridgeTwo = Refrigerator();
      fridgeTwo.tick();

      //Add second fridge and run simulation for 12 more ticks.
      s->registerModel(&fridgeTwo);
      s->run(3);
      TS_ASSERT(!fridgeOne.isRunning());
      TS_ASSERT(!fridgeTwo.isRunning());
      s->run(7);
      TS_ASSERT(fridgeOne.isRunning());
      TS_ASSERT(fridgeTwo.isRunning());
      TS_ASSERT_EQUALS(s->getTime(), 20);
      s->reset();

      LOG4CXX_DEBUG(log, "<-- Exiting SchedulerTest::test_runScheduler()");
    }
};

#endif /* SCHEDULERTEST_H_ */
