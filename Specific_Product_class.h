//
// Created by dengchujie on 24-4-26.
//
#ifndef SPECIFIC_PRODUCT_CLASS_H
#define SPECIFIC_PRODUCT_CLASS_H

#include <iostream>
#include <string>
#include "Specific_Discount_class.h"
#include "Abstract_Product_class.h"
using namespace std;

//This class is used to represent Cake type product
class Cake final : public Product    //Cake is a specific product, thus it should not be inherited
{
private:
	Cake_Discount CD;    //float discount(default=1), int discount_rule1, int discount_rule2 = 3
	//get the following data members from inheritance :
	//	string product_name;
	//	float product_price;
	//	int product_quantity;
	//	int product_code;
public:
	//Constructor
	Cake() = default;

	Cake(string& n, float p, int q) : Product(n, p, q)
	{}

	Cake(string& n, float p, int q, float d) : Product(n, p, q), CD(d)
	{}

	Cake(string& n, float p, int q, int dr1, float d) : Product(n, p, q), CD(dr1, d)
	{}

	//Creat a copy constructor
	Cake(Cake& cake) : Product(cake), CD(cake.getdiscount_rule1(), cake.getdiscount())
	{}

	//Destructor
	~Cake() override = default;

	//Mutators
	void setdiscount(float d) override
	{ CD.setdiscount(d); }

	void setdiscount_rule(int dr1) override
	{ CD.setdiscount_rule(dr1); }

	//Accessors
	float getdiscount() const override
	{ return CD.getdiscount(); }

	int getdiscount_rule1() const override
	{ return CD.getdiscount_rule(); }

	static int getdicount_rule2()
	{ return Cake_Discount::getdiscount_rule2(); }

	//Overload assign operator "=", so that we can copy one product to another product
	Cake& operator =(const Cake& r_product)
	{
		if (this == &r_product)
		{
			Cake* temp = new Cake;
			temp->setname(r_product.getname());
			temp->setprice(r_product.getprice());
			temp->setquantity(r_product.getquantity());
			temp->setdiscount(r_product.getdiscount());
			temp->setdiscount_rule(r_product.getdiscount_rule1());
			this->setname(temp->getname());
			this->setprice(temp->getprice());
			this->setquantity(temp->getquantity());
			this->setdiscount(temp->getdiscount());
			this->setdiscount_rule(temp->getdiscount_rule1());
			delete temp;
			return *this;
		} else
		{
			this->setname(r_product.getname());
			this->setprice(r_product.getprice());
			this->setquantity(r_product.getquantity());
			this->setdiscount(r_product.getdiscount());
			this->setdiscount_rule(r_product.getdiscount_rule1());
			return *this;
		}
	}

	//Same target as above but deal with different type
	Cake& operator =(const Product& r_product)
	{
		*this = dynamic_cast<const Cake&>(r_product);
		return *this;
	}

	//Overload assign operator "+=", so that we can add one product to another product itself
	Cake& operator +=(const Cake& r_product)
	{ return *this = *this + r_product; }

	//Same target as above but deal with different type
	Cake& operator +=(const Product& r_product)
	{ return *this = *this + dynamic_cast<const Cake&>(r_product); }

	//Overload assign operator "-=", so that we can subtract one product itself from another
	Cake& operator -=(const Cake& r_product)
	{ return *this = *this - r_product; }

	//Same target as above but deal with different type
	Cake& operator -=(const Product& r_product)
	{ return *this = *this - dynamic_cast<const Cake&>(r_product); }
};
//Also a specific product class as Cake, it has wholly same structure,
//same functions and same operators overloading, but for Cookie type not Cake type.
class Cookie final : public Product
{
private:
	Cookie_Discount CD;    //float discount(default=1), int discount_rule1, int discount_rule2 = 3
	//get the following data members from inheritance :
	//	string product_name;
	//	float product_price;
	//	int product_quantity;
	//	int product_code;
public:
	//Constructors
	Cookie() = default;

	Cookie(string& n, float p, int q) : Product(n, p, q)
	{}

	Cookie(string& n, float p, int q, float d) : Product(n, p, q), CD(d)
	{}

	Cookie(string& n, float p, int q, int dr1, float d) : Product(n, p, q), CD(dr1, d)
	{}

	//Creat a copy constructor
	Cookie(Cookie& cookie) : Product(cookie), CD(cookie.getdiscount_rule1(), cookie.getdiscount())
	{}

	//Destructor
	~Cookie() override = default;

	//Mutators
	void setdiscount(float d) override
	{ CD.setdiscount(d); }

	void setdiscount_rule(int dr1) override
	{ CD.setdiscount_rule(dr1); }

	//Accessors
	float getdiscount() const override
	{ return CD.getdiscount(); }

	int getdiscount_rule1() const override
	{ return CD.getdiscount_rule(); }

	static int getdicount_rule2()
	{ return Cake_Discount::getdiscount_rule2(); }

	//Overload operators as what I did in the Cake class
	//These operators do totally same things as what them do in Cake class,
	//but deal with Cookie type instead of Cake type
	Cookie& operator =(const Cookie& r_product)
	{
		if (this == &r_product)
		{
			Cake* temp = new Cake;
			temp->setname(r_product.getname());
			temp->setprice(r_product.getprice());
			temp->setquantity(r_product.getquantity());
			temp->setdiscount(r_product.getdiscount());
			temp->setdiscount_rule(r_product.getdiscount_rule1());
			this->setname(temp->getname());
			this->setprice(temp->getprice());
			this->setquantity(temp->getquantity());
			this->setdiscount(temp->getdiscount());
			this->setdiscount_rule(temp->getdiscount_rule1());
			delete temp;
			return *this;
		} else
		{
			this->setname(r_product.getname());
			this->setprice(r_product.getprice());
			this->setquantity(r_product.getquantity());
			this->setdiscount(r_product.getdiscount());
			this->setdiscount_rule(r_product.getdiscount_rule1());
			return *this;
		}
	}

	Cookie& operator =(const Product& r_product)
	{
		*this = dynamic_cast<const Cookie&>(r_product);
		return *this;
	}

	Cookie& operator +=(const Cookie& r_product)
	{ return *this = *this + r_product; }

	Cookie& operator +=(const Product& r_product)
	{ return *this = *this + dynamic_cast<const Cookie&>(r_product); }

	Cookie& operator -=(const Cookie& r_product)
	{ return *this = *this - r_product; }

	Cookie& operator -=(const Product& r_product)
	{ return *this = *this - dynamic_cast<const Cookie&>(r_product); }
};

#endif //SPECIFIC_PRODUCT_CLASS_H

