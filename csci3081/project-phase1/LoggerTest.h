#ifndef LOGGERTEST_H_
#define LOGGERTEST_H_

#include "Logger.h"

#include <cxxtest/TestSuite.h>

#include <iostream>
#include <fstream>
using std::fstream;
using std::ifstream;
using std::getline;
using std::ios;

class LoggerTest: public CxxTest::TestSuite
{
  public:
    // tests if variables are initialized correctly when Logger is created
    void test_initialization()
    {
      string filePath = "test.log"; // string for test log file name

      Scheduler sch = Scheduler();
      Logger log = Logger(&sch, filePath);

      // checks scheduler_ against the pointer value passed to the constructor
      TS_ASSERT_EQUALS(&sch, log.getScheduler());

      // checks str_filePath against the string passed to the constructor
      TS_ASSERT(filePath.compare(log.getFilePath()) == 0);
    }

    // tests if creation of Logger truncates the log file and prints a header
    void test_truncation()
    {
      string filePath = "test.log";   // string for test log file name
      string buffer;                  // string for input from test log file
      fstream logFile;                // for reading and writing to test log file

      Scheduler sch = Scheduler();

      // open test log file for writing
      logFile.open(filePath.c_str(), ios::out);

      // put some text into the file
      logFile << "This represents text that was previously in the log file.\n";
      logFile.close();

      Logger log = Logger(&sch, filePath);

      // open test log file for reading
      logFile.open(filePath.c_str(), ios::in);

      getline(logFile, buffer); // reads in header
      logFile.close();

      // checks if the first line in the log file is the header printed by constructor
      TS_ASSERT(buffer.compare("Simulation of Household energy usage:") == 0);
    }

    // tests if print function writes to file properly
    void test_print()
    {
      string filePath = "test.log";     // string for test log file name
      string buffer;                    // string for input
      ifstream logRead;                 // for reading from test log file

      Scheduler sch = Scheduler();
      Logger log = Logger(&sch, filePath);

      // prints a status message to test log file
      log.print("This is a test message.");

      // open test log file for reading
      logRead.open(filePath.c_str(), ios::in);

      getline(logRead, buffer); // header line
      getline(logRead, buffer); // blank line under header
      getline(logRead, buffer); // first line of log
      logRead.close();

      // checks that the test message was printed
      TS_ASSERT(buffer.compare("At 0 minute(s): This is a test message.") == 0);
    }
};

#endif /* LOGGERTEST_H_ */
