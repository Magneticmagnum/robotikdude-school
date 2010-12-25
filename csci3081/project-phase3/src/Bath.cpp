#include "Bath.h"
#include "ConfigurationOptions.h"
#include <stdlib.h>

log4cxx::LoggerPtr Bath::log_(log4cxx::Logger::getLogger("Bath"));

Bath::Bath(ConfigMap* config, Scheduler* scheduler, House* house)
{
  LOG4CXX_TRACE(log_, "--> Bath::Bath(ConfigMap*, Scheduler*, House*)");

  capacity_ = 100;
  currentLevel_ = 0;
  isFilling_ = false;
  timeRunning_ = 0;
  temperature_ = 42;
  scheduler_ = scheduler;
  house_ = house;
  waterheater_ = "waterheater";

  initializeConfiguration(config);

  LOG4CXX_DEBUG(log_, "    Bath created " << (isFilling_ ? "" : "not ")
      << "filling.");
  LOG4CXX_DEBUG(log_, "    Time running this cycle: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Default Bath capacity: " << capacity_ << ".");
  LOG4CXX_DEBUG(log_, "    Default Bath temperature: " << temperature_ << ".");
  LOG4CXX_DEBUG(log_, "    Bath currently contains " << currentLevel_ << "L.");

  LOG4CXX_TRACE(log_, "<-- Bath::Bath(ConfigMap*, Scheduler*, House*)");
}

/*
 * Initialize Bath with the Bath's capacity and the
 * water heater it is to use.
 */
void Bath::initializeConfiguration(ConfigMap* config)
{
  LOG4CXX_TRACE(log_, "--> Bath::initializeConfiguration(ConfigMap*)");

  if (config == 0) {
    LOG4CXX_TRACE(log_, "    No configuration given, using the default values");
  }
  else {
    ConfigMap::iterator iter;
    for (iter = config->begin(); iter != config->end(); iter++) {

      // configure capacity
      if (strcmp(iter->first, BATH_CAPACITY) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          capacity_ = temp;
          LOG4CXX_DEBUG(log_, "    Bath's capacity loaded from file: " << capacity_);
        }
        else {
          LOG4CXX_WARN(log_, "*** Bath's " << BATH_CAPACITY << " attribute must be greater then zero, given " << iter->second);
        }
      }

      // configure waterheater
      else if (strcmp(iter->first, BATH_WATERHEATER) == 0) {
        waterheater_ = iter->second;
        LOG4CXX_DEBUG(log_, "    Bath's water heater name loaded from file: " << capacity_);
      }

      // unknown configure option
      else {
        LOG4CXX_WARN(log_, "*** The Bath attribute " << iter->first << " was not recognized");
      }

    } // end for
  } // end if (config == 0) else

  LOG4CXX_TRACE(log_, "<-- Bath::initializeConfiguration(ConfigMap*)");
}

/*
 * Checks bath state and executes proper bath behavior.
 */
void Bath::tick()
{
  LOG4CXX_TRACE(log_, "--> Bath::tick()");

  if (isFilling_) {
    WaterHeater* wh = (WaterHeater*) house_->getModel(waterheater_);
    if (wh == 0) {
      LOG4CXX_WARN(log_, "*** Unable to find water heater " << waterheater_ << " in the house");
    }

    // Check to see if the bath has enough room for another flowRate_ worth of water.
    if (capacity_ - currentLevel_ >= flowRate_) {
      if (wh != 0) {
        wh->getWater(flowRate_, temperature_);
      }
      currentLevel_ += flowRate_;
      timeRunning_++;
      if (currentLevel_ >= capacity_) {
        isFilling_ = false;
        timeRunning_ = 0;
        currentLevel_ = 0;
      }
    }
    // Should only occur when the flowRate_ is changed while filling.
    // This code prevents "over-filling" the Bath.
    else {
      if (wh != 0) {
        wh->getWater((capacity_ - currentLevel_), temperature_);
      }
      isFilling_ = false;
      timeRunning_ = 0;
      currentLevel_ = 0;
    }
  }

  LOG4CXX_TRACE(log_, "<-- Bath::tick()");
}

/*
 * Returns the capacity of the bath.
 */
double Bath::getCapacity() const
{
  return capacity_;
}

/*
 * Returns the current water level of the bath.
 */
double Bath::getCurrentLevel() const
{
  return currentLevel_;
}

/*
 * Returns the amount of time the bath has been running.
 */
int Bath::getTimeRunning() const
{
  return timeRunning_;
}

/*
 * Returns the current temperature.
 */
double Bath::getTemperature() const
{
  return temperature_;
}

/*
 * Returns if the bath is filling or not.
 */
bool Bath::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> Bath::isRunning()");
  LOG4CXX_DEBUG(log_, "    Bath is currently " << (isFilling_ ? "" : "not ")
      << "filling.");
  LOG4CXX_TRACE(log_, "<-- Bath::isRunning()");
  return isFilling_;
}

/*
 * Starts filling the bath.
 */

// TODO user21: a second call should not empty the bath, but update the values for a new flow and temp and continue filling. once full, you can assume that it is immediately empty
void Bath::turnOn(double flowRate, double temperature)
{
  LOG4CXX_TRACE(log_, "--> Bath::turnOn()");

  if ((flowRate > 0) && (temperature > 0) && (temperature <= 50)) {
    isFilling_ = true;
    flowRate_ = flowRate;
    temperature_ = temperature;

    LOG4CXX_INFO(log_, "    At time " << scheduler_->getTimeStr()
        << " the bath started filling.");
    LOG4CXX_INFO(log_, "    Flow rate: " << flowRate_ << "L/minute.");
    LOG4CXX_INFO(log_, "    Temperature: " << temperature_ << " degrees C.");
  }
  else {
    if (temperature < 0 || temperature > 50) {
      LOG4CXX_WARN(log_, "*** Water temperature must be greater than 0 and less than "
          << "or equal to 50.");
    }
    if (flowRate < 0) {
      LOG4CXX_WARN(log_, "*** Flow rate must be positive.");
    }
  }

  LOG4CXX_TRACE(log_, "<-- Bath::turnOn()");
}

/*
 * Action method for bath.
 */
bool Bath::action(const std::string& actions)
{
  LOG4CXX_TRACE(log_, "--> Bath::action(const std::string&)");
  bool noerror = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);

  // Takes 3 arguments, start rate-per-tick water-temp
  if (argc == 3) {
    if (strcmp(BATH_START, argv[0]) == 0) {
      turnOn(atof(argv[1]), atof(argv[2]));
      isFilling_ = true;
    }
    else {
      noerror = false;
      LOG4CXX_WARN(log_, "*** Bath action " << argv[0] << " not recognized.");
    }
  }
  else {
    noerror = false;
    if (argc == 0) {
      LOG4CXX_WARN(log_, "*** Bath needs one argument, see documentation for usage.");
    }
    else {
      LOG4CXX_WARN(log_, "*** Bath takes one argument, see documentation for usage.");
    }
  }

  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log_, "<-- Bath::action(const std::string&)");
  return noerror;
}
/*
 * Unused function inherited from Model.
 */
double Bath::getEnergy() const
{
  return 0;
}
/*
 * Unused function inherited from Model.
 */
double Bath::getPower() const
{
  return 0.0;
}
