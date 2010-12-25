#ifndef SCHEDULERTEST_H_
#define SCHEDULERTEST_H_

#include "Scheduler.h"
#include "Refrigerator.h"
#include "MockRandom.h"

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

      Scheduler* scheduler = new Scheduler();

      TS_ASSERT_EQUALS(scheduler->getTime(), 0);
      TS_ASSERT_EQUALS(scheduler->getModels(), 0);

      delete (scheduler);

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

      Scheduler* scheduler = new Scheduler();
      MockRandom* random = new MockRandom();

      random->seedNormal(0.6);
      random->seedNormal(0);
      Refrigerator fridgeOne = Refrigerator(0, scheduler, random);

      Refrigerator fridgeTwo = Refrigerator(0, scheduler, random);

      //Add first fridge and check that it was added.
      scheduler->registerModel(&fridgeOne);
      std::vector<Model*> testVector = scheduler->getList();
      TS_ASSERT_EQUALS(scheduler->getModels(), 1);
      TS_ASSERT_EQUALS(testVector.at(0), &fridgeOne);

      //Add second fridge and check that both fridges are in the vector.
      scheduler->registerModel(&fridgeTwo);
      testVector = scheduler->getList();
      TS_ASSERT_EQUALS(scheduler->getModels(), 2);
      TS_ASSERT_EQUALS(testVector.at(0), &fridgeOne);
      TS_ASSERT_EQUALS(testVector.at(1), &fridgeTwo);

      delete (scheduler);
      delete (random);

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

      Scheduler* scheduler = new Scheduler();
      MockRandom* random = new MockRandom();

      random->seedNormal(0.6);
      random->seedNormal(0);
      Refrigerator fridgeOne = Refrigerator(0, scheduler, random);

      //Register fridgeOne and run simulation for 12 ticks.
      scheduler->registerModel(&fridgeOne);
      scheduler->run(3);
      TS_ASSERT(!fridgeOne.isRunning());
      scheduler->run(7);
      TS_ASSERT(fridgeOne.isRunning());
      TS_ASSERT_EQUALS(scheduler->getTime(), 10);

      //Create second fridge.
      random->seedNormal(0.6);
      random->seedNormal(0);
      Refrigerator fridgeTwo = Refrigerator(0, scheduler, random);

      //Add second fridge and run simulation for 12 more ticks.
      scheduler->registerModel(&fridgeTwo);
      scheduler->run(3);
      TS_ASSERT(!fridgeOne.isRunning());
      TS_ASSERT(!fridgeTwo.isRunning());
      scheduler->run(7);
      TS_ASSERT(fridgeOne.isRunning());
      TS_ASSERT(fridgeTwo.isRunning());
      TS_ASSERT_EQUALS(scheduler->getTime(), 20);

      delete (scheduler);
      delete (random);

      LOG4CXX_DEBUG(log, "<-- Exiting SchedulerTest::test_runScheduler()");
    }
};

#endif /* SCHEDULERTEST_H_ */
