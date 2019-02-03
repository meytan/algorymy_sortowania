#include "stdafx.h"
#include "Node.h"


Node::Node() 
	:next(NULL), prev(NULL) 
{};

Node::Node(int value)
	:next(NULL), prev(NULL), value(value) 
{};

Node::~Node()
{
}
