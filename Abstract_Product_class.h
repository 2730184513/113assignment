//
// Created by dengchujie on 24-5-2.
//

#ifndef ABSTRACT_PRODUCT_CLASS_H
#define ABSTRACT_PRODUCT_CLASS_H
#define CAKE (0)
#define CAKE_DISCOUNT_RULE (3)
#define COOKIE_DISCOUNT_RULE (5)
#define COOKIE (1)
#include <iostream>
#include <string>
#include "State.h"
#include "Abstract_Discount_class.h"
using namespace std;

class Product
{
protected:
	string product_name = "NO_INITIALIZED";
	float product_price = NO_INITIALIZED;
	int product_quantity = NO_INITIALIZED;
	int product_type = NO_INITIALIZED;
	Discount discount;
public:
	//Constructor
	Product() = default;

	Product(string& pn, float p, int q, int t, int dr, float d) : product_name(pn), product_price(p),
			product_quantity(q),
			product_type(t), discount(dr, d)
	{ this->setdiscount_rule2(); }
	//Creat a copy constructor
	Product(Product& p) : product_name(p.getname()), product_price(p.getprice()), product_quantity(p.getquantity()),
			product_type(p.gettype()), discount(p.getdiscount_rule1(), p.getdiscount())
	{ this->setdiscount_rule2(); }

	//Destructor
	~Product() = default;

	//Mutators
	void setname(const string& name)
	{ product_name = name; }

	void setprice(float price)
	{ product_price = price; }

	void setquantity(int quantity)
	{ product_quantity = quantity; }

	void settype(int type)
	{ product_type = type; }

	void setdiscount(float d)
	{ discount.setdiscount(d); }

	void setdiscount_rule1(int dr)
	{ discount.setdiscount_rule1(dr); }

	void setdiscount_rule2()
	{
		if (product_type == CAKE)
			discount.setdiscount_rule2(CAKE_DISCOUNT_RULE);
		if (product_type == COOKIE)
			discount.setdiscount_rule2(COOKIE_DISCOUNT_RULE);
	}

	//Accessors
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

	//Operators overloading: "=="; "!="; "+"; "-"
	//To judge whether two products are same or not
	bool operator ==(const Product& r_product) const
	{
		return product_type == r_product.product_type
			   && product_name == r_product.product_name
			   && product_price == r_product.product_price
			   && this->getdiscount() == r_product.getdiscount()
			   && this->getdiscount_rule1() == r_product.getdiscount_rule1();
	}

	//When overload "==", we usually need to also overload its opposite operation "!="
	bool operator !=(const Product& r_product) const
	{ return !(*this == r_product); }

	//Overload "+" to add one product's quantity into the same product's quantity
	Product& operator +(const Product& r_product)
	{
		if (*this != r_product)
		{
			cerr << "You can't add two different product" << endl;
			terminate();
		}
		else
		{
			this->setquantity(product_quantity+ r_product.product_quantity);
			return *this;
		}
	}

	//Simply add quantity into the product's quantity
	Product& operator +(int quantity)
	{
		this->setquantity(product_quantity + quantity);
		return *this;
	}

	//Overload "-" to subtract one product's quantity from the same product's quantity
	Product& operator -(const Product& r_product)
	{
		if (*this != r_product)
			throw runtime_error("You can't add two different product");
		else
		{
			this->setquantity(product_quantity - r_product.product_quantity);
			return *this;
		}
	}

	//Simply subtract quantity from the same product's quantity
	Product& operator -(int quantity)
	{
		this->setquantity(product_quantity - quantity);
		return *this;
	}

	Product& operator =(const Product& r_product)
	{
		if (this == &r_product)
		{
			auto* temp = new Product;
			temp->setname(r_product.product_name);
			temp->setprice(r_product.product_price);
			temp->setquantity(r_product.product_quantity);
			temp->settype(r_product.product_type);
			temp->setdiscount(r_product.getdiscount());
			temp->setdiscount_rule1(r_product.getdiscount_rule1());
			temp->setdiscount_rule2();
			this->setname(temp->product_name);
			this->setprice(temp->product_price);
			this->setquantity(temp->product_quantity);
			this->settype(temp->product_type);
			this->setdiscount(temp->getdiscount());
			this->setdiscount_rule1(temp->getdiscount_rule1());
			this->setdiscount_rule2();
			delete temp;
			return *this;
		}
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

	//Overload assign operator "+=", so that we can add one product to another product itself
	Product& operator +=(const Product& r_product)
	{ return *this = *this + r_product; }

	//Overload assign operator "-=", so that we can subtract one product itself from another
	Product& operator -=(const Product& r_product)
	{ return *this = *this - r_product; }
};
#endif //ABSTRACT_PRODUCT_CLASS_H
