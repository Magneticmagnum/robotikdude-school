#ifndef PERSON_H_
#define PERSON_H_

#include "Model.h"
#include "Stove.h"
#include "Dishwasher.h"
#include "Refrigerator.h"
#include "Microwave.h"
#include "Television.h"
#include "Toaster.h"
#include "Oven.h"

#include <log4cxx/logger.h>

#define  MICROWAVE     "microwave"
#define  STOVE         "stove"
#define  DISHWASHER    "dishwasher"
#define  REFRIGERATOR  "refrigerator"
#define  TOASTER       "toaster"
#define  BATHROOM      "bathroom"
#define  OVEN          "oven"

/**
 *  Person is a subclass of Model.  However, Person does not directly draw power.
 *  Instead, Person contains the schedule of activities for all appliance use
 *  throughout each day of the simulation.  Every day at midnight, Person resets
 *  the schedule of activities for the next day's worth of ticks, deciding when
 *  to wake up, cook breakfast, get home from work, etc.
 */
class Person: public Model
{
  public:

    /**
     * Creates a new Person object
     */
    Person();

    /**
     * Constructor that takes a seed for seeding
     * rand()
     */
    Person(int seed);

    /**
     * Alert the Person object to the passing
     * of another tick (minute).
     */
    void tick();


    /*
     * Return the amount of power being used.  Since the person does not
     * directly use electricity, this will always return 0.
     */
    double getPower() const;

    /*
     * Return the total amount of energy used by the person.  Always 0.
     */
   double getEnergy() const;

   /*
    * Return the current tick count.
    */
   int getTickCounter() const;

   /*
    * Return the current daily tick count.
    */
   int getDailyTickCounter() const;

   /*
    * Return the number of days since the dishwasher
    * has been run.
    */
   int getDaysSinceDishwasherRun() const;

   /*
    * Get the pointer to the current position in the activationTimes_
    * list.
    */
   int getActivationIndex() const;

   /*
    * Get the list of all times at which an appliance is activated.
    */
   std::vector<int> getActivationTimes();

   std::vector<int> getStoveActivationTimes();

   std::vector<int> getMicrowaveActivationTimes();

   std::vector<int> getOvenActivationTimes();

   std::vector<int> getDishwasherActivationTimes();

   std::vector<int> getToasterActivationTimes();

   std::vector<int> getRefrigeratorActivationTimes();

   std::vector<int> getWaterHeaterActivationTimes();

  private:

    /**
     * Gets called at midnight every day.  Reset() will
     * re-populate all of the stochastic values for the new day:
     * when the person wakes up, whether to take a shower, etc.
     */
    void reset();

    /*
     * tickCounter_ keeps track of the number of ticks that have
     * passed during the current simulation.
     */
    int tickCounter_;

    /*
     * dailyTickCounter keeps track of the number of ticks that have
     * passed during the current day.  Assuming a tick is equivalent to
     * one minute, dailyTickCounter_ is equal to tickCounter % 1440.  Gets
     * reset to zero every day at midnight.
     */
    int dailyTickCounter_;

    /*
     * The number of days since the dishwasher has been run.
     */
    int daysSinceDishwasherRun_;

    /*
     * The activationXTimes_ contain lists of times that the
     * respective appliances will be used.  The activationXIndices_ hold
     * pointers which track which index in the list points to the next
     * time each appliance will be used.  There are also vectors
     * to hold arguments that must be passed when certain appliances
     * (waterheater, stove) must be activated.
     */

    std::vector<int> activationTimes_;

    int activationIndex_;

    std::vector<int> waterHeaterActivationTimes_;

    std::vector<int> waterHeaterActivationTemps_;

    std::vector<int> waterHeaterActivationAmounts_;

    int waterHeaterActivationIndex_;

    std::vector<int> dishwasherActivationTimes_;

    int dishwasherActivationIndex_;

    std::vector<int> microwaveActivationTimes_;

    int microwaveActivationIndex_;

    std::vector<int> ovenActivationTimes_;

    int ovenActivationIndex_;

    std::vector<int> refrigeratorActivationTimes_;

    int refrigeratorActivationIndex_;

    std::vector<int> stoveActivationTimes_;

    std::vector<int> stoveBurnerDurations_;

    std::vector<int> stoveBurnerSettings_;

    int stoveActivationIndex_;

    std::vector<int> toasterActivationTimes_;

    int toasterActivationIndex_;

    std::vector<int> televisionActivationTimes_;

    int televisionActivationIndex_;

    /**
     * Pointer to the log
     */
    static log4cxx::LoggerPtr log;
};


#endif /* PERSON_H_ */
