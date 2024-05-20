#ifndef COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
#define COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H

#include "Warehouse.h"
#include "Bill.h"
#include<iostream>
#include <string>
#include <ctime>
#include <fstream>

using namespace std;

// Function to get the current date in "Year-Month-Day-Weekday" format.
string getdate();

// Function to get the current time in "Hour:Minute:Second" format.
string gettime();

// Commodity Outbound Management System class
class COM_System
{
	Product **const warehouse_accessor = nullptr; // Pointer to the warehouse's products

public:
	// Default constructor is deleted
	COM_System() = delete;

	// Constructor to initialize the COM_System with a reference to a Warehouse object
	explicit COM_System(Warehouse &wh) : warehouse_accessor(wh.getproducts())
	{}

	// Destructor
	~COM_System() = default;

	// Function to process outbound products based on a bill
	void outbound(const Bill &bill);
};

// Function definition to process outbound products based on a bill
void COM_System::outbound(const Bill &bill)
{
	// Generate a filename based on the current date
	string filename = getdate() + "-outbound_list.txt";
	// Get the current time
	string detail_time = gettime();
	// Open the outbound list file in append mode
	ofstream outbound_list(filename, ios::app);
	// Iterate through each product in the bill
	for (int i = 0; i < bill.gettotal(); i++)
	{
		if (i != 0)
			outbound_list << endl;
		// Get the product code
		int code = bill[i]->getcode();
		// Update the warehouse by subtracting the product quantity from the stock
		*warehouse_accessor[code] -= *bill[i];
		// Calculate the payment for the product
		float payment = bill[i]->getprice() * bill[i]->getquantity();
		// Calculate the discount for the product
		float discount = Trade_System::calculate_discount(*bill[i]);
		// Write the details of the outbound product to the file
		outbound_list << detail_time << "\t" << whichtype(bill[i]->gettype()) << "\t"
					  << bill[i]->getname() << "(" << code << ")\t"
					  << bill[i]->getquantity() << "\t" << payment - discount;
	}
	// Close the outbound list file
	outbound_list.close();
}

// Function to get the current date in "Year-Month-Day-Weekday" format.
string getdate()
{
	// Get the current system time
	time_t now = time(nullptr);
	// Convert system time to local time
	tm *local_time = localtime(&now);
	// Define a character buffer to hold the formatted date
	char buffer[80];
	// Format date in "Year-Month-Day-Weekday" format
	strftime(buffer, 80, "%Y-%B-%d-%A", local_time);
	// Store formatted date in a string variable
	string date = buffer;
	// Return formatted date
	return date;
}

// Function to get the current time in "Hour:Minute:Second" format.
string gettime()
{
	// Get the current system time
	time_t now = time(nullptr);
	// Convert system time to local time
	tm *local_time = localtime(&now);
	// Define a character buffer to hold the formatted time
	char buffer[80];
	// Format time in "Hour:Minute:Second" format
	strftime(buffer, 80, "%X", local_time);
	// Store formatted time in a string variable
	string detail_time = buffer;
	// Return formatted time
	return detail_time;
}

#endif //COMMODITY_OUTBOUND_MANAGEMENT_SYSTEM_H
