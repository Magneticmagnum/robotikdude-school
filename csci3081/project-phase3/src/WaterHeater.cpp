#include "WaterHeater.h"
#include "ConfigurationOptions.h"

log4cxx::LoggerPtr WaterHeater::log_(log4cxx::Logger::getLogger("WaterHeater"));

WaterHeater::WaterHeater(ConfigMap* configuration, Scheduler* scheduler) :
  running_(false), waterTemperature_(WATERHEATER_DEFAULT_TEMP_OFF),
      timeRunning_(0.0), capacity_(WATERHEATER_DEFAULT_CAPACITY),
      heatLoss_(WATERHEATER_DEFAULT_HEAT_LOSS),
      heatGain_(WATERHEATER_DEFAULT_HEAT_GAIN),
      power_(WATERHEATER_DEFAULT_POWER), energy_(0),
      tempOn_(WATERHEATER_DEFAULT_TEMP_ON),
      tempOff_(WATERHEATER_DEFAULT_TEMP_OFF),
      tempIncoming_(WATERHEATER_DEFAULT_TEMP_INCOMING)
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::WaterHeater(ConfigMap*, Scheduler*)");
  scheduler_ = scheduler;
  initializeConfiguration(configuration);
  waterTemperature_ = tempOff_;

  LOG4CXX_DEBUG(log_, "    WaterHeater created " << (running_ ? "" : "not ")
                  << "running.");
  LOG4CXX_DEBUG(log_, "    Water Temperature: " << waterTemperature_ << ".");
  LOG4CXX_DEBUG(log_, "    Time running: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    Capacity: " << capacity_ << ".");
  LOG4CXX_DEBUG(log_, "    Heat loss: " << heatLoss_ << ".");
  LOG4CXX_DEBUG(log_, "    Heat gain: " << heatGain_ << ".");
  LOG4CXX_DEBUG(log_, "    Power: " << timeRunning_ << ".");
  LOG4CXX_DEBUG(log_, "    On temperature: " << tempOn_ << ".");
  LOG4CXX_DEBUG(log_, "    Off temperature: " << tempOff_ << ".");
  LOG4CXX_DEBUG(log_, "    Incoming water temperature: " << tempIncoming_ << ".");

  LOG4CXX_TRACE(log_, "<-- WaterHeater::WaterHeater(ConfigMap*, Scheduler*)");
}

void WaterHeater::initializeConfiguration(ConfigMap* config)
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::initializeConfiguration(ConfigMap*)");

  if (config == 0) {
    LOG4CXX_TRACE(log_, "    No configuration given, using the default values");
  }
  else {
    ConfigMap::iterator iter;
    for (iter = config->begin(); iter != config->end(); iter++) {

      // configure capacity
      if (strcmp(iter->first, WATERHEATER_CAPACITY) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          capacity_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_CAPACITY << " attribute must be greater then zero");
        }
      }

      // configure power
      else if (strcmp(iter->first, WATERHEATER_POWER) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          power_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_POWER << " attribute must be greater then zero");
        }
      }

      // configure heat-loss
      else if (strcmp(iter->first, WATERHEATER_HEAT_LOSS) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          heatLoss_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_HEAT_LOSS << " attribute must be greater then zero");
        }
      }

      // configure heat-gain
      else if (strcmp(iter->first, WATERHEATER_HEAT_GAIN) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          heatGain_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_HEAT_GAIN << " attribute must be greater then zero");
        }
      }

      // configure temp-on
      else if (strcmp(iter->first, WATERHEATER_TEMP_ON) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          tempOn_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_TEMP_ON << " attribute must be greater then zero");
        }
      }

      // configure temp-off
      else if (strcmp(iter->first, WATERHEATER_TEMP_OFF) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          tempOff_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_TEMP_OFF << " attribute must be greater then zero");
        }
      }

      // configure temp-incoming
      else if (strcmp(iter->first, WATERHEATER_TEMP_INCOMING) == 0) {
        double temp = atof(iter->second);
        if (temp > 0) {
          tempIncoming_ = temp;
        }
        else {
          LOG4CXX_WARN(log_, "*** WaterHeater's " << WATERHEATER_TEMP_INCOMING << " attribute must be greater then zero");
        }
      }

      // unknown configure option
      else {
        LOG4CXX_WARN(log_, "*** The WaterHeater attribute " << iter->first << " was not recognized");
      }

    } // end for
  } // end if (config == 0) else

  LOG4CXX_TRACE(log_, "<-- WaterHeater::initializeConfiguration(ConfigMap*)");
}

void WaterHeater::tick()
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::tick()");
  if (running_ && waterTemperature_ > tempOff_) {
    running_ = false;

    LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " WaterHeater was turned off, total energy used: " << getEnergy());
  }
  else if (running_ || waterTemperature_ < tempOn_) {
    timeRunning_++;
    energy_ += power_ * SECONDS_PER_TICK;
    waterTemperature_ += heatGain_ + heatLoss_;

    if (!running_) {
      LOG4CXX_INFO(log_, scheduler_->getTimeStr() << " WaterHeater was turned on");
    }

    running_ = true;
  }
  waterTemperature_ -= heatLoss_;
  LOG4CXX_TRACE(log_, "<-- WaterHeater::tick()");
}

double WaterHeater::getPower() const
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::getPower()");
  LOG4CXX_TRACE(log_, "<-- WaterHeater::getPower()");
  return (running_ ? power_ : 0);
}

double WaterHeater::getEnergy() const
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::getEnergy()");
  LOG4CXX_TRACE(log_, "<-- WaterHeater::getEnergy()");
  return energy_;
}

bool WaterHeater::isRunning() const
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::isRunning()");
  LOG4CXX_TRACE(log_, "<-- WaterHeater::isRunning()");
  return running_;
}

bool WaterHeater::action(const std::string&)
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::action(const std::string&)");
  LOG4CXX_TRACE(log_, "<-- WaterHeater::action(const std::string&)");
  return true;
}

double WaterHeater::getWater(double amount, double temperature)
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::getWater(" << amount << ", " << temperature << ")");
  if (amount > capacity_) {
    double extraAmount = amount - capacity_;
    double maxTemp = (waterTemperature_ * capacity_ + tempIncoming_
        * extraAmount) / amount;
    waterTemperature_ = tempIncoming_;
    temperature = (temperature >= maxTemp ? maxTemp : temperature);
  }
  else {
    if (temperature > waterTemperature_) {
      temperature = waterTemperature_;
    }
    waterTemperature_ = (tempIncoming_ * amount + waterTemperature_
        * (capacity_ - amount)) / capacity_;
  }
  LOG4CXX_TRACE(log_, "<-- WaterHeater::getWater(" << amount << ", " << temperature << ")");
  return temperature;
}

double WaterHeater::getWaterTemperature() const
{
  LOG4CXX_TRACE(log_, "--> WaterHeater::getWaterTemperature()");
  LOG4CXX_TRACE(log_, "<-- WaterHeater::getWaterTemperature()");
  return waterTemperature_;
}
