#ifndef TELEVISIONTEST_H_
#define TELEVISIONTEST_H_

#include <cxxtest/TestSuite.h>

#include "Television.h"

class TelevisionTest: public CxxTest::TestSuite
{
  public:
    void test_constructor()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_constructor()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      // test initial state with default values
      TS_ASSERT(!tv.isRunning());
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 0);
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 0);
      TS_ASSERT_EQUALS(tv.getOffPower(), TELEVISION_DEFAULT_OFF_POWER);
      TS_ASSERT_EQUALS(tv.getOnPower(), TELEVISION_DEFAULT_ON_POWER);
      TS_ASSERT(tv.getScheduler() == &sch);

      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_constructor()");
    }

    // test initialization with values from config file
    void test_config()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_config()");

      MockScheduler sch = MockScheduler();
      ConfigMap* config = Model::parseConfiguration("unittest.config", TELEVISION, "television");
      Television tv = Television(config, &sch);

      TS_ASSERT(!tv.isRunning());
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 0);
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 0);
      TS_ASSERT_EQUALS(tv.getOffPower(), 25.0);
      TS_ASSERT_EQUALS(tv.getOnPower(), 150.0);

      ConfigMap* config2 = Model::parseConfiguration("unittest.config", TELEVISION, "fail-tv");
      Television tv2 = Television(config2, &sch);

      TS_ASSERT_EQUALS(tv2.getOffPower(), TELEVISION_DEFAULT_OFF_POWER);
      TS_ASSERT_EQUALS(tv2.getOnPower(), TELEVISION_DEFAULT_ON_POWER);

      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_config()");
    }

    // test turning on and off using action
    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_action()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      bool noError = tv.action("start");
      TS_ASSERT(noError);
      TS_ASSERT(tv.isRunning());

      noError = tv.action("stop");
      TS_ASSERT(noError);
      TS_ASSERT(!tv.isRunning());
      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_action()");
    }

    // test for invalid actions
    void test_bad_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_bad_action()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      bool noError = tv.action("start 0");
      TS_ASSERT(!noError);
      TS_ASSERT(!tv.isRunning());

      noError = tv.action("bad");
      TS_ASSERT(!noError);
      TS_ASSERT(!tv.isRunning());

      noError = tv.action("stop");
      TS_ASSERT(!noError);
      TS_ASSERT(!tv.isRunning());

      tv.action("start");
      noError = tv.action("start");
      TS_ASSERT(!noError);
      TS_ASSERT(tv.isRunning());

      noError = tv.action("stop 0");
      TS_ASSERT(!noError);
      TS_ASSERT(tv.isRunning());
      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_bad_action()")
    }

    // tests that totalTimeOff_ is incremented when television is off
    // and that TotalTimeOn_ is not changed.
    void test_time_off()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_time_off()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      tv.tick();
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 0);
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 1);
      for (int i = 0; i < 100; i++) {
        tv.tick();
      }
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 0);
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 101);

      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_time_off()");
    }

    // tests that totalTimeOn_ is incremented when television is on
    // and that TotalTimeOff_ is not changed.
    void test_time_on()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_time_on()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      tv.action("start");
      tv.tick();
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 1);
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 0);
      for (int i = 0; i < 100; i++) {
        tv.tick();
      }
      TS_ASSERT_EQUALS(tv.getTotalTimeOn(), 101);
      TS_ASSERT_EQUALS(tv.getTotalTimeOff(), 0);

      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_time_on()");
    }

    // tests for energy usage
    void test_energy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_energy()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      for(int i = 0; i < 100; i++) {
        tv.tick();
      }
      TS_ASSERT_DELTA(tv.getEnergy(), 60000.0, 0.1);

      tv.action("start");
      for(int i = 0; i < 100; i++) {
        tv.tick();
      }
      TS_ASSERT_DELTA(tv.getEnergy(), 1140000.0, 0.1);

      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_energy()");
    }

    // tests getPower()
    void test_get_power()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("TelevisionTest"));
      LOG4CXX_DEBUG(log, "--> TelevisionTest::test_get_power()");

      MockScheduler sch = MockScheduler();
      Television tv = Television(0, &sch);

      TS_ASSERT_EQUALS(tv.getPower(), TELEVISION_DEFAULT_OFF_POWER);

      tv.action("start");
      TS_ASSERT_EQUALS(tv.getPower(), TELEVISION_DEFAULT_ON_POWER);

      tv.action("stop");
      TS_ASSERT_EQUALS(tv.getPower(), TELEVISION_DEFAULT_OFF_POWER);

      LOG4CXX_DEBUG(log, "<-- TelevisionTest::test_get_power()");
    }
};

#endif /* TELEVISIONTEST_H_ */
