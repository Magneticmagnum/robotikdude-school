#include "WaterHeater.h"
#include "Scheduler.h"

log4cxx::LoggerPtr WaterHeater::log_(log4cxx::Logger::getLogger("WaterHeater"));

WaterHeater::WaterHeater() :
  running_(false), waterTemperature_(WATERHEATER_TEMP_OFF), timeRunning_(0.0)
{
}

WaterHeater::WaterHeater(double temperature) :
  running_(false), waterTemperature_(temperature), timeRunning_(0.0)
{
}

void WaterHeater::tick()
{
  if (running_ && waterTemperature_ > WATERHEATER_TEMP_OFF) {
    running_ = false;

    LOG4CXX_INFO(log_, "    At time " << Scheduler::getInstance()->getTimeStr()
        << " the water heater was turned off. Total energy used: "
        << getEnergy() << ".");
  }
  else if (running_ || waterTemperature_ < WATERHEATER_TEMP_ON) {
    timeRunning_++;
    waterTemperature_ += WATERHEATER_HEAT_GAIN + WATERHEATER_HEAT_LOSS;

    if (!running_) {
      LOG4CXX_INFO(log_, "    At time " << Scheduler::getInstance()->getTimeStr()
          << " the water heater was turned on.");
    }

    running_ = true;
  }
  waterTemperature_ -= WATERHEATER_HEAT_LOSS;
}

double WaterHeater::getPower() const
{
  return WATERHEATER_POWER;
}

double WaterHeater::getEnergy() const
{
  return getPower() * timeRunning_;
}

double WaterHeater::getWater(double amount, double temperature)
{
  if (amount > WATERHEATER_CAPACITY) {
    double extraAmount = amount - WATERHEATER_CAPACITY;
    double maxTemp = (waterTemperature_ * WATERHEATER_CAPACITY
        + WATERHEATER_TEMP_INCOMING * extraAmount) / amount;
    waterTemperature_ = WATERHEATER_TEMP_INCOMING;
    return (temperature >= maxTemp ? maxTemp : temperature);
  }
  else {
    if (temperature > waterTemperature_) {
      temperature = waterTemperature_;
    }
    waterTemperature_ = (WATERHEATER_TEMP_INCOMING * amount + waterTemperature_
        * (WATERHEATER_CAPACITY - amount)) / WATERHEATER_CAPACITY;
    return temperature;
  }
}

double WaterHeater::getWaterTemperature() const
{
  return waterTemperature_;
}

bool WaterHeater::isRunning() const
{
  return running_;
}
