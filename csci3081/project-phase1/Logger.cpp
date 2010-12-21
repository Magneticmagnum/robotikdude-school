#include "Logger.h"
#include "Scheduler.h"

#include <iostream>
#include <fstream>
using std::ios;
using std::ofstream;

// constructor for file path being passed as string object
Logger::Logger(Scheduler* sch_p, string& filePath)
{
  scheduler_ = sch_p;
  filePath_ = filePath;

  ofstream log; // for printing to log file

  // truncate file and print a header message into log file
  log.open(filePath.c_str(), ios::out | ios::trunc);
  log << "Simulation of Household energy usage:\n";
  log << "----------------------------------------\n";
  log.close();
}

// print status message to log file
void Logger::print(const string& text) const
{
  int ticks = scheduler_->getTime();

  ofstream logFile; // for printing to log file

  logFile.open(filePath_.c_str(), ios::out | ios::app);

  // Format:
  // At ## minute(s): <status message>.
  logFile << "At " << ticks << " minute(s): " << text << "\n";

  logFile.close();
}

// returns scheduler_
Scheduler* Logger::getScheduler() const
{
  return scheduler_;
}

// returns str_filePath_
string Logger::getFilePath() const
{
  return filePath_;
}
