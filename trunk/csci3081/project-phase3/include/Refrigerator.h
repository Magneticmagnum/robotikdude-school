#ifndef REFRIGERATOR_H_
#define REFRIGERATOR_H_

#include "Model.h"
#include "Scheduler.h"
#include "Random.h"

#include <log4cxx/logger.h>

#define REFRIGERATOR_DEFAULT_POWER    150.0 // Watts
#define REFRIGERATOR_DEFAULT_ON_TIME    3   // minutes
#define REFRIGERATOR_DEFAULT_DUTY_CYCLE 0.3 // on-time / cycle-time
#define REFRIGERATOR_DEFAULT_USE_CYCLE  0.5 // on-time / cycle-time
//
/**
 * The Refrigerator class is a Model with two states, running and off. It
 * switches to off three ticks after it starts running, and it switches to
 * running nine ticks after it shuts off. When the Refrigerator is first
 * created, it is running. When running, it uses 150 watts by default; when
 * off, it uses no power.
 *
 * When the Refrigerator turns on, it writes an INFO message to the log saying
 * it has turned on and giving the time (from Scheduler::getTime()).
 *
 * When the Refrigerator turns off, it writes an INFO message to the log saying
 * it has turned off and giving the time and the total energy it has used so
 * far.
 */
class Refrigerator: public Model
{
  public:

    /**
     * Creates a Refrigerator with the given configuration. If the
     * configuration is null or contains no options, all configurable options
     * will be set to their default values.
     *
     */
    // TODO user23: finish comment
    Refrigerator(ConfigMap* configuration, Scheduler* scheduler, Random* random);

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

    // TODO user23: comment
    bool action(const std::string& actions);

    /**
     * Sets whether the refrigerator is currently in use or not. In other
     * words, if a person is currently cooking or not.
     */
    void setInUse(bool usage);

  private:

    // TODO user23: comment
    void initializeConfiguration(ConfigMap* configuration);

    // TODO user23: comment
    double power_;

    // TODO user23: comment
    double energy_;

    /**
     * Determines if the refrigerator is currently running or not.
     */
    bool running_;

    /**
     * Determines if the refrigerator is currently in use or not.
     */
    bool inUse_;

    /**
     * The time since the last state switch, whether that be from running to
     * off or off to running.
     */
    int tStateSwitch_;

    /**
     * The total number of ticks that the refrigerator has been running.
     */
    int totalRunningTime_;

    // TODO user23: comment
    int onTime_;

    // TODO user23: comment
    double usageCycle_;

    // TODO user23: comment
    double dutyCycle_;

    // TODO user23: comment
    Scheduler* scheduler_;

    // TODO user23: comment
    Random* random_;

    /**
     * The logger for Refrigerator.
     */
    static log4cxx::LoggerPtr log_;

};

#endif /* REFRIGERATOR_H_ */
