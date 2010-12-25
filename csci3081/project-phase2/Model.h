#ifndef MODEL_H_
#define MODEL_H_

class Dishwasher; // forward declaration
class Microwave; // forward declaration
class Oven; // forward declaration
class Person; // forward declaration
class Refrigerator; // forward declaration
class Stove; // forward declaration
class Television; // forward declaration
class Toaster; // forward declaration
class WaterHeater; // forward declaration

#include <log4cxx/logger.h>

#include <string>

#define MODEL_DISHWASHER   "dishwasher"
#define MODEL_MICROWAVE    "microwave"
#define MODEL_OVEN         "oven"
#define MODEL_PERSON       "person"
#define MODEL_REFRIGERATOR "refrigerator"
#define MODEL_STOVE        "stove"
#define MODEL_TELEVISION   "television"
#define MODEL_TOASTER      "toaster"
#define MODEL_WATERHEATER  "waterheater"

/**
 * The base definition of something that can be simulated. Everything that can
 * be simulated must extend this class. It provides a set of required methods
 * and helper methods for the extension.
 *
 * Model is also a singleton factory of all the possible models. By calling the
 * getInstance(string) method you can obtain a pointer the singleton copy of
 * any Model.
 */
class Model
{
  public:

    /**
     * Notifies the model that one tick of time has passed since the last call
     * to tick(). Subclasses must implement this function to create their
     * behaviors.
     */
    virtual void tick() = 0;

    /**
     * Returns the instantaneous power usage of this Model.
     */
    virtual double getPower() const = 0;

    /**
     * Returns the total energy usage of this Model since it was created.
     */
    virtual double getEnergy() const = 0;

    /**
     * Returns a static copy of the model that is requested using the string.
     */
    static Model* getInstance(const std::string& model);

  private:

    /**
     * A static copy of the Dishwasher class.
     */
    static Dishwasher dishwasher_;

    /**
     * A static copy of the Microwave class.
     */
    static Microwave microwave_;

    /**
     * A static copy of the Oven class.
     */
    static Oven oven_;

    /**
     * A static copy of the Person class.
     */
    static Person person_;

    /**
     * A static copy of the Refrigerator class.
     */
    static Refrigerator refrigerator_;

    /**
     * A static copy of the Stove class.
     */
    static Stove stove_;

    /**
     * A static copy of the Television class.
     */
    static Television television_;

    /**
     * A static copy of the Toaster class.
     */
    static Toaster toaster_;

    /**
     * A static copy of the WaterHeater class.
     */
    static WaterHeater waterheater_;

    /**
     * The logger for Model.
     */
    static log4cxx::LoggerPtr log_;

};

#endif /* MODEL_H_ */
