#include "Scheduler.h"

#include <sstream> // std::stringstring

log4cxx::LoggerPtr Scheduler::log_(log4cxx::Logger::getLogger("Scheduler"));
Scheduler* Scheduler::singleton_ = 0;

Scheduler* Scheduler::getInstance()
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getInstance()");
  if (singleton_ == 0) {
    singleton_ = new Scheduler();
    LOG4CXX_DEBUG(log_, "    Creating the singleton instance of Scheduler");
  }
  LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance()");
  return singleton_;
}

Scheduler::Scheduler() :
  ticksPassed_(0), modelList_(std::vector<Model*>())
{
  LOG4CXX_TRACE(log_, "--> Scheduler::Scheduler()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::Scheduler()");
}

bool Scheduler::registerModel(Model* thing)
{
  LOG4CXX_TRACE(log_, "--> Scheduler::registerModel(Model*)");
  modelList_.push_back(thing);
  LOG4CXX_TRACE(log_, "<-- Scheduler::registerModel(Model*)");
  return true;
}

void Scheduler::reset()
{
  LOG4CXX_TRACE(log_, "--> Scheduler::reset()");
  modelList_.clear();
  ticksPassed_ = 0;
  LOG4CXX_TRACE(log_, "<-- Scheduler::reset()");
}

int Scheduler::getTime() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getTime()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getTime()");
  return ticksPassed_;
}

int Scheduler::getMinute() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getTime()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getTime()");
  return ticksPassed_ % 60;
}

int Scheduler::getHour() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getHour()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getHour()");
  return (ticksPassed_ / 60) % 24;
}

int Scheduler::getDay() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getDay()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getDay()");
  return ticksPassed_ / 1440;
}

std::string Scheduler::getTimeStr() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getTimeStr()");
  std::stringstream ss;
  ss << "(" << (getDay() < 10 ? "0" : "") << getDay() << ":" << (getHour() < 10
      ? "0" : "") << getHour() << ":" << (getMinute() < 10 ? "0" : "")
      << getMinute() << ")";
  LOG4CXX_TRACE(log_, "<-- Scheduler::getTimeStr()");
  return ss.str();
}

int Scheduler::getModels() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getModels()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getModels()");
  return modelList_.size();
}

std::vector<Model*> Scheduler::getList() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getList()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getList()");
  return modelList_;
}

void Scheduler::run(int duration)
{
  LOG4CXX_TRACE(log_, "--> Scheduler::run(int)");

  for (int i = 0; i < duration; i++) {
    ticksPassed_++;
    for (int j = 0; j < modelList_.size(); j++) {
      modelList_.at(j)->tick();
    }
    LOG4CXX_DEBUG(log_, "    Current tick count is " << ticksPassed_ << ".");
  }
  LOG4CXX_TRACE(log_, "<-- Scheduler::run(int)");
}
