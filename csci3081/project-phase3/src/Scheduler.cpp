#include "Scheduler.h"

#include <sstream> // stringstring
//
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
  return ticksPassed_ % MINUTES_PER_HOUR;
}

int Scheduler::getHour() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getHour()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getHour()");
  return (ticksPassed_ / MINUTES_PER_HOUR) % HOURS_PER_DAY;
}

int Scheduler::getDay() const
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getDay()");
  LOG4CXX_TRACE(log_, "<-- Scheduler::getDay()");
  return ticksPassed_ / MINUTES_PER_DAY;
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
    double power = 0;
    double energy = 0;

    for (int j = 0; j < modelList_.size(); j++) {
      Model* m = modelList_.at(j);
      m->tick();
      power += m->getPower();
      energy += m->getEnergy();
    }
    power /= 1000; // W to kW
    energy /= (1000 * SECONDS_PER_HOUR); // J to kWh
    LOG4CXX_INFO(log_, getTimeStr() << " Power: " << power << " kW, energy used: " << energy << " kWh");
  }
  LOG4CXX_TRACE(log_, "<-- Scheduler::run(int)");
}
