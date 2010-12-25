#ifndef WATERHEATER_H_
#define WATERHEATER_H_

#include "Model.h"
#include "Scheduler.h"

#include <log4cxx/logger.h>

#define WATERHEATER_DEFAULT_CAPACITY      200      // Liters
#define WATERHEATER_DEFAULT_HEAT_LOSS       0.0029 // Degrees Celcius / minute
#define WATERHEATER_DEFAULT_HEAT_GAIN       0.215  // Degrees Celcius / minute
#define WATERHEATER_DEFAULT_POWER        4500.0    // Watts
#define WATERHEATER_DEFAULT_TEMP_ON        49.0    // Degrees Celcius
#define WATERHEATER_DEFAULT_TEMP_OFF       50.0    // Degrees Celcius
#define WATERHEATER_DEFAULT_TEMP_INCOMING   7.0    // Degrees Celcius
//
/**
 * TODO user23: comment update
 * A WaterHeater is a Model.
 *
 * It holds 200 l of water, and loses heat at the rate of 40 watts
 * (0.576Kc/min), which means that the water temperature drops by
 * 0.0029 C/min. Whenever the water temperature drops below 49 C, its
 * 3000 watt element turns on, and stays on until the water temperature rises
 * to 50 C. Note that 3 kW will raise the temperature of 200 l of water by
 * 0.215 C/min. When hot water is used (by some other model), it is replaced
 * by incoming water at 7 C, which of course must be heated to 50 C. When
 * water is used at a temperature below 50 C, the hot water shall be mixed
 * with water at 7 C to achieve the correct temperature.
 */
class WaterHeater: public Model
{
  public:

    // TODO user23: comment
    WaterHeater(ConfigMap* configuration, Scheduler* scheduler);

    // TODO user23: comment
    void initializeConfiguration(ConfigMap* configuration);

    /**
     * The WaterHeater is responsible for keeping the water that it contains at
     * a nice and warm 50 degrees Celcius. It does this by turning on whenever
     * the water drops below 49 degrees Celcius until the water reaches 50
     * degrees Celcius again.
     */
    void tick();

    /**
     * Returns the amount of power the WaterHeater uses when running, which is
     * 3000 Watts.
     */
    double getPower() const;

    /**
     * Returns the amount of energy the WaterHeater has used in its lifetime.
     * (i.e., time_running * power_when_runnig = total_energy)
     */
    double getEnergy() const;

    /**
     * Returns true if the WaterHeater is currently running.
     */
    bool isRunning() const;

    // TODO user23: comment
    bool action(const std::string& actions);

    /**
     * Requests water from the WaterHeater in the given amount at the specified
     * temperature. Returns the temperature of the water that is sent out. If
     * temperature requested is not possible, the actual temperature of the
     * water is returned.
     */
    double getWater(double amount, double temperature);

    // TODO user23: comment
    double getWaterTemperature() const;

  private:

    /**
     * True if the WaterHeater is currently running.
     */
    bool running_;

    /**
     * The current temperature of the water in the WaterHeater.
     */
    double waterTemperature_;

    /**
     * The amount of time in minutes the Microwave has been running.
     */
    int timeRunning_;

    // TODO user23: comment
    int capacity_;

    // TODO user23: comment
    double heatLoss_;

    // TODO user23: comment
    double heatGain_;

    // TODO user23: comment
    double power_;

    // TODO user23: comment
    double energy_;

    // TODO user23: comment
    double tempOn_;

    // TODO user23: comment
    double tempOff_;

    // TODO user23: comment
    double tempIncoming_;

    // TODO user23: comment
    Scheduler* scheduler_;

    /**
     * The logger for WaterHeater.
     */
    static log4cxx::LoggerPtr log_;
};

#endif /* WATERHEATER_H_ */
