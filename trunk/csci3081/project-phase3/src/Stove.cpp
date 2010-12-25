#include "Stove.h"
#include "ConfigurationOptions.h"
#include <stdlib.h>
#include <iostream>
log4cxx::LoggerPtr Stove::log_(log4cxx::Logger::getLogger("Stove"));

/*
 * Creates a stove, with all burners initially set to off.
 */
Stove::Stove()
{
  LOG4CXX_TRACE(log_, "--> Stove::Stove()");

  burners_[0][0] = 0;
  burners_[0][1] = 0;
  burners_[1][0] = 0;
  burners_[1][1] = 0;
  burners_[2][0] = 0;
  burners_[2][1] = 0;
  burners_[3][0] = 0;
  burners_[3][1] = 0;

  burnersOn_ = 0;

  timeRunning_ = 0;
  totalEnergy_ = 0;
  isRunning_ = false;

  scheduler_ = Scheduler::getInstance();

  LOG4CXX_DEBUG(log_, "    Stove created " << (isRunning_ ? "" : "not ")
      << "running.");
  LOG4CXX_DEBUG(log_, "    Burners on: " << burnersOn_ << ".");
  LOG4CXX_DEBUG(log_, "    Time running: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Total energy used: " << totalEnergy_ << ".");

  LOG4CXX_TRACE(log_, "<-- Stove::Stove()");
}

Stove::Stove(Scheduler* scheduler)
{
  LOG4CXX_TRACE(log_, "--> Stove::Stove(Scheduler* scheduler)");

  burners_[0][0] = 0;
  burners_[0][1] = 0;
  burners_[1][0] = 0;
  burners_[1][1] = 0;
  burners_[2][0] = 0;
  burners_[2][1] = 0;
  burners_[3][0] = 0;
  burners_[3][1] = 0;

  burnersOn_ = 0;

  timeRunning_ = 0;
  totalEnergy_ = 0;
  isRunning_ = false;

  scheduler_ = scheduler;

  LOG4CXX_DEBUG(log_, "    Stove created " << (isRunning_ ? "" : "not ")
      << "running.");
  LOG4CXX_DEBUG(log_, "    Burners on: " << burnersOn_ << ".");
  LOG4CXX_DEBUG(log_, "    Time running: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Total energy used: " << totalEnergy_ << ".");

  LOG4CXX_TRACE(log_, "<-- Stove::Stove(Scheduler* scheduler)");
}

/*
 * Checks Stove state and executes proper Stove behavior.
 *
 * Goes through and checks each burner.  If the burner is on,
 * the cook time remaining for the burner is updated as well as
 * the energy used by the stove.  It then checks if the burner
 * needs to be turned off or not.
 *
 * After checking the burners, the stove is turned off if all of
 * the burners have been turned off.
 *
 */
void Stove::tick()
{
  LOG4CXX_TRACE(log_, "--> Stove::tick()");

  if (isRunning_) { //Stove is on.

    timeRunning_++;

    for (int i = 0; i < 4; i++) { //Check each burner's status.

      if (burners_[i][0] != 0) { //If the burner is on, update its status.

        totalEnergy_ += burners_[i][0]; //Update total amount of energy used by the stove.
        burners_[i][1]--; //Update cook time remaining.

        //After updating the status of the current burner,check if we need to turn it off.
        if (burners_[i][1] == 0) {
          burners_[i][0] = 0;
          burnersOn_--;
        }
      }
    }

    //After updating each burner's status as necessary, check to see if all the burners are off.
    //If so, set Stove's state of off.
    if (burnersOn_ == 0) {
      isRunning_ = false;

      LOG4CXX_INFO(log_, "    At time " << scheduler_->getTimeStr()
          << " the stove was turned off. Total energy used: "
          << getEnergy() << ".");
    }

  }
  LOG4CXX_TRACE(log_, "<-- Stove::tick()");
}

/*
 * Adds up and returns the amount of power that each burner is
 * currently using.
 */
