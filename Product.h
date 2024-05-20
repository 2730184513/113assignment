//
// Created by dengchujie on 24-5-2.
//

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <iomanip>
#include "State.h"
#include "Discount.h"

using namespace std;

// Function to convert user input string to product type.
int whichtype(string &user_choice);

// Function to convert product type integer to string.
string whichtype(int type);

// Class representing a product.
class Product
{
private:
	int product_type = NO_INITIALIZED; // Type of the product.
	string product_name = "NO_INITIALIZED"; // Name of the product.
	float product_price = NO_INITIALIZED; // Price of the product.
	int product_quantity = NO_INITIALIZED; // Quantity of the product.
	int product_code = NO_INITIALIZED; // Code of the product.
	Discount discount; // Discount information.
	const static int CODE_LENGTH = 7; // Length of the product code.

	// Helper function to set discount rule 2 based on product type.
	void setdiscount_rule2()
	{
		if (product_type == CAKE)
			discount.setdiscount_rule2(CAKE_DISCOUNT_RULE);
		if (product_type == COOKIE)
			discount.setdiscount_rule2(COOKIE_DISCOUNT_RULE);
	}

public:
	// Constructors
	Product() = default;

	Product(string pn, int t, float p, int q, int dr, float d)
			: product_name(std::move(pn)), product_type(t), product_price(p),
			  product_quantity(q), discount(dr, d)
	{
		this->setdiscount_rule2();
	}

	// Copy constructor
	Product(const Product &p)
			: product_name(p.product_name), product_price(p.product_price),
			  product_quantity(p.product_quantity), product_type(p.product_type),
			  discount(p.getdiscount_rule1(), p.getdiscount()), product_code(p.product_code)
	{
		this->setdiscount_rule2();
	}

	// Destructor
	~Product() = default;

	// Mutators
	void setname(const string &name)
	{ product_name = name; }

	void setprice(float price)
	{ product_price = price; }

	void setquantity(int quantity)
	{ product_quantity = quantity; }

	void settype(int type)
	{
		product_type = type;
		setdiscount_rule2();
	}

	void setdiscount(float d)
	{ discount.setdiscount(d); }

	void setdiscount_rule1(int dr)
	{ discount.setdiscount_rule1(dr); }

	void setproduct_code(int code)
	{ product_code = code; }

	void setproduct(string name, int type, float price, int quantity, int discount_rule1, float discounts)
	{
		setname(name);
		settype(type);
		setprice(price);
		setquantity(quantity);
		setdiscount_rule1(discount_rule1);
		setdiscount(discounts);
	}

	// Accessors
	string getname() const
	{ return product_name; }

	float getprice() const
	{ return product_price; }

	int getquantity() const
	{ return product_quantity; }

	int gettype() const
	{ return product_type; }

	float getdiscount() const
	{ return discount.getdiscount(); }

	int getdiscount_rule1() const
	{ return discount.getdiscount_rule1(); }

	int getdiscount_rule2() const
	{ return discount.getdiscount_rule2(); }

	int getcode() const
	{ return product_code; }

	static int getcode_length()
	{ return Product::CODE_LENGTH; }

	// Friend function to print product details.
	friend ostream &print(const Product &product);

	// Overloaded operators: "==", "!=", "+", "-"
	// Equality comparison operator to check if two products are the same.
	bool operator==(const Product &r_product) const
	{
		return product_type == r_product.product_type
			   && product_name == r_product.product_name
			   && product_price == r_product.product_price
			   && this->getdiscount() == r_product.getdiscount()
			   && this->getdiscount_rule1() == r_product.getdiscount_rule1();
	}

	// Inequality comparison operator to check if two products are different.
	bool operator!=(const Product &r_product) const
	{ return !(*this == r_product); }

	// Addition operator to add one product's quantity to another product's quantity.
	Product &operator+(const Product &r_product)
	{
		if (*this != r_product)
		{
			cerr << "You can't add two different products" << endl;
			terminate();
		}
		else
		{
			this->setquantity(product_quantity + r_product.product_quantity);
			return *this;
		}
	}

