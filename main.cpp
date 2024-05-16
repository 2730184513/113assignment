#include <iostream>
#include <ctime>
#include "Product_List.h"
#include "Commodity_Outbound_Management_System.h"
#include "Bill.h"

using namespace std;

int main()
{
	Product_List test(5);
	Product cake1("Chocolate Peanut Butter Cake", 0, 1, 110, 11, 0.7);
	Product cake2("Chocolate Covered Strawberry Cake", 0, 2, 120, 12, 0.7);
	Product cake3("Margarita Cake", 0, 3, 130, 13, 0.7);
	Product list[] = {cake1, cake2, cake3};
	Bill bill;
	for (auto & i : list)
	{
		bill.addproduct(i);
	}
	print(bill);
//	print(cake1)<<endl;
//	print(cake2)<<endl;
//	print(cake3)<<endl;
//	test.addback(list,3);
//	print(test);

//	print(cake1=cake2+cake1)<<endl;
//	print(cake1)<<endl;
//	print(cake2)<<endl;
//	print(cake3)<<endl;
//	Product* p1 =&cake1;
//	Product* p2 =&cake2;
//	Product* p3 =&cake3;
//	Product* list[3] = {p1,p2,p3};
//	test.addback(cake1);
//	test.addback(cake2);
//	test.addback(cake3);
//	test.addback(list,3);
//	cout<<p1<<"\t"<<p2<<"\t"<<p3<<"\t"<<endl;
//	print(test.front() = test.back())<<endl;
//	print(test[1])<<endl;
//	print(test.back())<<endl;
//
//	cout<<p1<<"\t"<<p2<<"\t"<<p3<<"\t"<<endl;
}

