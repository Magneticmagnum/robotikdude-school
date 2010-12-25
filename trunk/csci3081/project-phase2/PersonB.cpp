#include "PersonB.h"

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

log4cxx::LoggerPtr Person::log_(log4cxx::Logger::getLogger("Person"));

Person::Person() :
  stateSwitchTime_(0), daysSinceDishes_(0)
{
  LOG4CXX_TRACE(log_, "--> Person::Person()");
  statePointer_ = &Person::state_asleep;
  LOG4CXX_TRACE(log_, "<-- Person::Person()");
}

void Person::tick()
{
  LOG4CXX_TRACE(log_, "--> Person::tick()");
  (*this.*statePointer_)();
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
  static int wakeTime = 30 + (rand() / (RAND_MAX / 30));

  // wakes up between 6:30 and 7:00 --> state switch
  if (getHour() == 6 && getMinute() >= wakeTime || getHour() == 7
      && getMinute() == 0) {

    // 50% of the time he will take a shower
    if (rand() < RAND_MAX / 2) {
      stateSwitchTime_ = getTime();
      statePointer_ = &Person::state_shower;
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person woke up and is taking a shower");
    }

    // 50% of the time he will skip the shower
    else {
      stateSwitchTime_ = getTime();
      statePointer_ = &Person::state_breakfast;
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person woke up and is skipping the shower");

      // reset the upTime
      wakeTime = 30 + (rand() / (RAND_MAX / 30));
    }
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_asleep()");
}

int Person::state_shower()
{
  LOG4CXX_TRACE(log_, "--> Person::state_shower()");
  static WaterHeater* waterheater =
      (WaterHeater*) Model::getInstance(MODEL_WATERHEATER);

  static int showerTime = rand() / (RAND_MAX / 5) + 5;

  int showerDiff = getTime() - stateSwitchTime_ - PERSON_SHOWER_DELAY;

  if (showerDiff >= 0) {
    if (waterheater->getWater(8.0, 40.0) != 40.0) {
      // brrr... cold shower
    }

    // done with the shower --> state switch
    if (showerDiff >= showerTime) {
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person is done with their shower");
      stateSwitchTime_ = getTime();
      statePointer_ = &Person::state_breakfast;

      // reset the length of the shower
      showerTime = rand() / (RAND_MAX / 5) + 5;
    }
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_shower()");
}

int Person::state_breakfast()
{
  LOG4CXX_TRACE(log_, "--> Person::state_breakfast()");
  static Microwave* microwave =
      (Microwave*) Model::getInstance(MODEL_MICROWAVE);
  static Refrigerator* refrigerator =
      (Refrigerator*) Model::getInstance(MODEL_REFRIGERATOR);
  static Stove* stove = (Stove*) Model::getInstance(MODEL_STOVE);
  static Toaster* toaster = (Toaster*) Model::getInstance(MODEL_TOASTER);

  int breakfastDiff = getTime() - stateSwitchTime_ - PERSON_BREAKFAST_DELAY;

  if (breakfastDiff == 0) {
    LOG4CXX_INFO(log_, getTimeStr() << " -- "
        "Person is starting breakfast");
    refrigerator->setInUse(true);

    // coffee
    stove->turnOnBurner(3, 4);

    // food
    if (rand() < RAND_MAX / 2) {
      stove->turnOnBurner(2, 5);
    }
    else {
      microwave->turnOn();
    }

    // mmm.... toast
    toaster->turnOn();
  }
  else if (breakfastDiff >= PERSON_BREAKFAST_TIME) {
    LOG4CXX_INFO(log_, getTimeStr() << " -- "
        "Person is done with breakfast, time to go to work");
    // done with breakfast --> state switch
    refrigerator->setInUse(false);

    stateSwitchTime_ = getTime();
    statePointer_ = &Person::state_work;
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_breakfast()");
}

int Person::state_work()
{
  LOG4CXX_TRACE(log_, "--> Person::state_work()");
  static int homeTime = rand() / (RAND_MAX / 60);

  // gets home between 6:30 and 7:00 --> state switch
  if ((getHour() == 17 && getMinute() >= homeTime + 30) || (getHour() == 18
      && getMinute() >= homeTime - 30)) {
    LOG4CXX_INFO(log_, getTimeStr() << " -- "
        "Person is done with work, time to go home");

    stateSwitchTime_ = getTime();
    statePointer_ = &Person::state_dinner;

    // reset the home time
    homeTime = rand() / (RAND_MAX / 60);
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_work()");
}

int Person::state_dinner()
{
  LOG4CXX_TRACE(log_, "--> Person::state_dinner()");
  static Microwave* microwave =
      (Microwave*) Model::getInstance(MODEL_MICROWAVE);
  static Oven* oven = (Oven*) Model::getInstance(MODEL_OVEN);
  static Refrigerator* refrigerator =
      (Refrigerator*) Model::getInstance(MODEL_REFRIGERATOR);
  static Stove* stove = (Stove*) Model::getInstance(MODEL_STOVE);

  static int microwaveUseCount = 0;

  int homeHour = (stateSwitchTime_ / 60) % 24;

  if (homeHour == 17) {
    if (getTime() == stateSwitchTime_ + 1) {
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person is making a nice dinner");
      refrigerator->setInUse(true);
      stove->turnOnBurner(3, 15);
      stove->turnOnBurner(2, 20);
      stove->turnOnBurner(1, 30);

      if (rand() < RAND_MAX / 5) {
        oven->turnOn();
      }
    }

    // dinner finished --> switch states
    if (getTime() >= stateSwitchTime_ + PERSON_DINNER_TIME_LONG) {
      refrigerator->setInUse(false);
      microwaveUseCount = 0;

      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person now has to do the dishes");
      stateSwitchTime_ = getTime();
      statePointer_ = &Person::state_dishes;
    }
  }
  else if (homeHour == 18) {
    if (getTime() == stateSwitchTime_ + 1) {
      refrigerator->setInUse(true);
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person is making a quick dinner");
    }

    // use the microwave 3 times
    if (microwaveUseCount < 3 && !microwave->isRunning()) {
      microwaveUseCount++;
      microwave->turnOn();
    }

    // dinner finished --> switch states
    if (getTime() >= stateSwitchTime_ + PERSON_DINNER_TIME_SHORT) {
      refrigerator->setInUse(false);
      microwaveUseCount = 0;

      daysSinceDishes_++;
      stateSwitchTime_ = getTime();
      if (daysSinceDishes_ >= 3) {
        LOG4CXX_INFO(log_, getTimeStr() << " -- "
            "Person now has to do the dishes");
        statePointer_ = &Person::state_dishes;
      }
      else if (rand() < RAND_MAX / 5) {
        LOG4CXX_INFO(log_, getTimeStr() << " -- "
            "Person feels like taking a bath");
        statePointer_ = &Person::state_bath;
      }
      else {
        LOG4CXX_INFO(log_, getTimeStr() << " -- "
            "Person is vegging out");
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
  static Dishwasher* dishwasher =
      (Dishwasher*) Model::getInstance(MODEL_DISHWASHER);

  daysSinceDishes_ = 0;

  if (getTime() == stateSwitchTime_ + PERSON_DISHES_DELAY) {
    dishwasher->turnOn();
  }

  // dishes are done --> switch states
  if (getTime() >= stateSwitchTime_ + PERSON_DISHES_DELAY
      && dishwasher->getRunningTimeLeft() == 0) {
    stateSwitchTime_ = getTime();
    if (rand() < RAND_MAX / 5) {
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person feels like taking a bath");
      statePointer_ = &Person::state_bath;
    }
    else {
      LOG4CXX_INFO(log_, getTimeStr() << " -- "
          "Person is vegging out");
      statePointer_ = &Person::state_television;
    }
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_dishes()");
}

int Person::state_bath()
{
  LOG4CXX_TRACE(log_, "--> Person::state_bath()");
  static WaterHeater* waterheater =
      (WaterHeater*) Model::getInstance(MODEL_WATERHEATER);

  static int bathTime = 15 + rand() / (RAND_MAX / 5);

  // filling tub
  if (stateSwitchTime_ + PERSON_BATH_FILL_TIME >= getTime()) {
    if (waterheater->getWater(100 / PERSON_BATH_FILL_TIME, 42) != 42) {
      // brrr... cold bath
    }
  }
  // bath done --> switch states
  else if (getTime() >= stateSwitchTime_ + PERSON_BATH_FILL_TIME + bathTime) {
    LOG4CXX_INFO(log_, getTimeStr() << " -- "
        "Person is vegging out");
    stateSwitchTime_ = getTime();
    statePointer_ = &Person::state_television;
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_bath()");
}

int Person::state_television()
{
  LOG4CXX_TRACE(log_, "--> Person::state_television()");
  static Television* television =
      (Television*) Model::getInstance(MODEL_TELEVISION);

  static int bedTime = rand() / (RAND_MAX / 30);

  if (!television->isOn()) {
    television->turnOn();
  }

  // bed time! --> switch states
  if (getHour() >= 23 && getMinute() >= bedTime) {
    television->turnOff();
    LOG4CXX_INFO(log_, getTimeStr() << " -- "
        "Person is going to bed");

    stateSwitchTime_ = getTime();
    statePointer_ = &Person::state_asleep;
  }
  LOG4CXX_TRACE(log_, "<-- Person::state_television()");
}

state_t Person::getState()
{
  LOG4CXX_TRACE(log_, "--> Person::getState()");
  LOG4CXX_TRACE(log_, "<-- Person::getState()");
  return statePointer_;
}

int Person::getMinute()
{
  LOG4CXX_TRACE(log_, "--> Person::getMinute()");
  LOG4CXX_TRACE(log_, "<-- Person::getMinute()");
  return Scheduler::getInstance()->getMinute();
}

int Person::getHour()
{
  LOG4CXX_TRACE(log_, "--> Person::getHour()");
  LOG4CXX_TRACE(log_, "<-- Person::getHour()");
  return Scheduler::getInstance()->getHour();
}

int Person::getTime()
{
  LOG4CXX_TRACE(log_, "--> Person::getTime()");
  LOG4CXX_TRACE(log_, "<-- Person::getTime()");
  return Scheduler::getInstance()->getTime();
}

std::string Person::getTimeStr()
{
  LOG4CXX_TRACE(log_, "--> Person::getTimeStr()");
  LOG4CXX_TRACE(log_, "<-- Person::getTimeStr()");
  return Scheduler::getInstance()->getTimeStr();
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
