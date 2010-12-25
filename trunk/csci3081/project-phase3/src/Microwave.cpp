#include "Microwave.h"
#include "ConfigurationOptions.h" // strcmp
//
log4cxx::LoggerPtr Microwave::log_(log4cxx::Logger::getLogger("Microwave"));

Microwave::Microwave(ConfigMap* configuration, Scheduler* scheduler,
                     House* house, Random* random) :
  scheduler_(scheduler), random_(random), running_(false), onTimeLeft_(0),
      energy_(0), power_(MICROWAVE_DEFAULT_POWER),
      minTime_(MICROWAVE_DEFAULT_MIN_TIME),
      maxTime_(MICROWAVE_DEFAULT_MAX_TIME)
{
  LOG4CXX_TRACE(log_, "--> Microwave::Microwave(ConfigMap*, Scheduler*)");

  initializeConfiguration(configuration);

  LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Microwave created: power = " << power_ << ", min-time = " << minTime_ << ", max-time = " << maxTime_);

  LOG4CXX_TRACE(log_, "<-- Microwave::Microwave(ConfigMap*, Scheduler*)");
}
void Microwave::initializeConfiguration(ConfigMap* config)
{
  LOG4CXX_TRACE(log_, "--> Microwave::initializeConfiguration(ConfigMap*)");

  if (config == 0) {
    LOG4CXX_TRACE(log_, "    No configuration given, using the default values");
  }
  else {
    ConfigMap::iterator iter;
    for (iter = config->begin(); iter != config->end(); iter++) {

      // configure power
      if (strcmp(iter->first, MICROWAVE_POWER) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          power_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** Microwave's " << MICROWAVE_POWER << " attribute must be greater then zero");
        }
      }

      // configure min-time
      else if (strcmp(iter->first, MICROWAVE_MIN_TIME) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          minTime_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** Microwave's " << MICROWAVE_MIN_TIME << " attribute must be greater then zero");
        }
      }

      // configure max-time
      else if (strcmp(iter->first, MICROWAVE_MAX_TIME) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          maxTime_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** Microwave's " << MICROWAVE_MAX_TIME << " attribute must be greater then zero");
        }
      }

      // unknown configure option
      else {
        LOG4CXX_WARN(log_, "*** The Microwave attribute " << iter->first << " was not recognized");
      }

    } // end for
  } // end if (config == 0) else

  LOG4CXX_TRACE(log_, "<-- Microwave::initializeConfiguration(ConfigMap*)");
}

void Microwave::tick()
{
  LOG4CXX_TRACE(log_, "--> Entering Microwave tick method.");
  if (running_) {
    LOG4CXX_TRACE(log_, "    Microwave is running and has " << onTimeLeft_ << " minutes to go");
    onTimeLeft_ -= 1.0;
    energy_ += power_ * SECONDS_PER_TICK;
    if (onTimeLeft_ <= 0.0) {
      energy_ += power_ * onTimeLeft_ * SECONDS_PER_TICK;
      running_ = false;
      LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Microwave has turned off. Total energy used: " << energy_);
    }
  }
  LOG4CXX_TRACE(log_, "<-- Exiting Microwave tick method.");
}

double Microwave::getPower() const
{
  return (running_ ? power_ : 0.0);
}

double Microwave::getEnergy() const
{
  return energy_;
}

bool Microwave::turnOn()
{
  bool noerror = true;
  if (!running_) {
    running_ = true;
    onTimeLeft_ = (maxTime_ - minTime_) * random_->normal() + minTime_;
    LOG4CXX_DEBUG(log_, "    Microwave has turned on for " << onTimeLeft_ << " minutes");
    LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Microwave was turned on");
  }
  else {
    noerror = false;
    LOG4CXX_ERROR(log_, "!!! Microwave is already running!");
  }
  return noerror;
}

bool Microwave::isRunning() const
{
  return running_;
}

bool Microwave::action(const std::string& actions)
{
  LOG4CXX_TRACE(log_, "--> Microwave::action(const std::string&)");
  bool noerror = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);
  if (argc == 1) {
    if (strcmp(MICROWAVE_START, argv[0]) == 0) {
      noerror = turnOn();
    }
    else {
      noerror = false;
      LOG4CXX_WARN(log_, "*** Microwave action " << argv[0] << " not recognized, see documentation for usage");
    }
  }
  else {
    noerror = false;
    if (argc == 0) {
      LOG4CXX_WARN(log_, "*** Microwave needs one argument, see documentation for usage");
    }
    else {
      LOG4CXX_WARN(log_, "*** Microwave only takes one action, given " << argc << ": [" << actions << "], see documentation for usage");
    }
  }
  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log_, "<-- Microwave::action(const std::string&)");
  return noerror;
}
