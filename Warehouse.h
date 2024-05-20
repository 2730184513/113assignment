#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "Product.h" // Include Product header file for Product class definition.
#include<iostream> // Include necessary header files.
#include <string>
#include <fstream>

using namespace std; // Using the standard namespace for shorthand access to standard library entities.

// Forward declarations of functions defined outside the class.
double pow(double base, int exponent); // Function to calculate power.
bool is_prime(int n); // Function to check if a number is prime.
int next_prime(int x); // Function to find the next prime number.

// Declaration of Warehouse class.
class Warehouse
{
	static const int size; // Static constant variable to store size.
	static const int max_capacity; // Static constant variable to store maximum capacity.
	int total = 0; // Variable to store total number of products in the warehouse.
	bool updated_flag = false; // Flag to indicate if the warehouse has been updated.
	Product **products = new Product *[max_capacity]; // Array of pointers to store products.

public:
	// Constructor for Warehouse class.
	Warehouse()
	{
		for (int i = 0; i < max_capacity; i++)
			products[i] = nullptr;
	}

	// Destructor for Warehouse class.
	~Warehouse()
	{
		for (int i = 0; i < max_capacity; i++)
			delete products[i];
		delete[] products;
	}

	// Function to toggle the updated flag.
	void changeflag()
	{
		if (updated_flag)
			updated_flag = false;
		else
			updated_flag = true;
	}

	// Function to set products in the warehouse.
	void setproducts(Product **newproducts)
	{ products = newproducts; }

	// Static function to get the maximum capacity of the warehouse.
	static int getcapacity()
	{ return max_capacity; }

	// Function to get the products in the warehouse.
	Product **getproducts()
	{ return products; }

	// Function to get the updated flag.
	bool getflag() const
	{ return updated_flag; }

	// Function to update the total number of products in the warehouse.
	int update_total()
	{
		int original_total = total;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (products[i] != nullptr && products[i]->getquantity() != SELLOUT)
				total++;
		}
		this->changeflag();
		int updated_total = total;
		return original_total - updated_total;
	}

	// Function to get the total number of products in the warehouse.
	int gettotal() const
	{ return total; }

	// Function to clear the warehouse.
	void clear()
	{
		for (int i = 0; i < max_capacity; i++)
		{
			delete products[i];
			products[i] = nullptr;
		}
	}

	// Overloaded subscript operator to access products by code.
	const Product *operator[](int code)
	{
		if (code > max_capacity || code < 0)
			throw out_of_range("Out of range");
		else
			return products[code];
	}

	// Friend function declaration to print the warehouse.
	friend ostream &show_warehouse(Warehouse &warehouse);

};

// Definition of static const member variables of Warehouse class.
const int Warehouse::size = pow(10, Product::getcode_length());
const int Warehouse::max_capacity = next_prime(size);

// Function definition to calculate power.
double pow(double base, int exponent)
{
	double result = base;
	for (int temp = exponent; temp > 1; temp--)
	{
		result *= base;
	}
	return result;
}

// Function definition to check if a number is prime.
bool is_prime(int n)
{
	if (n <= 1) return false;
	if (n <= 3) return true;
	if (n % 2 == 0 || n % 3 == 0) return false;
	for (int i = 5; i * i <= n; i += 6)
		if (n % i == 0 || n % (i + 2) == 0) return false;
	return true;
}

// Function definition to find the next prime number.
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

// Friend function definition to print the warehouse.
ostream &show_warehouse(Warehouse &warehouse)
{
	for (int i = 0; i < Warehouse::getcapacity(); i++)
	{
		if (warehouse[i] != nullptr)
			print(*warehouse[i]);
	}
	return cout;
}

#endif //WAREHOUSE_H
