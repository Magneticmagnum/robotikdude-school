#define TELEVISION_ON_POWER 180.0
#define TELEVISION_OFF_POWER 10.0

#ifndef TELEVISION_H_
#define TELEVISION_H_

#include "Model.h"

class Television: public Model
{
  public:
    /*
     * Creates a television object that starts in the off state.
     */
    Television();

    /*
     * Increments the internal counter for ticks and total time on or off depending on its state.
     */
    void tick();

    /*
     *  Returns energy used by television.
     */
    double getEnergy() const;

    /*
     * Returns the state of television: true of on, false if off.
     */
    bool isOn() const;

    /*
     * Turns television on.
     */
    void turnOn();

    /*
     * Turns television off.
     */
    void turnOff();

    /*
     * Accessor: Returns the total number of ticks the television has been on.
     */
    int getTotalTimeOn() const;

    /*
     * Accessor: Returns the total number of ticks the television has been off.
     */
    int getTotalTimeOff() const;

    /*
     * Accessor: Returns the total number of ticks that have passed.
     */
    int getTotalTicks() const;

    /*
     * Not used.  Returns 0;
     */
    double getPower() const;

  private:
    /*
     * Boolean variable to keep track of if the television is on or off.
     */
    bool state_;

    /*
     * Total time that the television has been on.
     */
    int totalTimeOn_;

    /*
     * Total time that the television has been off.
     */
    int totalTimeOff_;

    /*
     * Total ticks that have passed.
     */
    int totalTicks_;
};

#endif /* TELEVISION_H_ */
