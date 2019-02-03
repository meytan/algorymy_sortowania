#pragma once
#include "Node.h"

class NodeList
{
public:
	// constructors
	NodeList();
	NodeList(Node *head);//uzyteczne przy dzieleniu listy
	~NodeList();
	
	//fields
	Node *head;
	Node *tail;
	int length;

	// methods 
	void push(int value);
	void unshift(int value);
	bool readFromFile(std::string fileName);
	void show();
	bool remove(int index);
	void putAfter(int val, int index);
	void putBefore(int val, int index);
	void switchElements(int index1, int index2);//zamiana dwoch dowolnych elementow
	void switchNextElement(int index);//zamiana nastepnego elementu
	void changeAt(int index, int value);//podmiana wartosci na indexie 
	int* readAt(int index);//czytanie z indexu
	NodeList* splitList();
	friend void bubbleSort(NodeList &list);
	friend void insertSort(NodeList &list);
};

