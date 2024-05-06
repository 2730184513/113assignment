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

bool is_prime(int n)
{
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6)
	{
		if (n % i == 0 || n % (i + 2) == 0)
			return false;
	}
	return true;
}

int next_prime(int x)
{
	if (x <= 1) return 2;
	int prime = x + 1;
	while (!is_prime(prime))
	{
		prime++;
	}
	return prime;
}

class Warehouse
{
	int max_capacity = 1000;
	Product* products = new Product[max_capacity];
public:
	Warehouse() = default;

	Warehouse(Warehouse& wh) : max_capacity(), products()
	{}

	~Warehouse()
	{ delete[] products; }

	void setcapacity(int capacity)
	{
		if (capacity <= 1000)
			max_capacity = 1009;
		else
			max_capacity= next_prime(capacity);
	}

	void settotal()
	{

	}

	int getcapacity()
	{ return max_capacity; }
};
#endif //INVENTORY_MANAGER_H
