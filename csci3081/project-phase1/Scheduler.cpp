#include "Scheduler.h"
#include <sstream>
using std::stringstream;

#include <iostream>
using std::cout;

Scheduler::Scheduler() :
  logFile_(0), ticksPassed_(0), modelList_(vector<Model*> ())
{
}

bool Scheduler::registerModel(Model* thing)
{
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

void Scheduler::setLog(Logger* log)
{
  logFile_ = log;
}

void Scheduler::run(int maxCount)
{
  int i;
  int j;

  //Run the simulation until maxCount of ticks is reached.
  for (i = 0; i < maxCount; i++) {

    //Update the tick counter
    ticksPassed_++;

    //Convert the number of ticks passed to a string.
    string ticksString = "Current tick count is ";

    stringstream out;
    out << ticksPassed_;
    ticksString.append(out.str());
    ticksString.append(".");

    //Print tick count to log
    logFile_->print(ticksString);

    //Call tick() for each model in modelList_
    for (j = 0; j < modelList_.size(); j++) {
      modelList_.at(j)->tick();
    }
  }
}
