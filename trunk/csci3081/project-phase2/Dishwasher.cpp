#include "WaterHeater.h"
#include "Dishwasher.h"
#include "Scheduler.h"

#include <cstdlib>

log4cxx::LoggerPtr Dishwasher::log(log4cxx::Logger::getLogger("Dishwasher"));

Dishwasher::Dishwasher()
{
  running_ = false;
  runningTimeLeft_ = 0;
  waterTimeLeft_ = 0;
  energyUsed_ = 0.0;
}

void Dishwasher::tick()
{
  LOG4CXX_TRACE(log, "--> Entering dishwasher's tick method.");
  if (running_) {
    runningTimeLeft_--;
    LOG4CXX_TRACE(log, " Dishwasher is running; has "
        << runningTimeLeft_ << " ticks left.");
    if (waterTimeLeft_ > 0) {
      ((WaterHeater*) getInstance(MODEL_WATERHEATER))-> getWater(
                                                           DISHWASHER_WATER_USAGE,
                                                           DISHWASHER_WATER_TEMP);
      waterTimeLeft_--;
      LOG4CXX_TRACE(log, " Dishwasher has "
          << waterTimeLeft_ << "ticks left of water usage.");
    }

    energyUsed_ += DISHWASHER_HIGH_POWER;

    if (runningTimeLeft_ <= 0) {
      runningTimeLeft_ = 0;
      running_ = false;
      LOG4CXX_TRACE(log, "Dishwasher has completed its cycle; turning off.");
      LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the dishwasher was turned off. Total energy used: "
          << getEnergy() << ".");
    }
  }
  else {
    energyUsed_ += DISHWASHER_LOW_POWER;
  }
  LOG4CXX_TRACE(log, "--> Exiting dishwasher's tick method.");
}

void Dishwasher::turnOn()
{
  LOG4CXX_TRACE(log, "Dishwasher has been activated.");
  if (!running_) {
    running_ = true;
    runningTimeLeft_ = DISHWASHER_CYCLE_DURATION;
    waterTimeLeft_ = DISHWASHER_WASH_CYCLE_DURATION;
    LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the dishwasher was turned on.");
  }
  else {
    LOG4CXX_ERROR(log,
        "!!! Tried to turn on dishwasher when it was already running.");
  }
}

double Dishwasher::getPower() const
{
  if (running_) {
    return DISHWASHER_HIGH_POWER;
  }
  else
    return DISHWASHER_LOW_POWER;
}

double Dishwasher::getEnergy() const
{
  return energyUsed_;
}

bool Dishwasher::isRunning() const
{
  return running_;
}

double Dishwasher::getRunningTimeLeft()
{
  return runningTimeLeft_;
}

double Dishwasher::getWaterTimeLeft()
{
  return waterTimeLeft_;
}
