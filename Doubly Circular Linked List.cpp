#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
struct list {
	int key;
	double value;
	char character;
	struct list *next, *prev;
};
using namespace std;

void AddToList(list *& HEAD, int value);
bool FindElement(list *&head, int value);
void DeleteFromList(list *&HEAD, int value);
int  GetNumberOfNodes(list *head);
void RemoveAllElements(list*&head);
void AddToListMany(list *&head, int X);
void Display(list *head);
void DisplayFirstXElements(list *head, int y);
void DisplayLastXElements(list * head, int z);

int main()
{
	int X, k1, k2, k3, k4, k5;
	srand(time(NULL));
	std::string nameOfFile = "inlab02.txt";
	std::ifstream file;
	file.open(nameOfFile.c_str());
	if (file.good() == false) return -1;
	else {
		file >> X >> k1 >> k2 >> k3 >> k4 >> k5;
	}
	file.close();
	clock_t begin, end;
	double time_spent;
	begin = clock();
	list* HEAD = nullptr;
	FindElement(HEAD, k1);
	AddToListMany(HEAD, X);
	cout << "The number of nodes is: " << GetNumberOfNodes(HEAD) << endl;
	DisplayFirstXElements(HEAD, 20);
	AddToList(HEAD, k2);
	DisplayFirstXElements(HEAD, 20);
	AddToList(HEAD, k3);
	DisplayFirstXElements(HEAD, 20);
	AddToList(HEAD, k4);
	DisplayFirstXElements(HEAD, 20);
	AddToList(HEAD, k5);
	DeleteFromList(HEAD, k3);
	DisplayFirstXElements(HEAD, 20);
	DeleteFromList(HEAD, k2);
	DisplayFirstXElements(HEAD, 20);
	DeleteFromList(HEAD, k5);
	cout << "The number of nodes is: " << GetNumberOfNodes(HEAD) << endl;
	FindElement(HEAD, k5);
	DisplayLastXElements(HEAD, 11);
	RemoveAllElements(HEAD);
	DisplayLastXElements(HEAD, 11);
	cout << "The number of nodes is: " << GetNumberOfNodes(HEAD) << endl;
	end = clock();
	time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	cout << "The running time of the algorithm: " << time_spent << endl;
	return 0;
}

