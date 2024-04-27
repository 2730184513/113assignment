#include <iostream>
#include "Bakery_Product.h"
using namespace std;

int main()
{
	string name1 = "test";
	string name2 = "text";
	Cake a(name1,15.5,10,15,0.6);
	Cake b(name2,15,10,16,0.6);
	a+b;
	cout<<a.getquantity();
}
