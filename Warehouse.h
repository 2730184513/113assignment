//
// Created by 邓初杰 on 24-5-10.
//

#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include "Product.h"
#include<iostream>
#include <string>
#include <fstream>
using namespace std;

double pow(double base, int exponent);

bool is_prime(int n);

int next_prime(int x);

class Warehouse
{
	static const int size;
	static const int max_capacity;
	Product** products = new Product* [max_capacity];
public:
	Warehouse()
	{
		for(int i =0;i<max_capacity;i++)
			products[i]= nullptr;
	}

	Warehouse(Warehouse& wh) = delete;    //不存在所谓的复制一个仓库所以禁止这个功能

	~Warehouse()
	{
		for(int i =0;i<max_capacity;i++)
			delete products[i];
		delete[] products;
	}

	//Accessors
	static int getcapacity()
	{ return max_capacity; }

	Product** getproducts()
	{ return products; }
};

const int Warehouse::size = pow(10, Product::getcode_length());
const int Warehouse::max_capacity = next_prime(size);

double pow(double base, int exponent)
{
	double result = base;
	for (int temp = exponent; temp > 1; temp--)
	{
		result *= base;
	}
	return result;
}

bool is_prime(int n)
{
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6)
		if (n % i == 0 || n % (i + 2) == 0) return false;
	return true;
}

int next_prime(int x)
{
	if (x <= 1) return 2;
	int prime = x + 1;
	while (true)
	{
		if (is_prime(prime)) return prime;
		prime++;
	}
}



#endif //WAREHOUSE_H
