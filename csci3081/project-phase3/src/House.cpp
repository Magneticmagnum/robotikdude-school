#include "House.h"
#include "Model.h"
#include "Scheduler.h"

log4cxx::LoggerPtr House::log_(log4cxx::Logger::getLogger("House"));

House::House(ConfigMap* config, Scheduler* scheduler) :
  scheduler_(scheduler)
{
  LOG4CXX_TRACE(log_, "--> House::House(configMap*, Scheduler*)");

  LOG4CXX_TRACE(log_, "    House created " << (!isRunning()? "not ": "") << " running.");
  LOG4CXX_TRACE(log_, "<-- House::House()");
}

void House::tick()
{
  LOG4CXX_TRACE(log_, "--> House::tick()");
  ModelMap::iterator modelItr = models_.begin();
  while (modelItr != models_.end()) {
    modelItr->second->tick();
    modelItr++;
  }
  LOG4CXX_TRACE(log_, "<-- House::tick()");
}

double House::getPower() const
{
  LOG4CXX_TRACE(log_, "--> House::getPower()");

  ModelMap::const_iterator modelItr = models_.begin();
  double totalPowerUsage = 0.0;

  while (modelItr != models_.end()) {
    totalPowerUsage += modelItr->second->getPower();
    modelItr++;
  }

  LOG4CXX_TRACE(log_, "    House's power usage: " << totalPowerUsage);
  LOG4CXX_TRACE(log_, "<-- House::getPower()");
  return totalPowerUsage;
}

double House::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> House::getEnergy()");

  ModelMap::const_iterator modelItr = models_.begin();
  double totalEnergyUsed = 0.0;

  while (modelItr != models_.end()) {
    totalEnergyUsed += modelItr->second->getEnergy();
    modelItr++;
  }
  LOG4CXX_TRACE(log_, "    House's energy usage: " << totalEnergyUsed);
  LOG4CXX_TRACE(log_, "<-- House::getEnergy()");

  return totalEnergyUsed;
}

bool House::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> House::isRunning()");

  bool isRunning = false;
  ModelMap::const_iterator modelItr = models_.begin();

  while (modelItr != models_.end()) {
    if (modelItr->second->isRunning()) {
      isRunning = true;
    }
    modelItr++;
  }
  LOG4CXX_TRACE(log_, "    House is " << (!isRunning? "not" : "") << " running. ");
  LOG4CXX_TRACE(log_, "<-- House::isRunning()");

  return isRunning;
}

bool House::action(const std::string& actions)
{
  return true;
}

bool House::addModel(const std::string& modelName, Model* newModel)
{
  LOG4CXX_TRACE(log_, "--> House::addModel()");

  ModelMap::iterator m = models_.find(modelName);
  if (m != models_.end()) {
    LOG4CXX_TRACE(log_, "<-- House::addModel()");
    return false;
  }
  else {
    models_[modelName] = newModel;
  }

  LOG4CXX_TRACE(log_, "<-- House::addModel()");
  return true;
}

Model* House::getModel(const std::string& modelName)
{
  LOG4CXX_TRACE(log_, "<-- House::getModel()");

  ModelMap::iterator m = models_.find(modelName);
  if (m != models_.end()) {
    LOG4CXX_TRACE(log_, "<-- House::getModel()");
    return m->second;
  }
  else {
    LOG4CXX_TRACE(log_, "<-- House::getModel()");
    return 0;
  }
}

bool House::removeModel(const std::string& modelName)
{
  LOG4CXX_TRACE(log_, "--> House::removeModel()");

  if (models_.erase(modelName)) {
    LOG4CXX_TRACE(log_, "<-- House::removeModel()");
    return true;
  }
  else {
    LOG4CXX_TRACE(log_, "<-- House::removeModel()");
    return false;
  }
}

