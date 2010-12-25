#include "Model.h" // cstrcmp_t
#include "Scheduler.h"
#include "ModelFactory.h"
#include "House.h"
#include "ConfigurationOptions.h"

#include <log4cxx/logger.h>
#include <log4cxx/propertyconfigurator.h>

#include <map> // map
#include <cstdlib> // atoi
#include <cstring> // strcmp, strtok
#include <iostream> // cout, endl
#include <fstream> // ifstream
//
#define DEFAULT_DAYS 10
#define BUFFER_SIZE 1024

/**
 * TODO user23: comment
 * The simulator file is used to run specific cases of the simulation. Case
 * variables are defined as constants at the top of the file. For this version
 * of the energy use simulator, the only easily manipulable variable is the
 * duration of the simulation. The Default is 10 days.
 */
int main(int argc, char* argv[])
{
  void usage(char*);
  bool validateExtension(const char*, const char*);

  int nDays = DEFAULT_DAYS;
  std::ifstream modelSpec;
  char* modelSpecFile;
  std::map<const char*, char*, cstrcmp_t> stateFiles;

  char buffer[BUFFER_SIZE];

  if (argc < 3 || (strcmp(argv[1], "-d") == 0 && argc < 5)) {
    usage(argv[0]);
    exit(1);
  }
  else {
    int fileStart = 1;
    if (strcmp(argv[1], "-d") == 0) {
      fileStart = 3;
      int newdays = atoi(argv[2]);
      if (newdays > 0) {
        nDays = newdays;
      }
      else {
        std::cout
            << "WARNING: Number of days must be greater then zero (given: "
            << argv[2] << "), using default of " << DEFAULT_DAYS << " days."
            << std::endl;
      }
    }
    modelSpecFile = argv[fileStart];
    modelSpec.open(modelSpecFile);
    if (modelSpec.fail()) {
      // error opening file
      exit(1);
    }

    for (int i = fileStart + 1; i < argc; i++) {
      FILE* f = fopen(argv[i], "r");
      if (f == 0) {
        // error opening file
        exit(1);
      }
      fclose(f);
      char* personName = (char*) malloc(sizeof(char) * (strlen(argv[i]) + 1));
      strcpy(personName, argv[i]);
      strtok(personName, ".");
      stateFiles[personName] = argv[i];
    }
  }
  // else { keep the defaults }

  log4cxx::PropertyConfigurator::configure(log4cxx::File("log.config"));
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("simulator"));

  Scheduler* scheduler = new Scheduler();
  ModelFactory* factory = new ModelFactory(scheduler);

  House* house = 0;

  char* type;
  char* name;
  while (!modelSpec.eof()) {
    modelSpec.getline(buffer, BUFFER_SIZE);

    if (!modelSpec.fail() // get line fail
        && (type = strtok(buffer, " ")) != 0 // model type
        && type[0] != '#' // comment
        && (name = strtok(0, " \r\n")) != 0) { // model name

      if (strcmp(type, HOUSE) == 0) {
        if (house != 0) {
          scheduler->registerModel(house);
        }
        house = factory->createHouse(name, modelSpecFile);
      }
      else if (house != 0) {
        if (factory->getModel(name) == 0) {
          Model* m = 0;

          // PERSON MODEL
          if (strcmp(type, PERSON) == 0) {
            if (stateFiles.find(name) != stateFiles.end()) {
              m = factory->createPerson(name, stateFiles[name], house);
            }
            else {
              // error, no matching state file
            }
          }
          // OTHER MODEL
          else {
            m = factory->createModel(type, name, modelSpecFile, house);
          }

          // ADDING MODEL
          if (m != 0) {
            house->addModel(name, m);
          }
          else {
            // error, could not create model
          }

        }
        else {
          // model already created
        }
      }
      else {
        // error, no house declared before model

      } // end else [if (strcpy(type, HOUSE) == 0)]

    }

  } // end while(!input.eof())

  if (house != 0) {
    scheduler->registerModel(house);
  }

  //Write initial message to log, run simulation, write final message to log
  LOG4CXX_INFO(log, "Log file initialized.  Simulation starting.");
  scheduler->run(nDays * TICKS_PER_DAY);
  LOG4CXX_INFO(log, "Simulation finished.");

  // free map

  return EXIT_SUCCESS;
}

/**
 * Prints out the usage for the simulator.
 */
void usage(char* prog)
{
  std::cout << "USAGE: " << prog
      << " [-d ndays] model-spec person-spec1 person-spec2 ..." << std::endl;
}

bool validateExtension(const char* filename, const char* extension)
{

}

