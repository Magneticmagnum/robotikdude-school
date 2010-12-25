#ifndef PERSONTESTB_H_
#define PERSONTESTB_H_

#include "PersonB.h"
#include "Scheduler.h"

#include <cxxtest/TestSuite.h>

#include <cstdlib>
#include <iostream>

class PersonTest: public CxxTest::TestSuite
{
  public:

    /*
     * Test the getEnergy() function, should
     * always return 0.0 because the person does
     * not directly use power.
     */
    void test_getEnergy()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_getEnergy()");

      Person p = Person();
      TS_ASSERT_EQUALS(p.getEnergy(), 0.0);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_getEnergy()");
    }

    /*
     * Test the getPower() function, again: should
     * always return 0.0 because the person does not
     * directly draw power.
     */
    void test_getPower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_getPower()");

      Person p = Person();
      TS_ASSERT_EQUALS(p.getPower(), 0.0);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_getPower()");
    }

    void test_initialConditions()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_initialConditions()");

      Person p = Person();

      TS_ASSERT_EQUALS(p.getStateSwitchTime(), 0);
      TS_ASSERT_EQUALS(p.getDaysSinceDishes(), 0);
      TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_initialConditions()");
    }

    void test_asleep()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_asleep()");

      srand(0); // wake time is 6:30, will skip shower
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);

      while (s->getHour() < 6 || s->getMinute() < 30) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
        s->run(1);
      }

      TS_ASSERT_EQUALS(p.getState(), &Person::state_breakfast);

      srand(2); // wake time is 6:45, takes a shower
      p = Person();
      s->reset();
      s->registerModel(&p);

      while (s->getHour() < 6 || s->getMinute() < 45) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
        s->run(1);
      }

      TS_ASSERT_EQUALS(p.getState(), &Person::state_shower);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_asleep()");
    }

    void test_shower()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_shower()");

      srand(2); // wake time is 6:45, takes a shower
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);

      //
      TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
      s->run(6 * 60 + 45);

      for (int i = 0; i < 11; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_shower);
        s->run(1);
      }

      TS_ASSERT_EQUALS(p.getState(), &Person::state_breakfast);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_shower()");
    }

    void test_breakfast()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_breakfast()");

      srand(2); // wake time is 6:45, takes a shower
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);

      //
      TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
      s->run(6 * 60 + 45);
      TS_ASSERT_EQUALS(p.getState(), &Person::state_shower);
      s->run(13);
      for (int i = 0; i < 25; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_breakfast);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_work);

      srand(9);
      p = Person();
      s->reset();
      s->registerModel(&p);

      TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
      s->run(6 * 60 + 45);
      TS_ASSERT_EQUALS(p.getState(), &Person::state_shower);
      s->run(11);
      for (int i = 0; i < 25; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_breakfast);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_work);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_breakfast()");
    }

    void test_work()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_work()");

      srand(2);
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);

      TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
      s->run(6 * 60 + 45);
      TS_ASSERT_EQUALS(p.getState(), &Person::state_shower);
      s->run(10);
      TS_ASSERT_EQUALS(p.getState(), &Person::state_breakfast);
      s->run(25);
      while (s->getHour() < 18 || s->getMinute() < 1) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_work);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_dinner);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_work()");
    }

    void test_dinner()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_dinner()");

      srand(0);
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);
      s->registerModel(Model::getInstance(MODEL_DISHWASHER));

      while (s->getHour() < 17 || s->getMinute() < 42) {
        s->run(1);
      }
      for (int i = 0; i < 40; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_dinner);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_dishes);

      srand(0);
      p = Person();
      s->reset();
      s->registerModel(&p);
      s->registerModel(Model::getInstance(MODEL_DISHWASHER));
      s->registerModel(Model::getInstance(MODEL_MICROWAVE));

      while (s->getHour() < 18 || s->getMinute() < 5) {
        s->run(1);
      }

      for (int i = 0; i < 10; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_dinner);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_television);

      srand(4);
      while (s->getHour() != 18 || s->getMinute() != 3) {
        s->run(1);
      }

      for (int i = 0; i < 10; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_dinner);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_television);

      srand(3);
      while (s->getHour() != 18 || s->getMinute() != 12) {
        s->run(1);
      }
      while (s->getHour() != 18 || s->getMinute() != 20) {
        s->run(1);
      }

      for (int i = 0; i < 10; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_dinner);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_dishes);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_dinner()");
    }

    void test_dishes()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_dishes()");

      srand(0);
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);
      s->registerModel(Model::getInstance(MODEL_DISHWASHER));

      while (s->getHour() != 18 || s->getMinute() != 11) {
        s->run(1);
      }

      for (int i = 0; i < 65; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_dishes);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_television);
      LOG4CXX_DEBUG(log, "<-- PersonTest::test_dishes()");
    }

    void test_bath()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_bath()");

      srand(3);
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);
      s->registerModel(Model::getInstance(MODEL_DISHWASHER));

      //      s->run(24*60);
      while (s->getHour() != 18 || s->getMinute() != 13) {
        s->run(1);
      }

      for (int i = 0; i < 19; i++) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_bath);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_television);
      LOG4CXX_DEBUG(log, "<-- PersonTest::test_bath()");
    }

    void test_television()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_television()");

      srand(3);
      Person p = Person();
      Scheduler* s = Scheduler::getInstance();
      s->reset();
      s->registerModel(&p);
      s->registerModel(Model::getInstance(MODEL_DISHWASHER));

      while (s->getHour() != 20 || s->getMinute() != 2) {
        s->run(1);
      }

      while (s->getHour() != 23 || s->getMinute() != 22) {
        TS_ASSERT_EQUALS(p.getState(), &Person::state_television);
        s->run(1);
      }
      TS_ASSERT_EQUALS(p.getState(), &Person::state_asleep);
      LOG4CXX_DEBUG(log, "<-- PersonTest::test_television()");
    }

};

#endif /* PERSONTESTB_H_ */