	// Addition operator to add quantity to the product's quantity.
	Product &operator+(int quantity)
	{
		this->setquantity(product_quantity + quantity);
		return *this;
	}

	// Subtraction operator to subtract one product's quantity from another product's quantity.
	Product &operator-(const Product &r_product)
	{
		if (*this != r_product)
			throw runtime_error("You can't subtract two different products");
		else
		{
			if ((product_quantity - r_product.product_quantity) < 0)
				throw runtime_error("You can't subtract a product's quantity into a negative value");
			else
				this->setquantity(product_quantity - r_product.product_quantity);
		}
		return *this;
	}

	// Subtraction operator to subtract quantity from the product's quantity.
	Product &operator-(int quantity)
	{
		if ((product_quantity - quantity) < 0)
			throw runtime_error("You can't subtract a product's quantity into a negative value");
		else
			this->setquantity(product_quantity - quantity);
		return *this;
	}

	// Assignment operator to copy the contents of one product to another.
	Product &operator=(const Product &r_product)
	{
		if (this == &r_product)
			return *this;
		else
		{
			this->setname(r_product.product_name);
			this->setprice(r_product.product_price);
			this->setquantity(r_product.product_quantity);
			this->settype(r_product.product_type);
			this->setdiscount(r_product.getdiscount());
			this->setdiscount_rule1(r_product.getdiscount_rule1());
			this->setdiscount_rule2();
			return *this;

		}
	}

	// Compound assignment operator to add one product to another product itself.
	Product &operator+=(const Product &r_product)
	{ return *this = *this + r_product; }

	// Compound assignment operator to subtract one product itself from another.
	Product &operator-=(const Product &r_product)
	{ return *this = *this - r_product; }
};

// External declaration of an empty product.
extern const Product Empty;

// Function to print product details.
ostream &print(const Product &product)
{
	string separator(81, '=');
	int size = 20;
	int text_length = (product.product_name).length();
	int right_size = size - text_length / 2;
	int left_size = size * 2 - text_length - right_size;
	cout << separator << endl;
	cout << left << setw(40) << "| Product Type:" << left << setw(size - 2) << "|" << left << setw(size + 2)
		 << whichtype(product.product_type) << "|" << endl;
	cout << left << setw(40) << "| Product Code:" << left << setw(size - 3) << "|" << right << setw(7)
		 << setfill('0') << product.product_code << right << setw(17) << setfill(' ') << "|" << endl;
	cout << left << setw(40) << "| Product Name:" << left << setw(right_size) << "|"
		 << product.product_name << right << setw(left_size) << " " << "|" << endl;
	cout << left << setw(40) << fixed << setprecision(2) << "| Product Price:" << left << setw(size - 2) << "|"
		 << left << setw(size + 2) << product.product_price << "|" << endl;
	cout << left << setw(40) << "| Product Quantity:" << left << setw(size - 1) << "|" << left << setw(size + 1)
		 << product.product_quantity << "|" << endl;
	cout << left << setw(40) << "| The Discount Rule of This Product:" << left << setw(size - 1) << "|"
		 << left << setw(size + 1) << product.getdiscount_rule1() << "|" << endl;
	cout << left << setw(40) << fixed << setprecision(2) << "| The Discount Percentage:" << left << setw(size - 2)
		 << "|"
		 << left << setw(size + 2) << product.getdiscount() << "|" << endl;
	cout << separator << endl;
	return cout;
}

// Function to convert user input string to product type.
int whichtype(string &user_choice)
{
	if (user_choice == "CAKE" || user_choice == "CAKES") return CAKE;
	else if (user_choice == "COOKIE" || user_choice == "COOKIES") return COOKIE;
	else return WRONG_TYPE;
}

// Function to convert product type integer to string.
string whichtype(int type)
{
	if (type == CAKE)
		return "CAKE";
	else if (type == COOKIE)
		return "COOKIE";
	else
		return "WRONG TYPE";
}

#endif //PRODUCT_H