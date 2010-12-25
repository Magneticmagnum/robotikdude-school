#include "PersonB.h"
#include "ModelFactory.h"
#include "ConfigurationOptions.h"

#include <cstdlib>
#include <sstream>
#include <cstring>
#include <iostream>
#include <fstream>

log4cxx::LoggerPtr Person::log_(log4cxx::Logger::getLogger("Person"));

Person::Person(const std::string& configuration, Scheduler* scheduler,
               House* house, Random* random) :
  scheduler_(scheduler), house_(house), random_(random), currentState_(0),
      currentArg_(0), currentName_(0), stateSwitchTime_(0)
{
  LOG4CXX_TRACE(log_, "--> Person::Person(const std::string&, Scheduler*, ModelFactory*)");

  std::ifstream input(configuration.c_str());
  if (input.fail()) {
    // TODO log error, unable to open file
  }
  else {

    char buffer[CONFIG_BUFFER];
    char* name;
    char* type;
    char* args;

    while (!input.eof()) {
      input.getline(buffer, CONFIG_BUFFER);
      if (!input.fail()) {

        if ((name = strtok(buffer, " ")) != 0 // state name
            && name[0] != '#' // comment
            && (type = strtok(0, " ")) != 0 // state type
            && (args = strtok(0, "\r\n")) != 0) { // state args

          char* mem = (char*) malloc(sizeof(char) * (strlen(name) + 1));
          strcpy(mem, name);
          if (addState(mem, type, args) == -1) {
            delete (mem);
          }
          //          else {
          //            std::cout << "Added state " << mem << ":" << type << std::endl;
          //          }
        }

      } // end if (!input.fail())
    } // end while(!input.eof())}

  } // end else [if (input.fail())]

  LOG4CXX_TRACE(log_, "<-- Person::Person(const std::string&, Scheduler*, ModelFactory*)");
}

