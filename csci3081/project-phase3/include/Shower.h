/*
 *  A Shower uses no power (and therefore no energy as well) and simply draws water
 *  from a WaterHeater every tick until it is turned off. When a Shower is turned on,
 *  the amount and temperature of water is specified. isRunning() will return "true"
 *  as long as the Shower is drawing water, "false" otherwise. action(const std::string&)
 *  turns the Shower on or off.
 */

#ifndef SHOWER_H_
#define SHOWER_H_

#include <log4cxx/logger.h>

#include "Scheduler.h"
#include "ConfigurationOptions.h"
#include "House.h"
#include "WaterHeater.h"
#include "Model.h"

#include <string>
using std::string;

class Shower: public Model
{
  public:
    /**
     * Constructor
     */
    Shower(ConfigMap*, Scheduler*, House*);

    /**
     *
     */
    void initConfig(ConfigMap*);

    /**
     * Tick method
     */
    void tick();

    /**
     * Returns the instantaneous power usage of Shower.  Since Shower
     * does not use any energy, the value returned is 0.0.
     */
    double getPower() const;

    /**
     * Returns the total energy used by Shower.  Since Shower does not
     * use any energy, the value returned is 0.0.
     */
    double getEnergy() const;

    /**
     * Turns shower on.  Returns true if successful, false otherwise.
     */
    bool turnOn();

    /**
     * Turns shower off.  Returns true if successful, false otherwise.
     */
    bool turnOff();

    /**
     * Check to see if shower is drawing water.
     */
    bool isRunning() const;

    /**
     * Turns the shower on and off.
     * Turning shower on requires the string:
     *   "start <amount> <temperature>"
     * Turning shower off requires the string:
     *   "stop"
     */
    bool action(const string&);

    /**
     * Accessor: returns pointer to Scheduler.
     */
    Scheduler* getScheduler() const;

    /**
     * Accessor: returns the amount of water to be drawn per minute.
     */
    double getDraw() const;

    /**
     * Accessor: returns the temperature of water to be drawn.
     */
    double getTemp() const;

    /**
     * Accessor: returns the House pointer.
     */
    House* getHouse() const;

    /**
     * Accessor: returns the water heater name
     */
    string getWHName() const;

    /**
     * Accessor: returns a pointer to the Water Heater used by Shower
     */
    WaterHeater* getWHModel() const;

    /**
     * Accessor: returns the total amount of water drawn by Shower
     */
    double getTotalWater() const;

  private:
    /**
     * Pointer to Scheduler to get time for logging
     */
    Scheduler* scheduler_;

    /**
     * Pointer to House Model to get waterheater
     */
    House* house_;

    /**
     * String for the name of the water heater.
     */
    string waterHeaterName_;

    /**
     * Amount of water to draw per tick.
     * Set when shower is turned on.
     */
    double waterDraw_;

    /**
     * Temperature of water drawn per tick.
     * Set when shower is turned on.
     */
    double waterTemp_;

    /**
     * Total water used by shower.
     * Used for testing purposes.
     */
    double totalWaterUsed_;

    /**
     * Boolean for if the shower is running
     */
    bool running_;

    /**
     * The logger for Shower.
     */
    static log4cxx::LoggerPtr log;

};

#endif /* SHOWER_H_ */
