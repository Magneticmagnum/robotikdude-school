#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Model.h"

#include <log4cxx/logger.h>

#include <vector>

#define SECONDS_PER_MINUTE (60)
#define MINUTES_PER_HOUR   (60)
#define HOURS_PER_DAY      (24)
#define SECONDS_PER_HOUR   (SECONDS_PER_MINUTE * MINUTES_PER_HOUR)
#define MINUTES_PER_DAY    (HOURS_PER_DAY * MINUTES_PER_HOUR)

#define TICKS_PER_MINUTE   (1)
#define TICKS_PER_HOUR     (TICKS_PER_MINUTE * MINUTES_PER_HOUR)
#define TICKS_PER_DAY      (TICKS_PER_HOUR * HOURS_PER_DAY)

#define SECONDS_PER_TICK   (SECONDS_PER_MINUTE / (double) TICKS_PER_MINUTE)

/**
 * The Scheduler class updates a list of models that are tied to itself by
 * 'running' the simulation for a certain amount of ticks using the method
 * run(int).
 *
 * The list of models to be updated by the scheduler is kept in the vector
 * modelList_, which holds a reference to each model.
 */
class Scheduler
{
  public:

    /**
     * Default constructor. Initializes the number of ticks passed to zero and
     * creates a vector of Model pointers.
     */
    Scheduler();

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
     * Accessor: returns the number of ticks that have passed since the
     * Scheduler was started.
     */
    virtual int getTime() const;

    /**
     * Accessor: returns the current minute of the hour.
     */
    virtual int getMinute() const;

    /**
     * Accessor: returns the current hour of the day.
     */
    virtual int getHour() const;

    /**
     * Accessor: returns how many days have passed since the biginnnig of the simulation.
     */
    virtual int getDay() const;

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
    virtual void run(int maxCount);

  private:

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
