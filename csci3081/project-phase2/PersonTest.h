#ifndef PERSONTEST_H_
#define PERSONTEST_H_

#include <cxxtest/TestSuite.h>
#include "Person.h"

class PersonTest: public CxxTest::TestSuite
{
  public:

  /*
   * Test the operation of the Person object
   * constructor
   */
//  void test_constructor()
//  {
//    Person p = Person();
//
//    TS_ASSERT_EQUALS(p.getActivationIndex(), 0);
//    TS_ASSERT_EQUALS(p.getDaysSinceDishwasherRun(), 0);
//    TS_ASSERT(p.getActivationTimes().front() > 0);
//    TS_ASSERT_EQUALS(p.getTickCounter(), 0);
//    TS_ASSERT_EQUALS(p.getDailyTickCounter(), 0);
//    TS_ASSERT_EQUALS(p.getEnergy(), 0.0);
//  }
//
//  /*
//   * Test the reset() method:  since it is called in the
//   * constructor, this is similar to test_constructor.
//   * Random
//   */
//  void test_reset()
//  {
//    /*
//     * Call person with constructor that takes a seed for
//     * rand().
//     * 9 values of rand that are used:
//     * 1697507
//     * 612712738
//     * 678900201
//     * 695061696
//     * 1738368639
//     * 246698238
//     * 1613847356
//     * 1214050682
//     * 1307682227
//     *
//     */
//
//    Person p = Person( 101 );
//
//    TS_ASSERT(p.getActivationTimes().front() > 0);
//
//
//  }

  /*
   * Test the tick() method in the person object.
   */
  void test_tick()
  {

  }

  /*
   * Test the getEnergy() function
   */
//  void test_getEnergy()
//  {
//    Person p = Person();
//    TS_ASSERT_EQUALS(p.getEnergy(), 0.0);
//  }
//
//  /*
//   * Test the getPower() function
//   */
//  void test_getPower()
//  {
//    Person p = Person();
//    TS_ASSERT_EQUALS(p.getPower(), 0.0);
//  }

//  void test_getTickCounter()
//  {
//    Person p = Person();
//
//    TS_ASSERT_EQUALS(p.getTickCounter(), 0);
//
//    for(int i = 1; i < 2000; i++) {
//      p.tick();
//      TS_ASSERT_EQUALS(p.getTickCounter(), i);
//    }
//  }

//  void test_getDailyTickCounter()
//  {
//    Person p = Person();
//
//    for(int i = 0; i < 1440; i++) {
//      TS_ASSERT_EQUALS(p.getDailyTickCounter(), i);
//      p.tick();
//    }
//    p.tick();
//    TS_ASSERT_EQUALS(p.getDailyTickCounter(), 0);
//  }

};

#endif /* PERSONTEST_H_ */
