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
	void Set_Base(int b) 
	{
		base = b;
	}
	int Get_Base() 
	{
		return base;
	}
	void Set_Size(int s)
	{
		size = s;
	}
	int Get_Size()
	{
		return size;
	}
	void Set_Next (Node* n)
	{
		next = n;
	}
	Node* Get_Next ()
	{
		return next;
	}
	bool isAllocated() {
		return allocated;
	}
	void UnSet_Allocate(Node* n) {
		n->allocated = 0;
	}
	friend class LinkedList;
}; // end of Node class

class LinkedList
{
private:
	Node* head;
public:
	LinkedList()
	{
		head = nullptr;
	}
	Node* GetHead() {
		return head;
	}
	bool isEmpty()
	{
		if (head == nullptr)
			return true;
		return false;
	}
	void AddFront(int b, int s, bool alloc)
	{
		Node * nw = new Node(b, s, alloc);
		nw->Set_Next(head);
		head = nw;
	}
	void RemoveFront()
	{
		if (isEmpty())
			return;
		Node * tmp = head;
		head = head->Get_Next();
		delete tmp;
	}
	void AddEnd(int b, int s, bool alloc)
	{
		Node * nw = nullptr;
		if (isEmpty())
			AddFront(b, s, alloc);
		else
		{
			Node * tmp = head;
			while (tmp->next != nullptr)
			{
				tmp = tmp->next;
			}
			nw = new Node(b, s, alloc);
			tmp->next = nw;
		}
	}
	void RemoveEnd()
	{
		if (isEmpty())
			return;
		if (head->next == nullptr)
		{
			RemoveFront();
			return;
		}
		Node * tmp1 = head;
		Node * tmp2 = head->next;

		while (tmp2->next != nullptr)
		{
			tmp1 = tmp1->next;
			tmp2 = tmp2->next;
		}
		tmp1->next = nullptr;
		delete tmp2;
	}
	void AddIndex(int b, int s, bool alloc, int index)
	{
		if (isEmpty() || index == 0)
		{
			AddFront(b, s, alloc);
			return;
		}
		Node * tmp = head;
		while (--index != 0) 
		{
			tmp = tmp->next;
			if (tmp == nullptr)
				return;
		}
		Node * nw = new Node(b, s, alloc);
		nw->next = tmp->next;
		tmp->next = nw;
	}
	void RemoveIndex(int index)
	{
		if (isEmpty())
		{
			return;
		}
		if (index == 0)
			RemoveFront();
		Node * tmp = head;
		while (--index != 0)
		{
			tmp = tmp->next;
			if (tmp == nullptr)
				return;
		}
		Node * toberemoved = tmp->next;
		tmp->next = toberemoved->next;
		delete toberemoved;
	}
	int FindItem(int b)
	{
		if (isEmpty())
		{
			cout << "List in empty" << endl;
			return -1;
		}
		Node * tmp = head;
		int index = 0;
		while (tmp != nullptr)
		{
			if (tmp->base == b)
				return index;
			tmp = tmp->next;
			index++;
		}
		return -1;
	}
	void PrintList()
	{
		Node * tmp = head;
		while (tmp != nullptr)
		{
			if (tmp->next != nullptr) {
				cout << "( Base address: " << tmp->base << ", Block size: " << tmp->size << ", Allocated?: " << tmp->allocated << " ) ->" << endl;
				tmp = tmp->next;
			}
			else
			{
				cout << "( Base address: " << tmp->base << ", Block size: " << tmp->size << ", Allocated?: " << tmp->allocated << " )" << endl;
				tmp = tmp->next;
			}
		}
	}
	void clear()
	{
		while (head != nullptr)
			RemoveFront();
	}
	Node* GetLast() {
		Node* tmp = head;
		if (isEmpty())
			return tmp;
		while (tmp != nullptr)
		{
			if (tmp->next == nullptr)
				return tmp;
			tmp = tmp->next;
		}
	}
	int GetNodes() {
		int count = 0;
		Node* tmp = head;
		while (tmp != nullptr)
		{
			count++;
			tmp = tmp->next;
		}
		return count;
	}
	Node* GetFirst() {
		return head;
	}
	void SizeSort(int method) {
		LinkedList tmplist;
		Node* tmp = head;
		int smallestSize = tmp->Get_Size();
		int smallestBase = tmp->Get_Base();
		bool smallestAlloc = tmp->isAllocated();
		int count = GetNodes();
		for (int i = 0; i < count; i++) {

			if (i == count - 1);
			else {
				while (tmp != nullptr)
				{
					if (tmp->Get_Size() < smallestSize)
					{
						smallestSize = tmp->Get_Size();
						smallestBase = tmp->Get_Base();
						smallestAlloc = tmp->isAllocated();
					}
					tmp = tmp->Get_Next();
				}
				RemoveIndex(FindItem(smallestBase));
				tmp = head;
			}
			if (method == 2)
			{
				tmplist.AddEnd(smallestBase, smallestSize, smallestAlloc);
			}
			else
			{
				tmplist.AddFront(smallestBase, smallestSize, smallestAlloc);
			}
			smallestSize = tmp->Get_Size();
			smallestBase = tmp->Get_Base();
			smallestAlloc = tmp->isAllocated();
		}
		*this = tmplist;
	}
	void FirstFit(int ProcSize) {
		Node* temp = head;
		while (temp != nullptr) {
			if (!temp->isAllocated() && (temp->Get_Size() >= ProcSize))
			{
				AddIndex(temp->Get_Base(), ProcSize, 1, FindItem(temp->Get_Base()));
				temp->Set_Base(temp->Get_Base() + ProcSize);
				temp->Set_Size(temp->Get_Size() - ProcSize);
				break;
			}
			temp = temp->Get_Next();
		}
	}
	void BaseSort() {
		LinkedList tmplist;
		Node* tmp = head;
		int smallestSize = tmp->Get_Size();
		int smallestBase = tmp->Get_Base();
		bool smallestAlloc = tmp->isAllocated();
		int count = GetNodes();
		for (int i = 0; i < count; i++) {

			if (i == count - 1);
			else {
				while (tmp != nullptr)
				{
					if (tmp->Get_Base() < smallestBase)
					{
						smallestSize = tmp->Get_Size();
						smallestBase = tmp->Get_Base();
						smallestAlloc = tmp->isAllocated();
					}
					tmp = tmp->Get_Next();
				}
				RemoveIndex(FindItem(smallestBase));
				tmp = head;
			}
			if (smallestSize != 0)
			{
				tmplist.AddEnd(smallestBase, smallestSize, smallestAlloc);
			}
			smallestSize = tmp->Get_Size();
			smallestBase = tmp->Get_Base();
			smallestAlloc = tmp->isAllocated();
		}
		*this = tmplist;

	}
	Node* GetNode(int b) {
		Node* tmp = head;
		if (isEmpty())
			return tmp;
		while (tmp->Get_Base() != b && tmp != nullptr)
		{
			tmp = tmp->next;
		}
		return tmp;
	}
	void RemoveProcess(int base) {
		Node* tmp = head;
		int f = 0;
		while (tmp != nullptr) {
			if (tmp->Get_Base() == base)
			{
				tmp->UnSet_Allocate(tmp);
				f = 1;
				cout << endl << "After de-allocation\n" << endl;
				return;
			}
			tmp = tmp->next;
		}
		if (!f)
		{
			cout << "\n<UNDEFINED PROCESS!>\n" << endl;
		}
		
	}
	void MergeNodes() {
		Node* tmp = head;
		if (isEmpty())
			return;
		while (tmp->next != nullptr)
		{
			if (!tmp->isAllocated() && !tmp->next->isAllocated())
			{
				tmp->Set_Size(tmp->Get_Size() + tmp->next->Get_Size());
				RemoveIndex(FindItem(tmp->next->Get_Base()));
				return;
			}
			tmp = tmp->next;
		}
	}
	int Full() {
		Node* tmp = head;
		int f = 0;
		while (tmp != nullptr) {
			if (!tmp->isAllocated())
			{
				f = 1;
				break;
			}
			tmp = tmp->next;
		}
		if (!f)
		{
			cout << endl << "<MEMORY FULL!>" << endl;
			return 1;
		}
		return 0;
	}
	void NoHole(int s) {
		Node *tmp = head;
		while (tmp != nullptr) {
			if (tmp->Get_Size() >= s && !tmp->isAllocated())
			{
				cout << endl << "After allocation\n" << endl;
				return;
			}
			tmp = tmp->next;
		}
		cout << "\n<NO SPACE IN MEMORY>\n" << endl << "Memory contains..\n" << endl;
	}
}; // end of LinkedList class