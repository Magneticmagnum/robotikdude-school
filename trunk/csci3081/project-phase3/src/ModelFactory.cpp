#include "ModelFactory.h"
#include "ConfigurationOptions.h"

log4cxx::LoggerPtr
    ModelFactory::log_(log4cxx::Logger::getLogger("ModelFactory"));

ModelFactory::ModelFactory(Scheduler* scheduler) :
  scheduler_(scheduler), random_(new Random())
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::ModelFactory(Scheduler*)");
  LOG4CXX_TRACE(log_, "<-- ModelFactory::ModelFactory(Scheduler*)");
}

ModelFactory::~ModelFactory()
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::~ModelFactory()");
  ModelMap::iterator iter;
  for (iter = models_.begin(); iter != models_.end(); iter++) {
    delete (iter->second);
  }
  models_.clear();
  delete (random_);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::~ModelFactory()");
}

Model* ModelFactory::getModel(const std::string& model)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getModel(" << model << ")");
  ModelMap::iterator m = models_.find(model);
  if (m != models_.end()) {
    LOG4CXX_TRACE(log_, "<-- ModelFactory::getModel(" << model << ")");
    return m->second;
  }
  else {
    LOG4CXX_TRACE(log_, "<-- ModelFactory::getModel(0)");
    return 0;
  }
}

Model* ModelFactory::createModel(const std::string& type,
                                 const std::string& name,
                                 const std::string& configFile, House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createModel(" << type << ", " << name << ", " << configFile << ", House*)");
  Model* model = getModel(name);
  if (model == 0) {
    if (type.compare(HOUSE) == 0) {
      model = createHouse(name, configFile);
    }
    else if (type.compare(BATH) == 0) {
      model = createBath(name, configFile, house);
    }
    else if (type.compare(DISHWASHER) == 0) {
      model = createDishwasher(name, configFile, house);
    }
    else if (type.compare(MICROWAVE) == 0) {
      model = createMicrowave(name, configFile, house);
    }
    else if (type.compare(OVEN) == 0) {
      model = createOven(name, configFile, house);
    }
    else if (type.compare(PERSON) == 0) {
      model = createPerson(name, configFile, house);
    }
    else if (type.compare(REFRIGERATOR) == 0) {
      model = createRefrigerator(name, configFile, house);
    }
    else if (type.compare(SHOWER) == 0) {
      model = createShower(name, configFile, house);
    }
    else if (type.compare(STOVE) == 0) {
      model = createStove(name, configFile, house);
    }
    else if (type.compare(TELEVISION) == 0) {
      model = createTelevision(name, configFile, house);
    }
    else if (type.compare(TOASTER) == 0) {
      model = createToaster(name, configFile, house);
    }
    else if (type.compare(WATERHEATER) == 0) {
      model = createWaterHeater(name, configFile, house);
    }
    else {
      LOG4CXX_WARN(log_, "*** Cannot create model, unable to match type " << type);
    }
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createModel(" << type << ", " << name << ", " << configFile << ", House*)");
  return model;
}

House* ModelFactory::getHouse(const std::string& house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getHouse(" << house << ")");
  Model* model = getModel(house);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getHouse(" << house << ")");
  return (House*) model;
}

House* ModelFactory::createHouse(const std::string& house,
                                 const std::string& configFile)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createHouse(" << house << ", " << configFile << ")");
  House* model = getHouse(house);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, HOUSE, house);
    model = new House(config, scheduler_);
    Model::deleteConfiguration(config);
    models_[house] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createHouse(" << house << ", " << configFile << ")");
  return model;
}

Bath* ModelFactory::getBath(const std::string& bath)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getBath(" << bath << ")");
  Model* model = getModel(bath);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getBath(" << bath << ")");
  return (Bath*) model;
}

Bath* ModelFactory::createBath(const std::string& bath,
                               const std::string& configFile, House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createBath(" << bath << ", " << configFile << ", House*)");
  Bath* model = getBath(bath);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, BATH, bath);
    model = new Bath(config, scheduler_, house);
    Model::deleteConfiguration(config);
    models_[bath] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createBath(" << bath << ", " << configFile << ", House*)");
  return model;
}

Dishwasher* ModelFactory::getDishwasher(const std::string& dishwasher)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getDishwasher(" << dishwasher << ")");
  Model* model = getModel(dishwasher);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getDishwasher(" << dishwasher << ")");
  return (Dishwasher*) model;
}

Dishwasher* ModelFactory::createDishwasher(const std::string& dishwasher,
                                           const std::string& configFile,
                                           House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createDishwasher(" << dishwasher << ", " << configFile << ", House*)");
  Dishwasher* model = getDishwasher(dishwasher);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, DISHWASHER,
                                                  dishwasher);
    model = new Dishwasher(config, scheduler_, house);
    Model::deleteConfiguration(config);
    models_[dishwasher] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createDishwasher(" << dishwasher << ", " << configFile << ", House*)");
  return model;
}

Microwave* ModelFactory::getMicrowave(const std::string& microwave)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getMicrowave(" << microwave << ")");
  Model* model = getModel(microwave);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getMicrowave(" << microwave << ")");
  return (Microwave*) getModel(microwave);
}

Microwave* ModelFactory::createMicrowave(const std::string& microwave,
                                         const std::string& configFile,
                                         House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createMicrowave(" << microwave << ", " << configFile << ", House*)");
  Microwave* model = getMicrowave(microwave);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, MICROWAVE,
                                                  microwave);
    model = new Microwave(config, scheduler_, house, random_);
    Model::deleteConfiguration(config);
    models_[microwave] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createMicrowave(" << microwave << ", " << configFile << ", House*)");
  return model;
}

