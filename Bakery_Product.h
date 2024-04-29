//
// Created by dengchujie on 24-4-26.
//
#ifndef BAKERY_PRODUCT_H
#define BAKERY_PRODUCT_H

#include <iostream>
#include <string>

using namespace std;
enum State    //Represent the default state(value) to increase readability.
{
	NO_INITIALIZED = 0,
	NO_DISCOUNT = 1,
};
//The basic  class to represent the act of discounting
//a pure virtual class which means it can't be instantiated.
class Discount
{
protected:
	// If customers buy more than this value, than they could enjoy the discount.
	int discount_rule = NO_INITIALIZED;
	float discount = NO_DISCOUNT;
public:
	//Constructor
	Discount() = default;
	//Using "explicit" key word to prohibit of implicit conversion behavior
	explicit Discount(float d) : discount(d)
	{}
	Discount(int dr, float d) : discount_rule(dr), discount(d)
	{}
	//Creat a copy constructor
	Discount(Discount& d) : discount_rule(d.getdiscount_rule()), discount(d.getdiscount())
	{}
	//Destructor
	virtual ~Discount() = default;
	//Create a pure virtual function to disable instantiation of this class,
	// as this class only represents an abstract act, the user shouldn't the creat an object for this class
	virtual void PURE_VIRTUAL() = 0;
	//Mutators
	void setdiscount(float dc)
	{ discount = dc; }
	void setdiscount_rule(int dr)
	{ discount_rule = dr; }
	//Accessors
	float getdiscount() const
	{ return discount; }
	int getdiscount_rule() const
	{ return discount_rule; }
};
//The basic class to represent the fundamental information and composition of a product.
//Also, a pure virtual(abstract) class, can't be instantiated neither.
class Product
{
protected:
	string product_name;
	float product_price;
	int product_quantity;
public:
	//Constructor
	Product() : product_name("NO_INITIALIZED"), product_price(NO_INITIALIZED), product_quantity(NO_INITIALIZED)
	{}
	Product(string& pn, float p, int t) : product_name(pn), product_price(p), product_quantity(t)
	{}
	//Creat a copy constructor
	Product(Product& p) : product_name(p.getname()), product_price(p.getprice()), product_quantity(p.getquantity())
	{}
	//Destructor
	virtual ~Product() = default;
	//Mutators
	void setname(const string& name)
	{ product_name = name; }
	void setprice(float price)
	{ product_price = price; }
	void setquantity(int quantity)
	{ product_quantity = quantity; }
	virtual void setdiscount(float d) = 0;
	virtual void setdiscount_rule(int dr) = 0;
	//Accessors
	string getname() const
	{ return product_name; }
	float getprice() const
	{ return product_price; }
	int getquantity() const
	{ return product_quantity; }
	virtual float getdiscount() const = 0;
	virtual int getdiscount_rule() const = 0;
	//Operators overloading: "=="; "!="; "+"; "-"
	//To judge whether two products are same or not
	bool operator ==(const Product& r_product) const
	{
		return this->getname() == r_product.getname()
			   && this->getprice() == r_product.getprice()
			   && this->getdiscount() == r_product.getdiscount()
			   && this->getdiscount_rule() == r_product.getdiscount_rule();
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
			this->setquantity(this->getquantity() + r_product.getquantity());
			return *this;
		}
	}
	//Simply add quantity into the product's quantity
	Product& operator +(int quantity)
	{
		this->setquantity(this->getquantity() + quantity);
		return *this;
	}
	//Overload "-" to subtract one product's quantity from the same product's quantity
	Product& operator -(const Product& r_product)
	{
		if (*this != r_product)
			throw runtime_error("You can't add two different product");
		else
		{
			this->setquantity(this->getquantity() - r_product.getquantity());
			return *this;
		}
	}
	//Simply subtract quantity from the same product's quantity
	Product& operator -(int quantity)
	{
		this->setquantity(this->getquantity() - quantity);
		return *this;
	}
};
//Cake_Discount inherits from Discount, this class is used to represent the act of discounting
//for the Cake type product.
class Cake_Discount final : public Discount
{
private:
	//No matter which cake customers buy, when the amount of one same cake that a customer purchased
	// is greater that discount_rule2, he or she could get (amount of purchasing // rule2) cakes for free
	// For example, if a customer buy 8 cake, while rule2 for cake is 3. Thus, he or she could get 2 cakes for free,
	//which means he or she only needs to pay money for 6 cake.

	static int discount_rule2;    //For cake, its always equal to 3

