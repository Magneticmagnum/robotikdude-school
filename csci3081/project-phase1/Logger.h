#ifndef LOGGER_H_
#define LOGGER_H_

class Scheduler; // forward declaration

#include <string>
using std::string;

/**
 * The Logger class provides an interface between the
 * other modules in the simulation and the log file, which
 * is used to capture information about each run of the
 * simulation.
 *
 * Logger requires access to the scheduler, so that it
 * will always know how many ticks have passed in the simulation.
 * Hence, both of its constructors require a pointer to the
 * scheduler object.  They also require the file path of the
 * log file.
 *
 * Logger has one useful method:  print().  Print takes a message
 * from whichever object has called it and prepends the
 * current internal time of the simulation, then writes
 * the revised message out to the log file.
 */
class Logger
{
  public:
    /**
     * Constructor that takes a pointer to a scheduler object and
     * a string object for log file name.
     */
    Logger(Scheduler* scheduler, string& filePath);

    /**
     * Prints the current time followed by the string passed.
     */
    void print(const string& string) const;

    /*
     * Accessor: Returns the Scheduler pointer for use in test cases.
     */
    Scheduler* getScheduler() const;

    /*
     * Accessor: Returns the log file path as a string object for
     * use in test cases.
     */
    string getFilePath() const;

  private:
    /*
     * A string object for log file path.
     */
    string filePath_;

    /**
     * A pointer to the Scheduler so the Logger can get the current time.
     */
    Scheduler* scheduler_;
};

#endif /* LOGGER_H_ */
