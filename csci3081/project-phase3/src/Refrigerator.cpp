#include "Refrigerator.h"
#include "ConfigurationOptions.h"

log4cxx::LoggerPtr
    Refrigerator::log_(log4cxx::Logger::getLogger("Refrigerator"));

Refrigerator::Refrigerator(ConfigMap* config, Scheduler* scheduler,
                           Random* random) :
  power_(REFRIGERATOR_DEFAULT_POWER), energy_(0), running_(true),
      inUse_(false), tStateSwitch_(0), totalRunningTime_(0), scheduler_(scheduler),
      random_(random), onTime_(REFRIGERATOR_DEFAULT_ON_TIME),
      usageCycle_(REFRIGERATOR_DEFAULT_USE_CYCLE),
      dutyCycle_(REFRIGERATOR_DEFAULT_DUTY_CYCLE)
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::Refrigerator(ConfigMap*, Scheduler*)");

  initializeConfiguration(config);

  running_ = (random_->normal() > 0.5 ? true : false);
  LOG4CXX_DEBUG(log_, "    Refrigerator created " << (running_ ? "" : "not ") << "running");

  tStateSwitch_ = random_->normal() * 10;
  LOG4CXX_DEBUG(log_, "    Refrigerator created with time since last state switch being " << tStateSwitch_);

  LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Refrigerator created: power = " << power_ << ", on-time = " << onTime_ << ", duty-cycle = " << dutyCycle_ << ", usage-cycle = " << usageCycle_);

  LOG4CXX_TRACE(log_, "<-- Refrigerator::Refrigerator(ConfigMap*, Scheduler*)");
}

void Refrigerator::initializeConfiguration(ConfigMap* config)
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::initializeConfiguration(ConfigMap*)");

  if (config == 0) {
    LOG4CXX_TRACE(log_, "    No configuration given, using the default values");
  }
  else {
    ConfigMap::iterator iter;
    for (iter = config->begin(); iter != config->end(); iter++) {

      // configure power
      if (strcmp(iter->first, REFRIGERATOR_POWER) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          power_ = temp;
          LOG4CXX_DEBUG(log_, "    Refrigerator's power loaded from file: " << power_);
        }
        else {
          LOG4CXX_WARN(log_, "*** Refrigerator's " << REFRIGERATOR_POWER << " attribute must be greater then zero, given " << iter->second);
        }
      }

      // configure on-time
      else if (strcmp(iter->first, REFRIGERATOR_ON_TIME) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          onTime_ = temp;
          LOG4CXX_DEBUG(log_, "    Refrigerator's on time loaded from file: " << onTime_);
        }
        else {
          LOG4CXX_WARN(log_, "*** Refrigerator's " << REFRIGERATOR_ON_TIME << " attribute must be greater then zero, given " << iter->second);
        }
      }

      // configure duty-cycle
      else if (strcmp(iter->first, REFRIGERATOR_DUTY_CYCLE) == 0) {
        double temp = atof(iter->second);
        if (temp <= 1 && temp > 0) {
          dutyCycle_ = temp;
          LOG4CXX_DEBUG(log_, "    Refrigerator's duty cycle loaded from file: " << dutyCycle_);
        }
        else {
          LOG4CXX_WARN(log_, "*** Refrigerator's " << REFRIGERATOR_DUTY_CYCLE << " attribute must be greater then zero and less then or equal one, given " << iter->second);
        }
      }

      // configure usage-cycle
      else if (strcmp(iter->first, REFRIGERATOR_USAGE_CYCLE) == 0) {
        double temp = atof(iter->second);
        if (temp <= 1 && temp > 0) {
          usageCycle_ = temp;
          LOG4CXX_DEBUG(log_, "    Refrigerator's usage cycle loaded from file: " << usageCycle_);
        }
        else {
          LOG4CXX_WARN(log_, "*** Refrigerator's " << REFRIGERATOR_USAGE_CYCLE << " attribute must be greater then zero and less then or equal one, given " << iter->second);
        }
      }

      // unknown configure option
      else {
        LOG4CXX_WARN(log_, "*** The Refrigerator attribute " << iter->first << " was not recognized");
      }

    } // end for
  } // end if (config == 0) else

  LOG4CXX_TRACE(log_, "<-- Refrigerator::initializeConfiguration(ConfigMap*)");
}

void Refrigerator::tick()
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::tick()");

  tStateSwitch_++;
  if (running_) {
    totalRunningTime_++;
    energy_ += power_ * SECONDS_PER_TICK;
    if (tStateSwitch_ >= onTime_ && ((!inUse_ && dutyCycle_ != 1.0) || (inUse_
        && usageCycle_ != 1.0))) {
      tStateSwitch_ = 0;
      running_ = false;

      LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Refrigerator was turned off. Total energy used: " << getEnergy());
    }
  }
  else {
    if ((!inUse_ && tStateSwitch_ + onTime_ >= (int) (onTime_ / dutyCycle_))
        || (inUse_ && tStateSwitch_ + onTime_ >= (int) (onTime_ / usageCycle_))) {
      tStateSwitch_ = 0;
      running_ = true;

      LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Refrigerator was turned on");
    }
  }

  LOG4CXX_TRACE(log_, "<-- Refrigerator::tick()");
}

double Refrigerator::getPower() const
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::getPower()");
  LOG4CXX_DEBUG(log_, "    Refrigerator is currently using " << (running_ ? power_ : 0.0) << " Watts of power");
  LOG4CXX_TRACE(log_, "<-- Refrigerator::getPower()");
  return (running_ ? power_ : 0.0);
}

double Refrigerator::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::getEnergy()");
  LOG4CXX_DEBUG(log_, "    Refrigerator has used " << energy_ << " Joules of energy");
  LOG4CXX_TRACE(log_, "<-- Refrigerator::getEnergy()");
  return energy_;
}

bool Refrigerator::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::isRunning()");
  LOG4CXX_DEBUG(log_, "    Refrigerator is currently " << (running_ ? "" : "not ") << "running");
  LOG4CXX_TRACE(log_, "<-- Refrigerator::isRunning()");
  return running_;
}

bool Refrigerator::action(const std::string& actions)
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::action(const std::string&)");
  bool noerror = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);
  if (argc == 1) {
    if (strcmp(REFRIGERATOR_START, argv[0]) == 0) {
      setInUse(true);
    }
    else if (strcmp(REFRIGERATOR_STOP, argv[0]) == 0) {
      setInUse(false);
    }
    else {
      noerror = false;
      LOG4CXX_WARN(log_, "*** Refrigerator action " << argv[0] << " not recognized, see documentation for usage");
    }
  }
  else {
    noerror = false;
    if (argc == 0) {
      LOG4CXX_WARN(log_, "*** Refrigerator needs one argument, see documentation for usage");
    }
    else {
      LOG4CXX_WARN(log_, "*** Refrigerator only takes one action, given " << argc << ": [" << actions << "], see documentation for usage");
    }
  }
  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log_, "<-- Refrigerator::action(const std::string&)");
  return noerror;
}

void Refrigerator::setInUse(bool usage)
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::setInUse(bool = " << usage << ")");
  inUse_ = usage;
  LOG4CXX_DEBUG(log_, "    Refrigerator is now set to be currently " << (inUse_ ? "" : "not ") << "in use");
  LOG4CXX_TRACE(log_, "<-- Refrigerator::setInUse(bool = " << usage << ")");
}