int Person::addState(const char* name, const char* type, char* args)
{
  int error = 0;

  // **************************************************************************
  // create RandomTime state argument
  // **************************************************************************
  if (strcmp(type, PERSON_RANDOM_TIME) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState;
    char* minTimeHour;
    char* minTimeMinute;
    char* maxTimeHour;
    char* maxTimeMinute;
    if ((nextState = strtok(args, " ")) != 0 // next state name
        && (minTimeHour = strtok(0, ":")) != 0 // min time hour
        && (minTimeMinute = strtok(0, " ")) != 0 // min time minute
        && (maxTimeHour = strtok(0, ":")) != 0 // max time hour
        && (maxTimeMinute = strtok(0, " ")) != 0) { // max time minute
      randomtime_t* data = (randomtime_t*) malloc(sizeof(randomtime_t));

      //      std::cout << nextState << "|" << minTimeHour << "|" << minTimeMinute
      //          << "|" << maxTimeHour << "|" << maxTimeMinute << std::endl;
      strcpy(data->nextState, nextState);
      data->minTime = (atoi(minTimeHour) * MINUTES_PER_HOUR
          + atoi(minTimeMinute)) * TICKS_PER_MINUTE;
      data->maxTime = (atoi(maxTimeHour) * MINUTES_PER_HOUR
          + atoi(maxTimeMinute)) * TICKS_PER_MINUTE;
      data->randTime = -1;

      states_[name] = &Person::state_RandomTime;
      args_[name] = (void*) data;
      //      std::cout << data->nextState << "|" << data->minTime << "|"
      //          << data->maxTime << "|" << data->randTime << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create Delay state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_DELAY) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState;
    char* delayTime;
    if ((nextState = strtok(args, " ")) != 0 // next state name
        && (delayTime = strtok(0, " "))) { // delay time
      delay_t* data = (delay_t*) malloc(sizeof(delay_t));

      //      std::cout << nextState << "|" << delayTime << std::endl;
      strcpy(data->nextState, nextState);
      data->delayTime = atoi(delayTime) * TICKS_PER_MINUTE;

      states_[name] = &Person::state_Delay;
      args_[name] = (void*) data;
      //      std::cout << data->nextState << "|" << data->delayTime << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create RandomDelay state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_RANDOM_DELAY) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState;
    char* minDelay;
    char* maxDelay;
    if ((nextState = strtok(args, " ")) != 0 // next state name
        && (minDelay = strtok(0, " ")) != 0 // min delay
        && (maxDelay = strtok(0, " ")) != 0) { // max delay
      randomdelay_t* data = (randomdelay_t*) malloc(sizeof(randomdelay_t));

      //      std::cout << nextState << "|" << minDelay << "|" << maxDelay << std::endl;
      strcpy(data->nextState, nextState);
      data->minDelay = atoi(minDelay) * TICKS_PER_MINUTE;
      data->maxDelay = atoi(maxDelay) * TICKS_PER_MINUTE;
      data->randDelay = -1;

      states_[name] = &Person::state_RandomDelay;
      args_[name] = (void*) data;
      //      std::cout << data->nextState << "|" << data->minDelay << "|"
      //          << data->maxDelay << "|" << data->randDelay << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create Choice state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_CHOICE) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState1;
    char* nextState2;
    char* chance;
    if ((nextState1 = strtok(args, " ")) != 0 // next state name 1
        && (nextState2 = strtok(0, " ")) != 0 // next state name 2
        && (chance = strtok(0, " ")) != 0) { // chance for 2
      choice_t* data = (choice_t*) malloc(sizeof(choice_t));

      //      std::cout << nextState1 << "|" << nextState2 << "|" << chance
      //          << std::endl;
      strcpy(data->nextState1, nextState1);
      strcpy(data->nextState2, nextState2);
      data->chance = atof(chance);

      states_[name] = &Person::state_Choice;
      args_[name] = (void*) data;
      //      std::cout << data->nextState1 << "|" << data->nextState2 << "|"
      //          << data->chance << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create Action state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_ACTION) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState;
    char* model;
    char* actions;
    if ((nextState = strtok(args, " ")) != 0 // next state name
        && (model = strtok(0, " ")) != 0 // model
        && (actions = strtok(0, "\r\n")) != 0) { // actions
      action_t* data = (action_t*) malloc(sizeof(action_t));

      //      std::cout << nextState << "|" << model << "|" << actions << std::endl;
      strcpy(data->nextState, nextState);
      strcpy(data->model, model);
      data->actions = (char*) malloc(sizeof(char) * strlen(actions) + 1);
      strcpy(data->actions, actions);

      states_[name] = &Person::state_Action;
      args_[name] = (void*) data;
      //      std::cout << data->nextState << "|" << data->model << "|"
      //          << data->actions << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create Wait state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_WAIT) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState;
    char* model;
    if ((nextState = strtok(args, " ")) != 0 // next state name
        && (model = strtok(0, " ")) != 0) { // model
      wait_t* data = (wait_t*) malloc(sizeof(wait_t));

      //      std::cout << nextState << "|" << model << std::endl;
      strcpy(data->nextState, nextState);
      strcpy(data->model, model);

      states_[name] = &Person::state_Wait;
      args_[name] = (void*) data;
      //      std::cout << data->nextState << "|" << data->model << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create TimeCond state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_TIME_COND) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState1;
    char* nextState2;
    char* timeHour;
    char* timeMin;
    if ((nextState1 = strtok(args, " ")) != 0 // next state name 1
        && (nextState2 = strtok(0, " ")) != 0 // next state name 2
        && (timeHour = strtok(0, ":")) != 0 // time hour
        && (timeMin = strtok(0, " ")) != 0) { // time min
      timecond_t* data = (timecond_t*) malloc(sizeof(timecond_t));

      //      std::cout << nextState1 << "|" << nextState2 << "|" << timeHour << "|"
      //          << timeMin << std::endl;
      strcpy(data->nextState1, nextState1);
      strcpy(data->nextState2, nextState2);
      data->condTime = (atoi(timeHour) * MINUTES_PER_HOUR + atoi(timeMin))
          * TICKS_PER_MINUTE;

      states_[name] = &Person::state_TimeCond;
      args_[name] = (void*) data;
      //      std::cout << data->nextState1 << "|" << data->nextState2 << "|"
      //          << data->condTime << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create Timer state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_TIMER) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState;
    char* action;
    char* timerName;
    char* waitTime;
    if ((nextState = strtok(args, " ")) != 0 // next state name
        && (action = strtok(0, " ")) != 0 // action
        && (timerName = strtok(0, " ")) != 0) { // timer name)
      waitTime = strtok(0, " "); // wait time
      ptimer_t* data = (ptimer_t*) malloc(sizeof(ptimer_t));

      //      std::cout << nextState << "|" << action << "|" << timerName;
      //      if (waitTime != 0)
      //        std::cout << "|" << waitTime;
      //      std::cout << std::endl;

      if (strcmp(action, PERSON_TIMER_WAIT) == 0 && waitTime != 0) {
        data->waiting = true;
        data->waitTime = atoi(waitTime);
      }
      else if (strcmp(action, PERSON_TIMER_SET) == 0) {
        data->waiting = false;
        data->waitTime = -1;
      }
      else {
        delete (data);
        // TODO error, unknown timer action
        error = -1;
      }

      if (error == 0) {
        strcpy(data->nextState, nextState);
        strcpy(data->timerName, timerName);

        states_[name] = &Person::state_Timer;
        args_[name] = (void*) data;
        //      std::cout << data->nextState << "|" << data->waiting << "|"
        //          << data->timerName << "|" << data->waitTime << std::endl;
      }
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  // **************************************************************************
  // create TimerCond state argument
  // **************************************************************************
  else if (strcmp(type, PERSON_TIMER_COND) == 0) {
    //    std::cout << name << "|" << type << "|" << args << std::endl;
    char* nextState1;
    char* nextState2;
    char* timerName;
    char* condTime;
    if ((nextState1 = strtok(args, " ")) != 0 // next state name 1
        && (nextState2 = strtok(0, " ")) != 0 // next state name 2
        && (timerName = strtok(0, " ")) != 0 // timer name
        && (condTime = strtok(0, " ")) != 0) { // condition time
      ptimercond_t* data = (ptimercond_t*) malloc(sizeof(ptimercond_t));

      //      std::cout << nextState1 << "|" << nextState2 << "|" << timerName << "|"
      //          << condTime << std::endl;
      strcpy(data->nextState1, nextState1);
      strcpy(data->nextState2, nextState2);
      strcpy(data->timerName, timerName);
      data->condTime = atoi(condTime);

      states_[name] = &Person::state_TimerCond;
      args_[name] = (void*) data;
      //      std::cout << data->nextState1 << "|" << data->nextState2 << "|"
      //          << data->timerName << "|" << data->condTime << std::endl;
    }
    else {
      // TODO error parsing args
      error = -1;
    }
  }

  else {
    // TODO error matching state type
    error = -1;
    //    std::cout << "Could not match: " << type << std::endl;
  }

  if (currentState_ == 0 && error != -1 && states_.find(name) != states_.end()) {
    currentState_ = states_[name];
    currentArg_ = args_[name];
    currentName_ = name;
  }

  return error;
}

void Person::tick()
{
  LOG4CXX_TRACE(log_, "--> Person::tick()");
  (*this.*currentState_)(currentArg_);
  LOG4CXX_TRACE(log_, "<-- Person::tick()");
}

double Person::getPower() const
{
  LOG4CXX_TRACE(log_, "--> Person::getPower()");
  LOG4CXX_TRACE(log_, "<-- Person::getPower()");
  return 0.0;
}

double Person::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> Person::getEnergy()");
  LOG4CXX_TRACE(log_, "<-- Person::getEnergy()");
  return 0.0;
}

const char* Person::getState()
{
  LOG4CXX_TRACE(log_, "--> Person::getState()");
  LOG4CXX_TRACE(log_, "<-- Person::getState()");
  return currentName_;
}

const void* Person::getStateArg()
{
  LOG4CXX_TRACE(log_, "--> Person::getStateArgs()");
  LOG4CXX_TRACE(log_, "<-- Person::getStateArgs()");
  return currentArg_;
}

bool Person::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> Person::isRunning()");
  LOG4CXX_TRACE(log_, "<-- Person::isRunning()");
  return false;
}

bool Person::action(const std::string& actions)
{
  LOG4CXX_TRACE(log_, "--> Person::action(const std::string&)");
  LOG4CXX_TRACE(log_, "<-- Person::action(const std::string&)");
  return true;
}

bool Person::changeState(const char* name)
{
  LOG4CXX_TRACE(log_, "--> Person::setNextState(" << name << ")");
  bool noerror = true;

  if (states_.find(name) != states_.end()) {
    currentState_ = states_[name];
    currentArg_ = args_[name];
    currentName_ = name;
    stateSwitchTime_ = scheduler_->getTime();
    LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " Person changed state to " << name);
  }
  else {
    noerror = false;
    LOG4CXX_WARN(log_, "*** Could not find the state " << name);
  }
  LOG4CXX_TRACE(log_, "<-- Person::setNextState(" << name << ")");
  return noerror;
}

// current-state RandomTime next-state min-time max-time
void* Person::state_RandomTime(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_RandomTime(void*)");
  randomtime_t* data = (randomtime_t*) arg;
  if (data->randTime == -1) {
    data->randTime = data->minTime + (random_->normal() * (data->maxTime
        - data->minTime)); // hour and minute
    int day = scheduler_->getDay();
    if (stateSwitchTime_ % MINUTES_PER_DAY > data->randTime) {
      day += 1; // next day
    }
    data->randTime += day * MINUTES_PER_DAY;
  }

  if (scheduler_->getTime() >= data->randTime) {
    data->randTime = -1;
    changeState(data->nextState);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_RandomTime(void*)");
}

// current-state Delay next-state delay-time
void* Person::state_Delay(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_Delay(void*)");
  delay_t* data = (delay_t*) arg;
  if (scheduler_->getTime() >= stateSwitchTime_ + data->delayTime) {
    changeState(data->nextState);
  }

  LOG4CXX_TRACE(log_, "<-- Person::state_Delay(void*)");
}

// current-state Delay next-state min-delay max-delay
void* Person::state_RandomDelay(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_RandomDelay(void*)");
  randomdelay_t* data = (randomdelay_t*) arg;
  if (data->randDelay == -1) {
    data->randDelay = data->minDelay + (random_->normal() * (data->maxDelay
        - data->minDelay));
  }
  if (scheduler_->getTime() >= stateSwitchTime_ + data->randDelay) {
    data->randDelay = -1;
    changeState(data->nextState);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_RandomDelay(void*)");
}

// current-state Choice next-state1 next-state2 chance-for2
void* Person::state_Choice(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_Choice(void*)");
  choice_t* data = (choice_t*) arg;
  if (random_->normal() < data->chance) {
    changeState(data->nextState2);
  }
  else {
    changeState(data->nextState1);
  }

  // should take no time, immediately call next state
  (*this.*currentState_)(currentArg_);
  LOG4CXX_TRACE(log_, "<-- Person::state_Choice(void*)");
}

// current-state Action next-state model arg0 arg1 ... argn
void* Person::state_Action(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_Action(void*)");
  action_t* data = (action_t*) arg;
  Model* model = house_->getModel(data->model);
  if (model != 0) {
    model->action(data->actions);
  }
  else {
    LOG4CXX_WARN(log_, "*** Model " << data->model << " not found, moving to next state");
  }
  changeState(data->nextState);
  LOG4CXX_TRACE(log_, "<-- Person::state_Action(void*)");
}

// current-state Action next-state model
void* Person::state_Wait(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_Wait(void*)");
  wait_t* data = (wait_t*) arg;
  Model* model = house_->getModel(data->model);
  if (model != 0) {
    if (!model->isRunning()) {
      changeState(data->nextState);
    }
  }
  else {
    LOG4CXX_WARN(log_, "*** Model " << data->model << " not found, moving to next state");
    changeState(data->nextState);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_Wait(void*)");
}

// current-state TimeCond next-state1 next-state2 time-for2
// should take no time, immediately next state
void* Person::state_TimeCond(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_TimeCond(void*)");
  timecond_t* data = (timecond_t*) arg;
  if (scheduler_->getTime() % MINUTES_PER_DAY >= data->condTime) {
    changeState(data->nextState2);
  }
  else {
    changeState(data->nextState1);
  }

  // should take no time, immediately call next state
  (*this.*currentState_)(currentArg_);
  LOG4CXX_TRACE(log_, "<-- Person::state_TimeCond(void*)");
}

// current-state Timer next-state <set timer-name> or <wait timer-name time-after-set>
// if set, should take no time, immediately next state
void* Person::state_Timer(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_Timer(void*)");
  ptimer_t* data = (ptimer_t*) arg;
  if (data->waiting) {
    if (scheduler_->getTime() >= timers_[data->timerName] + data->waitTime) {
      changeState(data->nextState);
    }
  }
  else {
    changeState(data->nextState);

    // should take no time, immediately all next state
    (*this.*currentState_)(currentArg_);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_Timer(void*)");
}

// current-state TimerCond next-state1 next-state2 timer-name time-for2
// should take no time, immediately next state
void* Person::state_TimerCond(void* arg)
{
  LOG4CXX_TRACE(log_, "--> Person::state_TimerCond(void*)");
  ptimercond_t* data = (ptimercond_t*) arg;
  if (scheduler_->getTime() >= timers_[data->timerName] + data->condTime) {
    changeState(data->nextState2);
  }
  else {
    changeState(data->nextState1);
  }

  // should take no time, immediately call next state
  (*this.*currentState_)(currentArg_);
  LOG4CXX_TRACE(log_, "<-- Person::state_TimerCond(void*)");
}
