#include "WaterHeater.h"
#include "Dishwasher.h"
#include "Scheduler.h"
#include "ConfigurationOptions.h"

#include <cstdlib>

log4cxx::LoggerPtr Dishwasher::log_(log4cxx::Logger::getLogger("Dishwasher"));

Dishwasher::Dishwasher() :
  running_(false), runningTimeLeft_(0), waterTimeLeft_(0), energyUsed_(0),
      scheduler_(0), house_(0), waterheater_("waterheater"),
      offPower_(DISHWASHER_OFF_POWER_DEFAULT),
      onPower_(DISHWASHER_ON_POWER_DEFAULT),
      waterUsage_(DISHWASHER_WATER_USAGE_DEFAULT),
      waterTemp_(DISHWASHER_WATER_TEMP_DEFAULT),
      cycleDuration_(DISHWASHER_CYCLE_DURATION_DEFAULT),
      washCycleDuration_(DISHWASHER_WASH_CYCLE_DURATION_DEFAULT)
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::Dishwasher()");

  LOG4CXX_DEBUG(log_, "    Dishwasher created with an off-cycle power draw of "
      << offPower_);
  LOG4CXX_DEBUG(log_, "    Dishwasher created with an on-cycle power draw of "
      << onPower_);
  LOG4CXX_DEBUG(log_, "    Dishwasher created with a water draw of " << offPower_
      << " liters.");
  LOG4CXX_DEBUG(log_, "    Dishwasher created to use water at " << offPower_
      << " degrees celsius.");
  LOG4CXX_DEBUG(log_, "    Dishwasher created with a running time of "
      << cycleDuration_);

  LOG4CXX_DEBUG(log_, "    Dishwasher created with a wash cycle of " << offPower_
      << " minutes.");

  LOG4CXX_DEBUG(log_, "    Dishwasher created. ");
  scheduler_ = Scheduler::getInstance();
  LOG4CXX_TRACE(log_, "<-- Dishwasher::Dishwasher()");
}

Dishwasher::Dishwasher(ConfigMap* config, Scheduler* scheduler, House* house)
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::Dishwasher(ConfigMap*, Scheduler*)");

  running_ = false;
  runningTimeLeft_ = 0.0;
  waterTimeLeft_ = 0.0;
  energyUsed_ = 0.0;
  onPower_ = DISHWASHER_ON_POWER_DEFAULT;
  offPower_ = DISHWASHER_OFF_POWER_DEFAULT;
  waterUsage_ = DISHWASHER_WATER_USAGE_DEFAULT;
  waterTemp_ = DISHWASHER_WATER_TEMP_DEFAULT;
  cycleDuration_ = DISHWASHER_CYCLE_DURATION_DEFAULT;
  washCycleDuration_ = DISHWASHER_WASH_CYCLE_DURATION_DEFAULT;
  scheduler_ = scheduler;
  house_ = house;
  waterheater_ = "waterheater";
  initializeConfiguration(config);

  LOG4CXX_DEBUG(log_, "    Dishwasher created with an off-cycle power draw of "
      << offPower_);
  LOG4CXX_DEBUG(log_, "    Dishwasher created with an on-cycle power draw of "
      << onPower_);
  LOG4CXX_DEBUG(log_, "    Dishwasher created with a water draw of " << offPower_
      << " liters.");
  LOG4CXX_DEBUG(log_, "    Dishwasher created to use water at " << offPower_
      << " degrees celsius.");
  LOG4CXX_DEBUG(log_, "    Dishwasher created with a running time of "
      << cycleDuration_);
  LOG4CXX_DEBUG(log_, "    Dishwasher created with a wash cycle of " << offPower_
      << " minutes.");
  LOG4CXX_DEBUG(log_, "    Dishwasher created. ");

  LOG4CXX_TRACE(log_, "<-- Dishwasher::Dishwasher(ConfigMap*, Scheduler*)");
}

void Dishwasher::initializeConfiguration(ConfigMap* config)
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::initializeConfiguration(ConfigMap*)");

  if (config == 0) {
    LOG4CXX_TRACE(log_, "    No configuration given, using the default values");
  }
  else {
    ConfigMap::iterator iter;
    for (iter = config->begin(); iter != config->end(); iter++) {

      if (strcmp(iter->first, DISHWASHER_ON_POWER) == 0) {
        double temp = atof(iter->second);
        if (temp > 0.0) {
          onPower_ = temp;
        }
        else {
          onPower_ = DISHWASHER_ON_POWER_DEFAULT;
          LOG4CXX_WARN(log_, "*** Dishwasher's " << DISHWASHER_ON_POWER <<
              " attribute must be greater then zero");
        }
      }

      if (strcmp(iter->first, DISHWASHER_OFF_POWER) == 0) {
        double temp = atof(iter->second);
        if (temp > 0.0 && temp < onPower_) {
          offPower_ = temp;
        }
        else {
          offPower_ = DISHWASHER_OFF_POWER_DEFAULT;
          LOG4CXX_WARN(log_, "*** Dishwasher's " << DISHWASHER_OFF_POWER <<
              " attribute must be greater than zero and less than "
              "it's running power.");
        }
      }

      if (strcmp(iter->first, DISHWASHER_RUN_TIME) == 0) {
        double temp = atof(iter->second);
        if (temp > 0.0) {
          cycleDuration_ = temp;
        }
        else {
          cycleDuration_ = DISHWASHER_CYCLE_DURATION_DEFAULT;
          LOG4CXX_WARN(log_, "*** Dishwasher's " << DISHWASHER_RUN_TIME <<
              " attribute must be greater than zero.");
        }
      }

      if (strcmp(iter->first, DISHWASHER_WATER_CYCLE_TIME) == 0) {
        double temp = atof(iter->second);
        if (temp > 0.0 && temp < cycleDuration_) {
          washCycleDuration_ = temp;
        }
        else {
          washCycleDuration_ = DISHWASHER_WASH_CYCLE_DURATION_DEFAULT;
          LOG4CXX_WARN(log_, "*** Dishwasher's " << DISHWASHER_WATER_CYCLE_TIME <<
              " attribute must be greater than zero and less than it's "
              "total cycle duration.");
        }
      }

      if (strcmp(iter->first, DISHWASHER_WATER_VOLUME) == 0) {
        double temp = atof(iter->second);
        if (temp > 0.0) {
          waterUsage_ = temp;
        }
        else {
          waterUsage_ = DISHWASHER_WATER_USAGE_DEFAULT;
          LOG4CXX_WARN(log_, "*** Dishwasher's " << DISHWASHER_WATER_VOLUME <<
              " attribute must be greater than zero.");
        }
      }

      if (strcmp(iter->first, DISHWASHER_WATER_TEMP) == 0) {
        double temp = atof(iter->second);
        if (temp > 7.0) {
          waterTemp_ = temp;
        }
        else {
          waterTemp_ = DISHWASHER_WATER_TEMP_DEFAULT;
          LOG4CXX_WARN(log_, "*** Dishwasher's " << DISHWASHER_WATER_TEMP <<
              " attribute must be greater than 7 degrees celsius.");
        }
      }

    }
  }
  LOG4CXX_TRACE(log_, "<-- Dishwasher::initializeConfiguration(ConfigMap*)");
}

