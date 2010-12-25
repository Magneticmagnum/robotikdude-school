#ifndef PERSON_H_
#define PERSON_H_

#include "Model.h"

#include <log4cxx/logger.h>

#include <string>

#define PERSON_SHOWER_DELAY       5
#define PERSON_BREAKFAST_DELAY   15
#define PERSON_BREAKFAST_TIME    10
#define PERSON_DINNER_TIME_LONG  40
#define PERSON_DINNER_TIME_SHORT 10
#define PERSON_DISHES_DELAY      20
#define PERSON_BATH_FILL_TIME     4

typedef int (Person::*state_t)(void);

class Person: public Model
{
  public:

    /**
     * Creates a new Person object
     */
    Person();

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

    int getMinute();

    int getHour();

    int getTime();

    std::string getTimeStr();

    int getStateSwitchTime();

    int getDaysSinceDishes();

  private:

    state_t statePointer_;

    int stateSwitchTime_;

    int daysSinceDishes_;

    static log4cxx::LoggerPtr log_;

};

#endif /* PERSON_H_ */
