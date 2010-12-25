#include "WaterHeater.h"

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
  }
  else if (running_ || waterTemperature_ < WATERHEATER_TEMP_ON) {
    timeRunning_++;
    waterTemperature_ += WATERHEATER_HEAT_GAIN + WATERHEATER_HEAT_LOSS;
    running_ = true;
  }
  waterTemperature_ -= WATERHEATER_HEAT_LOSS;
}

double WaterHeater::getPower() const
{
  return (isRunning() ? WATERHEATER_POWER : 0);
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

Model& WaterHeater::operator-=(int amount)
{
  getWater(amount, waterTemperature_);
  return *this;
}
