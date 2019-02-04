#include "stdafx.h"
#include "NodeList.h"


NodeList::NodeList() 
	:head(NULL), tail(NULL), length(0) 
{}

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
bool NodeList::readFromFile(std::string fileName)
{
	std::fstream plik;
	int val;
	plik.open(fileName.c_str(), std::ios::in);
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
		std::cout << std::endl;
		std::cout << "-----------------------------------------" << std::endl;
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
void NodeList::swap(int index1, int index2)
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
		std::cout << tmpa1->value << "  ---  " << tmpa2->value << std::endl;
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
void NodeList::swap(Node * node1, Node * node2)
{
	if (head && node1 && node2 && node1!=node2) {
		Node *node1_prev = node1->prev;
		Node *node1_next = node1->next;
		Node *node2_prev = node2->prev;
		Node *node2_next = node2->next;
		
		if (node1_next != node2 && node2_next != node1)
		{
			node1->prev = node2_prev;
			node1->next = node2_next;
			node2->prev = node1_prev;
			node2->next = node1_next;

			if (node1_next)
				node1_next->prev = node2;
			if (node1_prev)
				node1_prev->next = node2;
			if (node2_next)
				node2_next->prev = node1;
			if (node2_prev)
				node2_prev->next = node1;
		}
		else if(node1_next==node2)
		{
			node1->prev = node2;
			node1->next = node2_next;
			node2->prev = node1_prev;
			node2->next = node1;

			
			if (node1_prev)
				node1_prev->next = node2;
			if (node2_next)
				node2_next->prev = node1;
		}
		else if(node2_next==node1)
		{
			node1->prev = node2_prev;
			node1->next = node2;
			node2->prev = node1;
			node2->next = node1_next;

			if (node1_next)
				node1_next->prev = node2;
			if (node2_prev)
				node2_prev->next = node1;
		}
				
		

		if (this->head == node1)
			this->head = node2;
		else if (this->head == node2)
			this->head = node1;
		if (this->tail == node1)
			this->tail = node2;
		else if (this->tail == node2)
			this->tail = node1;

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
		std::cout << "Niepoprawny index!!" << std::endl;

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
		std::cout << "Niepoprawny index!!" << std::endl;
		return NULL;
	}
}
NodeList* NodeList::splitList()
{
	if (this->length < 2)
	{
		std::cout << "Lista jest zbyt krotka aby ja podzielic" << std::endl;
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

Node * NodeList::operator[](std::size_t el)
{
	if (el < length) {
		Node *tmp;
		for (tmp = head; el > 0; tmp = tmp->next, el--);
		return tmp;
	}
	else
		return nullptr;
}
