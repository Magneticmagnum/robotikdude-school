#include "Person.h"
#include "WaterHeater.h"
#include "Microwave.h"
#include "Dishwasher.h"
#include "Toaster.h"
#include "Stove.h"
#include "Oven.h"
#include "Television.h"
#include "Refrigerator.h"

#define DISHWASHER             "dishwasher"
#define MICROWAVE              "microwave"
#define OVEN                   "oven"
#define REFRIGERATOR           "refrigerator"
#define STOVE                  "stove"
#define TELEVISION             "television"
#define TOASTER                "toaster"
#define WATERHEATER            "waterheater"

#define BASE_WAKEUP_TIME       390    //The earliest time a person can wake up, in ticks after midnight
#define WAKEUP_RANGE           60     //Difference between earliest possible
                                      //wakeup time and latest possible time.
#define BASE_SLEEP_TIME        1380   //The earliest time a person can go to bed
#define SLEEP_RANGE            30     //The possible range of bedtime differences

#define WAKE_SHOWER_DIFFERENCE 5      //Amount of time, in ticks, between waking and showering
#define SHOWER_PROBABILITY     0.50   //The probability that a person will take a shower
                                      //on any given day
#define SHOWER_BASE_TIME        5      //Minimum amount of time that a shower lasts
#define SHOWER_RANGE           5      //Range, in ticks, of possible shower times
#define SHOWER_TEMP            40     //Temperature of shower water, in degrees celsius
#define SHOWER_FLOW_RATE       8      //Liters of water per minute for the shower

#define SHOWER_BREAKFAST_DIFFERENCE 15     //Amount of time, in ticks, between showering
                                      //and cooking
#define BREAKFAST_DURATION     10     //Number of ticks a person spends cooking
#define COFFEE_DURATION        4      //Amount of time a person makes coffee during
                                      //breakfast
#define COFFEE_STOVE_SETTING   "high" //Stove setting for making coffee
#define MICROWAVE_BREAKFAST_PROBABILITY 0.50 //Probability of making breakfast with microwave
#define OPTIONAL_STOVE_DURATION 5     //Duration of use for stove, non-coffee
#define OPTIONAL_STOVE_SETTING  "medium" //Setting for above use of stove

#define ARRIVE_HOME_MIN_TIME   1050   //Earliest a person may arrive home, in ticks
#define ARRIVE_HOME_MAX_RANGE  60     //ARRIVE_HOME_MIN_TIME + AARIVE_HOME_MAX_RANGE
                                      //is equal to latest time a person may arrive home
#define COOK_TIME_LONG         40     //If the person arrives home early, they cook for
                                      //40 minutes
#define OVEN_PROBABILITY       0.20   //Probability of using the oven for dinner
#define BURNER_COUNT           3      //Number of burners to use while cooking dinner
#define BURNER_ONE_TIME        15     //Number of ticks to use first burner
#define BURNER_ONE_SETTING     "high" //Setting for burner one
#define BURNER_TWO_TIME        20     //Number of ticks to use second burner
#define BURNER_TWO_SETTING     "medium" //Setting for burner two
#define BURNER_THREE_TIME      30     //Number of ticks to use third burner
#define BURNER_THREE_SETTING  "low"  //Setting for burner three
#define COOK_TIME_SHORT        10     //If the person arrives home late, they cook for 10
                                      //minutes.

#define COOK_DISHWASHER_RANGE  20     //Number of minutes between cooking and running
                                      //dishwasher
#define DISHWASHER_LIMIT       3      //Max number of days the dishwasher can go before
                                      //being run

#define COOK_BATH_RANGE        30     //Time between cooking and bathing
#define BATH_PROBABILITY       0.20   //Probability of taking a bath
#define BATH_WATER_AMOUNT      100.0  //Amount of water in a bath, in liters
#define BATH_TEMP              42.0   //Temp of bath, in degrees celsius
#define BATH_FILL_TIME         4      //Time, in ticks, it takes to fill bath
#define BATH_MIN_TIME          15     //Min duration of a bath
#define BATH_RANGE             5      //Maximum range of a bath: so MIN_TIME +
                                      //RANGE = maximum duration of a bath

#define LOW                    1
#define MEDIUM                 2
#define HIGH                   3

log4cxx::LoggerPtr Person::log(log4cxx::Logger::getLogger("Person"));

