#ifndef PERSON_H_
#define PERSON_H_

#include "Model.h"
#include "Scheduler.h"

#include <log4cxx/logger.h>

#include <string>

#define PERSON_DEFAULT_SHOWER_DELAY       5
#define PERSON_DEFAULT_BREAKFAST_DELAY   15
#define PERSON_DEFAULT_BREAKFAST_TIME    10
#define PERSON_DEFAULT_DINNER_TIME_NICE  40
#define PERSON_DEFAULT_DINNER_TIME_QUICK 10
#define PERSON_DEFAULT_DISHES_DELAY      20
#define PERSON_DEFAULT_BATH_FILL_TIME     4

#define STATE_INFO_MSG(MSG) \
  LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " -- "MSG)

typedef int (Person::*state_t)(void);

class Person: public Model
{
  public:

    /**
     * Creates a new Person object
     */
    Person();

    Person(ConfigMap* configuration, Scheduler* scheduler,
           Dishwasher* dishwasher, Microwave* microwave, Oven* oven,
           Refrigerator* refrigerator, Stove* stove, Television* television,
           Toaster* toaster, WaterHeater* waterheater);

    /**
     * Alert the Person object to the passing of another tick (minute).
     */
    void tick();

    /*
     * Return the amount of power being used. Since the person does not
     * directly use electricity, this will always return 0.
     */
    double getPower() const;

    /*
     * Return the total amount of energy used by the person. Always 0.
     */
    double getEnergy() const;

    int state_asleep();

    int state_shower();

    int state_breakfast();

    int state_work();

    int state_dinner();

    int state_dishes();

    int state_bath();

    int state_television();

    state_t getState();

    int getStateSwitchTime();

    int getDaysSinceDishes();

  private:

    state_t statePointer_;

    int stateSwitchTime_;

    int daysSinceDishes_;

    int showerDelay_;
    int breakfastDelay_;
    int breakfastTime_;
    int dinnerTimeNice_;
    int dinnerTimeQuick_;
    int dishesDelay_;
    int bathFillTime_;

    Scheduler* scheduler_;
    Dishwasher* dishwasher_;
    Microwave* microwave_;
    Oven* oven_;
    Refrigerator* refrigerator_;
    Stove* stove_;
    Television* television_;
    Toaster* toaster_;
    WaterHeater* waterheater_;

    int wakeTime_;
    int showerTime_;
    int homeTime_;
    int microwaveUseCount_;
    int bathTime_;
    int bedTime_;

    static log4cxx::LoggerPtr log_;

};

#endif /* PERSON_H_ */
