#include "Television.h"
#include "Scheduler.h"

log4cxx::LoggerPtr Television::log(log4cxx::Logger::getLogger("Television"));

// default constructor for Television, starts in off state
Television::Television()
{
  LOG4CXX_TRACE(log, "--> Entering Television constructor.");

  state_ = false;
  totalTimeOn_ = 0;
  totalTimeOff_ = 0;
  totalTicks_ = 0;

  LOG4CXX_TRACE(log, "<-- Exiting Television constructor.");
}

// turns television off
void Television::turnOff()
{
  LOG4CXX_TRACE(log, "--> Entering Television::turnOff()");

  if (isOn()) { // the television is on.
    state_ = false;

    LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the television was turned off. Total energy used: "
        << getEnergy() << ".");
  }

  LOG4CXX_TRACE(log, "<-- Exiting Television::turnOn()");
}

// turns television on
void Television::turnOn()
{
  LOG4CXX_TRACE(log, "--> Entering Television::turnOff()");

  if (!isOn()) { // the television is off.
    state_ = true;

    LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the television was turned on.");
  }

  LOG4CXX_TRACE(log, "<-- Exiting Television::turnOff()");
}

// checks if television is on
bool Television::isOn() const
{
  return state_;
}

// returns the total energy used by television
double Television::getEnergy() const
{
  return totalTimeOn_ * TELEVISION_ON_POWER + totalTimeOff_
      * TELEVISION_OFF_POWER;
}

// increments tick counter and either the on or off time as appropriate
void Television::tick()
{
  LOG4CXX_TRACE(log, "--> Entering Television::tick()");

  if (isOn()) { // television is on
    totalTimeOn_ += 1;
  }
  else { // television is off
    totalTimeOff_ += 1;
  }
  totalTicks_ += 1;

  LOG4CXX_TRACE(log, "<-- Exiting Television::tick()");
}

// returns total time the television has been on
int Television::getTotalTimeOn() const
{
  LOG4CXX_TRACE(log, "<-> Total time on is: " << totalTimeOn_ << ".");
  return totalTimeOn_;
}

// returns total time the television has been off
int Television::getTotalTimeOff() const
{
  LOG4CXX_TRACE(log, "<-> Total time off is: " << totalTimeOff_ << ".");
  return totalTimeOff_;
}

// returns total number of ticks that have passed
int Television::getTotalTicks() const
{
  LOG4CXX_TRACE(log, "<-> " << totalTicks_ << " total ticks have passed.");
  return totalTicks_;
}

// returns instantaneous power usage
double Television::getPower() const
{
  if (isOn()) { // television is on
    LOG4CXX_TRACE(log, "<-> The instantaneous power usage of television is " << TELEVISION_ON_POWER << "at tick " << getTotalTicks() << ".");
    return TELEVISION_ON_POWER;
  }
  else { // television is off
    LOG4CXX_TRACE(log, "<-> The instantaneous power usage of television is " << TELEVISION_OFF_POWER << "at tick " << getTotalTicks() << ".");
    return TELEVISION_OFF_POWER;
  }
}
