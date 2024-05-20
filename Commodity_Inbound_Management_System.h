// Header guard to prevent multiple inclusion of the Commodity Inbound Management System header file.
#ifndef COMMODITY_INBOUND_MANAGEMENT_SYSTEM_H
#define COMMODITY_INBOUND_MANAGEMENT_SYSTEM_H

#include "Warehouse.h" // Include Warehouse header file for Warehouse class definition.
#include "Product_List.h" // Include Product_List header file for Product_List class definition.
#include<iostream> // Include necessary header files.
#include <string>
#include <fstream>

using namespace std; // Using the standard namespace for shorthand access to standard library entities.

// Function declarations for string manipulation functions.
string toupper(const string &str); // Function to convert string to uppercase.
string title(const string &str); // Function to capitalize each word in a string.

// Declaration of Commodity Inbound Management System (CIM_System) class.
class CIM_System
{
	Product **const warehouse_accessor = nullptr; // Constant pointer to array of pointers to products in the warehouse.

	// Static function to calculate product code based on product name.
	static int calculate_code(const string &name)
	{
		int product_code = 0;
		int warehouse_capacity = Warehouse::getcapacity(); // Get warehouse capacity.
		for (const unsigned char c: name) // Iterate through each character in the name.
			product_code = ((product_code << 4) ^ (product_code >> 28) ^ (int) c) %
						   warehouse_capacity; // Calculate product code.
		return product_code;
	}

public:
	// Constructor for CIM_System class (deleted default constructor).
	CIM_System() = delete;    // An instance must be associated with a warehouse.

	// Constructor with Warehouse parameter.
	explicit CIM_System(Warehouse &warehouse)
			: warehouse_accessor(warehouse.getproducts()) // Initialize warehouse accessor.
	{}

	// Destructor for CIM_System class.
	~CIM_System() = default;

	// Function to add a product to the warehouse.
	State inbound(const Product &product);

	// Function to add products from a file to the warehouse.
	State inbound(ifstream &product_list);

	// Function to add products from a product list to the warehouse.
	State inbound(Product_List &product_list);
};

// Function definition to add a product to the warehouse.
State CIM_System::inbound(const Product &product)
{
	int position = calculate_code(product.getname()); // Calculate position in the warehouse based on product name.
	if (warehouse_accessor[position] == nullptr) // If position is empty.
	{
		warehouse_accessor[position] = new Product(product); // Add product to the warehouse.
		warehouse_accessor[position]->setproduct_code(position); // Set product code.
		return SUCCESS; // Return success state.
	}
	else
	{
		if (*warehouse_accessor[position] == product) // If product already exists in the warehouse.
		{
			*warehouse_accessor[position] += product; // Add quantity to existing product.
			return SUCCESS; // Return success state.
		}
		else
		{
			int flag = 1; // Flag to track number of attempts.
			for (int step = 1; step < INT_MAX; step++) // Iterate until INT_MAX steps.
			{
				position = (position + step * step) % Warehouse::getcapacity(); // Calculate new position.
				flag++; // Increment flag.
				if (warehouse_accessor[position] == nullptr) // If new position is empty.
				{
					warehouse_accessor[position] = new Product(product); // Add product to the warehouse.
					warehouse_accessor[position]->setproduct_code(position); // Set product code.
					break; // Exit loop.
				}
			}
			if (flag == INT_MAX) // If maximum attempts reached.
				return FAILED; // Return failed state.
			else
				return SUCCESS; // Return success state.
		}
	}
}

// Function to add products from a file to the warehouse.
State CIM_System::inbound(ifstream &product_list)
{
	Product *temp; // Temporary product pointer.
	while (!product_list.eof()) // Loop until end of file.
	{
		// Read product details from file.
		string name;
		bool type;
		float price, discount_percentage;
		int quantity, discount_rule1;
		getline(product_list, name, '\t'); // Read name.
		name = title(name); // Capitalize name.
		product_list >> type >> price >> quantity >> discount_rule1 >> discount_percentage; // Read other details.
		product_list.get(); // Consume newline character.
		temp = new Product(name, type, price, quantity, discount_rule1, discount_percentage); // Create product object.
		State state = inbound(*temp); // Add product to the warehouse.
		if (state == FAILED) // If addition failed.
		{
			delete temp; // Delete temporary product.
			return FAILED; // Return failed state.
		}
	}
	delete temp; // Delete temporary product.
	return SUCCESS; // Return success state.
}

State CIM_System::inbound(Product_List &product_list)
{
	int size = product_list.gettotal();
	State state;
	for (int i = 0; i < size; i++)
		state = inbound(*product_list[i]);
	return state;
}

// Function to convert string to uppercase.
string toupper(const string &str)
{
	string uppered_str = str;
	for (char &c: uppered_str)
	{
		if (c >= 'a' && c <= 'z') // If character is lowercase.
			c = c - 'a' + 'A'; // Convert to uppercase.
	}
	return uppered_str; // Return uppercase string.
}


// Function to capitalize each word in a string.
string title(const string &str)
{
	string capitalized_str = str;
	bool firstletter = true; // Flag to indicate first letter of a word.
	for (char &c: capitalized_str)
	{
		if (firstletter)
		{
			c = toupper(c); // Capitalize first letter.
			firstletter = false; // Reset flag.
		}
		else
		{
			c = tolower(c); // Convert other letters to lowercase.
			if (c == ' ' || c == '_') // If space or underscore encountered.
				firstletter = true; // Set flag for next word.
		}
	}
	return capitalized_str; // Return capitalized string.
}

#endif //COMMODITY_INBOUND_MANAGEMENT_SYSTEM_H

