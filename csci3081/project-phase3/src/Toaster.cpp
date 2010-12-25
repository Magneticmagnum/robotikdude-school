#include "Toaster.h"
#include "ConfigurationOptions.h"

log4cxx::LoggerPtr
    Toaster::log_(log4cxx::Logger::getLogger("Toaster"));

/*
 * Creates a toaster, initializing running to false (toaster is off)
 * and sets the time it has been running to zero.
 */
Toaster::Toaster() {
  LOG4CXX_TRACE(log_, "--> Toaster::Toaster()");

  isRunning_ = false;
  timeRunning_ = 0;
  totalTimeRunning_ = 0;
  ticksPassed_ = 0;

  scheduler_ = Scheduler::getInstance();

  LOG4CXX_DEBUG(log_, "    Toaster created " << (isRunning_ ? "" : "not ")
                << "running.");
  LOG4CXX_DEBUG(log_, "    Time running this cycle: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Total time running: " << totalTimeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Ticks passed: " << ticksPassed_ << ".");
  LOG4CXX_TRACE(log_, "<-- Toaster::Toaster()");
}

Toaster::Toaster(Scheduler* scheduler) {
  LOG4CXX_TRACE(log_, "--> Toaster::Toaster(Scheduler* scheduler)");

  isRunning_ = false;
  timeRunning_ = 0;
  totalTimeRunning_ = 0;
  ticksPassed_ = 0;

  scheduler_ = scheduler;

  LOG4CXX_DEBUG(log_, "    Toaster created " << (isRunning_ ? "" : "not ")
                << "running.");
  LOG4CXX_DEBUG(log_, "    Time running this cycle: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Total time running: " << totalTimeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Ticks passed: " << ticksPassed_ << ".");
  LOG4CXX_TRACE(log_, "<-- Toaster::Toaster(Scheduler* scheduler)");
}

/*
 * Checks toaster state and executes proper toaster behavior.
 *
 * If the toaster is on and has not run for two minutes, update it's
 * current cycle running time and the total time it has been running.
 * Also updates global tick count.
 *
 * If the toaster is off, just updates the global tick count.
 */
void Toaster::tick() {
  LOG4CXX_TRACE(log_, "--> Toaster::tick()");

  ticksPassed_++;

  if (isRunning_) { //If the toaster is currently on...

    timeRunning_++;
    totalTimeRunning_++;

    if (timeRunning_ >= 2) { //Toaster has ran for 2 minutes and should turn off.
      isRunning_ = false;
      timeRunning_ = 0;

      LOG4CXX_INFO(log_, "    At time " << scheduler_->getTimeStr()
          << " the toaster was turned off. Total energy used: "
          << getEnergy() << ".");
    }
  }

  LOG4CXX_TRACE(log_, "<-- Toaster::tick()");
}

/*
 * Returns the total amount of power the toaster has used.
 */
double Toaster::getEnergy() const {
  LOG4CXX_TRACE(log_, "--> Toaster::getEnergy()");
  LOG4CXX_DEBUG(log_, "    Total energy used by toaster: " <<
                (totalTimeRunning_ * TOASTER_POWER) << ".");
  LOG4CXX_TRACE(log_, "<-- Toaster::tick()");

  return totalTimeRunning_ * TOASTER_POWER * SECONDS_PER_TICK;
}

/*
 * Returns the time the toaster has been running in
 * the current toast cycle.
 */
double Toaster::getCycleTime() const {
  LOG4CXX_TRACE(log_, "--> Toaster::getCycleTime()");
  LOG4CXX_DEBUG(log_, "    Toaster has been running for "
                << ticksPassed_ << " ticks this cycle.");
  LOG4CXX_TRACE(log_, "<-- Toaster::getCycleTime()");

  return timeRunning_;
}

/*
 * Returns the total amount of time the toaster has been running.
 */
double Toaster::getTotalTime() const {
  LOG4CXX_TRACE(log_, "--> Toaster::getTotalTime()");
  LOG4CXX_DEBUG(log_, "    Toaster has been running for "
                << ticksPassed_ << " ticks this simulation.");
  LOG4CXX_TRACE(log_, "<-- Toaster::getTotalTime()");

  return totalTimeRunning_;
}

/*
 * Returns the toaster's lifetime.
 */
double Toaster::getLifetime() const {
  LOG4CXX_TRACE(log_, "--> Toaster::getLifetime()");
  LOG4CXX_DEBUG(log_, "    Toaster has existed for "
                << ticksPassed_ << " ticks of the simulation.");
  LOG4CXX_TRACE(log_, "<-- Toaster::getLifetime()");

  return ticksPassed_;
}

/*
 * Returns if the toaster is running or not.
 */
bool Toaster::isRunning() const{
  LOG4CXX_TRACE(log_, "--> Toaster::isRunning()");
  LOG4CXX_DEBUG(log_, "    Toaster is currently " << (isRunning_ ? "" : "not ")
                << "running.");
  LOG4CXX_TRACE(log_, "<-- Toaster::isRunning()");
  return isRunning_;
}

/*
 * Turns on the toaster
 */
void Toaster::turnOn() {
  LOG4CXX_TRACE(log_, "--> Toaster::turnOn()");

  if (!isRunning_) {
    isRunning_ = true;

    LOG4CXX_INFO(log_, "    At time " << scheduler_->getTimeStr()
        << " the toaster was turned on.");
  }

  LOG4CXX_TRACE(log_, "<-- Toaster::turnOn()");
}

/*
 * Action method for the toaster.
 */
bool Toaster::action(const std::string& actions) {
  LOG4CXX_TRACE(log_, "--> Toaster::action(const std::string&)");
  bool noerror = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);

  //Check to see if arguments were entered in pairs of
  //'powerLevel cookTime'
  if (argc == 1) {
    if (strcmp(TOASTER_START, argv[0]) == 0) {
      turnOn();
    }
    else {
      noerror = false;
      LOG4CXX_WARN(log_, "*** Toaster action " << argv[0] << " not recognized");
    }
  }
  else {
    noerror = false;
    if (argc == 0) {
      LOG4CXX_WARN(log_, "*** Toaster needs one argument, see documentation for usage");
    }
    else {
      LOG4CXX_WARN(log_, "*** Toaster takes one argument, see documentation for usage.");
    }
  }

  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log_, "<-- Toaster::action(const std::string&)");
  return noerror;
}
/*
 * Unused function inherited from Model.
 */
double Toaster::getPower() const {
  return 0.0;
}
