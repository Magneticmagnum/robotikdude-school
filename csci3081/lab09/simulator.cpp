#include "Model.h"
#include "Refrigerator.h"
#include "Scheduler.h"

#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

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
      std::cerr << "ERROR: invalid duration, must be an integer and"
        " greater then zero." << std::endl;
      error = true;
    }

    std::fstream logger(argv[2], std::ios::out | std::ios::trunc);
    if (!logger.is_open()) {
      // check for invalid file path
      std::cerr << "ERROR: invalid file path, must be a path to a log"
        " file that exists or can be created." << std::endl;
      error = true;
    }
    else {
      logger.close();
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
      std::fstream logger(argv[1], std::ios::out | std::ios::trunc);
      if (!logger.is_open()) {
        std::cout << "ERROR: invalid argument, must be an integer for"
          " duration of a file path for the log file." << std::endl;
        usage(argv[0]);
        exit(0);
      }
      else {
        logger.close();
      }
    }
  }
  // else { keep the defaults }

  // Create instance of scheduler
  Scheduler scheduler = Scheduler();

  // Create instance of Refrigerator
  Refrigerator refrigerator = Refrigerator();

  // Register refrigerator instance with the scheduler
  scheduler.registerModel(&refrigerator);

  //Start the model:  call scheduler.run(),
  //telling scheduler to run for DURATION.
  scheduler.run(duration);

  return 0;
}

void usage(char* prog)
{
  std::cout << "USAGE: " << prog << " [duration] [log file]" << std::endl;
}

