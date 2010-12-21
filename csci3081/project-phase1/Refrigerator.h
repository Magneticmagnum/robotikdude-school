#ifndef REFRIGERATOR_H_
#define REFRIGERATOR_H_

class Logger; // forward declaration
#include "Model.h"

#define REFRIGERATOR_POWER 150.0

/**
 * The Refrigerator class is a Model with two states, running and off. It
 * switches to off three ticks after it starts running, and it switches to
 * running nine ticks after it shuts off. When the Refrigerator is first
 * created, it is running. When running, it uses 150 watts; when off, it uses
 * no power.
 *
 * When the Refrigerator turns on, it writes an INFO message to the log saying
 * it has turned on and giving the time (from Scheduler.getTime()).
 *
 * When the Refrigerator turns off, it writes an INFO message to the log saying
 * it has turned off and giving the time and the total energy it has used so
 * far. In order to compute energy use, it shall assume that each tick
 * represents one minute of real-world time.
 */
class Refrigerator: public Model
{
  public:

    /**
     * Creates a new Refrigerator object that starts off running.
     */
    Refrigerator();

    /**
     * Creates a new Refrigerator object that starts off running and uses the
     * Logger class to print out various messages.
     */
    Refrigerator(Logger* logger);

    /**
     * The Refrigerator class is a Model with two states, running and off. It
     * switches to off three ticks after it starts running, and it switches to
     * running nine ticks after it shuts off.
     */
    void tick();

    /**
     * Returns the amount of power the Refrigerator uses when running. When
     * running, it uses 150 Watts; when off, it uses no power.
     */
    double getPower() const;

    /**
     * Returns the total amount of energy that the Refrigerator has used.
     */
    double getEnergy() const;

    /**
     * Returns if the refrigerator is running or not
     */
    bool isRunning() const;

  private:

    /**
     * Determines if the refrigerator is currently running or not.
     */
    bool running_;

    /**
     * The time since the last state switch, whether that be from running to
     * off or off to running.
     */
    int tStateSwitch_;

    /**
     * The total number of ticks that the refrigerator has been running
     */
    int totalRunningTime_;

};

#endif /* REFRIGERATOR_H_ */
