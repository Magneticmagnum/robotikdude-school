#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Model.h"

#include <log4cxx/logger.h>

#include <vector>

/**
 * The Scheduler class updates a list of models that are tied to itself by
 * 'running' the simulation for a certain amount of ticks using the method
 * run(int).
 *
 * The list of models to be updated by the scheduler is kept in the vector
 * modelList_, which holds a reference to each model.
 *
 * The Scheduler is also has a singleton instance and needs to be reset if you
 * plan to use it twice in the same program by calling reset().
 */
class Scheduler
{
  public:

    /**
     * Returns the singleton instance of Scheduler.
     */
    static Scheduler* getInstance();

    /**
     * Mutator: the Model instance thing shall be added to a list of models
     * that will be notified of ticks.
     */
    bool registerModel(Model* thing);

    /**
     * Mutator: removes all the Models and resets the tick counter to be zero.
     */
    void reset();

    /**
     * Accessor: returns the number of ticks that have passed since the
     * Scheduler was started.
     */
    int getTime() const;

    /**
     * Accessor: returns the current minute of the hour.
     */
    int getMinute() const;

    /**
     * Accessor: returns the current hour of the day.
     */
    int getHour() const;

    /**
     * Accessor: returns how many days have passed since the biginnnig of the simulation.
     */
    int getDay() const;

    /**
     * Accessor: returns a string of the form: "(dd:hh:mm)".
     */
    std::string getTimeStr() const;

    /**
     * Accessor: returns the number of models that the scheduler is updating.
     */
    int getModels() const;

    /**
     * Accessor: returns the vector of models being tracked by the scheduler.
     */
    std::vector<Model*> getList() const;

    /**
     * A simple loop that increments a tick counter, writes an INFO message to
     * the log giving the current tick count, and notifies each of its
     * registered Models by calling their tick() methods (in any order) until
     * maxCount ticks have been generated.
     */
    void run(int maxCount);

  private:

    /**
     * Default constructor. Initializes the number of ticks passed to zero and
     * creates a vector of Model pointers.
     */
    Scheduler();

    /**
     * the singleton instance of the Scheduler.
     */
    static Scheduler* singleton_;

    /**
     * Keeps track of the total ticks since the simulation was started.
     */
    int ticksPassed_;

    /**
     * Vector of pointers to Model instances that the simulator is responsible
     * for updating.
     */
    std::vector<Model*> modelList_;

    /**
     * The logger for Scheduler.
     */
    static log4cxx::LoggerPtr log_;
};

#endif /* SCHEDULER_H_ */
