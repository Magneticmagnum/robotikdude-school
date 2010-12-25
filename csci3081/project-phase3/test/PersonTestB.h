#ifndef PERSONTESTB_H_
#define PERSONTESTB_H_

#include "PersonB.h"
#include "ConfigurationOptions.h"
#include "MockScheduler.h"
#include "MockRandom.h"

#include <cxxtest/TestSuite.h>

#include <cstdlib>
#include <iostream>

class PersonTestB: public CxxTest::TestSuite
{
  public:

    void test_initialConditions()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_initialConditions()");

      Person p = Person("", 0, 0, 0);

      TS_ASSERT_EQUALS(p.getPower(), 0.0);
      TS_ASSERT_EQUALS(p.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(p.isRunning(), false);
      TS_ASSERT(p.getState() == 0);

      p = Person("unittest.state", 0, 0, 0);

      TS_ASSERT_EQUALS(p.getPower(), 0.0);
      TS_ASSERT_EQUALS(p.getEnergy(), 0.0);
      TS_ASSERT_EQUALS(p.isRunning(), false);
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      p = Person("fail.state", 0, 0, 0);
      TS_ASSERT(p.getState() == 0);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_initialConditions()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_initialConditions()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      Person p = Person("", scheduler, 0, random);

      TS_ASSERT_EQUALS(p.action("blah"), true);
      TS_ASSERT_EQUALS(p.action("fail"), true);
      TS_ASSERT_EQUALS(p.action("asldkf asldka ;slkdj;lakjs l;kaj s;lkj"), true);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_initialConditions()");
    }

    void test_changeState()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_changeState()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      char buffer[50];

      Person p = Person("", scheduler, 0, random);

