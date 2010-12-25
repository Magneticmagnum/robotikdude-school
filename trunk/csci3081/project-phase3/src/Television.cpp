#include "Television.h"

log4cxx::LoggerPtr Television::log(log4cxx::Logger::getLogger("Television"));

// constructor
Television::Television(ConfigMap* config, Scheduler* scheduler)
{
  LOG4CXX_TRACE(log, "--> Television(ConfigMap*, Scheduler*) constructor.");

  state_ = false;
  totalTimeOn_ = 0;
  totalTimeOff_ = 0;

  onPower_ = TELEVISION_DEFAULT_ON_POWER;
  offPower_ = TELEVISION_DEFAULT_OFF_POWER;

  initConfig(config);
  LOG4CXX_DEBUG(log, "    Television created " << (state_ ? "" : "not ")
                  << "running.");
  LOG4CXX_DEBUG(log, "    On Power: " << onPower_ << ".");
  LOG4CXX_DEBUG(log, "    Off Power: " << offPower_ << ".");
  LOG4CXX_DEBUG(log, "    Total time on: " << totalTimeOn_ << ".");
  LOG4CXX_DEBUG(log, "    Total time off: " << totalTimeOff_ << ".");

  scheduler_ = scheduler;

  LOG4CXX_TRACE(log, "<-- Television(ConfigMap*, Scheduler*) constructor.");
}

// initialize power draw from config file
void Television::initConfig(ConfigMap* config)
{
  LOG4CXX_TRACE(log, "-->  Television::initConfig(ConfigMap*)");
  if (config == 0) {
    LOG4CXX_TRACE(log, "    No Configuration given; using default values");
  }
  else { // configuration given
    ConfigMap::iterator configIter;
    for (configIter = config->begin(); configIter != config->end(); configIter++) {
      if (strcmp(configIter->first, TELEVISION_ON_POWER) == 0) {
        double temp = atof(configIter->second);
        if (temp > 0) {
          onPower_ = temp;
        }
        else { // given value is not greater than zero
          LOG4CXX_WARN(log, "*** Television on power, " << configIter->second
              << ", should be greater than 0.");
        }
      }
      else if (strcmp(configIter->first, TELEVISION_OFF_POWER) == 0) {
        double temp = atof(configIter->second);
        if (temp > 0) {
          offPower_ = temp;
        }
        else { // given value is not greater than zero
          LOG4CXX_WARN(log, "*** Television off power, " << configIter->second
              << ", should be greater than 0.");
        }
      }
      else { // attribute not recognized
        LOG4CXX_WARN(log, "*** Television attribute " << configIter->first << " is not"
            "recognized.");
      }
    }
  }
  LOG4CXX_TRACE(log, "<-- Television::initConfig(ConfigMap*)");
}

bool Television::action(const string& actions)
{
  LOG4CXX_TRACE(log, "--> Television::action(const string&)");

  bool noError = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);

  if (argc == 1) {
    if (strcmp(TELEVISION_START, argv[0]) == 0) {
      noError = turnOn();
    }
    else if (strcmp(TELEVISION_STOP, argv[0]) == 0) {
      noError = turnOff();
    }
    else { // argument is not recognized
      noError = false;
      LOG4CXX_WARN(log, "*** Television action " << argv[0] << " is not recognized.");
    }
  }
  else { // improper number of arguments given
    noError = false;
    LOG4CXX_WARN(log, "*** Oven requires only a single argument.  See documentation.");
  }

  LOG4CXX_TRACE(log, "<-- Television::action(const string&)");
  return noError;
}

// turns television off
bool Television::turnOff()
{
  LOG4CXX_TRACE(log, "--> Television::turnOff()");

  bool success = true;

  if (isRunning()) { // the television is on.
    state_ = false;

    LOG4CXX_INFO(log, "    At time " << scheduler_->getTimeStr()
        << " the television was turned off. Total energy used: "
        << getEnergy() << ".");
  }
  else { // the television is already off
    success = false;
    LOG4CXX_WARN(log, "*** Attempt to turn Television off failed."
        "  Television is already off.");
  }
  LOG4CXX_TRACE(log, "<-- Television::turnOn()");
  return success;
}

// turns television on
bool Television::turnOn()
{
  LOG4CXX_TRACE(log, "--> Television::turnOff()");

  bool success = true;

  if (!isRunning()) { // the television is off.
    state_ = true;

    LOG4CXX_INFO(log, "    At time " << scheduler_->getTimeStr()
        << " the television was turned on.");
  }
  else { // the television is already on
    success = false;
    LOG4CXX_WARN(log, "*** Attempt to turn Television on failed."
        " Television is already on.");
  }

  LOG4CXX_TRACE(log, "<-- Television::turnOff()");
  return success;
}

// checks if television is on
bool Television::isRunning() const
{
  LOG4CXX_TRACE(log, "<-> Television::isRunning(). Television is " << (state_ ? "on." : "off."));
  return state_;
}

// returns the total energy used by television
double Television::getEnergy() const
{
  int result = totalTimeOn_ * onPower_ + totalTimeOff_ * offPower_;
  LOG4CXX_TRACE(log, "<-> Television::getEnergy(). Total energy used: " << result << ".");
  return result * SECONDS_PER_TICK;
}

// increments tick counter and either the on or off time as appropriate
void Television::tick()
{
  LOG4CXX_TRACE(log, "--> Television::tick()");

  if (isRunning()) { // television is on
    totalTimeOn_ += 1;
  }
  else { // television is off
    totalTimeOff_ += 1;
  }

  LOG4CXX_TRACE(log, "<-- Television::tick()");
}

// returns total time the television has been on
int Television::getTotalTimeOn() const
{
  LOG4CXX_TRACE(log, "<-> Television::getTotalTimeOn(). Total time on is: "
      << totalTimeOn_ << ".");
  return totalTimeOn_;
}

// returns total time the television has been off
int Television::getTotalTimeOff() const
{
  LOG4CXX_TRACE(log, "<-> Televison::getTotalTimeOff().  Total time off is: "
      << totalTimeOff_ << ".");
  return totalTimeOff_;
}

// returns instantaneous power usage
double Television::getPower() const
{
  if (isRunning()) { // television is on
    LOG4CXX_TRACE(log, "<-> Television::getPower(). The instantaneous power usage"
        " of television is " << TELEVISION_ON_POWER << "at tick " << scheduler_->getTimeStr()
        << ".");
    return onPower_;
  }
  else { // television is off
    LOG4CXX_TRACE(log, "<-> Television::getPower(). The instantaneous power usage "
        "of television is " << TELEVISION_OFF_POWER << "at tick " << scheduler_->getTimeStr()
        << ".");
    return offPower_;
  }
}

double Television::getOffPower() const
{
  return offPower_;
}

double Television::getOnPower() const
{
  return onPower_;
}

Scheduler* Television::getScheduler() const
{
  return scheduler_;
}
