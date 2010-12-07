#ifndef STACK_H
#define STACK_H

using namespace std;

/**
 * A simple stack class that initializes with a set size. The methods included
 * are push, pop, isEmpty, getSize, and getTop.<br>
 * <br>
 * It can also take body shots.
 */
class SimpleStack
{

  public:

    /**
     * The constructor. Creates an instance of SimpleStack of the given size.
     */
    SimpleStack(int size);

    /**
     * The destructor.
     */
    ~SimpleStack();

    /**
     * Push one item into the stack. If the stack is not full, the top of the
     * stack should increase by 1. Return nothing if the stack is full, do
     * nothing and return nothing
     */
    void push(char);

    /**
     * Pop one item out of the stack, the top of the stack should decrease by
     * 1. If the stack is not empty, return the Char type item popped out of
     * the stack If the stack is empty, return -1
     */
    char pop();

    /**
     * Test whether the stack is empty. If empty, return true. If not empty
     * return false.
     */
    bool isEmpty();

    /**
     * Return the size of the stack, that is, the maximum size of the stack.
     */
    int getSize();

    /**
     * Return the top of the stack, that is, the current number of elements
     * in the stack.
     */
    int getTop();

  private:

    /**
     * Define the stack size.
     */
    int size_;

    /**
     * Indicates the top of the stack, top_ = 0, when the stack is empty.
     */
    int top_;

    /**
     * The items in the stack.
     */
    char* items_;

};

#endif /*STACK_H*/
