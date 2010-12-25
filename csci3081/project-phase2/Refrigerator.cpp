#include "Refrigerator.h"
#include "Scheduler.h"
#include <cstdlib>

log4cxx::LoggerPtr
    Refrigerator::log_(log4cxx::Logger::getLogger("Refrigerator"));

Refrigerator::Refrigerator() :
  running_(true), inUse_(false), tStateSwitch_(0), totalRunningTime_(0)
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::Refrigerator()");

  running_ = (rand() > RAND_MAX / 2 ? true : false);
  LOG4CXX_DEBUG(log_, "    Refrigerator created " << (running_ ? "" : "not ")
      << "running.");

  tStateSwitch_ = rand() / (RAND_MAX / 10);
  LOG4CXX_DEBUG(log_, "    Refrigerator created with time since last state"
      " switch being " << tStateSwitch_ << ".");

  LOG4CXX_TRACE(log_, "<-- Refrigerator::Refrigerator()");
}

void Refrigerator::tick()
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::tick()");

  tStateSwitch_++;
  if (running_) {
    totalRunningTime_++;
    if (tStateSwitch_ >= 3) {
      tStateSwitch_ = 0;
      running_ = false;

      LOG4CXX_INFO(log_, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the refrigerator was turned off. Total energy used: "
          << getEnergy() << ".");
    }
  }
  else {
    if ((!inUse_ && tStateSwitch_ >= 7) || (inUse_ && tStateSwitch_ >= 3)) {
      tStateSwitch_ = 0;
      running_ = true;

      LOG4CXX_INFO(log_, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the refrigerator was turned on.");
    }
  }

  LOG4CXX_TRACE(log_, "<-- Refrigerator::tick()");
}

void Refrigerator::setInUse(bool usage)
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::setInUse(bool)");
  LOG4CXX_DEBUG(log_, "    Refrigerator is now set to be currently "
      << (usage ? "" : "not ") << "in use.");
  LOG4CXX_TRACE(log_, "<-- Refrigerator::setInUse(bool)");
  inUse_ = usage;
}

double Refrigerator::getPower() const
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::getPower()");
  LOG4CXX_DEBUG(log_, "    Refrigerator is currently using "
      << (running_ ? REFRIGERATOR_POWER : 0.0) << " Watts of power.");
  LOG4CXX_TRACE(log_, "<-- Refrigerator::getPower()");
  return (running_ ? REFRIGERATOR_POWER : 0.0);
}

double Refrigerator::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::getEnergy()");
  LOG4CXX_DEBUG(log_, "    Refrigerator has used "
      << (totalRunningTime_ * REFRIGERATOR_POWER)
      << " minute Watts of energy.");
  LOG4CXX_TRACE(log_, "--> Refrigerator::getEnergy()");
  return totalRunningTime_ * REFRIGERATOR_POWER;
}

bool Refrigerator::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> Refrigerator::isRunning()");
  LOG4CXX_DEBUG(log_, "    Refrigerator is currently "
      << (running_ ? "" : "not ") << "running.");
  LOG4CXX_TRACE(log_, "--> Refrigerator::isRunning()");
  return running_;
}
