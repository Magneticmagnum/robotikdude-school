#ifndef SCHEDULERTEST_H_
#define SCHEDULERTEST_H_

#include <cxxtest/TestSuite.h>

#include "Scheduler.h"
#include "Refrigerator.h"

class SchedulerTest: public CxxTest::TestSuite
{
  public:

    /**
     * Test that the initial time and number of models start at zero.
     */
    void test_initialTimeModels()
    {
      Scheduler s = Scheduler();
      TS_ASSERT_EQUALS(s.getTime(), 0);
      TS_ASSERT_EQUALS(s.getModels(), 0);
    }

    /**
     * Test addition of a model to the scheduler.
     * Checks to ensure number of models is correct as well as
     * the list of models in the scheduler instance.
     */
    void test_addModel()
    {
      Scheduler s = Scheduler();
      Refrigerator fridgeOne = Refrigerator();
      Refrigerator* pFridge = &fridgeOne;

      Refrigerator fridgeTwo = Refrigerator();
      Refrigerator* pFridgeTwo = &fridgeTwo;

      //Add first fridge and check that it was added.
      s.registerModel(pFridge);
      vector<Model*> testVector = s.getList();
      TS_ASSERT_EQUALS(s.getModels(), 1);
      TS_ASSERT_EQUALS(testVector.at(0), pFridge);

      //Add second fridge and check that both fridges are in the vector.
      s.registerModel(pFridgeTwo);
      testVector = s.getList();
      TS_ASSERT_EQUALS(s.getModels(), 2);
      TS_ASSERT_EQUALS(testVector.at(0), pFridge);
      TS_ASSERT_EQUALS(testVector.at(1), pFridgeTwo);
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
      Scheduler s = Scheduler();
      Refrigerator fridgeOne = Refrigerator();
      Refrigerator* pFridgeOne = &fridgeOne;

      //Register fridgeOne and run simulation for 12 ticks.
      s.registerModel(pFridgeOne);
      s.run(3);
      TS_ASSERT(!fridgeOne.isRunning());
      s.run(9);
      TS_ASSERT(fridgeOne.isRunning());
      TS_ASSERT_EQUALS(s.getTime(), 12);

      //Create second fridge.
      Refrigerator fridgeTwo = Refrigerator();
      Refrigerator* pFridgeTwo = &fridgeTwo;

      //Add second fridge and run simulation for 12 more ticks.
      s.registerModel(pFridgeTwo);
      s.run(3);
      TS_ASSERT(!fridgeOne.isRunning());
      TS_ASSERT(!fridgeTwo.isRunning());
      s.run(9);
      TS_ASSERT(fridgeOne.isRunning());
      TS_ASSERT(fridgeTwo.isRunning());
      TS_ASSERT_EQUALS(s.getTime(), 24);
    }
};

#endif /* SCHEDULERTEST_H_ */
