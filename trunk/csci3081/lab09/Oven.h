/*
 * An Oven is a Model. When activated, it uses 7.5 kW for 10 min, and then switches to 2.5 kW for 30 min.
 */

#ifndef OVEN_H_
#define OVEN_H_

#include "Model.h"

#define PREHEATING_POWER 7500.0
#define BAKING_POWER 2500.0

class Oven: public Model
{
  public:
    /*
     * Constructor
     */
    Oven();

    /*
     * Turns oven on.
     */
    void turnOn();

    /*
     * Oven's tick function
     */
    void tick();

    /*
     * Checks if oven is on.
     */
    bool isOn() const;

    /*
     * Returns total energy used by stove.
     */
    double getEnergy() const;

    /*
     * Accessor: returns number of ticks that have passed.
     */
    int getTicks() const;

    /*
     * Accessor: returns the number of ticks the oven has been preheating.
     */
    int getPreheatTicks() const;

    /*
     * Accessor: returns the number of ticks the oven has been baking.
     */
    int getBakingTicks() const;

    /*
     * Accessor: returns the state counter
     */
    int getCounter() const;

    /*
     * Unused function inherited from Model; returns 0.0
     */
    double getPower() const;

  private:
    /*
     * Total number of ticks that have passed.
     */
    int totalTicks_;

    /*
     * Counter for state switching
     */
    int stateCounter_;

    /*
     * Total time preheating
     */
    int totalPreheatTime_;

    /*
     * Total time baking (after preheated)
     */
    int totalBakingTime_;

    /*
     * Boolean value for if the oven is running
     */
    bool isRunning_;
};

#endif /* OVEN_H_ */
