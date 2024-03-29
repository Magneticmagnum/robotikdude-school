#ifndef STOVETEST_H_
#define STOVETEST_H_

#include <cxxtest/TestSuite.h>
#include "Stove.h"

class StoveTest: public CxxTest::TestSuite
{
  public:

    /*
     * Test creation and initialization of a stove.
     */
    void test_stoveInitialization()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("StoveTest"));
      LOG4CXX_DEBUG(log, "--> StoveTest::test_stoveInitialization()");

      Stove stove1 = Stove();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 0);
      TS_ASSERT_EQUALS(stove1.getEnergy(), 0);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      //Make sure all the burners were initialized to off
      //with a cook time of zero.
      TS_ASSERT_EQUALS(stove1.getBurnerPower(0), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerPower(1), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerPower(2), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerPower(3), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerTime(0), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerTime(1), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerTime(2), 0);
      TS_ASSERT_EQUALS(stove1.getBurnerTime(3), 0);

      LOG4CXX_DEBUG(log, "<-- StoveTest::test_tstoveInitialization()");
    }

    void test_action()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("StoveTest"));
      LOG4CXX_DEBUG(log, "--> StoveTest::test_action()");

      Stove stove = Stove();
      TS_ASSERT_EQUALS(stove.action("high 10"), true);
      TS_ASSERT_EQUALS(stove.action("low -10"), false);
      TS_ASSERT_EQUALS(stove.action("low 10 medium 20 high 30"), true);
      TS_ASSERT_EQUALS(stove.action("high 10"), false);
      TS_ASSERT_EQUALS(stove.action("fail 0"), false);
      TS_ASSERT_EQUALS(stove.action("fail"), false);
      TS_ASSERT_EQUALS(stove.action(""), false);

      LOG4CXX_DEBUG(log, "<-- StoveTest::test_action()");
    }

    /*
     * Test turning burners on and ticking them one tick.
     */
    void test_turnBurnersOn()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("StoveTest"));
      LOG4CXX_DEBUG(log, "--> StoveTest::test_turnBurnersOn()");

      Stove stove1 = Stove();
      bool stoveOn = false;

      //Try to input negative values for both power and cook time.
      stoveOn = stove1.turnOnBurner(-1, -1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      //Input a power level greater than 3
      stoveOn = stove1.turnOnBurner(9001, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      //Turn on four burners
      stoveOn = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 1);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER);

      stoveOn = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 2);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER*2);

      stoveOn = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 3);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER*3);

      stoveOn = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 4);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER*4);

      TS_ASSERT_EQUALS(stove1.getPower(), 350*4);

      //Try to turn on an extra burner
      stoveOn = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 4);

      //Tick the stove.
      stove1.tick();

      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 1);
      TS_ASSERT_DELTA(stove1.getEnergy(), 84000.0, 0.1);

      LOG4CXX_DEBUG(log, "<-- StoveTest::test_turnBurnersOn()");
    }

    /*
     * Test the turnOff function.
     */
    void test_turnOff()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("StoveTest"));
      LOG4CXX_DEBUG(log, "--> Entering StoveTest::test_turnOff()");

      Stove stove1 = Stove();
      bool success = false;

      success = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      success = stove1.turnOnBurner(1, 1);
      success = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 2);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      success = stove1.turnOnBurner(1, 1);
      success = stove1.turnOnBurner(1, 1);
      success = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 3);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      success = stove1.turnOnBurner(1, 1);
      success = stove1.turnOnBurner(2, 1);
      success = stove1.turnOnBurner(3, 1);
      success = stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 4);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      LOG4CXX_DEBUG(log, "<-- Exiting StoveTest::test_turnOff()");

    }

    /*
     * Turn on four burners each with a different cook time,
     * then run the simulation until all of them turn off.
     */
    void test_varyingCookTimes()
    {
      log4cxx::LoggerPtr log(log4cxx::Logger::getLogger("StoveTest"));
      LOG4CXX_DEBUG(log, "--> Entering StoveTest::test_varyingCookTimes()");

      Stove stove1 = Stove();
      bool success = false;

      success = stove1.turnOnBurner(1, 1);
      success = stove1.turnOnBurner(1, 2);
      success = stove1.turnOnBurner(1, 3);
      success = stove1.turnOnBurner(1, 4);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);

      //First tick, three burners should remain on.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 3);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 1);
      TS_ASSERT_DELTA(stove1.getEnergy(), 84000.0, 0.1);
      TS_ASSERT_EQUALS(stove1.getPower(), 350*3);

      //Second tick, two burners should remain on.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 2);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 2);
      TS_ASSERT_DELTA(stove1.getEnergy(), 147000.0, 0.1);
      TS_ASSERT_EQUALS(stove1.getPower(), 350*2);

      //Third tick, one burner should remain on.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 3);
      TS_ASSERT_DELTA(stove1.getEnergy(), 189000.0, 0.1);
      TS_ASSERT_EQUALS(stove1.getPower(), 350*1);

      //Fourth tick, all burners should turn off.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 4);
      TS_ASSERT_DELTA(stove1.getEnergy(), 210000.0, 0.1);
      TS_ASSERT_EQUALS(stove1.getPower(), 0);

      //Do again, but put the cook times in descending order.
      Stove stove2 = Stove();

      stove2.turnOnBurner(1, 4);
      stove2.turnOnBurner(1, 3);
      stove2.turnOnBurner(1, 2);
      stove2.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove2.isRunning(), true);

      //First tick, three burners should remain on.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 3);
      TS_ASSERT_EQUALS(stove2.isRunning(), true);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 1);
      TS_ASSERT_DELTA(stove2.getEnergy(), 84000.0, 0.1);
      TS_ASSERT_EQUALS(stove2.getPower(), 350*3);

      //Second tick, two burners should remain on.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 2);
      TS_ASSERT_EQUALS(stove2.isRunning(), true);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 2);
      TS_ASSERT_DELTA(stove2.getEnergy(), 147000.0, 0.1);
      TS_ASSERT_EQUALS(stove2.getPower(), 350*2);

      //Third tick, one burner should remain on.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 1);
      TS_ASSERT_EQUALS(stove2.isRunning(), true);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 3);
      TS_ASSERT_DELTA(stove2.getEnergy(), 189000.0, 0.1);
      TS_ASSERT_EQUALS(stove2.getPower(), 350*1);

      //Fourth tick, all burners should turn off.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 0);
      TS_ASSERT_EQUALS(stove2.isRunning(), false);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 4);
      TS_ASSERT_DELTA(stove2.getEnergy(), 210000.0, 0.1);
      TS_ASSERT_EQUALS(stove2.getPower(), 0);

      LOG4CXX_DEBUG(log, "<-- Exiting StoveTest::test_varyingCookTimes()");
    }

};

#endif /* STOVETEST_H_ */
