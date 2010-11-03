#include "Scheduler.h"

#include <log4cxx/logger.h>

Scheduler::Scheduler() :
  ticksPassed_(0), modelList_(vector<Model*> ())
{
  static log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Scheduler"));
  LOG4CXX_DEBUG(log, "Initializing Scheduler.");
}

bool Scheduler::registerModel(Model* thing)
{
  static log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Scheduler"));
  LOG4CXX_DEBUG(log, "Registering model to vector.");

  modelList_.push_back(thing);
  return true;
}

int Scheduler::getTime() const
{
  return ticksPassed_;
}

int Scheduler::getModels() const
{
  return modelList_.size();
}

vector<Model*> Scheduler::getList() const
{
  return modelList_;
}

void Scheduler::run(int maxCount)
{
  static log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Scheduler"));

  int i;
  int j;

  //Run the simulation until maxCount of ticks is reached.
  for (i = 0; i < maxCount; i++) {

    //Update the tick counter
    ticksPassed_++;

    //Print tick count to log
    LOG4CXX_INFO(log, "Current tick count is " << this->getTime() << ".");

    //Call tick() for each model in modelList_
    for (j = 0; j < modelList_.size(); j++) {
      LOG4CXX_DEBUG(log, "Executing tick for model " << j << ".");
      modelList_.at(j)->tick();
    }
  }
}
