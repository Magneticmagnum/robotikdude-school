#include "Model.h"

#include "Dishwasher.h"
#include "Microwave.h"
#include "Oven.h"
#include "PersonB.h"
#include "Refrigerator.h"
#include "Stove.h"
#include "Television.h"
#include "Toaster.h"
#include "WaterHeater.h"

Dishwasher Model::dishwasher_;
Microwave Model::microwave_;
Oven Model::oven_;
Person Model::person_;
Refrigerator Model::refrigerator_;
Stove Model::stove_;
Television Model::television_;
Toaster Model::toaster_;
WaterHeater Model::waterheater_;

log4cxx::LoggerPtr Model::log_(log4cxx::Logger::getLogger("Model"));

Model* Model::getInstance(const std::string& model)
{
  LOG4CXX_TRACE(log_, "--> Scheduler::getInstance(string)");
  if (model.compare(MODEL_DISHWASHER) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &dishwasher_;
  }
  else if (model.compare(MODEL_MICROWAVE) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &microwave_;
  }
  else if (model.compare(MODEL_OVEN) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &oven_;
  }
  else if (model.compare(MODEL_PERSON) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &person_;
  }
  else if (model.compare(MODEL_REFRIGERATOR) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &refrigerator_;
  }
  else if (model.compare(MODEL_STOVE) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &stove_;
  }
  else if (model.compare(MODEL_TELEVISION) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &television_;
  }
  else if (model.compare(MODEL_TOASTER) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &toaster_;
  }
  else if (model.compare(MODEL_WATERHEATER) == 0) {
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return &waterheater_;
  }
  else {
    LOG4CXX_ERROR(log_, "!!! Unrecognized string used to request model");
    LOG4CXX_TRACE(log_, "<-- Scheduler::getInstance(string)");
    return 0;
  }
}
