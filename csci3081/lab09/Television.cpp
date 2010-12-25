#include "Television.h"

// default constructor for Television, starts in off state
Television::Television()
{
  state_ = false;
  totalTimeOn_ = 0;
  totalTimeOff_ = 0;
  totalTicks_ = 0;
}

// turns television off
void Television::turnOff()
{
  if (isOn()) { // the television is on.
    state_ = false;
  }
}

// turns television on
void Television::turnOn()
{
  if (!isOn()) { // the television is off.
    state_ = true;
  }
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
  if (isOn()) { // television is on
    totalTimeOn_ += 1;
  }
  else { // television is off
    totalTimeOff_ += 1;
  }
  totalTicks_ += 1;
}

// returns total time the television has been on
int Television::getTotalTimeOn() const
{
  return totalTimeOn_;
}

// returns total time the television has been off
int Television::getTotalTimeOff() const
{
  return totalTimeOff_;
}

// returns total number of ticks that have passed
int Television::getTotalTicks() const
{
  return totalTicks_;
}

// this function is not used
double Television::getPower() const
{
  return 0.0;
}
