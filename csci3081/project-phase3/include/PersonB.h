#ifndef PERSON_H_
#define PERSON_H_

// TODO user23: comment all

#include "Model.h"
#include "Scheduler.h"
#include "House.h"
#include "Random.h"
class ModelFactory; // forward declaration

#include <log4cxx/logger.h>

#include <string>
#include <map>

class Person; // forward declaration
typedef void* (Person::*state_t)(void*);
#define MAX_NAME_LENGTH 20

typedef struct
{
    char nextState[MAX_NAME_LENGTH];
    int minTime;
    int maxTime;
    int randTime;
} randomtime_t;

typedef struct
{
    char nextState[MAX_NAME_LENGTH];
    int delayTime;
} delay_t;

typedef struct
{
    char nextState[MAX_NAME_LENGTH];
    int minDelay;
    int maxDelay;
    int randDelay;
} randomdelay_t;

typedef struct
{
    char nextState1[MAX_NAME_LENGTH];
    char nextState2[MAX_NAME_LENGTH];
    double chance;
} choice_t;

typedef struct
{
    char nextState[MAX_NAME_LENGTH];
    char model[MAX_NAME_LENGTH];
    char* actions;
} action_t;

typedef struct
{
    char nextState[MAX_NAME_LENGTH];
    char model[MAX_NAME_LENGTH];
} wait_t;

typedef struct
{
    char nextState1[MAX_NAME_LENGTH];
    char nextState2[MAX_NAME_LENGTH];
    int condTime;
} timecond_t;

typedef struct
{
    char nextState[MAX_NAME_LENGTH];
    char timerName[MAX_NAME_LENGTH];
    bool waiting;
    int waitTime;
} ptimer_t;

typedef struct
{
    char nextState1[MAX_NAME_LENGTH];
    char nextState2[MAX_NAME_LENGTH];
    char timerName[MAX_NAME_LENGTH];
    int condTime;
} ptimercond_t;

class Person: public Model
{
  public:
    Person(const std::string& configuration, Scheduler* scheduler,
           House* house, Random* random);

    int addState(const char* name, const char* type, char* args);

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

    bool isRunning() const;

    const char* getState();

    const void* getStateArg();

    bool action(const std::string& actions);

    bool changeState(const char* name);

    // current-state RandomTime next-state min-time max-time
    void* state_RandomTime(void* arg);

    // current-state Delay next-state delay-time
    void* state_Delay(void* arg);

    // current-state Delay next-state min-delay max-delay
    void* state_RandomDelay(void* arg);

    // current-state Choice next-state1 next-state2 chance-for2
    // should take no time, immediately next state
    void* state_Choice(void* arg);

    // current-state Action next-state model arg0 arg1 ... argn
    void* state_Action(void* arg);

    // current-state Wait next-state model
    void* state_Wait(void* arg);

    // current-state TimeCond next-state1 next-state2 time-for2
    // should take no time, immediately next state
    void* state_TimeCond(void* arg);

    // current-state Timer next-state <set timer-name> or <wait timer-name time-after-set>
    // if set, should take no time, immediately next state
    void* state_Timer(void* arg);

    // current-state TimerCond next-state1 next-state2 timer-name time-for2
    // should take no time, immediately next state
    void* state_TimerCond(void* arg);

  private:

    state_t currentState_;
    void* currentArg_;
    const char* currentName_;
    int stateSwitchTime_;

    std::map<const char*, state_t, cstrcmp_t> states_;
    std::map<const char*, void*, cstrcmp_t> args_;
    std::map<const char*, int, cstrcmp_t> timers_;

    Scheduler* scheduler_;
    House* house_;
    Random* random_;

    static log4cxx::LoggerPtr log_;

};

#endif /* PERSON_H_ */
