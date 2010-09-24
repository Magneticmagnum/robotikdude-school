#include "Queue.h"
#include <cstdlib>

BuggyQueue::BuggyQueue()
{
  first_ = (Queue_NodeHolder*) NULL;
  last_ = (Queue_NodeHolder*) NULL;
  size_ = 0;
}

// copy-constructor has to replicate the node holders
BuggyQueue::BuggyQueue(const BuggyQueue& original)
{

  // not much to do for an empty queue
  if (original.first_ == NULL) {
    first_ = (Queue_NodeHolder*) NULL;
    last_ = (Queue_NodeHolder*) NULL;
    size_ = 0;
  }
  else {
    // need to copy the queue over
    first_ = (Queue_NodeHolder*) NULL;
    last_ = (Queue_NodeHolder*) NULL;

    Queue_NodeHolder* nh = original.first_;
    while (nh != NULL) {
      put(nh->getContent());
      nh = nh->getNext();
    }
    size_ = original.size_;
  }
}

BuggyQueue::~BuggyQueue()
{
  if (first_ != NULL) {
    delete (first_);
  }
}

void BuggyQueue::put(Node* item)
{
  Queue_NodeHolder* next = new Queue_NodeHolder(item);
  if (first_ == NULL) {
    first_ = next;
  }
  else {
    last_->setNext(next);
  }
  last_ = next;
  size_ += 1;
}

Node* BuggyQueue::get()
{
  if (first_ == NULL) {
    return NULL;
  }

  Node* result = first_->getContent();

  if (first_ == last_) {
    last_ = (Queue_NodeHolder*) NULL;
  }

  Queue_NodeHolder* tmp = first_;
  first_ = first_->getNext();
  tmp->setNext((Queue_NodeHolder*) NULL);
  delete tmp;
  size_ -= 1;

  return result;
}

int BuggyQueue::size()
{
  return size_;
}

// -- Queue_NodeHolder implementation --

BuggyQueue::Queue_NodeHolder::Queue_NodeHolder(Node* initialContent)
{
  content_ = initialContent;
}

BuggyQueue::Queue_NodeHolder::~Queue_NodeHolder()
{
  //don't delete content -- why?
  if (next_ != NULL) {
    delete next_;
  }
}

Node* BuggyQueue::Queue_NodeHolder::getContent()
{
  return content_;
}

BuggyQueue::Queue_NodeHolder* BuggyQueue::Queue_NodeHolder::getNext()
{
  return next_;
}

void BuggyQueue::Queue_NodeHolder::setNext(BuggyQueue::Queue_NodeHolder* holder)
{
  next_ = holder;
}
