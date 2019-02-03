#pragma once
class Node
{
public:
	Node();
	Node(int value);
	~Node();
	int value;
	Node *next, *prev;
};

