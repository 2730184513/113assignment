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
	CS_System() = delete;

	explicit CS_System(Warehouse& wh) : warehouse_accessor(wh.getproducts())
	{}

	~CS_System()=default;

	Product& getproduct(int product_code)
	{ return **(warehouse_accessor + product_code); }

	Product& getproduct(const string& product_name)
	{
		int product_code = calculate_code(product_name);
		return **(warehouse_accessor + product_code);
	}

	Product_List getcakes(Product** cakes)
	{
		Product_List temp_cakes();
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->gettype() == CAKE)
			{
				temp_cakes[count] = warehouse_accessor[i];
				count++;
			}
		}
		cakes = new Product* [count + 1];
		cakes[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			cakes[i + 1] = temp_cakes[i];
		return cakes;
	}

	Product** getcookies(Product** cookies)
	{
		Product* temp_cookies[Warehouse::getcapacity()];
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->gettype() == COOKIE)
			{
				temp_cookies[count] = warehouse_accessor[i];
				count++;
			}
		}
		cookies = new Product* [count + 1];
		cookies[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			cookies[i + 1] = temp_cookies[i];
		return cookies;
	}

	Product** getlower_price(Product** products, double price)
	{
		Product* temp_products[Warehouse::getcapacity()];
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getprice() <= price)
			{
				temp_products[count] = warehouse_accessor[i];
				count++;
			}
		}
		products = new Product* [count + 1];
		products[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			products[i + 1] = temp_products[i];
		return products;
	}

	Product** gethigher_price(Product** products, double price)
	{
		Product* temp_products[Warehouse::getcapacity()];
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getprice() >= price)
			{
				temp_products[count] = warehouse_accessor[i];
				count++;
			}
		}
		products = new Product* [count + 1];
		products[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			products[i + 1] = temp_products[i];
		return products;
	}

	Product** getsell_out(Product** products)
	{
		Product* temp_products[Warehouse::getcapacity()];
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getquantity() == SELLOUT)
			{
				temp_products[count] = warehouse_accessor[i];
				count++;
			}
		}
		products = new Product* [count + 1];
		products[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			products[i + 1] = temp_products[i];
		return products;
	}

	Product** need_replenishment(Product** products, int rule)

	{
		Product* temp_products[Warehouse::getcapacity()];
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getquantity() <= rule)
			{
				temp_products[count] = warehouse_accessor[i];
				count++;
			}
		}
		products = new Product* [count + 1];
		products[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			products[i + 1] = temp_products[i];
		return products;
	}

	Product** have_discount(Product** products)
	{
		Product* temp_products[Warehouse::getcapacity()];
		int count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i]->getdiscount() != 0)
			{
				temp_products[count] = warehouse_accessor[i];
				count++;
			}
		}
		products = new Product* [count + 1];
		products[0]->setquantity(count + 1);
		for (int i = 0; i < count; i++)
			products[i + 1] = temp_products[i];
		return products;
	}

};

#endif //COMMODITY_SEARCH_SYSTEM_H
