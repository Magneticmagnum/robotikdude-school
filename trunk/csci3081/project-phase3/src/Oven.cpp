#include "Oven.h"
#include "Scheduler.h"
#include "ConfigurationOptions.h"

log4cxx::LoggerPtr Oven::log(log4cxx::Logger::getLogger("Oven"));

// creates oven, starts in off state.
/*Oven::Oven()
{
  LOG4CXX_TRACE(log, "--> Entering Oven Constructor.");

  totalPreheatTime_ = 0;
  totalBakingTime_ = 0;
  isRunning_ = false;
  bakeTime_ = DEFAULT_BAKE_TIME;

  LOG4CXX_TRACE(log, "<-- Exiting Oven Constructor.");
}*/

Oven::Oven(ConfigMap* config, Scheduler* sch_p)
{
  LOG4CXX_TRACE(log, "--> Oven(ConfigMap*, Scheduler*)");

  totalPreheatTime_ = 0;
  totalBakingTime_ = 0;
  isRunning_ = false;
  bakeTime_ = OVEN_DEFAULT_BAKE_TIME;

  initConfig(config);

  scheduler_ = sch_p;

  LOG4CXX_DEBUG(log, "    Oven created " << (isRunning_ ? "" : "not ")
                    << "running.");
  LOG4CXX_DEBUG(log, "    Preheat Power: " << OVEN_PREHEATING_POWER
                << ".");
  LOG4CXX_DEBUG(log, "    Baking Power: " << OVEN_BAKING_POWER << ".");
  LOG4CXX_DEBUG(log, "    Total time preheating: " << totalPreheatTime_
                << ".");
  LOG4CXX_DEBUG(log, "    Total time baking: " << totalBakingTime_<< ".");

  LOG4CXX_TRACE(log, "<-- Oven(ConfigMap*, Scheduler*)");
}

// TODO comment
void Oven::initConfig(ConfigMap* config)
{
  LOG4CXX_TRACE(log, "--> Oven::initConfig(ConfigMap*)");

  if(config == 0) { // no configuration file given, using default values.
    LOG4CXX_TRACE(log, "    No configuration file given.  Default values loaded.");
  }
  else {
    ConfigMap::iterator configIter;

    for(configIter = config->begin(); configIter != config->end(); configIter++) {
      if(strcmp(configIter->first, OVEN_BAKE_TIME) == 0) {
        // set bake time from configuration file
        int temp = atoi(configIter->second);
        if(temp > 0) { // baking time is valid.
          bakeTime_ = temp;
        }
        else { // invalid bake time in config file
          LOG4CXX_WARN(log, "*** The value for bake time, " << bakeTime_ << ", should be "
              "greater than zero.");
        }
      }
      else {
        LOG4CXX_WARN(log, "*** Oven attribute" << configIter->first << " is not recognized.");
      }
    }
  }
  LOG4CXX_TRACE(log, "<-- Oven::initConfig(ConfigMap*)");
}

// Increments number of ticks passed and, if the oven has been turned
// on, it will increment either the number of preheating or baking ticks
// depending on where it is in the cycle.  Once the preheat-baking cycle
// is completed, it turns the oven off.
void Oven::tick()
{
  LOG4CXX_TRACE(log, "--> Oven::tick()");

  if (isRunning()) { // oven is running
    if (isPreheated_ == false && stateCounter_ < OVEN_PREHEAT_TIME - 1) { // oven is preheating
      totalPreheatTime_ += 1;
    }
    else if (isPreheated_ == false && stateCounter_ == OVEN_PREHEAT_TIME - 1) {
      totalPreheatTime_ += 1;
      isPreheated_ = true;
      stateCounter_ = 0;
    }
    else if (isPreheated_ == true && stateCounter_ < bakeTime_) { // oven is baking
      totalBakingTime_ += 1;
    }
    else { // oven has finished its cycle
      totalBakingTime_ += 1;
      isRunning_ = false;
      LOG4CXX_INFO(log, "    At time " << scheduler_->getTimeStr()
          << " the oven was turned off. Total energy used: "
          << getEnergy() << ".");
    }
    stateCounter_ += 1;
  }

  LOG4CXX_TRACE(log, "<-- Oven::tick()");
}

bool Oven::action(const string& actions)
{
  LOG4CXX_TRACE(log, "--> Oven::action(const string&)");

  bool noError = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);

  if (argc == 1) { //
    if (strcmp(OVEN_START, argv[0]) == 0) {
      noError = turnOn();
    }
    else { // unrecognized argument
      noError = false;
      LOG4CXX_WARN(log, "*** Oven action " << argv[0] << " is not recognized.");
    }
  }
  else { // incorrect number of arguments
    noError = false;
    LOG4CXX_WARN(log, "*** Oven requires only a single argument.  See documentation.");
  }
  LOG4CXX_TRACE(log, "<-- Oven::action(const string&)");
  return noError;
}

