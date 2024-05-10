#include <iostream>
#include "Inventory_manager.h"
using namespace std;
int main()
{
//	string user_choice;
//	system("pause");
	Warehouse wh;
	CIM_System cims(wh);
	cims.inbound(cin);
}

