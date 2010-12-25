#include "Oven.h"
#include "Scheduler.h"

log4cxx::LoggerPtr Oven::log(log4cxx::Logger::getLogger("Oven"));

// creates oven, starts in off state.
Oven::Oven()
{
  LOG4CXX_TRACE(log, "--> Entering Oven Constructor.");

  totalTicks_ = 0;
  totalPreheatTime_ = 0;
  totalBakingTime_ = 0;
  isRunning_ = false;

  LOG4CXX_TRACE(log, "<-- Exiting Oven Constructor.");
}

// Increments number of ticks passed and, if the oven has been turned
// on, it will increment either the number of preheating or baking ticks
// depending on where it is in the cycle.  Once the preheat-baking cycle
// is completed, it turns the oven off.
void Oven::tick()
{
  LOG4CXX_TRACE(log, "--> Entering Oven::tick()");

  totalTicks_ += 1;

  if (isOn()) { // oven is running
    if (stateCounter_ < 10) { // oven is preheating (10 ticks)
      totalPreheatTime_ += 1;
    }
    else if (stateCounter_ < 39) { // oven is baking (30 ticks)
      totalBakingTime_ += 1;
    }
    else { // oven has finished its cycle
      totalBakingTime_ += 1;
      isRunning_ = false;
      LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the oven was turned off. Total energy used: "
          << getEnergy() << ".");
    }
    stateCounter_ += 1;
  }

  LOG4CXX_TRACE(log, "<-- Exiting Oven::tick()");
}

// checks if oven is on
bool Oven::isOn() const
{
  if (isRunning_) {// oven is off
    return true;
  }
  else { // oven is off
    return false;
  }
}

// turns oven on
void Oven::turnOn()
{
  if (!isRunning_) { // oven is off
    isRunning_ = true;
    stateCounter_ = 0;
    LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the dishwasher was turned on.");
  }
}

// returns total energy used by oven
double Oven::getEnergy() const
{
  return totalPreheatTime_ * PREHEATING_POWER + totalBakingTime_ * BAKING_POWER;
}

// returns total ticks
int Oven::getTicks() const
{
  return totalTicks_;
}

// returns total preheating ticks
int Oven::getPreheatTicks() const
{
  return totalPreheatTime_;
}

// returns total baking ticks
int Oven::getBakingTicks() const
{
  return totalBakingTime_;
}

// returns the state counter
int Oven::getCounter() const
{
  return stateCounter_;
}

// unused function inherited from Model
double Oven::getPower() const
{
  if (isOn()) { // oven is on
    if (stateCounter_ < 10) { // oven is preheating
      return 7500.0;
    }
    else { // oven is not preheating
      return 2500.0;
    }
  }
  else { // oven is off
    return 0.0;
  }
}