Person::Person () : tickCounter_(0), dailyTickCounter_(0), daysSinceDishwasherRun_(0),
    activationTimes_(std::vector<int>()), activationIndex_(0),
    waterHeaterActivationTimes_(std::vector<int>()),
    waterHeaterActivationTemps_(std::vector<int>()),
    waterHeaterActivationAmounts_(std::vector<int>()),
    waterHeaterActivationIndex_(0),
    dishwasherActivationTimes_(std::vector<int>()), dishwasherActivationIndex_(0),
    microwaveActivationTimes_(std::vector<int>()), microwaveActivationIndex_(0),
    ovenActivationTimes_(std::vector<int>()), ovenActivationIndex_(0),
    refrigeratorActivationTimes_(std::vector<int>()), refrigeratorActivationIndex_(0),
    stoveActivationTimes_(std::vector<int>()), stoveBurnerDurations_(std::vector<int>()),
    stoveBurnerSettings_(std::vector<int>()), stoveActivationIndex_(0),
    toasterActivationTimes_(std::vector<int>()), toasterActivationIndex_(0),
    televisionActivationTimes_(std::vector<int>()), televisionActivationIndex_(0)
{
  reset();
}

Person::Person (int seed)
{
  srand(seed);

  Person();
}

void Person::tick ()
{
  LOG4CXX_TRACE(log, "Entering person's tick() method.");
  tickCounter_++;
  if(dailyTickCounter_ >= 1440) {

    LOG4CXX_TRACE(log,
      "Reached midnight; resetting dailyTickCounter and calling reset() method.");

    dailyTickCounter_ = 0;
    reset();
  } else {
    dailyTickCounter_++;
  }

  if(dailyTickCounter_ == activationTimes_[activationIndex_])
  {
    LOG4CXX_TRACE(log,
          "Found an activation event at "
          << dailyTickCounter_ << " ticks.  Searching for details.");

    if(waterHeaterActivationTimes_[waterHeaterActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                "Found a waterheater event at "
                << dailyTickCounter_ << " ticks.  Activating.");

      ((WaterHeater*)getInstance(WATERHEATER))->
          getWater(waterHeaterActivationAmounts_[waterHeaterActivationIndex_],
                   waterHeaterActivationTemps_[waterHeaterActivationIndex_]);
      waterHeaterActivationIndex_++;
    }

    if(dishwasherActivationTimes_[dishwasherActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                      "Found a dishwasher event at "
                      << dailyTickCounter_ << " ticks.  Activating.");

      ((Dishwasher*)getInstance(DISHWASHER))->turnOn();
      dishwasherActivationIndex_++;
    }

    if(microwaveActivationTimes_[microwaveActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                      "Found a microwave event at "
                      << dailyTickCounter_ << " ticks.  Activating.");

      ((Microwave*)getInstance(MICROWAVE))->turnOn();
      microwaveActivationIndex_++;
    }

    if(ovenActivationTimes_[ovenActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                      "Found an oven event at "
                      << dailyTickCounter_ << " ticks.  Activating.");

      ((Oven*)getInstance(OVEN))->turnOn();
      ovenActivationIndex_++;
    }

    if(refrigeratorActivationTimes_[refrigeratorActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                      "Found a refrigerator event at "
                      << dailyTickCounter_ << " ticks.  Activating.");

      ((Refrigerator*)getInstance(REFRIGERATOR))->setInUse(true);
      refrigeratorActivationIndex_++;
    }

    if(stoveActivationTimes_[stoveActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                      "Found a stove event at "
                      << dailyTickCounter_ << " ticks.  Activating.");

      ((Stove*)getInstance(STOVE))->
          turnOnBurner(stoveBurnerSettings_[stoveActivationIndex_],
                       stoveBurnerDurations_[stoveActivationIndex_]);
      stoveActivationIndex_++;
    }

    if(toasterActivationTimes_[toasterActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                      "Found a toaster event at "
                      << dailyTickCounter_ << " ticks.  Activating.");

      ((Toaster*)getInstance(TOASTER))->turnOn();
      toasterActivationIndex_++;
    }

    if(televisionActivationTimes_[televisionActivationIndex_] == dailyTickCounter_)
    {
      LOG4CXX_TRACE(log,
                    "Found a television event at "
                     << dailyTickCounter_ << " ticks.  Activating.");

            ((Television*)getInstance(TELEVISION))->turnOn();
            televisionActivationIndex_++;
    }

    activationIndex_++;
  }
}

double Person::getPower () const
{
  return 0.0;
}

double Person::getEnergy () const
{
  return 0.0;
}

