#include "Node.h"
#include <string>

using namespace std;

// Don't define no-arg constructor or destructor, use the defaults

Node::Node()
{
}

Node::Node (const string& initialContent)
{
	content_ = initialContent;
}

Node::~Node ()
{
}

string& Node::getContent()
{
	return content_;
}

void Node::setContent (const string& newContent)
{
	content_ = newContent;
}
