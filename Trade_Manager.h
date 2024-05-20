//
// Created by 邓初杰 on 24-5-2.
//

#ifndef Trade_MANAGER_H
#define Trade_MANAGER_H

#include<iostream>
#include<iomanip>
#include <fstream>
#include "Warehouse.h"
#include "Commodity_Inbound_Management_System.h"
#include "Commodity_Outbound_Management_System.h"
#include "Commodity_Search_System.h"
#include "Trade_System.h"
#include "Product_List.h"
#include "Bill.h"

using namespace std;

class Trade_Manager
{
	Warehouse warehouse; // Warehouse instance to manage products
	CIM_System cim_system; // Commodity Inbound Management System
	COM_System com_system; // Commodity Outbound Management System
	CS_System cs_system; // Commodity Search System
	Bill bill; // Bill instance to manage transactions
	// Function to copy products from one array to another
	static void copy_products(Product **products, Product **target)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
			target[i] = products[i];
	}

public:
	// Constructor
	Trade_Manager() : warehouse(), cim_system(warehouse),
					  com_system(warehouse), cs_system(warehouse), bill()
	{}

	Trade_Manager(Trade_Manager &t) = delete; // Disable copy constructor

	~Trade_Manager() = default; // Destructor

	int unique_products() // Get the number of unique products in the warehouse
	{
		if (!warehouse.getflag())
			warehouse.update_total();
		return warehouse.gettotal();
	}

	void remaining_inventory() // Save remaining inventory to a file
	{
		ofstream remaining_inventory("remaining_inventory.txt", ios::out | ios::trunc);
		int line_count = 0;
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse[i] != nullptr)
			{

				if (line_count != 0)
					remaining_inventory << endl;
				//product_name\t product_type\t product_price\t product_quantity\t discount_rule1\t discount_percentage
				remaining_inventory << warehouse[i]->getname() << "\t" << warehouse[i]->gettype() << "\t"
									<< warehouse[i]->getprice() << "\t" << warehouse[i]->getquantity() << "\t"
									<< warehouse[i]->getdiscount_rule1() << "\t" << warehouse[i]->getdiscount();
				line_count++;
			}
		}
	}

	State inbound(const Product &product) // Perform inbound operation with a single product
	{
		auto **original_products = new Product *[Warehouse::getcapacity()];
		copy_products(warehouse.getproducts(), original_products);
		State state = cim_system.inbound(product);
		if (state == FAILED)
		{
			delete[] warehouse.getproducts();
			warehouse.setproducts(original_products);
		}
		else
		{
			delete[]original_products;
			warehouse.changeflag();

			this->remaining_inventory();
		}
		return state;
	}

	State inbound(ifstream &product_list) // Perform inbound operation with a list of products from a file
	{
		auto **original_products = new Product *[Warehouse::getcapacity()];
		copy_products(warehouse.getproducts(), original_products);
		State state = cim_system.inbound(product_list);
		if (state == FAILED)
		{
			delete[] warehouse.getproducts();
			warehouse.setproducts(original_products);
		}
		else
		{
			delete[]original_products;
			warehouse.changeflag();
			this->remaining_inventory();
		}
		return state;
	}

	State inbound(Product_List &product_list) // Perform inbound operation with a list of products
	{
		auto **original_products = new Product *[Warehouse::getcapacity()];
		copy_products(warehouse.getproducts(), original_products);
		State state = cim_system.inbound(product_list);
		if (state == FAILED)
		{
			delete[] warehouse.getproducts();
			warehouse.setproducts(original_products);
		}
		else
		{
			delete[]original_products;
			warehouse.changeflag();
			this->remaining_inventory();
		}
		return state;
	}

	// Add product to the bill by product code
	State addbill(int code)
	{
		if (cs_system.getproduct(code) == Empty)
			return NOT_FIND;
		else
		{
			Product item(cs_system.getproduct(code));
			item.setquantity(1);
			bill.addproduct(item);
		};
		return SUCCESS;
	}

	// Add product to the bill by product name
	State addbill(const string &name)
	{
		if (cs_system.getproduct(name) == Empty)
			return NOT_FIND;
		else
		{
			bill.addproduct(cs_system.getproduct(name));
		}
		return SUCCESS;
	}

	// Get the number of products in the bill
	int getbill_count()
	{ return bill.gettotal(); }

	// Show the bill details
	ostream &showbill()
	{
		system("cls");
		print(bill);
		return cout;
	}

	// Remove the last added product from the bill
	void remove()
	{ bill.pop(); }

	// Remove product from the bill by position
	State remove(int position)
	{
		return bill.remove(position);
	}

	// Clear the bill
	void clear()
	{
		warehouse.clear();
	}

	// Set quantity of a product in the bill
	State setunit(int index, int unit)
	{
		int code = bill[index]->getcode();
		if (cs_system.getproduct(code).getquantity() >= unit)
			bill.setunit(index, unit);
		else
		{
			cout << "Only have " << cs_system.getproduct(code).getquantity() << " of "
				 << bill[index]->getname() << " but want to buy " << unit << endl;
			return FAILED;
		}
		return SUCCESS;
	}

	// Get the grand total of the bill
	float getgrand_total()
	{ return bill.getgrand_total() - bill.get_adjustment(); }

	bool bill_is_empty()
	{ return bill.is_empty(); }

	// Process payment for the bill
	bool paybill(float cash)
	{
		bill.setcash(cash);
		if (bill.getcash() >= this->getgrand_total())
		{
			com_system.outbound(bill);
			this->remaining_inventory();
			bill.clear_bill();
			return true;
		}
		else
		{
			showbill();
			return false;
		}
	}

	// Reload inventory from file
	State reload()
	{
		ifstream inventory("remaining_inventory.txt");
		if (!inventory.is_open())
			return NOT_FIND;
		else
		{
			cim_system.inbound(inventory);
			inventory.close();
			return SUCCESS;
		}
	}

	// Get product by product code
	const Product &getproduct(int product_code) const
	{ return cs_system.getproduct(product_code); }

	// Get product by product name
	const Product &getproduct(const string &product_name) const
	{ return cs_system.getproduct(product_name); }

