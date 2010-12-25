#ifndef DISHWASHER_H_
#define DISHWASHER_H_

#include "Model.h"

#define DISHWASHER_LOW_POWER            4.0         // Watts
#define DISHWASHER_HIGH_POWER           2000.0      // Watts
#define DISHWASHER_WATER_USAGE          22.0 / 20.0 // Liters / minute
#define DISHWASHER_CYCLE_DURATION       45.0        // Minutes
#define DISHWASHER_WASH_CYCLE_DURATION  20.0        // Minutes
/**
 * A Dishwasher is a model.
 *
 * When not in use, it draws 4 W of power.  When turned on, it
 * takes 45 minutes to complete a cycle.  It draws 2,000 W of power
 * for the full 45 minutes, and also draws 22.0 l of hot water (42 degrees C)
 * over the first 20 minutes of its cycle.
 */
class Dishwasher: public Model
{
  public:

    /**
     * Default constructor:  constructs a new dishwasher
     */
    Dishwasher();

    /**
     * A method to activate the dishwasher.  When this method is
     * called, the dishwasher begins its washing cycle and runs
     * until it is complete.
     */
    void turnOn();

    /**
     * getPower() returns the amount of power the dishwasher uses
     * when it is running.
     */
    double getPower() const;

    /**
     * getEnergy() returns the total energy the dishwasher has used
     * during the simulation
     */
    double getEnergy() const;

    /*
     * Returns true if the dishwasher is currently running
     */
    bool isRunning();

    /**
     * Return the amount of time left in the current dishwasher cycle, or
     * zero if the dishwasher is not running.
     */
    double getRunningTimeLeft();

    /**
     * Return the amount of time left in the current cycle during which
     * the dishwasher will be drawing water; zero if the dishwasher is
     * not running or has finished drawing water.
     */
    double getWaterTimeLeft();

    /**
     * Alerts the dishwasher that another unit of time has passed.
     */
    void tick();

  private:

    /**
     * True if the Dishwasher is currently running.
     */
    bool running_;

    /**
     * If the dishwasher is running, holds the number of minutes left
     * in the dishwasher cycle.  If the dishwasher is not running, it is
     * equal to 0.
     */
    double runningTimeLeft_;

    /**
     * If the dishwasher is running, waterTimeLeft_ holds the number
     * of ticks/minutes left in the cycle during which the dishwasher
     * will draw water from the water heater.
     */
    double waterTimeLeft_;

    /**
     * Track the total amount of energy the dishwasher has used since the
     * simulation started.
     */
    double energyUsed_;
};

#endif /* DISHWASHER_H_ */


