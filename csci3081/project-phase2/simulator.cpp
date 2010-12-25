#include "Model.h"
#include "Scheduler.h"

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include <cstdlib>
#include <iostream>

#define DEFAULT_DURATION (30 * 24 * 60) // 30 days

/**
 * The simulator file is used to run specific cases of the simulation. Case
 * variables are defined as constants at the top of the file. For this version
 * of the energy use simulator, the only easily manipulable variable is the
 * duration of the simulation. The Default is 30 days.
 */
int main(int argc, char* argv[])
{
  log4cxx::PropertyConfigurator::configure(log4cxx::File("log.config"));
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("simulator"));

  void usage(char*);

  int duration = DEFAULT_DURATION;

  if (argc >= 3) {
    usage(argv[0]);
    exit(EXIT_FAILURE);
  }
  else if (argc == 2) {
    duration = std::atoi(argv[1]);
    if (duration <= 0) {
      duration = DEFAULT_DURATION;
      std::cout << "Unable to parse the duration, using default" << std::endl;
      usage(argv[0]);
    }
  }
  // else { keep the defaults }

  // Create instance of scheduler
  Scheduler* scheduler = Scheduler::getInstance();

  // Register all the model instances with the scheduler
  scheduler->registerModel(Model::getInstance(MODEL_DISHWASHER));
  scheduler->registerModel(Model::getInstance(MODEL_MICROWAVE));
  scheduler->registerModel(Model::getInstance(MODEL_OVEN));
  scheduler->registerModel(Model::getInstance(MODEL_PERSON));
  scheduler->registerModel(Model::getInstance(MODEL_REFRIGERATOR));
  scheduler->registerModel(Model::getInstance(MODEL_STOVE));
  scheduler->registerModel(Model::getInstance(MODEL_TELEVISION));
  scheduler->registerModel(Model::getInstance(MODEL_TOASTER));
  scheduler->registerModel(Model::getInstance(MODEL_WATERHEATER));

  // Start the simulation
  scheduler->run(duration);

  return EXIT_SUCCESS;
}

/**
 * Prints out the usage for the simulator.
 */
void usage(char* prog)
{
  std::cout << "USAGE: " << prog << " [duration]" << std::endl;
}

