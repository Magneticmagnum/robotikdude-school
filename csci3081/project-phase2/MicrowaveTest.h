#ifndef MICROWAVETEST_H_
#define MICROWAVETEST_H_

#include "Microwave.h"

#include <cxxtest/TestSuite.h>

#include <cstdlib>

class MicrowaveTest: public CxxTest::TestSuite
{
  public:
    void test_initialConditions()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> Entering MicrowaveTest::test_initialConditions()");

      Microwave m = Microwave();
      TS_ASSERT(!m.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting MicrowaveTest::test_initialConditions()");
    }

    void test_getPower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> Entering MicrowaveTest::test_getPower()");

      Microwave m = Microwave();
      TS_ASSERT_EQUALS(m.getPower(), 0.0);
      m.turnOn();
      TS_ASSERT_EQUALS(m.getPower(), 1500.0);

      LOG4CXX_DEBUG(log, "<-- Exiting MicrowaveTest::test_getPower()");
    }

    void test_getEnergy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> Entering MicrowaveTest::test_getEnergy()");

      srand(0);
      Microwave m = Microwave();
      m.turnOn();
      TS_ASSERT_DELTA(m.getEnergy(), 0.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 1000.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 1000.0, 0.01);

      m.turnOn();
      TS_ASSERT_DELTA(m.getEnergy(), 1000.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 2500.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 3380.0, 0.01);
      m.tick();
      TS_ASSERT_DELTA(m.getEnergy(), 3380.0, 0.01);

      LOG4CXX_DEBUG(log, "<-- Exiting MicrowaveTest::test_getEnergy()");
    }

    void test_turnOn()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> Entering MicrowaveTest::test_turnOn()");

      Microwave m = Microwave();
      TS_ASSERT(!m.isRunning());
      m.turnOn();
      TS_ASSERT(m.isRunning());
      m.turnOn();
      TS_ASSERT(m.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting MicrowaveTest::test_turnOn()");
    }

    void test_isRunning()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("MicrowaveTest"));
      LOG4CXX_DEBUG(log, "--> Entering MicrowaveTest::test_isRunning()");

      Microwave m = Microwave();
      TS_ASSERT(!m.isRunning());
      m.turnOn();
      TS_ASSERT(m.isRunning());

      LOG4CXX_DEBUG(log, "<-- Exiting MicrowaveTest::test_isRunning()");
    }
};

#endif /* MICROWAVETEST_H_ */
