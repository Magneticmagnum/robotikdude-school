#ifndef MODELTEST_H_
#define MODELTEST_H_

#include "Model.h"
#include "Toaster.h"

#include <fstream>
#include <istream>
#include <stdio.h>

#include <cxxtest/TestSuite.h>

class ModelTest: public CxxTest::TestSuite
{
  public:
    void test_getInstance()
    {
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
    }

    void test_typeCasting()
    {
      Model* model = Model::getInstance(MODEL_WATERHEATER);
      TS_ASSERT_DELTA(0, (double) *model, 0.1);
      TS_ASSERT_EQUALS(0, (int) *model);
      for (int i = 0; i < 346; i++) {
        model->tick();
      }
      TS_ASSERT_DELTA(3000.0, (double) *model, 0.1);
      TS_ASSERT_EQUALS(3000, (int) *model);
      model->tick();
      TS_ASSERT_DELTA(6000.0, (double) *model, 0.1);
      TS_ASSERT_EQUALS(6000, (int) *model);

      Toaster* toaster = (Toaster*) Model::getInstance(MODEL_TOASTER);
      TS_ASSERT_DELTA(0.0, (double) *toaster, 0.1);
      TS_ASSERT_EQUALS(0, (int) *toaster);
      toaster->turnOn();
      toaster->tick();
      TS_ASSERT_DELTA(900.0, (double) *toaster, 0.1);
      TS_ASSERT_EQUALS(900, (int) *toaster);
    }

    void test_shift()
    {
      Model* model = Model::getInstance(MODEL_WATERHEATER);
      std::string str;

      std::ofstream ostream("model.test");
      ostream << *model << std::endl;
      ostream.close();

      std::ifstream istream("model.test");
      getline(istream, str);
      istream.close();

      TS_ASSERT_EQUALS(str, "Current power draw is 3000 and total energy used is 6000.");

      remove("model.test");
    }

};

#endif /* MODELTEST_H_ */
