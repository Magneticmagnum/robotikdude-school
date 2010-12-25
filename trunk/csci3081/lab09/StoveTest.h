#ifndef STOVETEST_H_
#define STOVETEST_H_

#include <cxxtest/TestSuite.h>
#include "Stove.h"

class StoveTest: public CxxTest::TestSuite {
  public:

    /*
     * Test creation and initialization of a stove.
     */
    void test_stoveInitialization() {
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
    }

    /*
     * Test turning burners on and ticking them one tick.
     */
    void test_turnBurnersOn() {
      Stove stove1 = Stove();

      //Try to input negative values for both power and cook time.
      stove1.turnOnBurner(-1, -1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      //Input a power level greater than 3
      stove1.turnOnBurner(9001, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      //Turn on four burners
      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 1);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER);

      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 2);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER*2);

      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 3);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER*3);

      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 4);
      TS_ASSERT_EQUALS(stove1.getPower(), LOW_POWER*4);

      //Try to turn on an extra burner
      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 4);

      //Tick the stove.
      stove1.tick();

      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 1);
      TS_ASSERT_EQUALS(stove1.getEnergy(), LOW_POWER*4);

    }

    /*
     * Test the turnOff function.
     */
    void test_turnOff() {
      Stove stove1 = Stove();

      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      stove1.turnOff();
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);

    }

    /*
     * Turn on four burners each with a different cook time,
     * then run the simulation until all of them turn off.
     */
    void test_varyingCookTimes() {
      Stove stove1 = Stove();

      stove1.turnOnBurner(1, 1);
      stove1.turnOnBurner(1, 2);
      stove1.turnOnBurner(1, 3);
      stove1.turnOnBurner(1, 4);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);

      //First tick, three burners should remain on.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 3);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 1);
      TS_ASSERT_EQUALS(stove1.getEnergy(), LOW_POWER*4);

      //Second tick, two burners should remain on.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 2);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 2);
      TS_ASSERT_EQUALS(stove1.getEnergy(), LOW_POWER*7);

      //Third tick, one burner should remain on.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 1);
      TS_ASSERT_EQUALS(stove1.isRunning(), true);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 3);
      TS_ASSERT_EQUALS(stove1.getEnergy(), LOW_POWER*9);

      //Fourth tick, all burners should turn off.
      stove1.tick();
      TS_ASSERT_EQUALS(stove1.getBurnersOn(), 0);
      TS_ASSERT_EQUALS(stove1.isRunning(), false);
      TS_ASSERT_EQUALS(stove1.getTimeRunning(), 4);
      TS_ASSERT_EQUALS(stove1.getEnergy(), LOW_POWER*10);




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
      TS_ASSERT_EQUALS(stove2.getEnergy(), LOW_POWER*4);

      //Second tick, two burners should remain on.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 2);
      TS_ASSERT_EQUALS(stove2.isRunning(), true);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 2);
      TS_ASSERT_EQUALS(stove2.getEnergy(), LOW_POWER*7);

      //Third tick, one burner should remain on.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 1);
      TS_ASSERT_EQUALS(stove2.isRunning(), true);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 3);
      TS_ASSERT_EQUALS(stove2.getEnergy(), LOW_POWER*9);

      //Fourth tick, all burners should turn off.
      stove2.tick();
      TS_ASSERT_EQUALS(stove2.getBurnersOn(), 0);
      TS_ASSERT_EQUALS(stove2.isRunning(), false);
      TS_ASSERT_EQUALS(stove2.getTimeRunning(), 4);
      TS_ASSERT_EQUALS(stove2.getEnergy(), LOW_POWER*10);
    }

};

#endif /* STOVETEST_H_ */