void Dishwasher::tick()
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::tick()");
  WaterHeater* waterheater = (WaterHeater*) house_->getModel(waterheater_);
  if (running_) {
    runningTimeLeft_--;
    LOG4CXX_TRACE(log_, "   Dishwasher is running; has " << runningTimeLeft_ << " ticks left.");
    if (waterTimeLeft_ > 0) {
      if (waterheater != 0) {
        waterheater->getWater((waterUsage_ / washCycleDuration_), waterTemp_);
      }
      waterTimeLeft_--;
      LOG4CXX_TRACE(log_, "   Dishwasher has " << waterTimeLeft_ << "ticks left of water usage.");
    }

    energyUsed_ += onPower_ * SECONDS_PER_TICK;

    if (runningTimeLeft_ <= 0) {
      runningTimeLeft_ = 0;
      running_ = false;
      LOG4CXX_TRACE(log_, "   Dishwasher has completed its cycle; turning off.");
      LOG4CXX_INFO(log_, "   At time " << scheduler_->getTimeStr() <<
          " the dishwasher was turned off. Total energy used: " << getEnergy() << ".");
    }
  }
  else {
    energyUsed_ += offPower_ * SECONDS_PER_TICK;
  }
  LOG4CXX_TRACE(log_, "<-- Dishwasher::tick()");
}

bool Dishwasher::turnOn()
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::turnOn()");
  if (!running_) {
    running_ = true;
    runningTimeLeft_ = cycleDuration_;
    waterTimeLeft_ = washCycleDuration_;
    LOG4CXX_INFO(log_, "   At time " << scheduler_->getTimeStr() << " the dishwasher was turned on.");
    return true;
  }
  else {
    LOG4CXX_WARN(log_, "*** Tried to turn on dishwasher when it was already running.");
    return false;
  }
  LOG4CXX_TRACE(log_, "<-- Dishwasher::turnOn()");
}

double Dishwasher::getPower() const
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::getPower()");
  LOG4CXX_TRACE(log_, "    Dishwasher is currently using " << (running_ ? onPower_ : offPower_) << " watts of power.");
  LOG4CXX_TRACE(log_, "<-- Dishwasher::getPower()");
  if (running_) {
    return onPower_;
  }
  else
    return offPower_;
}

double Dishwasher::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::getEnergy()");
  LOG4CXX_TRACE(log_, "<-- Dishwasher::getEnergy()");
  return energyUsed_;
}

bool Dishwasher::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::isRunning()");
  LOG4CXX_DEBUG(log_, "    Dishwasher is currently " << (running_ ? "" : "not ") << "running");
  LOG4CXX_TRACE(log_, "<-- Dishwasher::isRunning()");
  return running_;
}

double Dishwasher::getRunningTimeLeft()
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::getRunningTimeLeft()");
  LOG4CXX_TRACE(log_, "<-- Dishwasher::getRunningTimeLeft()");
  return runningTimeLeft_;
}

double Dishwasher::getWaterTimeLeft()
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::getWaterTimeLeft()");
  LOG4CXX_TRACE(log_, "<-- Dishwasher::getWaterTimeLeft()");
  return waterTimeLeft_;
}

bool Dishwasher::action(const std::string& actions)
{
  LOG4CXX_TRACE(log_, "--> Dishwasher::action(const std::string&)");
  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);
  if (argc == 1) {
    if (strcmp(DISHWASHER_START, argv[0]) == 0) {
      if (!turnOn()) {
        LOG4CXX_WARN(log_, "*** Dishwasher is already running.");
        return false;
      }
    }
    else {
      LOG4CXX_WARN(log_, "*** Dishwasher action " << argv[0] << " not recognized");
      return false;
    }
  }
  else {
    if (argc == 0) {
      LOG4CXX_WARN(log_, "*** Dishwasher needs one argument, got zero args. See documentation for usage");
    }
    else {
      LOG4CXX_WARN(log_, "*** Dishwasher only takes one action, given " << argc << ": [" << actions << "], see documentation for usage");
    }
    return false;
  }
  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log_, "<-- Dishwasher::action(const std::string&)");
  return true;
}
