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

double pow(double base, int exponent);

bool is_prime(int n);

int next_prime(int x);

string toupper(const string& str);

int whichtype(string& user_choice);

class Warehouse
{
	static const int size;
	static const int max_capacity;
	Product** products = new Product* [max_capacity];
public:
	Warehouse() = default;

	Warehouse(Warehouse& wh) = delete;    //不存在所谓的复制一个仓库所以禁止这个功能

	~Warehouse()
	{ delete[] products; }

	//Accessors
	static int getcapacity()
	{ return max_capacity; }

	Product** getproducts()
	{ return products; }
};

const int Warehouse::size = pow(10, Product::getcode_length());
const int Warehouse::max_capacity = next_prime(size);

//Commodity Inbound Management System
class CIM_System
{
	Product** warehouse_accessor = nullptr;
	int total = 0;

	static int calculate_code(const string& name)
	{
		int product_code = 0;
		int warehouse_capacity = Warehouse::getcapacity();
		for (const unsigned char c: name)
			product_code = ((product_code << 4)^(product_code >> 28)^(int) c) % warehouse_capacity;
		return product_code;
	}

	void addproduct(Product& temp)
	{
		int position = calculate_code(temp.getname());
		*(warehouse_accessor + position) = &temp;
		(*(warehouse_accessor + position))->setproduct_code(position);
		total++;
	}

public:
	CIM_System() = delete;    //必须要与一个仓库进行匹配

	explicit CIM_System(Warehouse& warehouse) : warehouse_accessor(warehouse.getproducts())
	{}

	~CIM_System()
	{ delete warehouse_accessor; }

	friend int whichtype(string& user_choice);

	void inbound(ifstream& product_list);

	void inbound(istream& user_input);

};

//Commodity Outbound Management System
class COM_System
{

};

class Inventory_Manager
{

};

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

string toupper(const string& str)
{
	string uppered_str = str;
	for (char c: uppered_str)
	{
		if (c >= 'a' && c <= 'z')
			c = c - 'a' + 'A';
	}
	return uppered_str;
}

int whichtype(string& user_choice)
{
	user_choice = toupper(user_choice);
	if (user_choice == "CAKE" || user_choice == "CAKES") return CAKE;
	else if (user_choice == "COOKIE" || user_choice == "COOKIES") return COOKIE;
	else return WRONG_TYPE;
}

void CIM_System::inbound(ifstream& product_list)
{
	Product* temp;
	while (!product_list.eof())
	{
		//The content of product_list is something like this.
		// product_name\t product_type\t product_price\t product_quantity\t discount_rule1\t discount_percentage
		string name;
		bool type;
		float price, discount_percentage;
		int quantity, discount_rule1;
		product_list >> name >> type >> price >> quantity >> discount_rule1 >> discount_percentage;
		temp = new Product(name, type, price, quantity, discount_rule1, discount_percentage);
		addproduct(*temp);
	}
	temp = nullptr;
	delete temp;
}

void CIM_System::inbound(istream& user_input)
{
	Product* temp;
	do
	{
		string name, user_choice;
		bool type;
		float price, discount_percentage;
		int quantity, discount_rule1;
		cout << "Please choose the type of the product you want to add (CAKE or COOKIE):\t";
		user_input >> user_choice;
		while (whichtype(user_choice) == WRONG_TYPE)
		{
			system("clear");
			cout << "You have entered a wrong type, please choose again:\t";
			user_input >> user_choice;
		}
		type = whichtype(user_choice);
		cout << "Please enter the name of the product you want to add:\t";
		user_input >> name;
		cout << "Please enter its price:\t";
		while (!(user_input >> price) || price <= 0)
		{
			user_input.clear();
			user_input.ignore(INT_MAX, '\n');
			cout << "You have entered a wrong value for price, pleas enter again:\t";
			user_input >> price;
		}
		cout << "Please enter its quantity:\t";
		while (!(user_input >> quantity) || quantity <= 0)
		{
			user_input.clear();
			user_input.ignore(INT_MAX, '\n');
			cout << "You have entered a wrong value for quantity, pleas enter again:\t";
			user_input >> quantity;
		}
		cout << "Please enter its discount rule.\n";
		cout << "If it doesn't have discount rule, please enter 0.\n";
		cout << "The discount rule:\t";
		while (!(user_input >> discount_rule1) || discount_rule1 < 0)
		{
			user_input.clear();
			user_input.ignore(INT_MAX, '\n');
			cout << "You have entered a wrong value for discount rule, pleas enter again:\t";
			user_input >> discount_rule1;
		}
		if (discount_rule1 == 0)
			discount_rule1 = INT_MAX;
		if (discount_rule1 != 0)
		{
			cout << "Please enter its discount percentage:\t";
			while (!(user_input >> discount_percentage) || !(0 < discount_percentage && discount_percentage < 1))
			{
				user_input.clear();
				user_input.ignore(INT_MAX, '\n');
				cout << "You have entered a wrong value for discount percentage, pleas enter again:\t";
				user_input >> discount_percentage;
			}
		}

	} while ();
}

#endif //INVENTORY_MANAGER_H
