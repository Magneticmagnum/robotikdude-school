#include "Person.h"

#include "Scheduler.h"
#include "Dishwasher.h"
#include "Microwave.h"
#include "Oven.h"
#include "Refrigerator.h"
#include "Stove.h"
#include "Television.h"
#include "Toaster.h"
#include "WaterHeater.h"

#include <cstdlib>
#include <sstream>

#include <iostream>

log4cxx::LoggerPtr Person::log_(log4cxx::Logger::getLogger("Person"));

Person::Person() :
  stateSwitchTime_(0), daysSinceDishes_(0),
      showerDelay_(PERSON_DEFAULT_SHOWER_DELAY),
      breakfastDelay_(PERSON_DEFAULT_BREAKFAST_DELAY),
      breakfastTime_(PERSON_DEFAULT_BREAKFAST_TIME),
      dinnerTimeNice_(PERSON_DEFAULT_DINNER_TIME_NICE),
      dinnerTimeQuick_(PERSON_DEFAULT_DINNER_TIME_QUICK),
      dishesDelay_(PERSON_DEFAULT_DISHES_DELAY),
      bathFillTime_(PERSON_DEFAULT_BATH_FILL_TIME), wakeTime_(30 + (rand()
          / (RAND_MAX / 30))), showerTime_(rand() / (RAND_MAX / 5) + 5),
      homeTime_(rand() / (RAND_MAX / 60)), microwaveUseCount_(0), bathTime_(15
          + rand() / (RAND_MAX / 5)), bedTime_(rand() / (RAND_MAX / 30))
{
  LOG4CXX_TRACE(log_, "--> Person::Person()");

  scheduler_ = Scheduler::getInstance();
  dishwasher_ = (Dishwasher*) Model::getInstance(MODEL_DISHWASHER);
  microwave_ = (Microwave*) Model::getInstance(MODEL_MICROWAVE);
  oven_ = (Oven*) Model::getInstance(MODEL_OVEN);
  refrigerator_ = (Refrigerator*) Model::getInstance(MODEL_REFRIGERATOR);
  stove_ = (Stove*) Model::getInstance(MODEL_STOVE);
  television_ = (Television*) Model::getInstance(MODEL_TELEVISION);

  // I have NO idea why I need to do this but it makes it work and core dumps
  // otherwise...
  Model* temp = Model::getInstance(MODEL_TOASTER);
  toaster_ = dynamic_cast<Toaster*> (temp);

  waterheater_ = (WaterHeater*) Model::getInstance(MODEL_WATERHEATER);

  statePointer_ = &Person::state_asleep;

  LOG4CXX_DEBUG(log_, "    Person created.");
  LOG4CXX_DEBUG(log_, "    State switch time: " << stateSwitchTime_ << ".");
  LOG4CXX_DEBUG(log_, "    Days since dishes: " << daysSinceDishes_ << ".");
  LOG4CXX_DEBUG(log_, "    Shower delay: " << showerDelay_ << ".");
  LOG4CXX_DEBUG(log_, "    Breakfast delay: " << breakfastDelay_ << ".");
  LOG4CXX_DEBUG(log_, "    Dinner time (nice): " << dinnerTimeNice_ << ".");
  LOG4CXX_DEBUG(log_, "    Dinner time (quick): " << dinnerTimeQuick_ << ".");
  LOG4CXX_DEBUG(log_, "    Dishes delay: " << dishesDelay_ << ".");
  LOG4CXX_DEBUG(log_, "    Bath fill time: " << bathFillTime_ << ".");
  LOG4CXX_DEBUG(log_, "    Home time: " << homeTime_ << ".");

  LOG4CXX_TRACE(log_, "<-- Person::Person()");
}

