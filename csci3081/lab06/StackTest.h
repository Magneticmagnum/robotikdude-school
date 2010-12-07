#ifndef STACKTEST_H_
#define STACKTEST_H_

#include "Stack.h"

#include <cxxtest/TestSuite.h>

class StackTest: public CxxTest::TestSuite
{
  public:

    /**
     * Test for default stack constructor, create a stack and assign the size
     * (say 2), then compare the getSize() with the assigned size (say 2).
     */
    void test_Stack_Size()
    {
      SimpleStack s = SimpleStack(2);
      TS_ASSERT_EQUALS(s.getSize(), 2);
    }

    /**
     * Test for the isEmpty function, create a stack and assign the size
     * (say 2), then compare the "isEmpty()" with "true".
     */
    void test_Stack_Empty()
    {
      SimpleStack s = SimpleStack(2);
      TS_ASSERT(s.isEmpty());
      s.push('I');
      TS_ASSERT(!s.isEmpty());
    }

    /**
     * Test for Push and Pop operations, create a stack and assign the size
     * (say 2), then push two items into the stack, then pop out the two items,
     * compare the popped two items with the original pushed two items, test
     * whether they are the same.
     */
    void test_Stack_Push_Pop()
    {
      SimpleStack s = SimpleStack(2);
      s.push('n');
      s.push('o');
      TS_ASSERT_EQUALS(s.pop(), 'o');
      TS_ASSERT_EQUALS(s.pop(), 'n');
      TS_ASSERT(s.isEmpty());
    }

    /**
     * Test for Push more items than the stack size, create a stack and assign
     * the size (say 2), then push three items into the stack, then check the
     * buffer overflow, then pop out three items, compare the first popped out
     * two items with the first pushed two items, compare the third popped out
     * items with -1, test whether they are the same.
     */
    void test_Stack_Push_More()
    {
      SimpleStack s = SimpleStack(2);
      s.push('c');
      s.push('a');
      TS_ASSERT_EQUALS(s.getSize(), s.getTop());
      s.push('r');
      TS_ASSERT_EQUALS(s.getSize(), s.getTop());
      TS_ASSERT_EQUALS(s.pop(), 'a');
      TS_ASSERT_EQUALS(s.pop(), 'c');
      TS_ASSERT_EQUALS(s.pop(), -1);
      TS_ASSERT(s.isEmpty());
    }

    /**
     * Test for Pop out more items than the pushed items, create a stack and
     * assign the size (say 2), then push one items into the stack, then pop
     * out the two items, compare the first popped item with the first pushed
     * item, compare the second popped item with -1, test whether they are the
     * same.
     */
    void test_Stack_Pop_More()
    {
      SimpleStack s = SimpleStack(2);
      s.push('I');
      TS_ASSERT_EQUALS(s.pop(), 'I');
      TS_ASSERT_EQUALS(s.pop(), -1);
      TS_ASSERT(s.isEmpty());
    }
};

#endif /* STACKTEST_H_ */
