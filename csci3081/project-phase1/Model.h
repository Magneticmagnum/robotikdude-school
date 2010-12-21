#ifndef MODEL_H_
#define MODEL_H_

class Logger; // forward declaration

#include <string>
using std::string;

/**
 * The base definition of something that can be simulated. Everything that can
 * be simulated must extend this class. It provides a set of required methods
 * and helper methods for the extension.
 */
class Model
{
  public:

    /**
     * Default constructor: creates a basic Model with no Logger.
     */
    Model();

    /**
     * Creates a Model and adds the given Logger.
     */
    Model(Logger* logger);

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

  protected:

    /**
     * Prints a INFO message to the Logger.
     */
    void print(const string& string) const;

  private:

    /**
     * The Logger used by this Model.
     */
    Logger* logger_;

};

#endif /* MODEL_H_ */
