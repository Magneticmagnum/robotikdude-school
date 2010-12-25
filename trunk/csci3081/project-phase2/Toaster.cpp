#include "Toaster.h"
#include "Scheduler.h"

/*
 * Creates a toaster, initializing running to false (toaster is off)
 * and sets the time it has been running to zero.
 */
Toaster::Toaster() {
  isRunning_ = false;
  timeRunning_ = 0;
  totalTimeRunning_ = 0;
  ticksPassed_ = 0;
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
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Toaster"));
  LOG4CXX_TRACE(log, "--> Toaster entering tick method.");

  ticksPassed_++;

  if (isRunning_) { //If the toaster is currently on...

    timeRunning_++;
    totalTimeRunning_++;

    if (timeRunning_ >= 2) { //Toaster has ran for 2 minutes and should turn off.
      isRunning_ = false;
      timeRunning_ = 0;

      LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the toaster was turned off. Total energy used: "
          << getEnergy() << ".");
    }
  }

  LOG4CXX_TRACE(log, "<-- Toaster exiting tick method.");
}

/*
 * Returns the total amount of power the toaster has used.
 */
double Toaster::getEnergy() const {
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Toaster"));
  LOG4CXX_TRACE(log, "<-> Total energy used by toaster: " <<
                (totalTimeRunning_ * TOASTER_POWER) << ".");

  return totalTimeRunning_ * TOASTER_POWER;
}

/*
 * Returns the time the toaster has been running in
 * the current toast cycle.
 */
double Toaster::getCycleTime() const {
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Toaster"));
  LOG4CXX_TRACE(log, "<-> Toaster has been running for "
                << ticksPassed_ << " ticks this cycle.");

  return timeRunning_;
}

/*
 * Returns the total amount of time the toaster has been running.
 */
double Toaster::getTotalTime() const {
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Toaster"));
  LOG4CXX_TRACE(log, "<-> Toaster has been running for "
                << ticksPassed_ << " ticks this simulation.");

  return totalTimeRunning_;
}

/*
 * Returns the toaster's lifetime.
 */
double Toaster::getLifetime() const {
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Toaster"));
  LOG4CXX_TRACE(log, "<-> Toaster has existed for "
                << ticksPassed_ << " ticks of the simulation.");

  return ticksPassed_;
}

/*
 * Returns if the toaster is running or not.
 */
bool Toaster::isRunning() const{
  return isRunning_;
}

/*
 * Turns on the toaster
 */
void Toaster::turnOn() {
  log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("Toaster"));
  LOG4CXX_TRACE(log, "--> Toaster entering turnOn method.");

  if (!isRunning_) {
    isRunning_ = true;

    LOG4CXX_INFO(log, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the toaster was turned on.");
  }

  LOG4CXX_TRACE(log, "<-- Toaster entering turnOn method.");
}

/*
 * Unused function inherited from Model.
 */
double Toaster::getPower() const {
  return 0.0;
}
