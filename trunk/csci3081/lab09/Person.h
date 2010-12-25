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

#define  MICROWAVE     "microwave"
#define  STOVE         "stove"
#define  DISHWASHER    "dishwasher"
#define  REFRIGERATOR  "refrigerator"
#define  TOASTER       "toaster"
#define  BATHROOM      "bathroom"
#define  OVEN          "oven"

/**
 *
 */
class Person: public Model
{
  public:

    /**
     * Creates a new Person object
     */
    Person();

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
};


#endif /* PERSON_H_ */