// TODO log
Person::Person(ConfigMap* configuration, Scheduler* scheduler,
               Dishwasher* dishwasher, Microwave* microwave, Oven* oven,
               Refrigerator* refrigerator, Stove* stove,
               Television* television, Toaster* toaster,
               WaterHeater* waterheater) :
  stateSwitchTime_(0), daysSinceDishes_(0),
      showerDelay_(PERSON_DEFAULT_SHOWER_DELAY),
      breakfastDelay_(PERSON_DEFAULT_BREAKFAST_DELAY),
      breakfastTime_(PERSON_DEFAULT_BREAKFAST_TIME),
      dinnerTimeNice_(PERSON_DEFAULT_DINNER_TIME_NICE),
      dinnerTimeQuick_(PERSON_DEFAULT_DINNER_TIME_QUICK),
      dishesDelay_(PERSON_DEFAULT_DISHES_DELAY),
      bathFillTime_(PERSON_DEFAULT_BATH_FILL_TIME), wakeTime_(30 + (rand()
          / (RAND_MAX / 30))), showerTime_(rand() / (RAND_MAX / 5) + 5),
      homeTime_(rand() / (RAND_MAX / 60)), microwaveUseCount_(0), bathTime_(15
          + rand() / (RAND_MAX / 5)), bedTime_(rand() / (RAND_MAX / 30))
{
  LOG4CXX_TRACE(log_, "--> Person::Person()");

  scheduler_ = scheduler;
  dishwasher_ = dishwasher;
  microwave_ = microwave;
  oven_ = oven;
  refrigerator_ = refrigerator;
  stove_ = stove;
  television_ = television;
  toaster_ = toaster;
  waterheater_ = waterheater;

  statePointer_ = &Person::state_asleep;

  LOG4CXX_DEBUG(log_, "    Person created.");
  LOG4CXX_DEBUG(log_, "    State switch time: " << stateSwitchTime_ << ".");
  LOG4CXX_DEBUG(log_, "    Days since dishes: " << daysSinceDishes_ << ".");
  LOG4CXX_DEBUG(log_, "    Shower delay: " << showerDelay_ << ".");
  LOG4CXX_DEBUG(log_, "    Breakfast delay: " << breakfastDelay_ << ".");
  LOG4CXX_DEBUG(log_, "    Dinner time (nice): " << dinnerTimeNice_ << ".");
  LOG4CXX_DEBUG(log_, "    Dinner time (quick): " << dinnerTimeQuick_ << ".");
  LOG4CXX_DEBUG(log_, "    Dishes delay: " << dishesDelay_ << ".");
  LOG4CXX_DEBUG(log_, "    Bath fill time: " << bathFillTime_ << ".");
  LOG4CXX_DEBUG(log_, "    Home time: " << homeTime_ << ".");

  LOG4CXX_TRACE(log_, "<-- Person::Person()");
}

