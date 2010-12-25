#ifndef MOCKSCHEDULER_H_
#define MOCKSCHEDULER_H_

#include "Scheduler.h"

class MockScheduler: public Scheduler
{
  private:
    int mockTime_;
    static log4cxx::LoggerPtr log_;

  public:
    MockScheduler() :
      Scheduler(), mockTime_(0)
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::MockScheduler()");
      LOG4CXX_TRACE(log_, "<-- MockScheduler::MockScheduler()");
    }

    virtual void setTime(int newTime)
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::setTime(" << newTime << ")");
      if (newTime >= 0) {
        mockTime_ = newTime;
      }
      LOG4CXX_TRACE(log_, "<-- MockScheduler::setTime(" << newTime << ")");
    }

    virtual void setTime(int newDay, int newHour, int newMinute)
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::setTime(" << newDay << ", " << newHour << ", " << newMinute << ")");
      if (newDay >= 0 && newHour >= 0 && newMinute >= 0) {
        mockTime_ = newDay * TICKS_PER_DAY + newHour * TICKS_PER_HOUR
            + newMinute * TICKS_PER_MINUTE;
      }
      LOG4CXX_TRACE(log_, "<-- MockScheduler::setTime(" << newDay << ", " << newHour << ", " << newMinute << ")");
    }

    virtual int getTime() const
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::getTime()");
      LOG4CXX_TRACE(log_, "<-- MockScheduler::getTime()");
      return mockTime_;
    }

    virtual int getMinute() const
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::getTime()");
      LOG4CXX_TRACE(log_, "<-- MockScheduler::getTime()");
      return mockTime_ % MINUTES_PER_HOUR;
    }

    virtual int getHour() const
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::getHour()");
      LOG4CXX_TRACE(log_, "<-- MockScheduler::getHour()");
      return (mockTime_ / MINUTES_PER_HOUR) % HOURS_PER_DAY;
    }

    virtual int getDay() const
    {
      LOG4CXX_TRACE(log_, "--> MockScheduler::getDay()");
      LOG4CXX_TRACE(log_, "<-- MockScheduler::getDay()");
      return mockTime_ / MINUTES_PER_DAY;
    }

};
log4cxx::LoggerPtr
    MockScheduler::log_(log4cxx::Logger::getLogger("MockScheduler"));

#endif /* MOCKSCHEDULER_H_ */
