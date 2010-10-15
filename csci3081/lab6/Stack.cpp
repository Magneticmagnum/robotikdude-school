// stack.cpp: stack functions
#include "Stack.h"

SimpleStack::SimpleStack(int size)
{
  size_ = size;
  top_ = 0;
  items_ = new char[size];
}

SimpleStack::~SimpleStack()
{
  delete[] items_;
}

void SimpleStack::push(char c)
{
  if (getTop() < getSize()) {
    items_[top_++] = c;
  }
}

char SimpleStack::pop()
{
  if (isEmpty()) {
    return -1;
  }
  else {
    return items_[--top_];
  }
}

int SimpleStack::getSize()
{
  return size_;
}

bool SimpleStack::isEmpty()
{
  if (top_ == 0) {
    return true;
  }
  else {
    return false;
  }
}

int SimpleStack::getTop()
{
  return top_;
}
