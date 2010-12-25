#ifndef STOVE_H_
#define STOVE_H_

#include "Model.h"

#define HIGH_POWER 1400
#define MEDIUM_POWER 700
#define LOW_POWER 350

/*
 * It has four 1400 W burners, each of which has 3 settings:
 * "high" uses the full power, "medium" uses half the power,
 * and "low" uses 25% of the power.
 */
class Stove: public Model {
  public:

    /*
     * Creates a stove that starts turned off.
     */
    Stove();

    /*
     * Update the state of the stove.
     */
    void tick();

    /*
     * Return the amount of power being used by adding up the
     * current power being used by each burner.
     */
    double getPower() const;

    /*
     * Return the amount of energy used by the Stove since startup.
     */
    double getEnergy() const;

    /*
     * Returns the amount of burners currently on.
     */
    int getBurnersOn() const;

    /*
     * Returns the amount of time the stove has been running.
     */
    int getTimeRunning() const;

    /*
     * Returns the power level of a specific burner.
     */
    int getBurnerPower(int burner) const;

    /*
     * Returns the cook time remaining of a specific burner.
     */
    int getBurnerTime(int burner) const;

    /*
     * Returns if the stove is running or not.
     */
    bool isRunning() const;

    /*
     * Used to turn a burner on, but does not have the user specify which burner.
     * The first unused burner will be turned on.  If burners are all being used,
     * nothing happens.
     *
     * Power level is inputed as either 1 (low), 2 (medium), or 3 (high).
     * Cook time is entered in minutes.
     */
    void turnOnBurner(int powerLevel, int cookTime);

    /*
     * Used to turn the whole stove off.
     */
    void turnOff();

  private:
    /*
     * Two-dimensional array that tracks the power-level and remaining amount of cooking time
     * left of each burner.
     *
     * First column is power level of burner, second column is cook time remaining.
     */
    int burners_[4][2];

    /*
     * Keeps track of number of burners turned on, used to determine
     * whether or not to set the stove state to off.
     */
    int burnersOn_;

    /*
     * Total amount of time the stove has been running.
     */
    int timeRunning_;

    /*
     * Tracks whether the stove is running or not.
     */
    bool isRunning_;

    /*
     * Tracks total amount of energy used by the stove since startup.
     */
    int totalEnergy_;

};

#endif /* STOVE_H_ */