Oven* ModelFactory::getOven(const std::string& oven)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getOven(" << oven << ")");
  Model* model = getModel(oven);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getOven(" << oven << ")");
  return (Oven*) model;
}

Oven* ModelFactory::createOven(const std::string& oven,
                               const std::string& configFile, House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createOven(" << oven << ", " << configFile << ", House*)");
  Oven* model = getOven(oven);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, OVEN, oven);
    model = new Oven(config, scheduler_);
    Model::deleteConfiguration(config);
    models_[oven] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createOven(" << oven << ", " << configFile << ", House*)");
  return model;
}

Person* ModelFactory::getPerson(const std::string& person)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getPerson(" << person << ")");
  Model* model = getModel(person);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getPerson(" << person << ")");
  return (Person*) model;
}

Person* ModelFactory::createPerson(const std::string& person,
                                   const std::string& configFile, House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createPerson(" << person << ", " << configFile << ", House*)");
  Person* model = getPerson(person);
  if (model == 0) {
    model = new Person(configFile, scheduler_, house, random_);
    models_[person] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createPerson(" << person << ", " << configFile << ", House*)");
  return model;
}

Refrigerator* ModelFactory::getRefrigerator(const std::string& refrigerator)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getBath(" << refrigerator << ")");
  Model* model = getModel(refrigerator);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getBath(" << refrigerator << ")");
  return (Refrigerator*) model;
}

Refrigerator* ModelFactory::createRefrigerator(const std::string& refrigerator,
                                               const std::string& configFile,
                                               House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createRefrigerator(" << refrigerator << ", " << configFile << ", House*)");
  Refrigerator* model = getRefrigerator(refrigerator);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, REFRIGERATOR,
                                                  refrigerator);
    model = new Refrigerator(config, scheduler_, random_);
    Model::deleteConfiguration(config);
    models_[refrigerator] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createRefrigerator(" << refrigerator << ", " << configFile << ", House*)");
  return model;
}

Shower* ModelFactory::getShower(const std::string& shower)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getShower(" << shower << ")");
  Model* model = getModel(shower);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getShower(" << shower << ")");
  return (Shower*) model;
}

Shower* ModelFactory::createShower(const std::string& shower,
                                   const std::string& configFile, House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createShower(" << shower << ", " << configFile << ", House*)");
  Shower* model = getShower(shower);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, SHOWER, shower);
    model = new Shower(config, scheduler_, house);
    Model::deleteConfiguration(config);
    models_[shower] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createShower(" << shower << ", " << configFile << ", House*)");
  return model;
}

Stove* ModelFactory::getStove(const std::string& stove)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getStove(" << stove << ")");
  Model* model = getModel(stove);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getStove(" << stove << ")");
  return (Stove*) model;
}

Stove* ModelFactory::createStove(const std::string& stove,
                                 const std::string& configFile, House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createStove(" << stove << ", " << configFile << ", House*)");
  Stove* model = getStove(stove);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, STOVE, stove);
    model = new Stove(scheduler_);
    Model::deleteConfiguration(config);
    models_[stove] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createStove(" << stove << ", " << configFile << ", House*)");
  return model;
}

Television* ModelFactory::getTelevision(const std::string& television)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getTelevision(" << television << ")");
  Model* model = getModel(television);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getTelevision(" << television << ")");
  return (Television*) model;
}

Television* ModelFactory::createTelevision(const std::string& television,
                                           const std::string& configFile,
                                           House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createTelevision(" << television << ", " << configFile << ", House*)");
  Television* model = getTelevision(television);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, TELEVISION,
                                                  television);
    model = new Television(config, scheduler_);
    Model::deleteConfiguration(config);
    models_[television] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createTelevision(" << television << ", " << configFile << ", House*)");
  return model;
}

Toaster* ModelFactory::getToaster(const std::string& toaster)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getToaster(" << toaster << ")");
  Model* model = getModel(toaster);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getToaster(" << toaster << ")");
  return (Toaster*) model;
}

Toaster* ModelFactory::createToaster(const std::string& toaster,
                                     const std::string& configFile,
                                     House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createToaster(" << toaster << ", " << configFile << ", House*)");
  Toaster* model = getToaster(toaster);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, TOASTER, toaster);
    model = new Toaster(scheduler_);
    Model::deleteConfiguration(config);
    models_[toaster] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createToaster(" << toaster << ", " << configFile << ", House*)");
  return model;
}

WaterHeater* ModelFactory::getWaterHeater(const std::string& waterheater)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::getBath(" << waterheater << ")");
  Model* model = getModel(waterheater);
  LOG4CXX_TRACE(log_, "<-- ModelFactory::getBath(" << waterheater << ")");
  return (WaterHeater*) model;
}

WaterHeater* ModelFactory::createWaterHeater(const std::string& waterheater,
                                             const std::string& configFile,
                                             House* house)
{
  LOG4CXX_TRACE(log_, "--> ModelFactory::createWaterHeater(" << waterheater << ", " << configFile << ", House*)");
  WaterHeater* model = getWaterHeater(waterheater);
  if (model == 0) {
    ConfigMap* config = Model::parseConfiguration(configFile, WATERHEATER,
                                                  waterheater);
    model = new WaterHeater(config, scheduler_);
    Model::deleteConfiguration(config);
    models_[waterheater] = model;
  }
  LOG4CXX_TRACE(log_, "<-- ModelFactory::createWaterHeater(" << waterheater << ", " << configFile << ", House*)");
  return model;
}
