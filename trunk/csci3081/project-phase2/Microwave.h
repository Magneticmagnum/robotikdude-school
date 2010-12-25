#ifndef MICROWAVE_H_
#define MICROWAVE_H_

#include "Model.h"

#include <log4cxx/logger.h>

#define MICROWAVE_POWER            1500.0 // Watts
#define MICROWAVE_MIN_TIME  (40.0 / 60.0) // Minutes
#define MICROWAVE_MAX_TIME (120.0 / 60.0) // Minutes
/**
 * A Microwave is a Model.
 *
 * When activated, it uses 1500 W for a period of time selected from a uniform
 * distribution across 40-120 sec.
 */
class Microwave: public Model
{
  public:

    /**
     * Default constructor: creates a new default Microwave.
     */
    Microwave();

    /**
     * The Microwave is a simple Model that only runs for 40-120 seconds based
     * on a uniform distribution. The Microwave uses 1500 W when running.
     */
    void tick();

    /**
     * Returns the amount of power the Microwave uses when running, which is
     * 1500 Watts.
     */
    double getPower() const;

    /**
     * Returns the amount of energy the Microwave has used in its lifetime.
     * (i.e., time_running * power_when_running = total_energy)
     */
    double getEnergy() const;

    /**
     * Turns the Microwave on and runs it for 40-120 seconds.
     */
    void turnOn();

    /**
     * Returns true if the Microwave is currently running.
     */
    bool isRunning() const;

  private:

    /**
     * True if the Microwave is currently running.
     */
    bool running_;

    /**
     * The amount of time the Microwave needs to run in minutes before it can
     * turn off.
     */
    double onTimeLeft_;

    /**
     * The amount of time in minutes the Microwave has been running.
     */
    double timeRunning_;

    /**
     *
     */
    static log4cxx::LoggerPtr log;
};

#endif /* MICROWAVE_H_ */
