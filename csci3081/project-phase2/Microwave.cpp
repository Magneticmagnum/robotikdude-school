#include "Microwave.h"
#include "Scheduler.h"

#include <cstdlib>

log4cxx::LoggerPtr Microwave::log(log4cxx::Logger::getLogger("Microwave"));

Microwave::Microwave() :
  running_(false), onTimeLeft_(0), timeRunning_(0)
{
}

void Microwave::tick()
{
  LOG4CXX_TRACE(log, "--> Entering Microwave tick method.");
  if (running_) {
    LOG4CXX_TRACE(log, "    Microwave is running and has " << onTimeLeft_
        << " minutes to go.");
    onTimeLeft_ -= 1.0;
    timeRunning_ += 1.0;
    if (onTimeLeft_ <= 0.0) {
      timeRunning_ += onTimeLeft_;
      LOG4CXX_TRACE(log, "    DING! Microwave is done! Total run time so"
          " far is " << timeRunning_ << " minutes");
      running_ = false;
      LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the microwave was turned off. Total energy used: "
          << getEnergy() << ".");
    }
  }
  LOG4CXX_TRACE(log, "<-- Exiting Microwave tick method.");
}

double Microwave::getPower() const
{
  return (running_ ? MICROWAVE_POWER : 0.0);
}

double Microwave::getEnergy() const
{
  return timeRunning_ * MICROWAVE_POWER;
}

void Microwave::turnOn()
{
  if (!running_) {
    running_ = true;
    onTimeLeft_ = (MICROWAVE_MAX_TIME - MICROWAVE_MIN_TIME) * (rand()
        / (double) RAND_MAX) + MICROWAVE_MIN_TIME;
    LOG4CXX_DEBUG(log, "    Microwave has turned on for " << onTimeLeft_ << " minutes");
    LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the microwave was turned on");
  }
  else {
    LOG4CXX_ERROR(log, "!!! Microwave is already running!");
  }
}

bool Microwave::isRunning() const
{
  return running_;
}
