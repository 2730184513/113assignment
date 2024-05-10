//
// Created by dengchujie on 24-5-2.
//

#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <string>
#include "State.h"
#include "Discount.h"

using namespace std;

string toupper(const string& str);

int whichtype(string& user_choice);

string whichtype(int type);

class Product
{
private:
	bool product_type = NO_INITIALIZED;
	string product_name = "NO_INITIALIZED";
	float product_price = NO_INITIALIZED;
	int product_quantity = NO_INITIALIZED;
	int product_code = NO_INITIALIZED;
	Discount discount;
	const static int CODE_LENGTH = 5;

	void setdiscount_rule2()
	{
		if (product_type == CAKE)
			discount.setdiscount_rule2(CAKE_DISCOUNT_RULE);
		if (product_type == COOKIE)
			discount.setdiscount_rule2(COOKIE_DISCOUNT_RULE);
	}

public:
	//Constructor
	Product() = default;

	Product(const string& pn, int t, float p, int q, int dr, float d) : product_name(pn), product_type(t),
			product_price(p),
			product_quantity(q), discount(dr, d)
	{ this->setdiscount_rule2(); }

	//Creat a copy constructor
	Product(Product& p)
			: product_name(p.product_name), product_price(p.product_price), product_quantity(p.product_quantity),
			product_type(p.product_type), discount(p.getdiscount_rule1(), p.getdiscount()),
			product_code(p.product_code)
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

	void setproduct_code(int code)
	{ product_code = code; }

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

	int getcode() const
	{ return product_code; }

	static int getcode_length()
	{ return Product::CODE_LENGTH; }

	friend ostream& print(Product& product);

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
			this->setquantity(product_quantity + r_product.product_quantity);
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

ostream& print(Product& product)
{
	cout << "Product type:\t"<<whichtype(product.product_type)<<endl;
	cout<<"Product name:\t"<<product.product_name<<endl;
	cout<<"Product price:\t"<<product.product_price<<endl;
	cout<<"Product quantity:\t"<<product.product_quantity<<endl;
	cout<<"The discount rule of this product:\t"<<product.getdiscount_rule1()<<endl;
	cout<<"The discount percentage is:\t"<<product.getdiscount()<<endl;
	return cout;
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
//string title(const string& str)
//{
//	bool first_letter_flag=0;
//	for(char c:str)
//	{
//		if(first_letter_flag==0)
//		{
//			string uppered_str = str;
//			for (char c: uppered_str)
//			{
//				if (c >= 'a' && c <= 'z')
//					c = c - 'a' + 'A';
//			}
//			return uppered_str;
//		}
//	}
//}

int whichtype(string& user_choice)
{
	if (user_choice == "CAKE" || user_choice == "CAKES") return CAKE;
	else if (user_choice == "COOKIE" || user_choice == "COOKIES") return COOKIE;
	else return WRONG_TYPE;
}

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