      strcpy(buffer, "next-state2 10");
      int r = p.addState("next-state1", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT(strcmp(p.getState(), "next-state1") == 0);

      strcpy(buffer, "next-state1 10");
      r = p.addState("next-state2", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);
      TS_ASSERT(strcmp(p.getState(), "next-state1") == 0);

      bool e = p.changeState("next-state2");
      TS_ASSERT(e);
      TS_ASSERT(strcmp(p.getState(), "next-state2") == 0);

      e = p.changeState("next-state3");
      TS_ASSERT(!e);
      TS_ASSERT(strcmp(p.getState(), "next-state2") == 0);

      e = p.changeState("next-state1");
      TS_ASSERT(e);
      TS_ASSERT(strcmp(p.getState(), "next-state1") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_changeState()");
    }

    void test_state_Fail()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_Fail()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      char buffer[50];
      ptimer_t* arg;

      Person p = Person("", scheduler, 0, random);

      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", "fail", buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_Fail()");
    }

    void test_state_RandomTime()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_RandomTime()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      char buffer[50];
      randomtime_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_RANDOM_TIME, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      strcpy(buffer, "next-state 1:00 2:00");
      r = p.addState("current-state", PERSON_RANDOM_TIME, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      arg = (randomtime_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "next-state") == 0);
      TS_ASSERT_EQUALS(arg->minTime, 60);
      TS_ASSERT_EQUALS(arg->maxTime, 120);
      TS_ASSERT_EQUALS(arg->randTime, -1);

      strcpy(buffer, "current-state 10");
      r = p.addState("next-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");

      // test
      scheduler->setTime(0, 1, 20);
      random->seedNormal(0.50001);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      arg = (randomtime_t*) p.getStateArg();
      TS_ASSERT_EQUALS(arg->randTime, 90);

      scheduler->setTime(0, 1, 30);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);
      TS_ASSERT_EQUALS(arg->randTime, -1);

      scheduler->setTime(0, 1, 40);
      random->seedNormal(0.50001);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      TS_ASSERT_EQUALS(arg->randTime, -1);

      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      TS_ASSERT_EQUALS(arg->randTime, 24 * 60 + 90);

      scheduler->setTime(1, 1, 20);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      TS_ASSERT_EQUALS(arg->randTime, 24 * 60 + 90);

      scheduler->setTime(1, 1, 30);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);
      TS_ASSERT_EQUALS(arg->randTime, -1);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_RandomTime()");
    }

    void test_state_Delay()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_Delay()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      char buffer[50];
      delay_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_DELAY, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      strcpy(buffer, "next-state 30");
      r = p.addState("current-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (delay_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "next-state") == 0);
      TS_ASSERT_EQUALS(arg->delayTime, 30);

      strcpy(buffer, "next-state 1");
      r = p.addState("next-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (delay_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "next-state") == 0);

      scheduler->setTime(0, 0, 0);
      p.tick();
      TS_ASSERT_EQUALS(p.getState(), "current-state");

      scheduler->setTime(0, 0, 29);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      scheduler->setTime(0, 0, 30);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_Delay()");
    }

    void test_state_RandomDelay()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_RandomDelay()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      char buffer[50];
      randomdelay_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_RANDOM_DELAY, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      strcpy(buffer, "next-state 30 60");
      r = p.addState("current-state", PERSON_RANDOM_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (randomdelay_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "next-state") == 0);
      TS_ASSERT_EQUALS(arg->minDelay, 30);
      TS_ASSERT_EQUALS(arg->maxDelay, 60);
      TS_ASSERT_EQUALS(arg->randDelay, -1);

      strcpy(buffer, "next-state 1");
      r = p.addState("next-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (randomdelay_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "next-state") == 0);

      // test
      scheduler->setTime(0, 0, 0);
      random->seedNormal(0.50001);
      p.tick();
      TS_ASSERT_EQUALS(p.getState(), "current-state");
      TS_ASSERT_EQUALS(arg->randDelay, 45);

      scheduler->setTime(0, 0, 30);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      scheduler->setTime(0, 0, 44);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      scheduler->setTime(0, 0, 45);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);
      TS_ASSERT_EQUALS(arg->randDelay, -1);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_RandomDelay()");
    }

    void test_state_Choice()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_Choice()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      char buffer[50];
      choice_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_CHOICE, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      strcpy(buffer, "next-state1 next-state2 0.5");
      r = p.addState("current-state", PERSON_CHOICE, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (choice_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(arg->nextState2, "next-state2") == 0);
      TS_ASSERT_EQUALS(arg->chance, 0.5);

      strcpy(buffer, "current-state 10");
      r = p.addState("next-state1", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (choice_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(arg->nextState2, "next-state2") == 0);
      TS_ASSERT_EQUALS(arg->chance, 0.5);

      strcpy(buffer, "current-state 10");
      r = p.addState("next-state2", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (choice_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(arg->nextState2, "next-state2") == 0);
      TS_ASSERT_EQUALS(arg->chance, 0.5);

      random->seedNormal(0.25);
      scheduler->setTime(0, 0, 0);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state2") == 0);

      scheduler->setTime(0, 0, 10);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      random->seedNormal(0.75);
      scheduler->setTime(0, 0, 11);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state1") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_Choice()");
    }

    void test_state_Action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_Action()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      House* house = new House(0, scheduler);
      Microwave* microwave = new Microwave(0, scheduler, house, random);
      house->addModel("microwave", microwave);

      char buffer[50];
      action_t* arg;

      Person p = Person("", scheduler, house, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_ACTION, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      strcpy(buffer, "fail-state microwave start");
      r = p.addState("current-state", PERSON_ACTION, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");
      arg = (action_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "fail-state") == 0);

      strcpy(buffer, "next-state fail! start");
      r = p.addState("fail-state", PERSON_ACTION, buffer);
      TS_ASSERT_EQUALS(r, 0);

      strcpy(buffer, "next-state 10");
      r = p.addState("next-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT_EQUALS(p.getState(), "current-state");

      // test
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      p.tick();
      TS_ASSERT(microwave->isRunning());
      TS_ASSERT(strcmp(p.getState(), "fail-state") == 0);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_Action()");
    }

    void test_state_Wait()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_Wait()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();
      House* house = new House(0, scheduler);
      Microwave* microwave = new Microwave(0, scheduler, house, random);
      house->addModel("microwave", microwave);

      char buffer[50];
      wait_t* arg;

      Person p = Person("", scheduler, house, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_WAIT, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      strcpy(buffer, "fail-state microwave");
      r = p.addState("current-state", PERSON_WAIT, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      arg = (wait_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "fail-state") == 0);

      strcpy(buffer, "next-state fail!");
      r = p.addState("fail-state", PERSON_WAIT, buffer);
      TS_ASSERT_EQUALS(r, 0);

      strcpy(buffer, "next-state 10");
      r = p.addState("next-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      // test
      random->seedNormal(0.0);
      microwave->turnOn();
      for (int i = 0; i < 100; i++) {
        p.tick();
        TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      }
      microwave->tick();
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "fail-state") == 0);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_Wait()");
    }

    void test_state_TimeCond()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_TimeCond()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      char buffer[50];
      timecond_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_TIME_COND, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      // add person state
      strcpy(buffer, "next-state1 next-state2 2:00");
      r = p.addState("current-state", PERSON_TIME_COND, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      arg = (timecond_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(arg->nextState2, "next-state2") == 0);
      TS_ASSERT_EQUALS(arg->condTime, 120);

      // add person state
      strcpy(buffer, "current-state 10");
      r = p.addState("next-state1", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      arg = (timecond_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(arg->nextState2, "next-state2") == 0);
      TS_ASSERT_EQUALS(arg->condTime, 120);

      // add person state
      strcpy(buffer, "current-state 10");
      r = p.addState("next-state2", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);
      arg = (timecond_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(arg->nextState2, "next-state2") == 0);
      TS_ASSERT_EQUALS(arg->condTime, 120);

      scheduler->setTime(0, 1, 30);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state1") == 0);

      scheduler->setTime(0, 1, 40);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      scheduler->setTime(0, 2, 10);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state2") == 0);

      scheduler->setTime(0, 2, 20);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "current-state") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_TimeCond()");
    }

    void test_state_Timer()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_Timer()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      char buffer[50];
      ptimer_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_TIMER, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      strcpy(buffer, "next-state fail! blah");
      r = p.addState("fail-state", PERSON_TIMER, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      // add person state
      strcpy(buffer, "wait-state set blah");
      r = p.addState("set-state", PERSON_TIMER, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);
      arg = (ptimer_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "wait-state") == 0);
      TS_ASSERT(strcmp(arg->timerName, "blah") == 0);
      TS_ASSERT(!arg->waiting);
      TS_ASSERT_EQUALS(arg->waitTime, -1);

      // add person state
      strcpy(buffer, "next-state wait blah 20");
      r = p.addState("wait-state", PERSON_TIMER, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);
      arg = (ptimer_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "wait-state") == 0);
      TS_ASSERT(strcmp(arg->timerName, "blah") == 0);
      TS_ASSERT(!arg->waiting);
      TS_ASSERT_EQUALS(arg->waitTime, -1);

      // add person state
      strcpy(buffer, "next-state 10");
      r = p.addState("next-state", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);
      arg = (ptimer_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "wait-state") == 0);
      TS_ASSERT(strcmp(arg->timerName, "blah") == 0);
      TS_ASSERT(!arg->waiting);
      TS_ASSERT_EQUALS(arg->waitTime, -1);

      // test
      scheduler->setTime(0);
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);
      for (int i = 0; i < 100; i++) {
        p.tick();
        TS_ASSERT(strcmp(p.getState(), "wait-state") == 0);
      }
      scheduler->setTime(0, 0, 20);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_Timer()");
    }

    void test_state_TimerCond()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("PersonTest"));
      LOG4CXX_DEBUG(log, "--> PersonTest::test_state_TimerCond()");

      // set up person
      MockScheduler* scheduler = new MockScheduler();
      MockRandom* random = new MockRandom();

      char buffer[50];
      ptimer_t* arg;

      Person p = Person("", scheduler, 0, random);

      // test the argument parsing ********************************************
      strcpy(buffer, "fail!");
      int r = p.addState("fail-state", PERSON_TIMER_COND, buffer);
      TS_ASSERT_DIFFERS(r, 0);
      TS_ASSERT(p.getState() == 0);
      TS_ASSERT(p.getStateArg() == 0);

      // test the actual state ************************************************
      // add person state
      strcpy(buffer, "cond-state set blah");
      r = p.addState("set-state", PERSON_TIMER, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);
      arg = (ptimer_t*) p.getStateArg();
      TS_ASSERT(strcmp(arg->nextState, "cond-state") == 0);
      TS_ASSERT(strcmp(arg->timerName, "blah") == 0);
      TS_ASSERT(!arg->waiting);
      TS_ASSERT_EQUALS(arg->waitTime, -1);

      // add person state
      strcpy(buffer, "next-state1 next-state2 blah 30");
      r = p.addState("cond-state", PERSON_TIMER_COND, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test person state
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);

      // add person state
      strcpy(buffer, "cond-state 5");
      r = p.addState("next-state1", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // add person state
      strcpy(buffer, "cond-state 5");
      r = p.addState("next-state2", PERSON_DELAY, buffer);
      TS_ASSERT_EQUALS(r, 0);

      // test
      scheduler->setTime(0);
      TS_ASSERT(strcmp(p.getState(), "set-state") == 0);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state1") == 0);
      scheduler->setTime(5);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "cond-state") == 0);
      ptimercond_t* condarg = (ptimercond_t*) p.getStateArg();
      TS_ASSERT(strcmp(condarg->nextState1, "next-state1") == 0);
      TS_ASSERT(strcmp(condarg->nextState2, "next-state2") == 0);
      TS_ASSERT(strcmp(condarg->timerName, "blah") == 0);
      TS_ASSERT_EQUALS(condarg->condTime, 30);

      scheduler->setTime(35);
      p.tick();
      TS_ASSERT(strcmp(p.getState(), "next-state2") == 0);

      delete (random);
      delete (scheduler);

      LOG4CXX_DEBUG(log, "<-- PersonTest::test_state_TimerCond()");
    }

};

#endif /* PERSONTESTB_H_ */
