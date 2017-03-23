#include <iostream>
using namespace std;

class Node
{
private:
	int base, size;
	bool allocated;
	Node * next;
public:
	Node()
	{
		base = 0;
		size = 0;
		allocated = true;
		next = nullptr;
	}
	Node (int b, int s, bool alloc)
	{
		base = b;
		size = s;
		allocated = alloc;
		next = nullptr;
	}	
};

class LinkedList
{
private:
	Node* head;
public:
	LinkedList()
	{
		head = nullptr;
	}
};