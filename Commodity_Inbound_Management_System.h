//
// Created by 邓初杰 on 24-5-10.
//

#ifndef COMMODITY_INBOUND_MANAGEMENT_SYSTEM_H
#define COMMODITY_INBOUND_MANAGEMENT_SYSTEM_H

#include "Warehouse.h"
#include<iostream>
#include <string>
#include <fstream>

using namespace std;

string toupper(const string& str);

string tolower(const string& str);

string title(const string& str);

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

	State addproduct(Product& temp);

public:
	CIM_System() = delete;    //必须要与一个仓库进行匹配

	explicit CIM_System(Warehouse& warehouse) : warehouse_accessor(warehouse.getproducts())
	{}

	~CIM_System()
	{ delete warehouse_accessor; }

	int gettotal() const
	{ return total; }

	State inbound(ifstream& product_list);

	void inbound(istream& user_input);

	int update_total();
};

State CIM_System::addproduct(Product& temp)
{
	int position = calculate_code(temp.getname());
	if (warehouse_accessor[position] == nullptr)
	{
		warehouse_accessor[position] = &temp;
		warehouse_accessor[position]->setproduct_code(position);
		total++;
		return SUCCESS;
	}
	else
	{
		if (*warehouse_accessor[position] == temp)
		{
			*warehouse_accessor[position] += temp;
			return SUCCESS;
		}
		else
		{
			int flag = 1;
			for (int step = 1; step < INT_MAX; step++)
			{
				position = (position + step * step) % Warehouse::getcapacity();
				flag++;
				if (warehouse_accessor[position] == nullptr)
				{
					warehouse_accessor[position] = &temp;
					break;
				}
			}
			if (flag == INT_MAX)
				return FAILED;
			else
			{
				total++;
				return SUCCESS;
			}
		}
	}
}

State CIM_System::inbound(ifstream& product_list)
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
	if (product_list.fail())
		return FAILED;
	else
		return SUCCESS;
}

void CIM_System::inbound(istream& user_input)
{
	string user_choice;
	do
	{
		Product* temp;
		string name;
		bool type;
		float price, discount_percentage;
		int quantity, discount_rule1;
		cout << "Please choose the type of the product you want to add (CAKE or COOKIE):\t";
		user_input >> user_choice;
		user_choice = toupper(user_choice);
		while (whichtype(user_choice) == WRONG_TYPE)
		{
			system("cls");
			cout << "You have entered a wrong type, please choose again:\t";
			user_input >> user_choice;
		}
		type = whichtype(user_choice);
		system("cls");
		cout << "Please enter the name of the product you want to add:\t";
		getchar();
		getline(user_input, name);
		name = title(name);
		system("cls");
		cout << "Please enter its price:\t";
		user_input >> price;
		while (user_input.fail() || price <= 0)
		{
			user_input.clear();
			user_input.ignore(INT_MAX, '\n');
			system("cls");
			cout << "You have entered a wrong value for price, pleas enter again:\t";
			user_input >> price;
		}
		system("cls");
		cout << "Please enter its quantity:\t";
		user_input >> quantity;
		while (user_input.fail() || quantity <= 0)
		{
			user_input.clear();
			user_input.ignore(INT_MAX, '\n');
			system("cls");
			cout << "You have entered a wrong value for quantity, pleas enter again:\t";
			user_input >> quantity;
		}
		system("cls");
		cout << "Please enter its discount rule.\n";
		cout << "If it doesn't have discount rule, please enter 0.\n";
		cout << "The discount rule:\t";
		user_input >> discount_rule1;
		while (user_input.fail() || discount_rule1 < 0)
		{
			user_input.clear();
			user_input.ignore(INT_MAX, '\n');
			system("cls");
			cout << "You have entered a wrong value for discount rule, pleas enter again:\t";
			user_input >> discount_rule1;
		}
		if (discount_rule1 == 0)
		{
			discount_rule1 = INT_MAX;
			discount_percentage = 0;
		}
		else
		{
			system("cls");
			cout << "Please enter its discount percentage(between 0 and 1):\t";
			user_input >> discount_percentage;
			while (user_input.fail() || !(0 < discount_percentage && discount_percentage < 1))
			{
				user_input.clear();
				user_input.ignore(INT_MAX, '\n');
				system("cls");
				cout << "You have entered a wrong value for discount percentage, pleas enter again:\t";
				user_input >> discount_percentage;
			}
		}
		temp = new Product(name, type, price, quantity, discount_rule1, discount_percentage);
		system("cls");
		cout << "Here is the information of the product you want to add. Please check whether it is correct or not.\n";
		print(*temp);
		cout << "If correct enter Y, if not enter N:\t";
		getchar();
		getline(user_input, user_choice);
		user_choice = toupper(user_choice);
		while (user_choice != "Y" && user_choice != "N")
		{
			system("cls");
			cout << user_choice;
			cout << "You have entered a wrong choice, please enter again:\t";
			getline(user_input, user_choice);
		}
		if (user_choice == "Y")
		{
			cout << "This product has been successfully added into warehouse." << endl;
			temp = nullptr;
			delete temp;
		}
		else
		{
			delete temp;
			cout << "The information of the product that you entered has been cleared" << endl;
		}

		cout << "Do you want to add again?" << endl;
		cout << "Enter Y to add again or enter N to quit:\t";
		getline(user_input, user_choice);
		user_choice = toupper(user_choice);
		while (user_choice != "Y" && user_choice != "N")
		{
			system("cls");
			cout << "You have entered a wrong choice, please enter again:\t";
			getline(user_input, user_choice);
		}
		user_choice = toupper(user_choice);
		if (user_choice == "N")
		{
			system("cls");
			cout << "Thank you for use." << endl;
		}
		else system("cls");
	} while (user_choice != "N");
}

int CIM_System::update_total()
{
	int original_total = total;
	int count = total;
	for (int i = 0; i < Warehouse::getcapacity(); i++)
	{

		if (count == 0)
			break;
		if (warehouse_accessor[i] != nullptr)
		{
			count--;
			if (warehouse_accessor[i]->getquantity() == SELLOUT)
				total--;
		}
	}
	int updated_total = total;
	return original_total - updated_total;
}

string toupper(const string& str)
{
	string uppered_str = str;
	for (char& c: uppered_str)
	{
		if (c >= 'a' && c <= 'z')
			c = c - 'a' + 'A';
	}
	return uppered_str;
}

string tolower(const string& str)
{
	string lowered_str = str;
	for (char& c: lowered_str)
	{
		if (c >= 'A' && c <= 'Z')
			c = c - 'A' + 'a';
	}
	return lowered_str;
}

string title(const string& str)
{
	string capitalized_str = str;
	bool firstletter = true;
	for (char& c: capitalized_str)
	{
		if (firstletter)
		{
			c = toupper(c);
			firstletter = false;
		}
		else
		{
			c = tolower(c);
			if (c == ' ' || c == '_')
				firstletter = true;
		}
	}
	return capitalized_str;
}

#endif //COMMODITY_INBOUND_MANAGEMENT_SYSTEM_H
