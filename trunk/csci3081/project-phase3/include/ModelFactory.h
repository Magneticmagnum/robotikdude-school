#ifndef MODELFACTORY_H_
#define MODELFACTORY_H_

#include "Model.h"
#include "Scheduler.h"
#include "House.h"

#include "Bath.h"
#include "Dishwasher.h"
#include "Microwave.h"
#include "Oven.h"
#include "PersonB.h"
#include "Refrigerator.h"
#include "Shower.h"
#include "Stove.h"
#include "Television.h"
#include "Toaster.h"
#include "WaterHeater.h"
#include "Random.h"

#include <log4cxx/logger.h>

#include <string>
#include <map>

// TODO user23: comment all
class ModelFactory
{
  public:

    ModelFactory(Scheduler* scheduler);

    virtual ~ModelFactory();

    Model* getModel(const std::string& model);
    Model* createModel(const std::string& type, const std::string& name,
                       const std::string& configFile, House* house);

    House* getHouse(const std::string& house);
    House* createHouse(const std::string& house, const std::string& configFile);

    Bath* getBath(const std::string& bath);
    Bath* createBath(const std::string& bath, const std::string& configFile,
                     House* house);

    Dishwasher* getDishwasher(const std::string& dishwasher);
    Dishwasher* createDishwasher(const std::string& dishwasher,
                                 const std::string& configFile, House* house);

    Microwave* getMicrowave(const std::string& microwave);
    Microwave* createMicrowave(const std::string& microwave,
                               const std::string& configFile, House* house);

    Oven* getOven(const std::string& oven);
    Oven* createOven(const std::string& oven, const std::string& configFile,
                     House* house);

    Person* getPerson(const std::string& person);
    Person* createPerson(const std::string& person,
                         const std::string& configFile, House* house);

    Refrigerator* getRefrigerator(const std::string& refrigerator);
    Refrigerator* createRefrigerator(const std::string& refrigerator,
                                     const std::string& configFile,
                                     House* house);

    Shower* getShower(const std::string& shower);
    Shower* createShower(const std::string& shower,
                         const std::string& configFile, House* house);

    Stove* getStove(const std::string& stove);
    Stove* createStove(const std::string& stove, const std::string& configFile,
                       House* house);

    Television* getTelevision(const std::string& television);
    Television* createTelevision(const std::string& television,
                                 const std::string& configFile, House* house);

    Toaster* getToaster(const std::string& toaster);
    Toaster* createToaster(const std::string& toaster,
                           const std::string& configFile, House* house);

    WaterHeater* getWaterHeater(const std::string& waterheater);
    WaterHeater* createWaterHeater(const std::string& waterheater,
                                   const std::string& configFile, House* house);

  private:

    ModelMap models_;

    Scheduler* scheduler_;

    Random* random_;

    static log4cxx::LoggerPtr log_;

};

#endif /* MODELFACTORY_H_ */
