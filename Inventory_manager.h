//
// Created by 邓初杰 on 24-5-2.
//

#ifndef INVENTORY_MANAGER_H
#define INVENTORY_MANAGER_H

#include "Abstract_Product_class.h"
#include<iostream>
#include <string>
#include <fstream>

using namespace std;

double pow(double base, int exponent)
{
	double result = base;
	for (int temp = exponent; temp > 1; temp--)
	{
		result *= base;
	}
	return result;
}

class Warehouse
{
	const int max_capacity = pow(10, Product::getcode_length());
	Product **products = new Product *[max_capacity];
public:
	Warehouse() = default;

//	Warehouse(Warehouse &wh) = delete;    //不存在所谓的复制一个仓库所以禁止这个功能

	~Warehouse()
	{ delete[] products; }

	//Accessors
	int getcapacity() const
	{ return max_capacity; }

	Product **getproducts()
	{ return products; }
};

//Commodity Inbound Management System
class CIM_System
{
	Product **warehouse_accessor = nullptr;

	static bool is_prime(int n)
	{
		if (n <= 1) return false;
		if (n <= 3) return true;
		if (n % 2 == 0 || n % 3 == 0) return false;
		for (int i = 5; i * i <= n; i += 6)
			if (n % i == 0 || n % (i + 2) == 0) return false;
		return true;
	}

	static int next_prime(int x)
	{
		if (x <= 1) return 2;
		int prime = x + 1;
		while (true)
		{
			if (is_prime(prime)) return prime;
			prime++;
		}
	}

	int calculate_code(const string &name)
	{
		int product_code = 0;
		int prime_number = next_prime(pow(10, Product::getcode_length()));
		for (const unsigned char c: name)
			product_code = ((product_code << 4) ^ (product_code >> 28) ^ (int) c) % prime_number;
		return product_code;
	}

	void setproduct_code(Product &product)
	{
		int product_code = calculate_code(product.getname());
		product.setproduct_code(product_code);
	}

public:
	CIM_System() = delete;    //必须要与一个仓库进行匹配

	explicit CIM_System(Warehouse &warehouse) : warehouse_accessor(warehouse.getproducts())
	{}

	~CIM_System()
	{ delete warehouse_accessor; }

	void inbound(ifstream &product_list)
	{
		while (!product_list.eof())
		{
			//The content of product_list is something like this.
			// product_name\t product_type\t product_price\t product_quantity\t discount_rule1\t discount_percentage
			string name;
			bool type;
			float price, discount_percentage;
			int quantity, discount_rule1;
			product_list >> name >> type >> price >> quantity >> discount_rule1 >> discount_percentage;
			int position = calculate_code(name);
			*(warehouse_accessor +
			  position) = new Product(name, type, price, quantity, discount_rule1, discount_percentage);
			(*(warehouse_accessor + position))->setproduct_code(position);
		}
	}
};

//Commodity Outbound Management System
class COM_System
{

};

class Inventory_Manager
{
	Warehouse wh;
	int total=0;
	CIM_System Cims;
	COM_System COMS;
	friend void CIM_System::inbound(std::ifstream &product_list);
public:

};
#endif //INVENTORY_MANAGER_H
