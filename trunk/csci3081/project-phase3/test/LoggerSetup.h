#ifndef LOGGERSETUP_H_
#define LOGGERSETUP_H_

#include <cxxtest/GlobalFixture.h>
#include <iostream>
#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

class LoggerSetup: public CxxTest::GlobalFixture
{
  public:
    bool setUpWorld()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("LoggerSetup"));
      log4cxx::PropertyConfigurator::configure(
                                               log4cxx::File(
                                                             "log_testing.config"));
      LOG4CXX_INFO(log, "--> Starting test");
      return true;
    }

    bool tearDownWorld()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("LoggerSetup"));
      LOG4CXX_INFO(log, "<-- Leaving.");
      return true;
    }
};

//
// We can rely on this file being included exactly once
// and declare this global variable in the header file.
//
static LoggerSetup loggerSetup;
#endif /*LOGGERSETUP_H_*/
