//
// Created by 邓初杰 on 24-5-10.
//

#ifndef COMMODITY_SEARCH_SYSTEM_H
#define COMMODITY_SEARCH_SYSTEM_H

#include "Warehouse.h"
#include "Product_List.h"
#include<iostream>
#include <string>

using namespace std;

//Commodity search system
class CS_System
{
	Product **const warehouse_accessor = nullptr;

	static int calculate_code(const string &name)
	{
		int product_code = 0;
		int warehouse_capacity = Warehouse::getcapacity();
		for (const unsigned char c: name)
			product_code = ((product_code << 4) ^ (product_code >> 28) ^ (int) c) % warehouse_capacity;
		return product_code;
	}

public:
	CS_System() = delete;

	explicit CS_System(Warehouse &wh) : warehouse_accessor(wh.getproducts())
	{}

	~CS_System() = default;

	Product &getproduct(int product_code)
	{ return *warehouse_accessor[product_code]; }

	Product &getproduct(const string &product_name)
	{
		int product_code = calculate_code(product_name);
		return *warehouse_accessor[product_code];
	}

	Product_List getcakes(Product_List cakes)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->gettype() == CAKE)
				cakes.addback(*warehouse_accessor[i]);
		}
		return cakes;
	}

	Product_List getcookies(Product_List cookies)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->gettype() == CAKE)
				cookies.addback(*warehouse_accessor[i]);
		}
		return cookies;
	}

	Product_List getlower_price(Product_List products, double price)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getprice() <= price)
				products.addback(*warehouse_accessor[i]);
		}
		return products;
	}

	Product_List gethigher_price(Product_List products, double price)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getprice() >= price)
				products.addback(*warehouse_accessor[i]);
		}
		return products;
	}

	Product_List getsell_out(Product_List products)
	{

		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getquantity() == SELLOUT)
				products.addback(*warehouse_accessor[i]);
		}
		return products;
	}

	Product_List need_replenishment(Product_List products, int rule)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getquantity() <= rule)
				products.addback(*warehouse_accessor[i]);
		}
		return products;
	}

	Product_List have_discount(Product_List products)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getdiscount() != NO_DISCOUNT)
				products.addback(*warehouse_accessor[i]);
		}
		return products;
	}

};

#endif //COMMODITY_SEARCH_SYSTEM_H
