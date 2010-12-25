#include "Model.h"

#include "Dishwasher.h"
#include "Microwave.h"
#include "Oven.h"
#include "Person.h"
#include "Refrigerator.h"
#include "Stove.h"
#include "Television.h"
#include "Toaster.h"
#include "WaterHeater.h"

//Dishwasher Model::dishwasher_;
//Microwave Model::microwave_;
Oven Model::oven_;
//Person Model::person_;
Refrigerator Model::refrigerator_;
Stove Model::stove_;
Television Model::television_;
Toaster Model::toaster_;
WaterHeater Model::waterheater_;

Model* Model::getInstance(const std::string& model)
{
  if (model.compare(MODEL_DISHWASHER) == 0) {
    //    return &dishwasher_;
    return 0;
  }
  else if (model.compare(MODEL_MICROWAVE) == 0) {
    //    return &microwave_;
    return 0;
  }
  else if (model.compare(MODEL_OVEN) == 0) {
    return &oven_;
  }
  else if (model.compare(MODEL_PERSON) == 0) {
    //    return &person_;
    return 0;
  }
  else if (model.compare(MODEL_REFRIGERATOR) == 0) {
    return &refrigerator_;
  }
  else if (model.compare(MODEL_STOVE) == 0) {
    return &stove_;
  }
  else if (model.compare(MODEL_TELEVISION) == 0) {
    return &television_;
  }
  else if (model.compare(MODEL_TOASTER) == 0) {
    return &toaster_;
  }
  else if (model.compare(MODEL_WATERHEATER) == 0) {
    return &waterheater_;
  }
  else {
    // error! not a proper model type requested.
    return 0;
  }
}

Model::operator int() const
{
  return (int) getEnergy();
}

Model::operator double() const
{
  return getEnergy();
}

std::ostream& operator<<(std::ostream& output, const Model& m)
{
  output << "Current power draw is " << m.getPower()
      << " and total energy used is " << m.getEnergy() << ".";
  return output;
}
