#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "Model.h"
#include "Logger.h"

#include <vector>
using std::vector;

/**
 * The Scheduler class updates a list of models that are tied to itself
 * by 'running' the simulation for a certain amount of ticks using the
 * method run(int maxCount).
 *
 * The list of models to be updated by the scheduler is kept in
 * the vector modelList_, which holds a reference to each model.
 * The logger that is used to write to the log file is kept as a
 * reference in the variable logFile_.
 */
class Scheduler
{
  public:

    /**
     * Default constructor that initializes logFile_, ticksPassed_, and
     * modelList_ to zero/empty.
     */
    Scheduler();

    /**
     * Mutator: The Model instance thing shall be added to a list of models
     * that will be notified of ticks.
     */
    bool registerModel(Model* thing);

    /**
     * Accessor: returns the number of ticks that have passed since the
     * Scheduler was started.
     */
    int getTime() const;

    /**
     * Accessor: returns the number of models that the scheduler is updating.
     */
    int getModels() const;

    /**
     * Accessor: returns the vector of models being tracked by the scheduler.
     */
    vector<Model*> getList() const;

    /**
     * Mutator: Sets the reference to the log file.
     */
    void setLog(Logger* log);

    /**
     * A simple loop that increments a tick counter, writes an INFO message to
     * the log giving the current tick count, and notifies each of its
     * registered Models by calling their tick() methods (in any order) until
     * maxCount ticks have been generated.
     */
    void run(int maxCount);

  private:

    /**
     * Keeps track of the total ticks since the simulation was started.
     */
    int ticksPassed_;

    /**
     * Keeps a pointer to a log file.
     */
    Logger* logFile_;

    /**
     * Vector of pointers to Model instances that the simulator is responsible
     * for updating.
     */
    vector<Model*> modelList_;
};

#endif /* SCHEDULER_H_ */