// Get all products
	void getall(Product_List &all, Commands sort_base = BASE_NAME, Commands order = ASCENDING_ORDER)
	{ cs_system.getall(all, sort_base, order); }

// Get all cakes
	void getcakes(Product_List &cakes, Commands sort_base = BASE_NAME, Commands order = ASCENDING_ORDER)
	{ cs_system.getcakes(cakes, sort_base, order); }

// Get all cookies
	void getcookies(Product_List &cookies, Commands sort_base = BASE_NAME, Commands order = ASCENDING_ORDER)
	{ cs_system.getcookies(cookies, sort_base, order); }

// Get products with lower price than the specified price
	void getlower_price(Product_List &products, double price, Commands sort_base = BASE_PRICE,
						Commands order = ASCENDING_ORDER)
	{ cs_system.getlower_price(products, price, sort_base, order); }

// Get products with higher price than the specified price
	void gethigher_price(Product_List &products, double price, Commands sort_base = BASE_PRICE,
						 Commands order = DESCENDING_ORDER)
	{ cs_system.gethigher_price(products, price, sort_base, order); }

// Get products needing replenishment based on a rule
	void need_replenishment(Product_List &products, int rule, Commands sort_base = BASE_QUANTITY,
							Commands order = ASCENDING_ORDER)
	{ cs_system.need_replenishment(products, rule, sort_base, order); }

// Get products with discount
	void have_discount(Product_List &products, Commands sort_base = BASE_DISCOUNT, Commands order = ASCENDING_ORDER)
	{ cs_system.have_discount(products, sort_base, order); }

// Perform fuzzy search for products based on a substring
	void fuzzy_search(const string &sub_string, Product_List &result, Commands sort_base = BASE_NAME,
					  Commands order = ASCENDING_ORDER)
	{ cs_system.fuzzy_search(sub_string, result, sort_base, order); }


	ostream &showproducts() // Show all products in the warehouse
	{
		show_warehouse(warehouse);
		return cout;
	}

};


#endif //Trade_MANAGER_H

