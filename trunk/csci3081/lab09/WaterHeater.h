#ifndef WATERHEATER_H_
#define WATERHEATER_H_

#include "Model.h"

#define WATERHEATER_CAPACITY      200      // Liters
#define WATERHEATER_HEAT_LOSS       0.0029 // Degrees Celcius / minute
#define WATERHEATER_HEAT_GAIN       0.215  // Degrees Celcius / minute
#define WATERHEATER_POWER        3000.0    // Watts
#define WATERHEATER_TEMP_ON        49.0    // Degrees Celcius
#define WATERHEATER_TEMP_OFF       50.0    // Degrees Celcius
#define WATERHEATER_TEMP_INCOMING   7.0    // Degrees Celcius
/**
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

    /**
     * Default constructor: creates a new default WaterHeater with 200 liters
     * of water at 50 degrees Celcius.
     */
    WaterHeater();

    /**
     * Creates a new WaterHeater with 200 liters of water at the specified
     * temperature in Celcius.
     */
    WaterHeater(double temperature);

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
     * Requests water from the WaterHeater in the given amount at the specified
     * temperature. Returns the temperature of the water that is sent out. If
     * temperature requested is not possible, the actual temperature of the
     * water is returned.
     */
    double getWater(double amount, double temperature);

    /**
     *
     */
    double getWaterTemperature() const;

    /**
     * Returns true if the WaterHeater is currently running.
     */
    bool isRunning() const;


    Model& operator-=(int amount);

    //Model& operator=(const Model&);

    //friend Model& operator-(const Model&, int);

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
};

#endif /* WATERHEATER_H_ */