double Stove::getPower() const
{
  LOG4CXX_TRACE(log_, "--> Stove::getPower()");
  LOG4CXX_DEBUG(log_, "    Current power draw of Stove: " <<
      burners_[0][0] + burners_[1][0] + burners_[2][0] +
      burners_[3][0] << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::getPower()");

  return burners_[0][0] + burners_[1][0] + burners_[2][0] + burners_[3][0];
}

double Stove::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> Stove::getEnergy()");
  LOG4CXX_DEBUG(log_, "    Total energy used by stove: " << totalEnergy_
      << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::getEnergy()");

  return totalEnergy_ * SECONDS_PER_TICK;
}

/*
 * Get # burners currently on.
 */
int Stove::getBurnersOn() const
{
  LOG4CXX_TRACE(log_, "--> Stove::getBurnersOn()");
  LOG4CXX_DEBUG(log_, "    Number of burners currently on: " << burnersOn_
      << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::getBurnersOn()");

  return burnersOn_;
}

/*
 * Get the time the stove has been running.
 */
int Stove::getTimeRunning() const
{
  LOG4CXX_TRACE(log_, "--> Stove::getTimeRunning()");
  LOG4CXX_DEBUG(log_, "    Time the stove has been running is " << timeRunning_
      << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::getTimeRunning()");

  return timeRunning_;
}

/*
 * Get power level of a specific burner.
 */
int Stove::getBurnerPower(int burner) const
{
  LOG4CXX_TRACE(log_, "--> Stove::getBurnerPower()");
  LOG4CXX_DEBUG(log_, "    Current power level of burner " << burner <<
      " is " <<burners_[burner][0] << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::getBurnerPower()");

  return burners_[burner][0];
}

/*
 * Get cook time remaining of a specific burner.
 */
int Stove::getBurnerTime(int burner) const
{
  LOG4CXX_TRACE(log_, "--> Stove::getBurnerTime()");
  LOG4CXX_DEBUG(log_, "    Cook time remaining of burner " << burner <<
      " is " <<burners_[burner][1] << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::getBurnerTime()");

  return burners_[burner][1];
}

/*
 * Cycle through burners until an open one is found, then set its power
 * level and duration of use.
 */
bool Stove::turnOnBurner(int powerLevel, int cookTime)
{
  LOG4CXX_TRACE(log_, "--> Stove::turnOnBurner()");

  int i = 0;
  bool turnedOn = false;
  bool noerror = true;

  if ((powerLevel > 0) && (powerLevel < 4) && (cookTime > 0)
      && (burnersOn_ < 4)) {
    while (!turnedOn && (i < 4)) { //Look for an open burner.

      if (burners_[i][0] == 0) { //Check to see if the current burner is unused.

        if (powerLevel == 1) { //Power level set to low.
          burners_[i][0] = LOW_POWER;
        }
        else if (powerLevel == 2) { //Power level set to medium.
          burners_[i][0] = MEDIUM_POWER;
        }
        else { //Power level set to high.
          burners_[i][0] = HIGH_POWER;
        }

        burners_[i][1] = cookTime;
        burnersOn_++;
        if (!isRunning_) {
          LOG4CXX_INFO(log_, "    At time " << scheduler_->getTimeStr()
              << " the stove was turned on.");
        }
        isRunning_ = true;
        turnedOn = true; //Set exit condition

      }

      i++;
    }
  }
  else { //Error cases
    noerror = false;
    if (cookTime < 0) {
      LOG4CXX_ERROR(log_, "    Cook time must be positive.");
    }

    if (powerLevel < 0 || powerLevel > 3) {
      LOG4CXX_ERROR(log_, "    Burner power level must be 1 (low), 2 (medium), or 3 (high).");
    }

    if (burnersOn_ >= 4) {
      LOG4CXX_ERROR(log_, "    No open burners.");
    }
  }
  LOG4CXX_TRACE(log_, "<-- Stove::turnOnBurner()");
  return noerror;
}

/*
 *
 */
bool Stove::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> Stove::isRunning()");
  LOG4CXX_DEBUG(log_, "    Stove is currently " << (isRunning_ ? "" : "not ")
      << "running.");
  LOG4CXX_TRACE(log_, "<-- Stove::isRunning()");
  return isRunning_;
}

/*
 *
 */
bool Stove::action(const std::string& actions)
{
  LOG4CXX_TRACE(log_, "--> Stove::action(const std::string&)");
  bool noerror = true;

  char** argv;
  int argc = Model::makeargv(actions, " ", &argv);

  //Check to see if arguments were entered in pairs of
  //'powerLevel cookTime'
  if (argc > 0 && argc % 2 == 0) {
    for (int i = 0; i < argc; i += 2) {
      int cookTime = atoi(argv[i + 1]);

      if (strcmp(STOVE_LOW, argv[i]) == 0) {
        noerror &= turnOnBurner(1, cookTime);
      }
      else if (strcmp(STOVE_MEDIUM, argv[i]) == 0) {
        noerror &= turnOnBurner(2, cookTime);
      }
      else if (strcmp(STOVE_HIGH, argv[i]) == 0) {
        noerror &= turnOnBurner(3, cookTime);
      }
      else {
        noerror = false;
        LOG4CXX_WARN(log_, "*** Stove action " << argv[i] << " " << argv[i+1] << " not recognized");
      }
    }
  }
  else {
    noerror = false;
    if (argc == 0) {
      LOG4CXX_WARN(log_, "*** Stove needs two or more arguments, see documentation for usage");
    }
    else {
      LOG4CXX_WARN(log_, "*** Stove takes pairs of arguments, see documentation for usage.");
    }
  }

  Model::freemakeargv(argv);
  LOG4CXX_TRACE(log_, "<-- Stove::action(const std::string&)");
  return noerror;
}

/*
 * Turns off all of the burners and sets isRunning_ to false.
 * With the cook times being tracked by each burner this may not be
 * entirely necessary, but it's here in case a total stove shutdown
 * is needed (in case of house fire, for example).
 */
void Stove::turnOff()
{
  LOG4CXX_TRACE(log_, "--> Stove::turnOff()");

  burners_[0][0] = 0;
  burners_[0][1] = 0;
  burners_[1][0] = 0;
  burners_[1][1] = 0;
  burners_[2][0] = 0;
  burners_[2][1] = 0;
  burners_[3][0] = 0;
  burners_[3][1] = 0;

  burnersOn_ = 0;
  isRunning_ = false;

  LOG4CXX_INFO(log_, "    At time " << scheduler_->getTimeStr()
      << " the stove was turned off. Total energy used: "
      << getEnergy() << ".");
  LOG4CXX_TRACE(log_, "<-- Stove::turnOff()");
}
