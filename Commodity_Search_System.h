#ifndef COMMODITY_SEARCH_SYSTEM_H
#define COMMODITY_SEARCH_SYSTEM_H

#include "Warehouse.h"
#include "Product_List.h"
#include<iostream>
#include <string>
#include <algorithm>

using namespace std;

// Class for the Commodity Search System
class CS_System
{
	Product **const warehouse_accessor = nullptr; // Pointer to the warehouse's products

	// Function to calculate the product code based on its name
	static int calculate_code(const string &name)
	{
		int product_code = 0;
		int warehouse_capacity = Warehouse::getcapacity();
		for (const unsigned char c: name)
			product_code = ((product_code << 4) ^ (product_code >> 28) ^ (int) c) % warehouse_capacity;
		return product_code;
	}

public:
	// Default constructor is deleted
	CS_System() = delete;

	// Constructor to initialize the CS_System with a reference to a Warehouse object
	explicit CS_System(Warehouse &wh) : warehouse_accessor(wh.getproducts())
	{}

	// Destructor
	~CS_System() = default;

	// Function to retrieve a product by its code
	const Product &getproduct(int product_code) const
	{
		if (warehouse_accessor[product_code] != nullptr)
			return *warehouse_accessor[product_code];
		else
			return Empty;
	}

	// Function to retrieve a product by its name
	const Product &getproduct(const string &product_name) const
	{
		int product_code = calculate_code(product_name);
		return getproduct(product_code);
	}

	// Function to sort a product list based on given parameters
	void sort_list(Product_List &list, Commands sort_base, Commands order)
	{
		switch (sort_base)
		{
			case BASE_NAME:
			{
				if (order == ASCENDING_ORDER)
					list.compare_by_name_ascend();
				if (order == DESCENDING_ORDER)
					list.compare_by_name_descend();
			}
				break;
			case BASE_PRICE:
			{
				if (order == ASCENDING_ORDER)
					list.compare_by_price_ascend();
				if (order == DESCENDING_ORDER)
					list.compare_by_price_descend();
			}
				break;
			case BASE_QUANTITY:
			{
				if (order == ASCENDING_ORDER)
					list.compare_by_quantity_ascend();
				if (order == DESCENDING_ORDER)
					list.compare_by_quantity_descend();
			}
				break;
			case BASE_DISCOUNT:
			{
				if (order == ASCENDING_ORDER)
					list.compare_by_discount_ascend();
				if (order == DESCENDING_ORDER)
					list.compare_by_discount_descend();
			}
		}
	}

	// Function to retrieve cakes from the warehouse and sort them
	void getcakes(Product_List &cakes, Commands sort_base = BASE_NAME, Commands order = ASCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				if (warehouse_accessor[i]->gettype() == CAKE)
					cakes.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(cakes, sort_base, order);
	}

	// Function to retrieve cookies from the warehouse and sort them
	void getcookies(Product_List &cookies, Commands sort_base = BASE_NAME, Commands order = ASCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				if (warehouse_accessor[i]->gettype() == COOKIE)
					cookies.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(cookies, sort_base, order);
	}

	// Function to retrieve all products from the warehouse and sort them
	void getall(Product_List &all, Commands sort_base = BASE_NAME, Commands order = ASCENDING_ORDER)
	{
		getcakes(all, sort_base, order);
		getcookies(all, sort_base, order);
	}

	// Function to retrieve products with price lower than or equal to the given price and sort them
	void getlower_price(Product_List &products, double price, Commands sort_base = BASE_PRICE,
						Commands order = ASCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				if (warehouse_accessor[i]->getprice() <= price)
					products.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(products, sort_base, order);
	}

	// Function to retrieve products with price higher than or equal to the given price and sort them
	void gethigher_price(Product_List &products, double price, Commands sort_base = BASE_PRICE,
						 Commands order = DESCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				if (warehouse_accessor[i]->getprice() >= price)
					products.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(products, sort_base, order);
	}

	// Function to retrieve products that need replenishment based on the given rule and sort them
	void need_replenishment(Product_List &products, int rule = 0, Commands sort_base = BASE_QUANTITY,
							Commands order = ASCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				if (warehouse_accessor[i]->getquantity() <= rule)
					products.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(products, sort_base, order);
	}

	// Function to retrieve products with discounts and sort them
	void have_discount(Product_List &products, Commands sort_base = BASE_DISCOUNT, Commands order = ASCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				if (warehouse_accessor[i]->getdiscount() != NO_DISCOUNT)
					products.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(products, sort_base, order);
	}

	// Function to perform fuzzy search for products based on a sub-string and sort the results
	void fuzzy_search(const string &sub_string, Product_List &result, Commands sort_base = BASE_NAME,
					  Commands order = ASCENDING_ORDER)
	{
		for (int i = 0; i < Warehouse::getcapacity(); i++)
		{
			if (warehouse_accessor[i] != nullptr)
			{
				string name = warehouse_accessor[i]->getname();
				if (name.find(sub_string) != string::npos)
					result.addback(*warehouse_accessor[i]);
			}
		}
		sort_list(result, sort_base, order);
	}
};

#endif //COMMODITY_SEARCH_SYSTEM_H
