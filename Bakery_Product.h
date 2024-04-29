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
class Discount    //The basic  class to represent the act of discounting
{// a pure virtual class which means it can't be instantiated.
protected:
	int discount_rule = NO_INITIALIZED;    // If customers buy more than this value, than they could enjoy the discount.
	float discount = NO_DISCOUNT;
public:
	Discount() = default;
	explicit Discount(float d) : discount(d)
	{}    //Using "explicit" key word to prohibit of implicit conversion behavior

	Discount(int dr, float d) : discount_rule(dr), discount(d)
	{}
	Discount(Discount& d) : discount_rule(d.getdiscount_rule()), discount(d.getdiscount())
	{}
	virtual ~Discount() = default;
	virtual void
	PURE_VIRTUAL() = 0;    //Create a pure virtual function to disable instantiation of this class,
	// as this class only represents an abstract act, the user shouldn't the creat an object for this class
	void setdiscount(float dc)    //Mutators
	{ discount = dc; }
	void setdiscount_rule(int dr)
	{ discount_rule = dr; }
	float getdiscount() const    //Accessors
	{ return discount; }
	int getdiscount_rule() const
	{ return discount_rule; }

};
class Product    //The basic class to represent the fundamental information and composition of a product.
{// Also a pure virtual(abstract) class, can't be instantiated neither.
protected:
	string product_name;
	float product_price;
	int product_quantity;
public:
	Product() : product_name("NO_INITIALIZED"), product_price(NO_INITIALIZED), product_quantity(NO_INITIALIZED)
	{}
	Product(string& pn, float p, int t) : product_name(pn), product_price(p), product_quantity(t)
	{}
	Product(Product& p) : product_name(p.getname()), product_price(p.getprice()), product_quantity(p.getquantity())
	{}
	virtual ~Product() = default;
	void setname(const string& name)
	{ product_name = name; }
	void setprice(float price)
	{ product_price = price; }
	void setquantity(int quantity)
	{ product_quantity = quantity; }
	virtual void setdiscount(float d) = 0;
	virtual void setdiscount_rule(int dr) = 0;
	string getname() const
	{ return product_name; }
	float getprice() const
	{ return product_price; }
	int getquantity() const
	{ return product_quantity; }
	virtual float getdiscount() const = 0;
	virtual int getdiscount_rule() const = 0;
	bool operator ==(const Product& r_product) const
	{
		return this->getname() == r_product.getname()
			   && this->getprice() == r_product.getprice()
			   && this->getdiscount() == r_product.getdiscount()
			   && this->getdiscount_rule() == r_product.getdiscount_rule();
	}
	bool operator !=(const Product& r_product) const
	{ return !(*this == r_product); }
	Product& operator +(const Product& r_product)
	{
		try
		{
			if (*this != r_product)
				throw runtime_error("You can't add two different product");
			else
			{
				this->setquantity(this->getquantity() + r_product.getquantity());
				return *this;
			}
		}
		catch (runtime_error& err)
		{
			if (this->getname() != r_product.getname())
				cerr << "Different name: " << this->getname() << "\t" << r_product.getname() << endl;
			if (this->getprice() != r_product.getprice())
				cerr << "Different price: " << this->getprice() << "\t" << r_product.getprice() << endl;
			if (this->getdiscount() != r_product.getdiscount())
				cerr << "Different discount rule: " << this->getdiscount() << "\t"
					 << r_product.getdiscount() << endl;
			if (this->getdiscount_rule() != r_product.getdiscount_rule())
				cerr << "Different discount rule: " << this->getdiscount_rule() << "\t"
					 << r_product.getdiscount_rule() << endl;
			terminate();
		}
	}
	Product& operator +(int quantity)
	{
		this->setquantity(this->getquantity() + quantity);
		return *this;
	}
	Product& operator -(const Product& r_product)
	{
		try
		{
			if (*this != r_product)
				throw runtime_error("You can't add two different product");
			else
			{
				this->setquantity(this->getquantity() - r_product.getquantity());
				return *this;
			}
		}
		catch (runtime_error& err)
		{
			if (this->getname() != r_product.getname())
				cerr << "Different name: " << this->getname() << "\t" << r_product.getname() << endl;
			if (this->getprice() != r_product.getprice())
				cerr << "Different price: " << this->getprice() << "\t" << r_product.getprice() << endl;
			if (this->getdiscount() != r_product.getdiscount())
				cerr << "Different discount rule: " << this->getdiscount() << "\t"
					 << r_product.getdiscount() << endl;
			if (this->getdiscount_rule() != r_product.getdiscount_rule())
				cerr << "Different discount rule: " << this->getdiscount_rule() << "\t"
					 << r_product.getdiscount_rule() << endl;
			terminate();
		}
	}
	Product& operator -(int quantity)
	{
		this->setquantity(this->getquantity() - quantity);
		return *this;
	}

};
class Cake_Discount final : public Discount
{
private:
	static int discount_rule2;
	//float discount	From inheritance
public:
	Cake_Discount() = default;
	Cake_Discount(int dr1, float d) : Discount(dr1, d)
	{}
	explicit Cake_Discount(float d) : Discount(d)
	{}
	Cake_Discount(Cake_Discount& c) : Discount(c)
	{}
	~Cake_Discount() override = default;
	void PURE_VIRTUAL() override
	{}
	static int getdiscount_rule2()
	{ return discount_rule2; }

};
int Cake_Discount::discount_rule2 = 3;
class Cookie_Discount final : public Discount
{
private:
	static int discount_rule2;
	//float discount	From inheritance
public:
	Cookie_Discount() = default;
	Cookie_Discount(int dr1, float d) : Discount(dr1, d)
	{}
	explicit Cookie_Discount(float d) : Discount(d)
	{}
	Cookie_Discount(Cookie_Discount& c) : Discount(c)
	{}
	~Cookie_Discount() override = default;
	void PURE_VIRTUAL() override
	{}
	static int getdiscount_rule2()
	{ return discount_rule2; }
};
int Cookie_Discount::discount_rule2 = 5;
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
	Cake() = default;
	Cake(string& n, float p, int q) : Product(n, p, q)
	{}
	Cake(string& n, float p, int q, float d) : Product(n, p, q), CD(d)
	{}
	Cake(string& n, float p, int q, int dr1, float d) : Product(n, p, q), CD(dr1, d)
	{}
	Cake(Cake& cake) : Product(cake), CD(cake.getdiscount_rule(), cake.getdiscount())
	{}
	~Cake() override = default;
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

