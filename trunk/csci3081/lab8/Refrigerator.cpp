#include "Refrigerator.h"

#include <log4cxx/logger.h>

Refrigerator::Refrigerator() :
  scheduler_(0), running_(true), tStateSwitch_(0), totalRunningTime_(0)
{
  static log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Refrigerator"));
  LOG4CXX_DEBUG(log, "Initializing a refrigerator without a scheduler.");
}

Refrigerator::Refrigerator(Scheduler* scheduler) :
  scheduler_(scheduler), running_(true), tStateSwitch_(0), totalRunningTime_(0)
{
  static log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Refrigerator"));
  LOG4CXX_DEBUG(log, "Initializing a refrigerator with a scheduler.");
}

void Refrigerator::tick()
{
  static log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Refrigerator"));
  LOG4CXX_DEBUG(log, "Starting tick on refrigerator...");

  LOG4CXX_DEBUG(log, "  update time since state switch.");
  tStateSwitch_++;
  if (running_) {
    LOG4CXX_DEBUG(log, "  running_ = true");
    totalRunningTime_++;
    if (tStateSwitch_ >= 3) {
      LOG4CXX_DEBUG(log, "  refrigerator has been running for long enough, turning off.");
      tStateSwitch_ = 0;
      running_ = false;

      if (scheduler_ != 0) {
        LOG4CXX_INFO(log, "(" << scheduler_->getTime() << ") Refrigerator"
            " turning off. Total energy used by refrigerator: " << getEnergy()
            << ".");
      }
      else {
        LOG4CXX_INFO(log, "Refrigerator turning off. Total energy used by"
            " refrigerator: " << getEnergy() << ".");
      }
    }
  }
  else {
    LOG4CXX_DEBUG(log, "  running_ = false");
    if (tStateSwitch_ >= 9) {
      LOG4CXX_DEBUG(log, "  refrigerator has been off for long enough, turning on.");
      tStateSwitch_ = 0;
      running_ = true;

      if (scheduler_ != 0) {
        LOG4CXX_INFO(log, "(" << scheduler_->getTime() << ") Refrigerator"
            " turning on.");
      }
      else {
        LOG4CXX_INFO(log, "Refrigerator turning on.");
      }
    }
  }
}

double Refrigerator::getPower() const
{
  return REFRIGERATOR_POWER;
}

double Refrigerator::getEnergy() const
{
  return getPower() * totalRunningTime_;
}

bool Refrigerator::isRunning() const
{
  return running_;
}
