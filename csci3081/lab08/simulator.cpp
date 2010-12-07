#include "Model.h"
#include "Refrigerator.h"
#include "Scheduler.h"

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include <string>
#include <cstdlib>
#include <fstream>
#include <iostream>

#define DEFAULT_LOG_FILE_PATH "simulator.log"
#define DEFAULT_DURATION      90

/**
 * The simulator file is used to run specific cases of the
 * simulation.  Case variables are defined as constants at
 * the top of the file.  For this version of the energy
 * use simulator, the only easily manipulable variable is
 * the duration of the simulation.  In this case,
 * the simulation is run with only one appliance (a refrigerator)
 * for 90 minutes/ticks.
 */
int main(int argc, char* argv[])
{
  log4cxx::PropertyConfigurator::configure(log4cxx::File("log.config"));

  log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("simulator"));

  void usage(char*);

  std::string logFile = DEFAULT_LOG_FILE_PATH;
  int duration = DEFAULT_DURATION;

  if (argc >= 4) {
    usage(argv[0]);
    exit(0);
  }
  else if (argc == 3) {
    duration = std::atoi(argv[1]);
    logFile = std::string(argv[2]);

    bool error = false;

    if (duration <= 0) {
      LOG4CXX_ERROR(logger, "Invalid duration, must be an integer and greater"
          " then zero.");
      error = true;
    }

    std::fstream logFileTest(argv[2], std::ios::out | std::ios::trunc);
    if (!logFileTest.is_open()) {
      // check for invalid file path
      LOG4CXX_ERROR(logger, "Invalid file path, must be a path to a log file"
          " that exists or can be created.");
      error = true;
    }
    else {
      logFileTest.close();
    }

    if (error) {
      usage(argv[0]);
      exit(0);
    }

  }
  else if (argc == 2) {
    duration = std::atoi(argv[1]);
    if (duration <= 0) {
      duration = DEFAULT_DURATION;
      logFile = std::string(argv[1]);
      std::fstream logFileTest(argv[1], std::ios::out | std::ios::trunc);
      if (!logFileTest.is_open()) {
        LOG4CXX_ERROR(logger, "Invalid argument, must be an integer for"
            " duration of a file path for the log file.");
        usage(argv[0]);
        exit(0);
      }
      else {
        logFileTest.close();
      }
    }
  }
  // else { keep the defaults }

  LOG4CXX_INFO(logger, "About to begin simulation with one refrigerator and"
      " duration of " << duration << " ticks.");

  // Create instance of scheduler
  Scheduler scheduler = Scheduler();

  // Create instance of Refrigerator
  Refrigerator refrigerator = Refrigerator(&scheduler);

  // Register refrigerator instance with the scheduler
  scheduler.registerModel(&refrigerator);

  // Start the model:  call scheduler.run(), telling scheduler to run for
  // duration.
  scheduler.run(duration);

  LOG4CXX_INFO(logger, "Simulation complete");
  return 0;
}

void usage(char* prog)
{
  std::cout << "USAGE: " << prog << " [duration] [log file]" << std::endl;
}

