// AIDS_LAB.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "NodeList.h"
#include <fstream>
#include <string>
using namespace std;

void bubbleSort(NodeList &list)
{
	if (list.length > 1)
	{
		Node* tmp, *tmpTail = list.tail;
		int x;

		for (int i = 0; i < list.length; i++) {
			x = 0;
			tmp = list.head;
			while (tmp->next)
			{
				if (tmp->value > tmp->next->value)
				{
					list.switchNextElement(x);
					tmp = tmp->prev;
				}
				x++;
				if (tmp->next)
					tmp = tmp->next;
			}

		}
	}
}

void insertSort(NodeList &list)
{
	if (list.head && list.head->next)
	{
		Node *tmp, *tmp1, *tmp2;
		tmp = list.head;
		tmp1 = list.head->next;
		tmp2 = list.head->next->next;
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
					list.head = tmp1;
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
			if (tmp1)
				tmp2 = tmp1->next;
			tmp = list.head;
		}
	}
}

void selectionSort(NodeList &list) {

	if (list.head && list.head->next) {
		Node *min;
		Node *tmp_head = list.head, *tmp = list.head->next;
		
		for (int i = 0; tmp_head->next; i++, tmp_head = list[i],tmp = tmp_head->next  ) {
			min = tmp_head;
			
			

			while (tmp) {

				if (tmp->value < min->value) {
					min = tmp;
				}
				tmp = tmp->next;

			}

			list.swap(tmp_head, min);
			
		}
	}
}

int main()
{
	NodeList lista;
	lista.readFromFile("Text.txt");
	lista.show();
	selectionSort(lista);
	lista.show();

	cin.get();

	return 0;
}

