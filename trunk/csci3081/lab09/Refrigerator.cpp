#include "Refrigerator.h"

#include <sstream>

Refrigerator::Refrigerator() :
  running_(true), tStateSwitch_(0), totalRunningTime_(0)
{
}

void Refrigerator::tick()
{
  tStateSwitch_++;
  if (running_) {
    totalRunningTime_++;
    if (tStateSwitch_ >= 3) {
      tStateSwitch_ = 0;
      running_ = false;

      std::string message = "Refrigerator turning off. Total energy used by"
        " refrigerator: ";

      std::stringstream out;
      out << getEnergy();
      message.append(out.str());
      message.append(".");

      // print(message);
    }
  }
  else {
    if (tStateSwitch_ >= 9) {
      tStateSwitch_ = 0;
      running_ = true;
      // print("Refrigerator turning on.");
    }
  }
}

double Refrigerator::getPower() const
{
  return REFRIGERATOR_POWER;
}

double Refrigerator::getEnergy() const
{
  return getPower() * totalRunningTime_;
}

bool Refrigerator::isRunning() const
{
  return running_;
}
