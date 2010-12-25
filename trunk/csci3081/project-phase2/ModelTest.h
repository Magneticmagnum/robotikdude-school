#ifndef MODELTEST_H_
#define MODELTEST_H_

#include "Model.h"

#include <cxxtest/TestSuite.h>

class ModelTest: public CxxTest::TestSuite
{
  public:
    void test_getInstance()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelTest"));
      LOG4CXX_DEBUG(log, "--> Entering ModelTest::test_getInstance()");

      Model* model1 = Model::getInstance(MODEL_DISHWASHER);
      //      TS_ASSERT(model1);
      Model* model2 = Model::getInstance(MODEL_DISHWASHER);
      //      TS_ASSERT(model2);
      //      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_MICROWAVE);
      //            TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_MICROWAVE);
      //            TS_ASSERT(model2);
      //            TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_OVEN);
      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_OVEN);
      TS_ASSERT(model2);
      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_PERSON);
      //      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_PERSON);
      //      TS_ASSERT(model2);
      //      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_REFRIGERATOR);
      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_REFRIGERATOR);
      TS_ASSERT(model2);
      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_STOVE);
      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_STOVE);
      TS_ASSERT(model2);
      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_TELEVISION);
      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_TELEVISION);
      TS_ASSERT(model2);
      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_TOASTER);
      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_TOASTER);
      TS_ASSERT(model2);
      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance(MODEL_WATERHEATER);
      TS_ASSERT(model1);
      model2 = Model::getInstance(MODEL_WATERHEATER);
      TS_ASSERT(model2);
      TS_ASSERT_EQUALS(model1, model2);

      model1 = Model::getInstance("blah");
      TS_ASSERT(!model1);

      LOG4CXX_DEBUG(log, "<-- Exiting ModelTest::test_getInstance()");
    }

};

#endif /* MODELTEST_H_ */
