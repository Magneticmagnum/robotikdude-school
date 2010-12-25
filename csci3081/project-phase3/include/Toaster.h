#ifndef TOASTER_H_
#define TOASTER_H_

#include "Model.h"
#include "Scheduler.h"
#include <log4cxx/logger.h>

#define TOASTER_POWER 900
/*
 * A Toaster is a Model that, when activated, uses 900W for 2 minutes (ticks).
 */
class Toaster: public Model
{
  public:

    /*
     * Creates a toaster that starts turned off.
     */
    Toaster();

    Toaster(Scheduler* scheduler);

    /*
     * Updates the state of the toaster when called by the scheduler.
     */
    void tick();

    /*
     * Returns the amount of power the toaster uses
     */
    double getPower() const;

    /*
     * Returns the total amount of energy the toaster has used.
     */
    double getEnergy() const;

    /*
     * Returns the time the toaster has been running in
     * the current toast cycle.
     */
    double getCycleTime() const;

    /*
     * Returns the total amount of time the toaster has been running.
     */
    double getTotalTime() const;

    /*
     * Returns the lifetime of the toaster
     */
    double getLifetime() const;

    /*
     * Returns if the toaster is currently running or not.
     */
    bool isRunning() const;

    /*
     * Action method for toaster.  Used to turn
     * the toaster on.
     */
    bool action(const std::string& actions);

    /*
     * Turns the toaster on.
     */
    void turnOn();

  private:
    /*
     * Is the toaster running?
     */
    bool isRunning_;

    /*
     * Amount of time the toaster has been running.
     * Used to determine current state of the toaster.
     */
    int timeRunning_;

    /*
     * Total amount of time the toaster has been running over
     * the entire simulation.  Used to calculate the
     * total amount of power consumed by the toaster.
     */
    int totalTimeRunning_;

    /*
     * Keeps track of the number of ticks that have passed since
     * toaster creation.
     */
    int ticksPassed_;

    Scheduler* scheduler_;

    /**
     * The logger for Toaster.
     */
    static log4cxx::LoggerPtr log_;
};

#endif /* TOASTER_H_ */