	//int discount_rule1	From inheritance
	//float discount	From inheritance
public:
	//Constructor
	Cake_Discount() = default;
	Cake_Discount(int dr1, float d) : Discount(dr1, d)
	{}
	explicit Cake_Discount(float d) : Discount(d)
	{}
	//Creat a copy constructor
	Cake_Discount(Cake_Discount& c) : Discount(c)
	{}
	//Destructor
	~Cake_Discount() override = default;
	//Override PURE_VIRTUAL function with empty function body
	// to transfer this class from abstract class into normal class
	void PURE_VIRTUAL() override
	{}
	//Creat a static function to get the static data member
	static int getdiscount_rule2()
	{ return discount_rule2; }
};
int Cake_Discount::discount_rule2 = 3;

//The same target as Cake_Discount, but for Cookie instead of Cake
class Cookie_Discount final : public Discount
{
private:
	static int discount_rule2;
	//int discount_rule1	From inheritance
	//float discount	From inheritance
public:
	//Constructor
	Cookie_Discount() = default;
	Cookie_Discount(int dr1, float d) : Discount(dr1, d)
	{}
	explicit Cookie_Discount(float d) : Discount(d)
	{}
	//Create a copy constructor
	Cookie_Discount(Cookie_Discount& c) : Discount(c)
	{}
	//Destructor
	~Cookie_Discount() override = default;
	//Override PURE_VIRTUAL function with empty function body
	//	// to transfer this class from abstract class into normal class
	void PURE_VIRTUAL() override
	{}
	//Same target as it in Cake_Discount, but it is assigned as 5 instead of 3
	static int getdiscount_rule2() //always be 5
	{ return discount_rule2; }
};
int Cookie_Discount::discount_rule2 = 5;

//This class is used to represent Cake type product
class Cake final : public Product
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
	Cake(Cake& cake) : Product(cake), CD(cake.getdiscount_rule(), cake.getdiscount())
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
	int getdiscount_rule() const override
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
			temp->setdiscount_rule(r_product.getdiscount_rule());
			this->setname(temp->getname());
			this->setprice(temp->getprice());
			this->setquantity(temp->getquantity());
			this->setdiscount(temp->getdiscount());
			this->setdiscount_rule(temp->getdiscount_rule());
			delete temp;
			return *this;
		} else
		{
			this->setname(r_product.getname());
			this->setprice(r_product.getprice());
			this->setquantity(r_product.getquantity());
			this->setdiscount(r_product.getdiscount());
			this->setdiscount_rule(r_product.getdiscount_rule());
			return *this;
		}
	}
	Cake& operator =(const Product& r_product)
	{
		*this = dynamic_cast<const Cake&>(r_product);
		return *this;
	}
	Cake& operator +=(const Cake& r_product)
	{ return *this = *this + r_product; }
	Cake& operator +=(const Product& r_product)
	{ return *this = *this + dynamic_cast<const Cake&>(r_product); }
	Cake& operator -=(const Cake& r_product)
	{ return *this = *this - r_product; }
	Cake& operator -=(const Product& r_product)
	{ return *this = *this - dynamic_cast<const Cake&>(r_product); }
};
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
	Cookie() = default;
	Cookie(string& n, float p, int q) : Product(n, p, q)
	{}
	Cookie(string& n, float p, int q, float d) : Product(n, p, q), CD(d)
	{}
	Cookie(string& n, float p, int q, int dr1, float d) : Product(n, p, q), CD(dr1, d)
	{}
	Cookie(Cookie& cookie) : Product(cookie), CD(cookie.getdiscount_rule(), cookie.getdiscount())
	{}
	~Cookie() override = default;
	void setdiscount(float d) override
	{ CD.setdiscount(d); }
	void setdiscount_rule(int dr1) override
	{ CD.setdiscount_rule(dr1); }
	float getdiscount() const override
	{ return CD.getdiscount(); }
	int getdiscount_rule() const override
	{ return CD.getdiscount_rule(); }
	static int getdicount_rule2()
	{ return Cake_Discount::getdiscount_rule2(); }
	Cookie& operator =(const Cookie& r_product)
	{
		if (this == &r_product)
		{
			Cake* temp = new Cake;
			temp->setname(r_product.getname());
			temp->setprice(r_product.getprice());
			temp->setquantity(r_product.getquantity());
			temp->setdiscount(r_product.getdiscount());
			temp->setdiscount_rule(r_product.getdiscount_rule());
			this->setname(temp->getname());
			this->setprice(temp->getprice());
			this->setquantity(temp->getquantity());
			this->setdiscount(temp->getdiscount());
			this->setdiscount_rule(temp->getdiscount_rule());
			delete temp;
			return *this;
		} else
		{
			this->setname(r_product.getname());
			this->setprice(r_product.getprice());
			this->setquantity(r_product.getquantity());
			this->setdiscount(r_product.getdiscount());
			this->setdiscount_rule(r_product.getdiscount_rule());
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

#endif //BAKERY_PRODUCT_H