void AddToList(list *& HEAD, int value) {

	if (HEAD == nullptr) {  
		HEAD = (list*)malloc(sizeof(list));
		HEAD->value = rand() & 100000 + 99;
		HEAD->character = 'T';
		HEAD->key = value;
		HEAD->next = HEAD;
		HEAD->prev = HEAD;
	}
	else if (HEAD->key < value)
	{
		list *tmp = HEAD;
		while (tmp->next->key < value && tmp->next != HEAD && tmp->next->key != value)
		{
			tmp = tmp->next;
		}
		if (tmp->next->key == value) {
			cout << "Blad." << endl;
			return;
		}
		list *newElement = (list*)malloc(sizeof(list));
		newElement->value = rand() % 1000 + 1001;
		newElement->character = 'T';
		newElement->key = value;
		newElement->next = tmp->next;
		newElement->prev = tmp;
		tmp->next = newElement;
		newElement->next->prev = newElement;

	}
	else 
	{
		list* currentNode = HEAD;
		list * tmp = (list*)malloc(sizeof(list));
		tmp->value = rand() % 99900 + 90;
		tmp->character = 'T';
		tmp->key = value;
		if (currentNode->key == value) { 
			cout << "This key exist" << endl;
			return;
		}
		else if (currentNode->key > value) { 
			tmp->prev = currentNode->prev;
			tmp->next = currentNode;
			currentNode->prev = tmp;
			tmp->prev->next = tmp;
			HEAD = tmp;
		}
		else if (currentNode->next->key > value) {
			tmp->next = currentNode->next;
			currentNode->next = tmp;
			tmp->prev = currentNode;
			currentNode->next->prev = tmp;
			HEAD = tmp;
		}
		return;
	}
}
void DeleteFromList(list *&HEAD, int value)
{
	if (HEAD == nullptr)
	{
		cout << "List is empty!";
		return;
	}
	if (FindElement(HEAD, value) == false)
	{
		return;
	}
	list * temp = HEAD;
	if (temp->key == value && temp->next == temp)
	{
		temp = nullptr;
		delete HEAD;
		cout << "Deleted  1 element, because only 1 existed : " << endl;
		HEAD = temp;
		return;
	}
	if (HEAD->key == value && HEAD->next != HEAD)
	{
		HEAD->next->prev = HEAD->prev;
		HEAD->prev->next = HEAD->next;
		HEAD = HEAD->next;
		cout << "Deleted element: " << value << endl;
		return;
	}
	list * tempnext = HEAD->next;
	list * tempprev = HEAD->prev;
	while (tempnext->next != HEAD)  
	{
		if (tempnext->key == value) 
		{
			tempnext->next->prev = tempnext->prev;
			tempnext->prev->next = tempnext->next;
			tempnext = tempnext->next;
			cout << "Deleted element: " << value << endl;
		}
		tempnext = tempnext->next;
	}
	if (temp->prev->key == value)
	{
		temp->prev->prev->next = temp;
		temp->prev = temp->prev->prev;
		HEAD = temp;
		cout << "Deleted element: " << value << endl;
	}
}
void Display(list * head)
{
	list * temp = head;
	int counter = 0;
	int ilosc_wezlow = GetNumberOfNodes(temp);
	if (head == nullptr)
	{
		cout << "List is empty" << endl;
		return;
	}
	while (temp->next != head && counter < 20)
	{
		cout << temp->key << endl;
		temp = temp->next;
		counter++;
	}
	cout << temp->key << endl;

}
int GetNumberOfNodes(list *head)
{
	int counter = 1;
	if (head == nullptr)
	{
		return 0;
	}
	list *temp = head;
	while (temp->next != head)
	{
		temp = temp->next;
		counter++;
	}
	return counter + 1; 
}
bool FindElement(list *&head, int value)
{
	list * tmp = head;
	if (head == nullptr) { 
		return false;
	}
	if (tmp->key == value) 
	{
		return true;
	}
	if (tmp->prev->key == value)
	{
		cout << "Element " << tmp->prev->key << " exist and is the last" << endl;
		return true;
	}
	list *tmpnext = head->next;
	while (tmpnext != head) 
	{
		if (tmpnext->key == value)
		{
			return true;
		}
		else
		{
			tmpnext = tmpnext->next;
		}
	}
	if (false)
	{
		cout << "Not found this element in list" << endl;
		return false;
	}
}
void AddToListMany(list *&head, int X) {
	for (int i = 0; i < X; i++) {
		int rnd = rand() % 99900 + 99;
		if (false == FindElement(head, rnd))
		{
			AddToList(head, rnd);
		}
		else {
			i--;
		}
	}
}
void DisplayFirstXElements(list * head, int y)
{
	if (head == nullptr)
	{
		cout << "List is empty" << endl;
		return;
	}
	list *temp = head;
	int counter = 0;
	int ilosc_wezlow = GetNumberOfNodes(temp);
	while (temp->next != head && counter < y) 
	{
		cout << temp->key << endl;
		temp = temp->next;
		counter++;
	}
	if (temp->next == head && counter < y)
	{
		cout << temp->key << endl;
	}
}
void DisplayLastXElements(list * head, int z)
{
	if (head == nullptr)
	{
		cout << "List is empty" << endl;
		return;
	}
	list *temp = head->prev;
	int counter = 0;
	while (temp->prev != head->prev && counter < z) 
	{
		cout << temp->key << endl;
		temp = temp->prev;
		counter++;
	}
	if (counter < z)
	{
		cout << temp->key << endl;
	}
}
void RemoveAllElements(list*&head)
{
	if (head == nullptr)
	{
		return;
	}
	list * temp = head->next;
	while (temp->next != head)
	{
		list * tempnext = temp->next;
		delete temp;
		temp = tempnext;
	}
	delete head;
	head = nullptr;
	cout << "Deleted all elements " << endl;
}