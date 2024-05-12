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

//Commodity Outbound Management System
class COM_System
{
	Product **warehouse_accessor = nullptr;

	void remove_product(Product &product)
	{
		int position = product.getcode();
		*warehouse_accessor[position] -= product;
	}

public:
	COM_System() = delete;

	explicit COM_System(Warehouse &wh) : warehouse_accessor(wh.getproducts())
	{}

	void outbound(Product &product);

	void outbound(istream &user_input);

	void outbound(Product **product_list);


};

#endif //COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
