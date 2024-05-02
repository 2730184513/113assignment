//
// Created by dengchujie on 24-5-2.
//

#ifndef ABSTRACT_DISCOUNT_CLASS_H
#define ABSTRACT_DISCOUNT_CLASS_H
#include <iostream>
#include <string>
#include "State.h"
using namespace std;
//The basic  class to represent the act of discounting
//a pure virtual class which means it can't be instantiated.
class Discount
{
protected:
	// If customers buy more than this value, than they could enjoy the discount.
	int discount_rule1 = NO_INITIALIZED;
	float discount = NO_DISCOUNT;
	int discount_rule2 = NO_INITIALIZED;
public:
	//Constructor
	Discount() = default;

	//Using "explicit" key word to prohibit of implicit conversion behavior
	explicit Discount(float d) : discount(d)
	{}

	Discount(int dr, float d) : discount_rule1(dr), discount(d)
	{}

	//Creat a copy constructor
	Discount(Discount& d) : discount_rule1(d.getdiscount_rule1()), discount(d.getdiscount()), discount_rule2()
	{}

	//Destructor
	~Discount() = default;
	//Create a pure virtual function to disable instantiation of this class,
	// as this class only represents an abstract act, the user shouldn't the creat an object for this class

	//Mutators
	void setdiscount(float dc)
	{ discount = dc; }

	void setdiscount_rule1(int dr)
	{ discount_rule1 = dr; }

	void setdiscount_rule2(int dr)
	{ discount_rule2 = dr; }

	//Accessors
	float getdiscount() const
	{ return discount; }

	int getdiscount_rule1() const
	{ return discount_rule1; }

	int getdiscount_rule2() const
	{ return discount_rule2; }
};
#endif //ABSTRACT_DISCOUNT_CLASS_H
