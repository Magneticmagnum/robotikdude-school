#ifndef QUEUE_H_
#define QUEUE_H_

#include "Node.h"

/**
 * An abstract queue of Node instances, implemented with a linked list.
 */
class BuggyQueue
{
public:
	
	/**
	 * Standard zero-arg constructor
	 */
	BuggyQueue();
	
	/**
	 * Copy-constructor
	 */
	BuggyQueue (const BuggyQueue& original);
	
	virtual ~BuggyQueue();
	
	/**
	 * Adds an item to the queue.
	 */
	void put (Node* item);
	
	/**
	 * Removes an item from the queue.
	 */
	Node* get ();
	
	/**
	 * Returns the number of Nodes currently in the queue.
	 */
	int size ();
	// Holder for queue elements.

private:
	class Queue_NodeHolder
	{
	public:
		Queue_NodeHolder (Node* initialContent);
		virtual ~Queue_NodeHolder ();
		
		Node* getContent ();
		Queue_NodeHolder* getNext ();
		void setNext (Queue_NodeHolder* holder);

	private:
		Node* content_;
		Queue_NodeHolder* next_;
		
		// private constructor
		// prevents generation of public zero-arg constructor.
		Queue_NodeHolder ();
	};

	Queue_NodeHolder* first_; // Pointer to start of queue
	Queue_NodeHolder* last_; // Pointer to end of queue
	int size_; // number of elements in the queue
};

#endif /*QUEUE_H_*/
