// AIDS_LAB.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Node
{
	int value;
	Node *next, *prev;
	Node() :next(NULL), prev(NULL) {}
	Node(int value) :next(NULL), prev(NULL), value(value) {}
};
struct NodeList
{
	Node *head, *tail;
	int length;
	NodeList() :head(NULL), tail(NULL), length(0) {}
	NodeList(Node *head);//uzyteczne przy dzieleniu listy
	~NodeList();
	void push(int value);
	void unshift(int value);
	bool readFromFile(string fileName);
	void show();
	bool remove(int index);
	void putAfter(int val, int index);
	void putBefore(int val, int index);
	void switchElements(int index1, int index2);//zamiana dwoch dowolnych elementow
	void switchNextElement(int index);//zamiana nastepnego elementu
	void changeAt(int index, int value);//podmiana wartosci na indexie 
	int* readAt(int index);//czytanie z indexu
	NodeList* splitList();
	void bubbleSort();
	void insertSort();
};
NodeList::~NodeList()
{
	Node* tmp;
	while (head)
	{
		tmp = head;
		head = head->next;
		delete tmp;
	}
}
NodeList::NodeList(Node *head)
{
	this->head = head;
	this->head->prev = NULL;
	this->length = 1;
	Node* tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		this->length++;
	}
	this->tail = tmp;

}
void NodeList::push(int value)
{
	Node* tmp = new Node(value);

	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		tail->next = tmp;
		tmp->prev = tail;
		tail = tmp;
	}
	length++;

}
void NodeList::unshift(int value)
{
	Node* tmp = new Node(value);

	if (head == NULL)
	{
		head = tmp;
		tail = tmp;
	}
	else
	{
		head->prev = tmp;
		tmp->next = head;
		head = tmp;
	}
	length++;
}
bool NodeList::readFromFile(string fileName)
{
	fstream plik;
	int val;

	plik.open(fileName.c_str(), ios::in);
	if (plik.good() == true)
	{
		while (!plik.eof())
		{
			plik >> val;
			this->push(val);

		}
		plik.close();
		return true;
	}
	else return false;
}
void NodeList::show()
{
	if (this)
	{
		Node* tmp = head;
		while (tmp)
		{
			std::cout << tmp->value << "\t";
			tmp = tmp->next;
		}
		std::cout << endl;
		std::cout << "-----------------------------------------" << endl;
	}
}
bool NodeList::remove(int index)
{
	Node *tmp = head, *tmp1;
	if (index > length - 1 || index < 0)return false;
	else if (index == 0)
	{
		head = head->next;
		head->prev = NULL;
		delete tmp;
		length--;
	}
	else if (index == length - 1)
	{
		tmp = tail;
		tail = tail->prev;
		tail->next = NULL;
		delete tmp;
		length--;
	}
	else
	{
		while (index)
		{
			tmp = tmp->next;
			index--;
		}
		tmp1 = tmp->prev;
		tmp1->next = tmp->next;
		tmp->next->prev = tmp1;
		delete tmp;
		length--;

	}
	return true;
}
void NodeList::putAfter(int val, int index)
{
	if (index < length - 1 && index >= 0)
	{

		Node *tmp = head, *tmp1 = new Node(val);
		while (index)
		{
			tmp = tmp->next;
			index--;
		}

		if (tmp->next)
		{
			tmp1->next = tmp->next;
			tmp->next->prev = tmp1;
			tmp1->prev = tmp;
			tmp->next = tmp1;
		}
		else if (!tmp->next)
		{
			tmp->next = tmp1;
			tmp1->prev = tmp;
			tail = tmp1;
		}
		length++;
	}
}
void NodeList::putBefore(int val, int index)
{
	if (index > length - 1)
	{

		Node *tmp = head, *tmp1 = new Node(val);
		while (index)
		{
			tmp = tmp->next;
			index--;
		}
		if (tmp->prev)
		{
			tmp1->next = tmp;
			tmp1->prev = tmp->prev;
			tmp->prev = tmp1;
			tmp1->prev->next = tmp1;
		}
		else if (!tmp->next)
		{
			tmp->next = tmp1;
			tmp1->prev = tmp;
			tail = tmp1;
		}
		length++;
	}
}
void NodeList::switchNextElement(int index)
{
	Node* tmp = head, *tmp1;
	while (index) {
		tmp = tmp->next;
		index--;
	}
	tmp1 = tmp->next;
	if (tmp1->next)
		tmp1->next->prev = tmp;
	if (tmp->prev)
		tmp->prev->next = tmp1;
	tmp->next = tmp1->next;
	tmp1->next = tmp;
	tmp1->prev = tmp->prev;
	tmp->prev = tmp1;
	if (!tmp1->prev) head = tmp1;
	if (!tmp->next) tail = tmp;


}
void NodeList::switchElements(int index1, int index2)
{
	if (index1 >= 0 && index1 < length && index2 >= 0 && index2 < length && index1 != index2)
	{
		if (index1 + 1 == index2 || index1 - 1 == index2)
		{

			if (index1 > index2)this->switchNextElement(index2);
			else this->switchNextElement(index1);
			return;
		}


		Node *tmp1 = head, *tmp2 = head, *tmpa1 = NULL, *tmpa2 = NULL;
		while (index1) {
			tmp1 = tmp1->next;
			index1--;
		}
		while (index2) {
			tmp2 = tmp2->next;
			index2--;
		}

		if (tmp1->next)
			tmp1->next->prev = tmp2;
		if (tmp2->next)
			tmp2->next->prev = tmp1;
		if (tmp1->prev)
			tmp1->prev->next = tmp2;
		if (tmp2->prev)
			tmp2->prev->next = tmp1;




		tmpa1 = tmp1->next;
		tmpa2 = tmp2->next;
		std::cout << tmpa1->value << "  ---  " << tmpa2->value << endl;
		tmp1->next = tmpa2;
		tmp2->next = tmpa1;
		tmpa1 = tmp1->prev;
		tmpa2 = tmp2->prev;
		tmp1->prev = tmpa2;
		tmp2->prev = tmpa1;


		if (!tmp2->next)
			tail = tmp2;
		if (!tmp2->prev)
			head = tmp2;
		if (!tmp1->next)
			tail = tmp1;
		if (!tmp1->prev)
			head = tmp1;
	}
}
void NodeList::changeAt(int index, int value)
{
	if (!(index < 0 || index > length - 1))
	{

		Node *tmp = head;
		while (index)
		{
			tmp = tmp->next;
			index--;
		}
		tmp->value = value;

	}
	else
		std::cout << "Niepoprawny index!!" << endl;

}
int* NodeList::readAt(int index)
{
	if (!(index < 0 || index > length - 1))
	{

		Node *tmp = head;
		while (index)
		{
			tmp = tmp->next;
			index--;
		}
		int *ret = new int(tmp->value);
		return ret;

	}
	else
	{
		std::cout << "Niepoprawny index!!" << endl;
		return NULL;
	}
}
NodeList* NodeList::splitList()
{
	if (this->length < 2)
	{
		std::cout << "Lista jest zbyt krotka aby ja podzielic" << endl;
		return NULL;
	}
	Node* tmp = head;
	int x = 1;
	while (x < length / 2)
	{
		tmp = tmp->next;
		x++;
	}
	this->tail = tmp;
	NodeList* lista = new NodeList(this->tail->next);
	this->tail->next = NULL;
	this->length = x;
	return lista;
}
void NodeList::bubbleSort()
{
	if (length > 1)
	{
		Node* tmp, *tmpTail = tail;
		int x;

		for (int i = 0; i <length; i++) {
			x = 0;
			tmp = head;
			while (tmp->next)
			{
				if (tmp->value > tmp->next->value)
				{
					switchNextElement(x);
					tmp = tmp->prev;
				}
				x++;
				if (tmp->next)
					tmp = tmp->next;
			}

		}
	}
}

void NodeList::insertSort()
{
	if (head && head->next)
	{
		Node *tmp, *tmp1, *tmp2;
		tmp = head;
		tmp1 = head->next;
		tmp2 = head->next->next;
		while (tmp1)
		{
			if (tmp1->value < tmp1->prev->value)
			{
				if (tmp2)
					tmp2->prev = tmp1->prev;
				tmp1->prev->next = tmp2;
				if (tmp1->value < tmp->value)
				{
					tmp1->next = tmp;
					tmp1->prev = NULL;
					tmp->prev = tmp1;
					head = tmp1;
				}
				else
				{
					for (; tmp1->value > tmp->value; tmp = tmp->next);
					tmp1->prev = tmp->prev;
					tmp1->next = tmp;
					tmp->prev->next = tmp1;
					tmp->prev = tmp1;
				}
				
			}
			tmp1 = tmp2;
			if(tmp1)
				tmp2 = tmp1->next;
			tmp = head;
		}
	}

}


int main()
{
	NodeList lista;
	lista.readFromFile("Text.txt");
	lista.show();
	lista.insertSort();
	lista.show();


	cin.get();

	return 0;
}

