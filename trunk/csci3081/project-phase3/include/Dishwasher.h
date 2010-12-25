#ifndef DISHWASHER_H_
#define DISHWASHER_H_

#include "Model.h"
#include "House.h"
#include "Scheduler.h"
#include "WaterHeater.h"

#include <log4cxx/logger.h>

#define DISHWASHER_OFF_POWER_DEFAULT            4.0         // Watts
#define DISHWASHER_ON_POWER_DEFAULT             2000.0      // Watts
#define DISHWASHER_WATER_USAGE_DEFAULT          22.0        // Liters / minute
#define DISHWASHER_WATER_TEMP_DEFAULT           42.0        // Temp of water used
#define DISHWASHER_CYCLE_DURATION_DEFAULT       45.0        // Minutes
#define DISHWASHER_WASH_CYCLE_DURATION_DEFAULT  20.0        // Minutes
//
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

    //A constructor that will create a dishwasher object, taking
    //its configuration from the passed ConfigMap.  Values for
    //power and water usage and cycle time may be included in
    //the config map, otherwise default values are used.
    Dishwasher(ConfigMap* config, Scheduler* scheduler, House* house);

    // If the dishwasher does not use default values for its
    // various settings (water temp, cycle duration, etc.), the
    // initializeConfiguration function will set all of these member
    // variables to the values passed in the config map.
    void initializeConfiguration(ConfigMap* config);

    /**
     * A method to activate the dishwasher.  When this method is
     * called, the dishwasher begins its washing cycle and runs
     * until it is complete.
     */
    bool turnOn();

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
    bool isRunning() const;

    // A function that allows the dishwasher to be activated.
    // Since the dishwasher only has one function that controls
    // its activation (turnOn()), that is the only valid value to
    // be passed as an argument.
    bool action(const std::string& actions);

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

    /**
     * The amount of power the dishwasher draws per second when it is in use,
     * in watts.
     */
    double onPower_;

    /*
     * The amount of power the dishwasher draws, per second, when it is not in use.
     */
    double offPower_;

    /*
     * The amount of water the dishwasher draws during the wash cycle, in liters.
     */
    double waterUsage_;

    /*
     * Temperature of the water used during the wash cycle.
     */
    double waterTemp_;

    /*
     * Total run time of the dishwasher.
     */
    double cycleDuration_;

    /*
     * Duration of the wash cycle.
     */
    double washCycleDuration_;

    /*
     * A reference to the simulation's scheduler object
     */
    Scheduler* scheduler_;

    /*
     * Stores the name of the WaterHeater that the Dishwasher uses.
     */
    std::string waterheater_;

    /*
     * Pointer to House that the dishwasher is in.
     */
    House* house_;

    /**
     *  Pointer to the log.
     */
    static log4cxx::LoggerPtr log_;
};

#endif /* DISHWASHER_H_ */

