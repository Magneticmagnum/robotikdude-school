#define TELEVISION_DEFAULT_ON_POWER 180.0
#define TELEVISION_DEFAULT_OFF_POWER 10.0

#ifndef TELEVISION_H_
#define TELEVISION_H_

#include <log4cxx/logger.h>

#include "Model.h"
#include "Scheduler.h"
#include "ConfigurationOptions.h"

#include <string>
using std::string;

/*
 * Television models come in various sizes.  Different sizes use varying amounts
 * of energy.  The on and off power usage is defined by the configuration file.
 */
class Television: public Model
{
  public:
    /*
     * Creates a television object that starts in the off state.
     */
    //Television();

    /*
     * Constructor
     */
    Television(ConfigMap*, Scheduler*);

    /*
     * Initialize on and off power from configuration file.
     */
    void initConfig(ConfigMap* config);

    /*
     * Increments the internal counter for ticks and total time on or off depending on its state.
     */
    void tick();

    /*
     *  Returns energy used by television.
     */
    double getEnergy() const;

    /*
     * Returns the state of television: true of on, false if off.
     */
    bool isRunning() const;

    /*
     * Turns television on and off.
     */
    bool action(const string&);

    /*
     * Accessor: Returns the total number of ticks the television has been on.
     */
    int getTotalTimeOn() const;

    /*
     * Accessor: Returns the total number of ticks the television has been off.
     */
    int getTotalTimeOff() const;

    /*
     * Returns instantaneous power usage.
     */
    double getPower() const;

    /**
     * Accessor: Returns the off power
     */
    double getOffPower() const;

    /**
     * Accessor: Returns the on power
     */
    double getOnPower() const;

    /**
     * Accessor: Returns a pointer to the scheduler
     */
    Scheduler* getScheduler() const;

  private:
    /*
     * Turns television on.  Returns true if successful, false otherwise.
     */
    bool turnOn();

    /*
     * Turns television off.  Returns true if successful, false otherwise.
     */
    bool turnOff();

    /*
     * Boolean variable to keep track of if the television is on or off.
     */
    bool state_;

    /*
     * Total time that the television has been on.
     */
    int totalTimeOn_;

    /*
     * Total time that the television has been off.
     */
    int totalTimeOff_;

    /*
     * Power usage when television is on
     * Default value is 10.0
     */
    double onPower_;

    /*
     * Power usage when television is off
     * Default value is 180.0
     */
    double offPower_;

    /*
     * Pointer to Scheduler for getting the time passed.
     */
    Scheduler* scheduler_;

    /*
     * Logger for Television
     */
    static log4cxx::LoggerPtr log;
};

#endif /* TELEVISION_H_ */