void Person::tick()
{
  LOG4CXX_TRACE(log_, "--> Person::tick()");
  (this->*statePointer_)();
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

int Person::state_asleep()
{
  LOG4CXX_TRACE(log_, "--> Person::state_asleep()");

  // wakes up between 6:30 and 7:00 --> state switch
  if (scheduler_->getHour() == 6 && scheduler_->getMinute() >= wakeTime_
      || scheduler_->getHour() == 7 && scheduler_->getMinute() == 0) {

    // 50% of the time he will take a shower
    if (rand() < RAND_MAX / 2) {
      stateSwitchTime_ = scheduler_->getTime();
      statePointer_ = &Person::state_shower;
      STATE_INFO_MSG("Person woke up and is taking a shower");
    }

    // 50% of the time he will skip the shower
    else {
      stateSwitchTime_ = scheduler_->getTime();
      statePointer_ = &Person::state_breakfast;
      STATE_INFO_MSG("Person woke up and is skipping the shower");

      // reset the upTime
      wakeTime_ = 30 + (rand() / (RAND_MAX / 30));
    }
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_asleep()");
}

int Person::state_shower()
{
  LOG4CXX_TRACE(log_, "--> Person::state_shower()");

  int showerDiff = scheduler_->getTime() - stateSwitchTime_ - showerDelay_;

  if (showerDiff >= 0) {
    if (waterheater_->getWater(8.0, 40.0) != 40.0) {
      // brrr... cold shower
    }

    // done with the shower --> state switch
    if (showerDiff >= showerTime_) {
      STATE_INFO_MSG("Person is done with their shower");
      stateSwitchTime_ = scheduler_->getTime();
      statePointer_ = &Person::state_breakfast;

      // reset the length of the shower
      showerTime_ = rand() / (RAND_MAX / 5) + 5;
    }
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_shower()");
}

int Person::state_breakfast()
{
  LOG4CXX_TRACE(log_, "--> Person::state_breakfast()");

  int breakfastDiff = scheduler_->getTime() - stateSwitchTime_
      - breakfastDelay_;

  if (breakfastDiff == 0) {
    STATE_INFO_MSG("Person is starting breakfast");
    refrigerator_->setInUse(true);

    // coffee
    stove_->turnOnBurner(3, 4);

    // food
    if (rand() < RAND_MAX / 2) {
      stove_->turnOnBurner(2, 5);
    }
    else {
      microwave_->turnOn();
    }

    // mmm.... toast
    toaster_->turnOn();
  }
  else if (breakfastDiff >= breakfastTime_) {
    STATE_INFO_MSG("Person is done with breakfast, time to go to work");
    // done with breakfast --> state switch
    refrigerator_->setInUse(false);

    stateSwitchTime_ = scheduler_->getTime();
    statePointer_ = &Person::state_work;
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_breakfast()");
}

int Person::state_work()
{
  LOG4CXX_TRACE(log_, "--> Person::state_work()");

  // gets home between 6:30 and 7:00 --> state switch
  if ((scheduler_->getHour() == 17 && scheduler_->getMinute() >= homeTime_ + 30)
      || (scheduler_->getHour() == 18 && scheduler_->getMinute() >= homeTime_
          - 30)) {
    STATE_INFO_MSG("Person is done with work, time to go home");

    stateSwitchTime_ = scheduler_->getTime();
    statePointer_ = &Person::state_dinner;

    // reset the home time
    homeTime_ = rand() / (RAND_MAX / 60);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_work()");
}

int Person::state_dinner()
{
  LOG4CXX_TRACE(log_, "--> Person::state_dinner()");

  int homeHour = (stateSwitchTime_ / 60) % 24;

  if (homeHour == 17) {
    if (scheduler_->getTime() == stateSwitchTime_ + 1) {
      STATE_INFO_MSG("Person is making a nice dinner");
      refrigerator_->setInUse(true);
      stove_->turnOnBurner(3, 15);
      stove_->turnOnBurner(2, 20);
      stove_->turnOnBurner(1, 30);

      if (rand() < RAND_MAX / 5) {
        oven_->turnOn();
      }
    }

    // dinner finished --> switch states
    if (scheduler_->getTime() >= stateSwitchTime_ + dinnerTimeNice_) {
      refrigerator_->setInUse(false);
      microwaveUseCount_ = 0;

      STATE_INFO_MSG("Person now has to do the dishes");
      stateSwitchTime_ = scheduler_->getTime();
      statePointer_ = &Person::state_dishes;
    }
  }
  else if (homeHour == 18) {
    if (scheduler_->getTime() == stateSwitchTime_ + 1) {
      refrigerator_->setInUse(true);
      STATE_INFO_MSG("Person is making a quick dinner");
    }

    // use the microwave 3 times
    if (microwaveUseCount_ < 3 && !microwave_->isRunning()) {
      microwaveUseCount_++;
      microwave_->turnOn();
    }

    // dinner finished --> switch states
    if (scheduler_->getTime() >= stateSwitchTime_ + dinnerTimeQuick_) {
      refrigerator_->setInUse(false);
      microwaveUseCount_ = 0;

      daysSinceDishes_++;
      stateSwitchTime_ = scheduler_->getTime();
      if (daysSinceDishes_ >= 3) {
        STATE_INFO_MSG("Person now has to do the dishes");
        statePointer_ = &Person::state_dishes;
      }
      else if (rand() < RAND_MAX / 5) {
        STATE_INFO_MSG("Person feels like taking a bath");
        statePointer_ = &Person::state_bath;
      }
      else {
        STATE_INFO_MSG("Person is vegging out");
        statePointer_ = &Person::state_television;
      }
    }
  }
  else {
    // error! when did he get home?
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_dinner()");
}

int Person::state_dishes()
{
  LOG4CXX_TRACE(log_, "--> Person::state_dishes()");

  daysSinceDishes_ = 0;

  if (scheduler_->getTime() == stateSwitchTime_ + dishesDelay_) {
    dishwasher_->turnOn();
  }

  // dishes are done --> switch states
  if (scheduler_->getTime() >= stateSwitchTime_ + dishesDelay_
      && dishwasher_->getRunningTimeLeft() == 0) {
    stateSwitchTime_ = scheduler_->getTime();
    if (rand() < RAND_MAX / 5) {
      STATE_INFO_MSG("Person feels like taking a bath");
      statePointer_ = &Person::state_bath;
    }
    else {
      STATE_INFO_MSG("Person is vegging out");
      statePointer_ = &Person::state_television;
    }
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_dishes()");
}

int Person::state_bath()
{
  LOG4CXX_TRACE(log_, "--> Person::state_bath()");

  // filling tub
  if (stateSwitchTime_ + bathFillTime_ >= scheduler_->getTime()) {
    if (waterheater_->getWater(100 / bathFillTime_, 42) != 42) {
      // brrr... cold bath
    }
  }

  // bath done --> switch states
  else if (scheduler_->getTime() >= stateSwitchTime_ + bathFillTime_
      + bathTime_) {
    STATE_INFO_MSG("Person is vegging out");
    stateSwitchTime_ = scheduler_->getTime();
    statePointer_ = &Person::state_television;

    bathTime_ = 15 + rand() / (RAND_MAX / 5);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_bath()");
}

int Person::state_television()
{
  LOG4CXX_TRACE(log_, "--> Person::state_television()");

  if (!television_->isOn()) {
    television_->turnOn();
  }

  // bed time! --> switch states
  if (scheduler_->getHour() >= 23 && scheduler_->getMinute() >= bedTime_) {
    television_->turnOff();
    STATE_INFO_MSG("Person is going to bed");

    stateSwitchTime_ = scheduler_->getTime();
    statePointer_ = &Person::state_asleep;

    bedTime_ = rand() / (RAND_MAX / 30);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_television()");
}

state_t Person::getState()
{
  LOG4CXX_TRACE(log_, "--> Person::getState()");
  LOG4CXX_TRACE(log_, "<-- Person::getState()");
  return statePointer_;
}

int Person::getStateSwitchTime()
{
  LOG4CXX_TRACE(log_, "--> Person::getStateSwitchTime()");
  LOG4CXX_TRACE(log_, "<-- Person::getStateSwitchTime()");
  return stateSwitchTime_;
}

int Person::getDaysSinceDishes()
{
  LOG4CXX_TRACE(log_, "--> Person::getDaysSinceDishes()");
  LOG4CXX_TRACE(log_, "<-- Person::getDaysSinceDishes()");
  return daysSinceDishes_;
}
