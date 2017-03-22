#include "LinkedList.h"

void main() {
	LinkedList Memory;
	int mem_size=0, b, s, cont, flag;
	bool t = 1;
	cout << "Welcome to MemoryAllocation app\n===============================" << endl << endl;
	//setting the memory size
	while (mem_size == 0)
	{
		cout << "**Memory MUST be greater than 0 byte**\n";
		cout << "Enter Memory size: ";
		cin >> mem_size;
	}
	//initializing the memory with ones => allocate all the memory
	int* MemState = new int[mem_size]();
	for (int i = 0; i < mem_size; ++i) {
		MemState[i] = 1;
	}
	//adding holes to memory
	while (t){
		cout << endl << "Enter hole base address: ";
		cin >> b;
		cout << "Enter hole size: ";
		cin >> s;
		for (int i = 0; i < s; i++){
			MemState[b + i] = 0;
		}
		cout << endl << "To continue entering holes press (1), to exit press (0): ";
		cin >> cont;
		if (!cont)
			t = 0;
	}
	int ii = 0;
	Node* tmp = nullptr;
	//arranging the memory to contain allocated parts (initially exist) and de-allocated parts (added holes)
	while (ii <= mem_size - 1){
		flag = MemState[ii];
		Memory.AddEnd(ii, 0, MemState[ii]);
		tmp = Memory.GetLast();
		while (flag == MemState[ii]){
			tmp->Set_Size(tmp->Get_Size() + 1);
			ii++;
		}
	}
	//choosing allocation method
	int method, ProcSize, conti = 1, ba, full = 0;
	char allocation;
	cout << endl << "Enter method of allocation: \n(1) for First fit \n(2) for Best fit \n(3) for Worst fit\n=> ";
	cin >> method;
	cout << endl;
	while (conti)
	{
		if (method == 1 || method == 2 || method == 3) {
		cout << endl << "To allocate a process press (a) \nTo deallocate a process press (d): ";
		cin >> allocation;
		while (allocation != 'a' && allocation != 'd')
		{
			cout << endl << "Enter a correct choice, please!" << endl;
			cout << endl << "To allocate a process press (a) \nTo deallocate a process press (d): ";
			cin >> allocation;
		}
		if (allocation == 'a')
		{
			full = Memory.Full();
			if (!full)
			{
				cout << endl << "Enter process' size: ";
				cin >> ProcSize;
				while (!(ProcSize > 0))
				{
					cout << endl << "Enter process' size again please: ";
					cin >> ProcSize;
				}
				Memory.NoHole(ProcSize);
				switch (method) {
				case 1:
					Memory.FirstFit(ProcSize);
					break;
				case 2:
					Memory.SizeSort(method);
					Memory.FirstFit(ProcSize);
					Memory.BaseSort();
					break;
				case 3:
					Memory.SizeSort(method);
					Memory.FirstFit(ProcSize);
					Memory.BaseSort();
					break;
				default:
					
					break;
				}
			}
		}
		else if (allocation == 'd')
		{
			cout << endl << "Enter base address of the process to be removed: ";
			cin >> ba;
			Memory.RemoveProcess(ba);
		}
		Memory.MergeNodes();
		Memory.PrintList();
		cout << endl << "To take another action press (1), to exit press (0): ";
		cin >> conti;
		if (!conti)
			conti = 0;
		}
		else {
			cout << "Wrong choice, try again" <<endl;
			cout << endl << "Enter method of allocation: \n(1) for First fit \n(2) for Best fit \n(3) for Worst fit\n=> ";
			cin >> method;
		}
	}
}