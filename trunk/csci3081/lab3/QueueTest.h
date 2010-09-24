#ifndef QUEUETEST_H_
#define QUEUETEST_H_

#include <cxxtest/TestSuite.h>
#include "Queue.h"

class QueueTest: public CxxTest::TestSuite
{
  public:

    /**
     * This is a test for the default queue constructor. A queue should be
     * empty, size 0, when first created
     */
    void test_global_Queue_Queue()
    {
      BuggyQueue q = BuggyQueue();
      TS_ASSERT_EQUALS(q.size(), 0);
    }

    /**
     * Getting an item from an empty queue should return NULL. Getting the
     * third item from a queue that originally had two items put into it should
     * also return NULL.
     */
    void testGet_EmptyQueue()
    {
      BuggyQueue q = BuggyQueue();
      TS_ASSERT_EQUALS(q.get(), (Node*) 0);

      Node* n1 = new Node("n1");
      Node* n2 = new Node("n2");
      q.put(n1);
      q.put(n2);
      q.get();
      q.get();
      TS_ASSERT_EQUALS(q.get(), (Node*) 0);

      delete (n1);
      delete (n2);
    }

    /**
     * This is a test for the default queue constructor. A queue should be
     * empty, size 0, when first created
     */
    void testGet_Size()
    {
      BuggyQueue q = BuggyQueue();
      Node* n = new Node("n");
      q.put(n);

      int originalSize = q.size();
      q.get();
      TS_ASSERT_EQUALS(originalSize - 1, q.size());

      q.get();
      TS_ASSERT_EQUALS(q.size(), 0);

      delete (n);
    }

    /**
     * Getting an item should return the first item in the queue, no matter how
     * many items you put in.
     */
    void testGet_FIFO()
    {
      BuggyQueue q = BuggyQueue();
      Node* n1 = new Node("n1");
      Node* n2 = new Node("n2");

      q.put(n1);
      q.put(n2);

      TS_ASSERT_EQUALS(q.get(), n1);

      delete (n1);
      delete (n2);
    }

    /**
     * Getting an item should return an item that has the same values as the
     * items that were put into the queue. Try putting a few items in the
     * queue, then getting them and checking that they are returning the
     * correct items.
     */
    void testGet_Values()
    {
      BuggyQueue q = BuggyQueue();
      Node* n1 = new Node("n1");
      Node* n2 = new Node("n2");

      q.put(n1);
      q.put(n2);

      TS_ASSERT_EQUALS(q.get(), n1);
      TS_ASSERT_EQUALS(q.get(), n2);

      delete (n1);
      delete (n2);
    }

    /**
     * Putting an item into a queue should increment size by 1.
     */
    void testPut_Size()
    {
      BuggyQueue q = BuggyQueue();
      Node* n = new Node("n");

      int originalSize = q.size();

      q.put(n);
      TS_ASSERT_EQUALS(originalSize + 1, q.size());

      delete (n);
    }

    /**
     * Should always return the size of the queue (>= 0). A queue should have
     * size 0 when created with the default constructor. The size can be
     * expressed as max(0, (# of puts) - (# of gets)).
     */
    void testSize()
    {
      BuggyQueue q = BuggyQueue();
      Node* n1 = new Node("n1");
      Node* n2 = new Node("n2");
      Node* n3 = new Node("n3");

      q.put(n1);
      q.put(n2);
      q.put(n3);

      TS_ASSERT_EQUALS(q.size(), 3);

      q.get();

      TS_ASSERT_EQUALS(q.size(), 2);

      q.get();
      q.get();

      TS_ASSERT_EQUALS(q.size(), 0);

      q.get();

      TS_ASSERT_EQUALS(q.size(), 0);

      delete (n1);
      delete (n2);
      delete (n3);
    }

    /**
     * This is a test for the queue copy constructor. The copy constructor
     * should perform a deep copy of any given queue. To determine that the
     * copy is being done correctly, add some elements, make a copy, then take
     * a few elements off the first queue and make sure the second queue is
     * still the original size.
     */
    void test_global_Queue_QueueCopy_Size()
    {
      BuggyQueue q1 = BuggyQueue();
      Node* n1 = new Node("n1");
      Node* n2 = new Node("n2");

      q1.put(n1);
      q1.put(n2);

      BuggyQueue q2 = BuggyQueue(q1);
      q1.get();
      TS_ASSERT_EQUALS(q2.size(), 2);

      delete (n1);
      delete (n2);
    }

    /**
     * The copy constructor should perform a deep copy of any given queue. Add
     * some elements, make a copy, then take elements off the second queue.
     * Make sure they are the same nodes that were on the first queue and track
     * sizes on both queues.
     */
    void test_global_Queue_QueueCopy_Contents()
    {
      BuggyQueue q1 = BuggyQueue();
      Node* n1 = new Node("n1");
      Node* n2 = new Node("n2");

      q1.put(n1);
      q1.put(n2);

      BuggyQueue q2 = BuggyQueue(q1);

      TS_ASSERT_EQUALS(q2.get(), n1);
      TS_ASSERT_EQUALS(q2.get(), n2);

      TS_ASSERT_EQUALS(q2.size(), 0);
      TS_ASSERT_EQUALS(q1.size(), 2);

      delete (n1);
      delete (n2);
    }

};

#endif /*QUEUETEST_H_*/
