#include "Stove.h"
#include <iostream>

/*
 * Creates a stove, with all burners initially set to off.
 */
Stove::Stove () {
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
}

/*
 *
 */
void Stove::tick() {

  if (isRunning_) { //Stove is on.

    timeRunning_++;

    for (int i = 0; i < 4; i++) {  //Check each burner's status.

      if (burners_[i][0] != 0) {  //If the burner is on, update its status.

        totalEnergy_ += burners_[i][0];  //Update total amount of energy used by the stove.
        burners_[i][1]--;  //Update cook time remaining.

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
    }

  }
}


/*
 * Adds up and returns the amount of power that each burner is
 * currently using.
 */
double Stove::getPower() const {
  return burners_[0][0] + burners_[1][0] + burners_[2][0] + burners_[3][0];
}


double Stove::getEnergy() const {
  return totalEnergy_;
}

/*
 * Get # burners currently on.
 */
int Stove::getBurnersOn() const {
  return burnersOn_;
}

/*
 * Get the time the stove has been running.
 */
int Stove::getTimeRunning() const {
  return timeRunning_;
}

/*
 * Get power level of a specific burner.
 */
int Stove::getBurnerPower(int burner) const {
  return burners_[burner][0];
}

/*
 * Get cook time remaining of a specific burner.
 */
int Stove::getBurnerTime(int burner) const {
  return burners_[burner][1];
}

/*
 * Cycle through burners until an open one is found, then set its power
 * level and duration of use.
 */
void Stove::turnOnBurner(int powerLevel, int cookTime) {

  int i = 0;
  bool turnedOn = false;

  if ((powerLevel > 0) && (powerLevel < 4) && (cookTime > 0) && (burnersOn_ < 4)) {
    while (!turnedOn && (i < 4)) { //Look for an open burner.

      if (burners_[i][0] == 0) { //Check to see if the current burner is unused.

        if (powerLevel == 1) {  //Power level set to low.
          burners_[i][0] = LOW_POWER;
        }
        else if (powerLevel == 2) {  //Power level set to medium.
          burners_[i][0] = MEDIUM_POWER;
        }
        else { //Power level set to high.
          burners_[i][0] = HIGH_POWER;
        }

        burners_[i][1] = cookTime;
        burnersOn_++;
        isRunning_ = true;
        turnedOn = true;  //Set exit condition

      }

      i++;
    }
  }
  else { //Error cases
    if (cookTime < 0) {
      std::cout << "Cook time must be positive.";
    }

    if (powerLevel < 0 || powerLevel > 3){
      std::cout << "Burner power level must be 1 (low), 2 (medium), or 3 (high).";
    }

    if (burnersOn_ >= 4) {
      std::cout << "No open burners.";
    }
  }
}


/*
 * Turns off all of the burners and sets isRunning_ to false.
 * With the cook times being tracked by each burner this may not be
 * entirely necessary, but it's here in case a total stove shutdown
 * is needed (in case of house fire, for example).
 */
void Stove::turnOff() {
  burners_[0][0] = 0;
  burners_[0][1] = 0;
  burners_[1][0] = 0;
  burners_[1][1] = 0;
  burners_[2][0] = 0;
  burners_[2][1] = 0;
  burners_[3][0] = 0;
  burners_[3][1] = 0;

  isRunning_ = false;
}
