#include "Model.h"

#include <iostream> // cout, endl
#include <fstream>  // ifstream
#include <cstring>  // strtok
#include <cstdlib>  // atof
//

log4cxx::LoggerPtr Model::log_(log4cxx::Logger::getLogger("Model"));

int Model::makeargv(const std::string& string, const char* delimiters,
                    char*** argvp)
{
  LOG4CXX_TRACE(log_, "--> Model::makeargv(const std::string&, const char*, char***)");
  if ((delimiters == 0) || (argvp == 0)) {
    LOG4CXX_ERROR(log_, "!!! Passed delimiters or where to put argv is null");
    LOG4CXX_TRACE(log_, "<-- Model::makeargv(const std::string&, const char*, char***)");
    return -1;
  }

  /* Taken from Unix Systems Programming, Robbins & Robbins, p37 */
  int error;
  int i;
  int numtokens;
  const char *snew;
  char *t;

  *argvp = 0;
  snew = string.c_str() + strspn(string.c_str(), delimiters);
  if ((t = (char*) malloc(strlen(snew) + 1)) == 0) {
    //    LOG4CXX_ERROR(log_, "!!! Unable to free memory for the argv");
    //    LOG4CXX_TRACE(log_, "<-- Model::makeargv(const std::string&, const char*, char***)");
    return -1;
  }
  strcpy(t, snew);
  numtokens = 0;
  if (strtok(t, delimiters) != 0) {
    for (numtokens = 1; strtok(0, delimiters) != 0; numtokens++) {
      ;
    }
  }

  if ((*argvp = (char**) malloc((numtokens + 1) * sizeof(char *))) == 0) {
    //    LOG4CXX_ERROR(log_, "!!! Unable to free memory for the argv");
    free(t);
    //    LOG4CXX_TRACE(log_, "<-- Model::makeargv(const std::string&, const char*, char***)");
    return -1;
  }

  if (numtokens == 0) {
    free(t);
  }
  else {
    strcpy(t, snew);
    **argvp = strtok(t, delimiters);
    for (i = 1; i < numtokens; i++) {
      *((*argvp) + i) = strtok(0, delimiters);
    }
  }
  *((*argvp) + numtokens) = 0;

  LOG4CXX_TRACE(log_, "<-- Model::makeargv(const std::string&, const char*, char***)");
  return numtokens;
}

void Model::freemakeargv(char** string)
{
  LOG4CXX_TRACE(log_, "--> Model::freemakeargv(char**)");
  if (string != 0) {
    if (*string != 0) {
      delete (*string);
    }
    delete (string);
  }
  LOG4CXX_TRACE(log_, "<-- Model::freemakeargv(char**)");
}

// model-type model-name model-attribute attribute-value
ConfigMap* Model::parseConfiguration(const std::string& file,
                                     const std::string& modelType,
                                     const std::string& name)
{
  LOG4CXX_TRACE(log_, "--> Model::parseConfiguration(" << file << ", " << modelType << ", " << name << ")");
  std::ifstream input(file.c_str());
  if (input.fail()) {
    LOG4CXX_WARN(log_, "*** Unable to open file: " << file);
    return 0;
  }

  ConfigMap* config = new ConfigMap();
  char buffer[CONFIG_BUFFER];
  char* attribute;
  char* value;

  while (!input.eof()) {
    input.getline(buffer, CONFIG_BUFFER);
    if (!input.fail()) {
      if (modelType.compare(strtok(buffer, " ")) == 0 // check model type
          && name.compare(strtok(0, " ")) == 0 // check model name
          && (attribute = strtok(0, " ")) != 0 // get attribute
          && (value = strtok(0, " \r\n")) != 0) { // get attribute value

        char* memAttr = (char*) malloc(sizeof(char) * (strlen(attribute) + 1));
        char* memValue = (char*) malloc(sizeof(char) * (strlen(value) + 1));
        strcpy(memAttr, attribute);
        strcpy(memValue, value);
        (*config)[memAttr] = memValue;
      }

    } // end if (!input.fail())
  } // end while(!input.eof())

  input.close();

  LOG4CXX_TRACE(log_, "<-- Model::parseConfiguration(" << file << ", " << modelType << ", " << name << ")");
  return config;
}

void Model::deleteConfiguration(ConfigMap* config)
{
  LOG4CXX_TRACE(log_, "--> Model::deleteConfiguration(ConfigMap*)");
  if (config != 0) {
    ConfigMap::iterator iter;
    for (iter = config->begin(); iter != config->end(); iter++) {
      delete (iter->first);
      delete (iter->second);
    }
    config->clear();
    delete (config);
  }
  LOG4CXX_TRACE(log_, "<-- Model::deleteConfiguration(ConfigMap*)");
}
