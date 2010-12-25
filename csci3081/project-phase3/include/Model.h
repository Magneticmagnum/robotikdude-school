#ifndef MODEL_H_
#define MODEL_H_

#include <log4cxx/logger.h>

#include <string> // string
#include <cstring> // strcmp
#include <map> // map
//

class strcmp_t
{
  public:
    bool operator()(const std::string& x, const std::string& y)
    {
      return x.compare(y) < 0;
    }
};

class cstrcmp_t
{
  public:
    bool operator()(const char* x, const char* y)
    {
      return strcmp(x, y) < 0;
    }
};

class Model; // forward declaration
typedef std::map<const std::string, Model*, strcmp_t> ModelMap;

// max length the line of a configuration file can be
#define CONFIG_BUFFER 128
typedef std::map<const char*, char*, cstrcmp_t> ConfigMap;

/**
 * TODO user23: comment
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

    // TODO user23: comment
    virtual bool isRunning() const = 0;

    // TODO user23: comment
    virtual bool action(const std::string& actions) = 0;

    // TODO user23: comment
    // Taken from Unix Systems Programming, Robbins & Robbins, p37
    static int makeargv(const std::string& string, const char* delimiters,
                        char*** argvp);

    // TODO user23: comment
    static void freemakeargv(char** string);

    /**
     * Parses a configuration file and returns a ConfigMap with the
     * corresponding elements.
     */
    static ConfigMap* parseConfiguration(const std::string& file,
                                         const std::string& modelType,
                                         const std::string& name);

    /**
     * Deletes a configuration map. Once this method has been called, the
     * ConfigMap pointer will no longer point to allocated memory and should
     * not be used again.
     */
    static void deleteConfiguration(ConfigMap* configuration);

  private:

    /**
     * The logger for Model.
     */
    static log4cxx::LoggerPtr log_;

};

#endif /* MODEL_H_ */
