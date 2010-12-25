#include "Shower.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

log4cxx::LoggerPtr
    Shower::log(log4cxx::Logger::getLogger("Shower"));

// constructor
Shower::Shower(ConfigMap* config, Scheduler* sch,
               House* house)
{
  LOG4CXX_TRACE(log, "--> Shower::Shower(ConfigMap*, Scheduler*, Waterheater*)");

  // initialize default values
  waterTemp_ = 0.0;
  waterDraw_ = 0.0;
  totalWaterUsed_ = 0.0;
  running_ = false;

  scheduler_ = sch;
  house_ = house;
  // set a default name for water heater
  waterHeaterName_ = "waterheater";

  initConfig(config);

  LOG4CXX_TRACE(log, "    Shower created, " << (!running_? "not" : "") << "running.");
  LOG4CXX_TRACE(log, "    Shower created that uses water at "
                << waterTemp_ << " degrees celsius.");
  LOG4CXX_TRACE(log, "    Shower created that draws "
                << waterDraw_ << " liters of water when in use.");


  LOG4CXX_TRACE(log, "<-- Shower::Shower(ConfigMap*, Scheduler*, Waterheater*)");
}

void Shower::initConfig(ConfigMap* config)
{
  LOG4CXX_TRACE(log, "--> Shower::initConfig(ConfigMap*)");

  if (config == 0) { // no configuration file given, using default values.
    LOG4CXX_TRACE(log, "    No configuration file given.  Default values loaded.");
  }
  else { // configuration file given
    ConfigMap::iterator configIter;

    for (configIter = config->begin(); configIter
        != config->end(); configIter++) {
      if (strcmp(configIter->first, SHOWER_WATERHEATER_NAME)
          == 0) {
        waterHeaterName_ = configIter->second;
      }
      else { // not recognized
        LOG4CXX_WARN(log, "*** Shower attribute" << configIter->first << " is not recognized.");
      }
    }
  }
  LOG4CXX_TRACE(log, "<-- Shower::initConfig(ConfigMap*)");
}

// returns true if shower is running, otherwise returns false
bool Shower::isRunning() const
{
  LOG4CXX_TRACE(log, "--> Shower::isRunning()");
  bool result;
  if (running_) { // shower is running
    result = true;
  }
  else { // shower is not running
    result = false;
  }
  LOG4CXX_TRACE(log, "<-- Shower::isRunning()");
  return result;
}

// draws water from Water Heater if Shower is on
void Shower::tick()
{
  LOG4CXX_TRACE(log, "<-- Shower::tick()");

  WaterHeater* wh = (WaterHeater*) house_->getModel(waterHeaterName_);
  if (wh == 0) {
    LOG4CXX_WARN(log, "*** Attempt to obtain water heater failed.");
  }

  if (isRunning()) { // shower is drawing water
    wh->getWater(waterDraw_, waterTemp_);
    totalWaterUsed_ += waterDraw_;
  }
  else { // shower is not drawing water
    // do nothing
  }
  LOG4CXX_TRACE(log, "--> Shower::tick()");
}

// no power used by Shower; return 0.0
double Shower::getPower() const
{
  return 0.0;
}

// no energy used by Shower; return 0.0
double Shower::getEnergy() const
{
  return 0.0;
}

// turns shower on
bool Shower::turnOn()
{
  LOG4CXX_TRACE(log, "--> Shower::turnOn()");

  bool noError = true;

  if (isRunning()) { // shower is already on
    LOG4CXX_WARN(log, "*** Attempt to turn shower on failed.  Shower is already running.");
    noError = false;
  }
  else { // shower is not running
    running_ = true;
  }

  LOG4CXX_TRACE(log, "<-- Shower::turnon()");
  return noError;
}

// turns shower off
bool Shower::turnOff()
{
  LOG4CXX_TRACE(log, "--> Shower::turnOff()");

  bool noError = true;

  if (isRunning()) { // shower is running
    running_ = false;
  }
  else { // shower is not running
    LOG4CXX_WARN(log, "*** Attempt to turn shower off failed.  Shower is not running.");
    noError = false;
  }
  LOG4CXX_TRACE(log, "<-- Shower::turnOff()");
  return noError;
}

bool Shower::action(const string& actions)
{
  LOG4CXX_TRACE(log, "--> Shower::action(const string&");
  bool noError = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);

  if (argc >= 1) {
    if (strcmp(SHOWER_START, argv[0]) == 0) {
      if (argc == 3) { // proper number of arguments for turning the shower on
        if (turnOn()) {
          waterDraw_ = atof(argv[1]);
          waterTemp_ = atof(argv[2]);
        }
        else { // failed to turn shower on
          noError = false;
        }
      }
      else { // improper number of arguments for turning the shower on
        noError = false;
        LOG4CXX_WARN(log, "*** Improper number of arguments given to turn Shower on.  See documentation.");
      }
    }
    else if (strcmp(SHOWER_STOP, argv[0]) == 0) {
      if (argc == 1) { // proper number of arguments for turning the shower off
        if (turnOff()) { // turnOff() succeeded
          waterDraw_ = 0.0;
          waterTemp_ = 0.0;
        }
        else { // turnOff() failed
          noError = false;
        }
      }
      else { // improper number of arguments for turning the shower off
        noError = false;
        LOG4CXX_WARN(log, "*** Improper number of arguments given to turn Shower off.  See documentation.");
      }
    }
    else { // action not recognized
      noError = false;
      LOG4CXX_WARN(log, "*** Shower action " << argv[0] << " is not recognized.");
    }
  }
  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log, "<-- Shower::action(const string&)");
  return noError;
}

// returns scheduler_
Scheduler* Shower::getScheduler() const
{
  return scheduler_;
}

// returns water draw
double Shower::getDraw() const
{
  return waterDraw_;
}

// returns water temp
double Shower::getTemp() const
{
  return waterTemp_;
}

// returns House*
House* Shower::getHouse() const
{
  return house_;
}

// returns water heater name
string Shower::getWHName() const
{
  return waterHeaterName_;
}

// returns water heater pointer
WaterHeater* Shower::getWHModel() const
{
  return (WaterHeater*) house_->getModel(waterHeaterName_);
}

double Shower::getTotalWater() const
{
  return totalWaterUsed_;
}
