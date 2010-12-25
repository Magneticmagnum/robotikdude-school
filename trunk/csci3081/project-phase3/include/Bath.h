#ifndef BATH_H_
#define BATH_H_

#include "Model.h"
#include "House.h"
#include "Scheduler.h"
#include "WaterHeater.h"
#include <log4cxx/logger.h>

/*
 * A Bath is a Model. Baths require 100 l of water at
 * 42 C, the tub takes 4 minutes to fill, and the bath takes
 * 15-20 minutes after the tub is filled.
 */
class Bath: public Model
{
  public:

    /*
     * Creates a Bath tied to a specific House and Scheduler, also
     * takes in a config map.
     */
    Bath(ConfigMap* config, Scheduler* scheduler, House* house);

    /*
     * Initialize Bath capacity and wather heater that it
     * is tied to.
     */
    void initializeConfiguration(ConfigMap* config);

    /*
     * Updates the state of the bath when called by the scheduler.
     */
    void tick();

    /*
     * Returns the amount of power the bath uses.
     * Should return 0
     */
    double getPower() const;

    /*
     * Returns the total amount of energy the bath has used.
     * Should return 0.
     */
    double getEnergy() const;

    /*
     * Returns the capacity of the bath.
     */
    double getCapacity() const;

    /*
     * Returns the current water level of the bath.
     */
    double getCurrentLevel() const;

    /*
     * Returns the amount of time the bath has been filling.
     */
    int getTimeRunning() const;

    /*
     * Returns the current bath temperature.
     */
    double getTemperature() const;

    /*
     * Returns if the bath is currently filling or not.
     */
    bool isRunning() const;

    /*
     * Action method for bath.
     */
    bool action(const std::string& actions);

    /*
     * Turns the bath on to fill.
     */
    void turnOn(double flowRate, double temperature);

  private:
    /*
     * Is the bath filling?
     */
    bool isFilling_;

    /*
     * Amount of time the bath has been filling.
     */
    int timeRunning_;

    /*
     * Keeps track of the amount of water currently in the bath.
     */
    double currentLevel_;

    /*
     * Current flow rate of the Bath as it fills.
     */
    double flowRate_;

    /*
     * Stores the Bath's capacity.
     */
    double capacity_;

    /*
     * Stores the water temperature in degrees Celcius.
     */
    double temperature_;

    /*
     * Stores the name of the WaterHeater that the Bath uses.
     */
    std::string waterheater_;

    /*
     * Pointer to House that the Bath is in.
     */
    House* house_;

    /*
     * Pointer to the scheduler instance that is responsible
     * for notifying the Bath of updates.
     */
    Scheduler* scheduler_;

    /**
     * The logger for Bath.
     */
    static log4cxx::LoggerPtr log_;
};

#endif /* BATH_H_ */
