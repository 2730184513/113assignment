//
// Created by 邓初杰 on 24-5-10.
//

#ifndef COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
#define COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H

#include "Warehouse.h"
#include<iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

string getdate();

string gettime();

//Commodity Outbound Management System
class COM_System
{
	Product** warehouse_accessor = nullptr;

	void remove_product(Product& product)
	{
		int position = product.getcode();
		*warehouse_accessor[position] -= product;
	}

public:
	COM_System() = delete;

	explicit COM_System(Warehouse& wh) : warehouse_accessor(wh.getproducts())
	{}

	State outbound(Product& product);

	int outbound(Product** product_list);

};

State COM_System::outbound(Product& product)
{
	string date = getdate();
	string detail_time = gettime();
	ofstream outbound_list(date, ios::app);
	int position = product.getcode();
	if (warehouse_accessor[position]->getquantity() >= product.getquantity())
	{
		*warehouse_accessor[position] -= product;
		outbound_list << detail_time << "\t" << whichtype(product.gettype()) << "\t"
					  << product.getname() << "(" << product.getcode() << ")\t"
					  << product.getquantity() << endl;
		return SUCCESS;
	}
	else
	{
		cout << "Only have " << warehouse_accessor[position]->getquantity() << " of "
			 << warehouse_accessor[position]->getname()
			 << " but want to outbound " << product.getquantity() << endl;
		return FAILED;
	}

}

int COM_System::outbound(Product** product_list)
{
	string date = getdate();
	string detail_time = gettime();
	ofstream outbound_list(date, ios::app);
	int i = 1;
	for (i; i <= product_list[0]->getquantity(); i++)
	{
		State state = outbound(*product_list[i]);
		if (state == FAILED)
			break;
	}
	return i;
}

string getdate()
{
	time_t now = time(0);
	tm* local_time = localtime(&now);
	char buffer[80];
	strftime(buffer, 80, "%Y-%B-%d-%A", local_time);
	string date = buffer;
	return date;
}

string gettime()
{
	time_t now = time(0);
	tm* local_time = localtime(&now);
	char buffer[80];
	strftime(buffer, 80, "%X", local_time);
	string detail_time = buffer;
	return detail_time;
}

#endif //COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
