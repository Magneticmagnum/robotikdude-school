#ifndef MODELTEST_H_
#define MODELTEST_H_

#include "Model.h"
#include "ConfigurationOptions.h"

#include <cxxtest/TestSuite.h>

class ModelTest: public CxxTest::TestSuite
{
  public:
  void test_makeargv()
  {
    log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelTest"));
    LOG4CXX_DEBUG(log, "--> ModelTest::test_makeargv()");

    char** argv = 0;
    int argc = 0;

    // test fails
    argc = Model::makeargv("", 0, &argv);
    TS_ASSERT(argv == 0);
    TS_ASSERT_EQUALS(argc, -1);
    Model::freemakeargv(argv);

    argc = Model::makeargv("", " ", 0);
    TS_ASSERT(argv == 0);
    TS_ASSERT_EQUALS(argc, -1);
    Model::freemakeargv(argv);

    argc = Model::makeargv("", " ", &argv);
    TS_ASSERT(argv != 0);
    TS_ASSERT_EQUALS(argc, 0);
    Model::freemakeargv(argv);

    // test successes
    argc = Model::makeargv("this is a test", " ", &argv);
    TS_ASSERT(argv != 0);
    TS_ASSERT_EQUALS(argc, 4);
    Model::freemakeargv(argv);

    LOG4CXX_DEBUG(log, "<-- ModelTest::test_makeargv()");
  }

  void test_perseConfiguration()
  {
    log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("ModelTest"));
    LOG4CXX_DEBUG(log, "--> ModelTest::test_perseConfiguration()");

    ConfigMap* config = 0;

    // test fails
    config = Model::parseConfiguration("fail", "fail", "fail");
    TS_ASSERT(config == 0);
    Model::deleteConfiguration(config);

    // test successes
    config = Model::parseConfiguration("unittest.config", REFRIGERATOR, "refrigerator");
    TS_ASSERT(config != 0);
    TS_ASSERT_EQUALS(config->size(), 4);
    Model::deleteConfiguration(config);

    LOG4CXX_DEBUG(log, "<-- ModelTest::test_perseConfiguration()");
  }

};

#endif /* MODELTEST_H_ */
