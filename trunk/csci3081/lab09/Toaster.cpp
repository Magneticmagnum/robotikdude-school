#include "Toaster.h"

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

  ticksPassed_++;

  if (isRunning_) { //If the toaster is currently on...

    timeRunning_++;
    totalTimeRunning_++;

    if (timeRunning_ >= 2) { //Toaster has ran for 2 minutes and should turn off.
      isRunning_ = false;
      timeRunning_ = 0;
    }
  }
}

/*
 * Returns the total amount of power the toaster has used.
 */
double Toaster::getEnergy() const {
  return totalTimeRunning_ * TOASTER_POWER;
}

/*
 * Returns the time the toaster has been running in
 * the current toast cycle.
 */
double Toaster::getCycleTime() const {
  return timeRunning_;
}

/*
 * Returns the total amount of time the toaster has been running.
 */
double Toaster::getTotalTime() const {
  return totalTimeRunning_;
}

/*
 * Returns the toaster's lifetime.
 */
double Toaster::getLifetime() const {
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
  if (!isRunning_) {
    isRunning_ = true;
  }
}

/*
 * Unused function inherited from Model.
 */
double Toaster::getPower() const {
  return 0.0;
}
