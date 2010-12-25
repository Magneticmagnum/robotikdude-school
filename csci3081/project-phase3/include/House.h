#ifndef HOUSE_H_
#define HOUSE_H_

#include "Model.h"
#include "Scheduler.h"

#include <log4cxx/logger.h>

#include <map>

// TODO user22: comment
class House: public Model
{
  public:

    /*
     * This constructor creates a house with a reference
     * to the scheduler object.
     */
    House(ConfigMap* map, Scheduler* scheduler);

    // The house's tick method does not modify anything in
    //the house object, but does alert all models contained
    //in this house object that a tick has passed.
    void tick();

    /*
     * Returns the instantaneous power usage of all appliances
     * in the house.
     */
    double getPower() const;

    /*
     * Returns the cumulative power usage of all appliances in
     * the house.
     */
    double getEnergy() const;

    // Returns true if any appliance in the house is running.
    bool isRunning() const;

    // A function that doesn't do anything.  It is present to
    //comply with the specification for House's parent class, Model.
    bool action(const std::string& actions);

    //Adds an appliance to the map of appliances attached to this
    //house.  Returns true if the appliance was successfully added,
    //or false if the appliance is already in the house.
    bool addModel(const std::string& modelName, Model* newModel);

    // Takes the unique name of a model and, if that model
    // is in this house's ModelMap, returns a pointer to that
    // model object.  Otherwise return null.
    Model* getModel(const std::string& modelName);

    //Removes an appliance from the houses list of models.  Returns
    //true if the appliance is successfully removed, or false if
    //the model was not there in the first place.
    bool removeModel(const std::string& modelName);

  private:

    /*
     * Made default constructor private.
     */
    House();

    /* A map of all the models (appliances, people) that this house
     * contains.
     */
    ModelMap models_;

    /* A pointer to the scheduler object associated with this house.
     * (There should only be one scheduler per simulation).
     */
    Scheduler* scheduler_;

    /**
     * The logger for House.
     */
    static log4cxx::LoggerPtr log_;
};

#endif /* HOUSE_H_ */
