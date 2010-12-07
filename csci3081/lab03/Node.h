#ifndef NODE_H_
#define NODE_H_

#include <string>
using std::string;

class Node
{
public:
	/**
	 * Creates a Node with an empty string as content
	 */
	Node ();
	
	/**
	 * Creates a Node with the given string as content
	 */
	Node (const string& initialContent);
	
	/**
	 * Deletes a node
	 */
	virtual ~Node ();
	
	/**
	 * Returns the content string.
	 */
	string& getContent ();
	
	/**
	 * Sets a new content string.
	 */
	void setContent (const string& newContent);
	
private:
	string content_;
};

#endif /*NODE_H_*/
