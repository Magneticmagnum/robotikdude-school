#ifndef OVEN_H_
#define OVEN_H_

#include "Model.h"
#include "Scheduler.h"

#include <log4cxx/logger.h>

#include <string>
using std::string;

#define OVEN_PREHEATING_POWER 7500.0
#define OVEN_BAKING_POWER 2500.0
#define OVEN_PREHEAT_TIME 10
#define OVEN_DEFAULT_BAKE_TIME 30

/**
 * An Oven is a Model. When activated, it uses 7.5 kW for 10 min, and then switches to 2.5 kW for
 * an amount of time set by the configuration file.  The default baking time is 30 minutes.
 */
class Oven: public Model
{
  public:
    /**
     * Constructor
     * If no ConfigMap is available, pass in
     * 0 for that argument and the default values
     * will be used.
     */
    Oven(ConfigMap*, Scheduler*);

    /**
     * Set the baking time from the configuration file.
     */
    void initConfig(ConfigMap*);

    /**
     * Oven's tick function
     */
    void tick();

    /**
     * Performs action specified by string.
     * To turn oven on use: action("start")
     */
    bool action(const string&);

    /**
     * Checks if oven is on.
     */
    bool isRunning() const;

    /**
     * Returns total energy used by stove.
     */
    double getEnergy() const;

    /**
     * Accessor: returns the number of ticks the oven has been preheating.
     */
    int getPreheatTicks() const;

    /**
     * Accessor: returns the number of ticks the oven has been baking.
     */
    int getBakingTicks() const;
    /**
     * Accessor: Returns the baking time
     */
    int getBakeTime() const;

    /**
     * Accessor: Returns pointer to Scheduler
     */
    Scheduler* getScheduler() const;

    /**
     * Checks if Oven is preheated.
     */
    bool isPreheated() const;

    /**
     * Unused function inherited from Model; returns 0.0
     */
    double getPower() const;

  private:
    /**
     * Turns oven on. Returns true if successful, false otherwise.
     */
    bool turnOn();

    /**
     * Counter for state switching
     */
    int stateCounter_;

    /**
     * Total time preheating
     */
    int totalPreheatTime_;

    /**
     * Total time baking (after preheated)
     */
    int totalBakingTime_;

    /**
     * Baking time set by configuration file
     */
    int bakeTime_;

    /**
     * Boolean value for if the oven is running
     */
    bool isRunning_;

    /**
     * Boolean value for if the oven is preheated.
     */
    bool isPreheated_;

    /**
     * Logger for Oven
     */
    static log4cxx::LoggerPtr log;

    /**
     * Pointer to scheduler
     */
    Scheduler* scheduler_;
};

#endif /* OVEN_H_ */
