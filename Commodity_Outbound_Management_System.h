//
// Created by 邓初杰 on 24-5-10.
//

#ifndef COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
#define COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
#include "Warehouse.h"
#include<iostream>
#include <string>
#include <fstream>
using namespace std;

//Commodity Outbound Management System
class COM_System
{
	Product** warehouse_accessor = nullptr;

	static int calculate_code(const string& name)
	{
		int product_code = 0;
		int warehouse_capacity = Warehouse::getcapacity();
		for (const unsigned char c: name)
			product_code = ((product_code << 4)^(product_code >> 28)^(int) c) % warehouse_capacity;
		return product_code;
	}

public:
	COM_System() = delete;

	COM_System(Warehouse& wh) : warehouse_accessor(wh.getproducts())
	{}

	~COM_System()
	{ delete warehouse_accessor; }

};

#endif //COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
