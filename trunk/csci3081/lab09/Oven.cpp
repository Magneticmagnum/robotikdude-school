#include "Oven.h"

// creates oven, starts in off state.
Oven::Oven()
{
  totalTicks_ = 0;
  totalPreheatTime_ = 0;
  totalBakingTime_ = 0;
  isRunning_ = false;
}

// Increments number of ticks passed and, if the oven has been turned
// on, it will increment either the number of preheating or baking ticks
// depending on where it is in the cycle.  Once the preheat-baking cycle
// is completed, it turns the oven off.
void Oven::tick()
{
  totalTicks_ += 1;

  if (isOn()) { // oven is running
    if (stateCounter_ < 10) { // oven is preheating (10 ticks)
      totalPreheatTime_ += 1;
    }
    else if (stateCounter_ < 40) { // oven is baking (30 ticks)
      totalBakingTime_ += 1;
    }
    else { // oven has finished its cycle
      isRunning_ = false;
    }
    stateCounter_ += 1;
  }
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
  return 0.0;
}
