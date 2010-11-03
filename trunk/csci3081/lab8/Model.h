#ifndef MODEL_H_
#define MODEL_H_

/**
 * The base definition of something that can be simulated. Everything that can
 * be simulated must extend this class. It provides a set of required methods
 * and helper methods for the extension.
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

};

#endif /* MODEL_H_ */