int Person::getTickCounter() const
{
  return tickCounter_;
}

int Person::getDailyTickCounter() const
{
  return dailyTickCounter_;
}

int Person::getDaysSinceDishwasherRun() const
{
  return daysSinceDishwasherRun_;
}

int Person::getActivationIndex() const
{
  return activationIndex_;
}

std::vector<int> Person::getActivationTimes()
{
  return activationTimes_;
}

std::vector<int> Person::getStoveActivationTimes()
{
  return stoveActivationTimes_;
}

std::vector<int> Person::getMicrowaveActivationTimes()
{
  return microwaveActivationTimes_;
}

std::vector<int> Person::getOvenActivationTimes()
{
  return ovenActivationTimes_;
}

std::vector<int> Person::getDishwasherActivationTimes()
{
  return dishwasherActivationTimes_;
}

std::vector<int> Person::getToasterActivationTimes()
{
  return toasterActivationTimes_;
}

std::vector<int> Person::getRefrigeratorActivationTimes()
{
  return refrigeratorActivationTimes_;
}

std::vector<int> Person::getWaterHeaterActivationTimes()
{
  return waterHeaterActivationTimes_;
}

void Person::reset()
{
  LOG4CXX_TRACE(log, "Entering person's reset() method.");
  dailyTickCounter_ = 0;
  activationIndex_ = 0;
  microwaveActivationIndex_ = 0;
  refrigeratorActivationIndex_ = 0;
  toasterActivationIndex_ = 0;
  ovenActivationIndex_ = 0;
  dishwasherActivationIndex_ = 0;
  waterHeaterActivationIndex_ = 0;
  stoveActivationIndex_ = 0;
  televisionActivationIndex_ = 0;

  int wakeTime = BASE_WAKEUP_TIME + (rand() % WAKEUP_RANGE);
  bool isShower = false;

  LOG4CXX_TRACE(log, "In person.reset(), wakeup time is: " << wakeTime);

  //Set up shower-related activation times
  if(((double) rand() / (double) RAND_MAX) <= SHOWER_PROBABILITY)
  {
    isShower = true;
    int showerDuration = (SHOWER_BASE_TIME + (rand() % SHOWER_RANGE));
    for(int i = 0; i < showerDuration; i++)
    {
      activationTimes_.push_back(wakeTime + WAKE_SHOWER_DIFFERENCE + i);
      waterHeaterActivationTimes_.push_back(wakeTime + WAKE_SHOWER_DIFFERENCE + i);
      waterHeaterActivationTemps_.push_back(SHOWER_TEMP);
      waterHeaterActivationAmounts_.push_back(SHOWER_FLOW_RATE);
    }
    LOG4CXX_TRACE(log, "In person.reset(), person will take a shower with"
        "duration of: " << showerDuration << " ticks.");
  }

  //Set up breakfast preparation activation times
  int breakfastTime;
  bool useMicrowave = ((double) rand() / (double) RAND_MAX) >= MICROWAVE_BREAKFAST_PROBABILITY;

  if(isShower) {
    //Breakfast occurs a certain amount of time after the shower is over
    breakfastTime = activationTimes_.back() + SHOWER_BREAKFAST_DIFFERENCE;
  } else {
    //If no shower occurs, don't have to worry about shower duration
    breakfastTime = wakeTime + SHOWER_BREAKFAST_DIFFERENCE;
  }

  LOG4CXX_TRACE(log,
    "In person.reset(), breakfast occurs at: " << breakfastTime << " ticks.");

  //Use the stove to make coffee
  stoveActivationTimes_.push_back(breakfastTime);
  stoveBurnerDurations_.push_back(COFFEE_DURATION);
  stoveBurnerSettings_.push_back(HIGH);

  //If not using the microwave, will be using the stove
  if(!useMicrowave)
  {
    LOG4CXX_TRACE(log,
        "In person.reset(), using stove to make breakfast (not microwave).");

    stoveActivationTimes_.push_back(breakfastTime + COFFEE_DURATION);
    stoveBurnerDurations_.push_back(OPTIONAL_STOVE_DURATION);
    stoveBurnerSettings_.push_back(MEDIUM);
  }

  for(int i = 0; i < BREAKFAST_DURATION; i++) {
    //Need to alert the fridge that you are cooking.  Also, fill
    //in all activation times of cooking.
    activationTimes_.push_back(breakfastTime + i);
    refrigeratorActivationTimes_.push_back(breakfastTime + i);

  }

  //Use the microwave once.
  if(useMicrowave) {
    LOG4CXX_TRACE(log,
        "In person.reset(), using microwave to cook breakfast (not stove).");
    microwaveActivationTimes_.push_back(breakfastTime);
  }

  //Set up dinner preparation activation times
  int arriveHomeTime = ARRIVE_HOME_MIN_TIME + (rand() % ARRIVE_HOME_MAX_RANGE);

  LOG4CXX_TRACE(log,
      "In person.reset().  Arrive home at: " << arriveHomeTime << " ticks.");

  int finishDinnerTime;
  bool cookDinnerLong = (arriveHomeTime <= 1080);

  //Got home before 6:00 pm, need to use stove and possibly oven
  if(cookDinnerLong)
  {
    LOG4CXX_TRACE(log,
        "In person.reset().  Got home before 6:00 pm, cooking dinner w/stove.");

    bool useOven = (((double) rand() / (double) RAND_MAX) <= OVEN_PROBABILITY);

    LOG4CXX_TRACE(log,
        "In person.reset(), will cook dinner with oven? " << useOven);

    stoveActivationTimes_.push_back(arriveHomeTime);
    stoveActivationTimes_.push_back(arriveHomeTime + 1);
    stoveActivationTimes_.push_back(arriveHomeTime + 2);

    stoveBurnerDurations_.push_back(BURNER_ONE_TIME);
    stoveBurnerDurations_.push_back(BURNER_TWO_TIME);
    stoveBurnerDurations_.push_back(BURNER_THREE_TIME);

    stoveBurnerSettings_.push_back(HIGH);
    stoveBurnerSettings_.push_back(MEDIUM);
    stoveBurnerSettings_.push_back(LOW);

    for(int i = 0; i <= COOK_TIME_LONG; i++)
    {
      activationTimes_.push_back(arriveHomeTime + i);
      if(useOven)
      {
        ovenActivationTimes_.push_back(arriveHomeTime + i);
      }
    }
    finishDinnerTime = activationTimes_.back();
  } else {
    LOG4CXX_TRACE(log,
        "In person.reset(), got home after 6:00 pm: cooking dinner "
        "quickly (w/microwave only).");

    for(int i = 0; i<= COOK_TIME_SHORT; i++) {
      activationTimes_.push_back(arriveHomeTime + i);
      refrigeratorActivationTimes_.push_back(arriveHomeTime + i);
      if((arriveHomeTime + i) % 3 == 0) {
        microwaveActivationTimes_.push_back(arriveHomeTime + i);
      }
    }
    finishDinnerTime = activationTimes_.back();
  }

  //Check if the dishwasher needs to be run.
  if(daysSinceDishwasherRun_ >= DISHWASHER_LIMIT || cookDinnerLong) {
    LOG4CXX_TRACE(log,
        "In person.reset(), running dishwasher after dinner.");

    int dishwasherActivateTime = activationTimes_.back() + COOK_DISHWASHER_RANGE;
    activationTimes_.push_back(dishwasherActivateTime);
    dishwasherActivationTimes_.push_back(dishwasherActivateTime);
    daysSinceDishwasherRun_ = 0;
  } else {
    daysSinceDishwasherRun_++;
  }

  int bathDuration = 0;
  if(((double) rand() / (double) RAND_MAX) <= BATH_PROBABILITY)
  {
    LOG4CXX_TRACE(log,
            "In person.reset(), taking bath after dinner.");

    for(int i = 0; i < BATH_FILL_TIME; i++)
    {
      activationTimes_.push_back(finishDinnerTime + COOK_BATH_RANGE + i);
      waterHeaterActivationTimes_.push_back(finishDinnerTime + COOK_BATH_RANGE + i);
      waterHeaterActivationTemps_.push_back(BATH_TEMP);
      waterHeaterActivationAmounts_.push_back(BATH_WATER_AMOUNT / BATH_FILL_TIME);
    }
    bathDuration = BATH_MIN_TIME + (rand() % BATH_RANGE);
  }

  int sleepTime = BASE_SLEEP_TIME + (rand() % SLEEP_RANGE);
  int j = finishDinnerTime + bathDuration;

  LOG4CXX_TRACE(log,
          "In person.reset(), finished dinner. Now watching tv until bed at "
                << sleepTime);

  while(j < SLEEP_RANGE)
  {
    activationTimes_.push_back(j);
    televisionActivationTimes_.push_back(j);
  }
}