// checks if oven is on
bool Oven::isRunning() const
{
  LOG4CXX_TRACE(log, "--> Oven::isRunning()");
  if (isRunning_) {// oven is off
    LOG4CXX_DEBUG(log, "    Oven is on.");
    LOG4CXX_TRACE(log, "<-- Oven::isRunning()");
    return true;
  }
  else { // oven is off
    LOG4CXX_DEBUG(log, "    Oven is off.");
    LOG4CXX_TRACE(log, "<-- Oven::isRunning()");
    return false;
  }
}

// turns oven on
bool Oven::turnOn()
{
  LOG4CXX_TRACE(log, "--> Oven::turnOn()");

  bool success = true;

  if (!isRunning_) { // oven is off
    isRunning_ = true;
    stateCounter_ = 0;
    isPreheated_ = false;
    LOG4CXX_INFO(log, "    At time " << scheduler_->getTimeStr()
        << " the dishwasher was turned on.");
  }
  else { // oven is already on
    success = false;
    LOG4CXX_WARN(log, "*** Cannot turn Oven on.  It is already on.");
  }
  LOG4CXX_TRACE(log, "<-- Oven::turnOn()");
  return success;
}

// returns total energy used by oven
double Oven::getEnergy() const
{
  double result = totalPreheatTime_ * OVEN_PREHEATING_POWER + totalBakingTime_ * OVEN_BAKING_POWER;
  LOG4CXX_TRACE(log, "--> Oven::getEnergy()");
  LOG4CXX_DEBUG(log, "    Energy = " << result << ".");
  LOG4CXX_TRACE(log, "<-> Oven::getEnergy()");
  return result * SECONDS_PER_TICK;
}

// returns total preheating ticks
int Oven::getPreheatTicks() const
{
  LOG4CXX_TRACE(log, "--> Oven::getPreheatTicks()");
  LOG4CXX_DEBUG(log, "    Preheat ticks = " << totalPreheatTime_ << ".");
  LOG4CXX_TRACE(log, "<-- Oven::getPreheatTicks()");
  return totalPreheatTime_;
}

// returns total baking ticks
int Oven::getBakingTicks() const
{
  LOG4CXX_TRACE(log, "--> Oven::getBakingTicks()");
  LOG4CXX_DEBUG(log, "    Baking ticks = " << totalBakingTime_ << ".");
  LOG4CXX_TRACE(log, "<-- Oven::getBakingTicks()");
  return totalBakingTime_;
}

// unused function inherited from Model
double Oven::getPower() const
{
  LOG4CXX_TRACE(log, "--> Oven::getPower()");
  if (isRunning()) { // oven is on
    if (isPreheated_) { // oven is finished preheating
      LOG4CXX_DEBUG(log, "Power usage is " << OVEN_BAKING_POWER << ".");
      LOG4CXX_TRACE(log, "<-- Exiting Oven::getPower()");
      return OVEN_BAKING_POWER;
    }
    else { // oven is preheating
      LOG4CXX_DEBUG(log, "Power usage is " << OVEN_PREHEATING_POWER << ".");
      LOG4CXX_TRACE(log, "<-- Oven::getPower()");
      return OVEN_PREHEATING_POWER;
    }
  }
  else { // oven is off
    LOG4CXX_DEBUG(log, "Power usage is 0.0.");
    LOG4CXX_TRACE(log, "<-- Oven::getPower()")
    return 0.0;
  }
}

// return total time baking
int Oven::getBakeTime() const
{
  LOG4CXX_TRACE(log, "--> Oven::getBakeTime()");
  LOG4CXX_DEBUG(log, "    Bake time is " << bakeTime_ << ".");
  LOG4CXX_TRACE(log, "<-- Oven::getBakeTime()");
  return bakeTime_;
}

// check whether the Oven is preheated
bool Oven::isPreheated() const
{
  LOG4CXX_TRACE(log, "--> Oven::isPreheated()");
  LOG4CXX_DEBUG(log, "    Oven is " << (isPreheated_ ? "preheated."
      : "not preheated."));
  LOG4CXX_TRACE(log, "<-- Oven::isPreheated().");

  return isPreheated_;
}

// return Scheduler*
Scheduler* Oven::getScheduler() const
{
  LOG4CXX_TRACE(log, "--> Oven::getScheduler()");
  LOG4CXX_TRACE(log, "<-- Oven::getScheduler()");
  return scheduler_;
}
