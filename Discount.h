//
// Created by dengchujie on 24-5-2.
//

#ifndef DISCOUNT_H
#define DISCOUNT_H

#include <iostream>
#include <string>
#include "State.h"

using namespace std;

// The base class to represent the act of discounting.
// It's a pure virtual class, meaning it can't be instantiated directly.
class Discount
{
protected:
	// If customers buy more than this value, they could enjoy the discount.
	int discount_rule1 = NO_INITIALIZED;
	// The discount percentage.
	float discount = NO_DISCOUNT;
	// Another rule for discount.
	int discount_rule2 = NO_INITIALIZED;

public:
	// Constructor
	Discount() = default;

	// Using "explicit" keyword to prohibit implicit conversion behavior.
	explicit Discount(float d) : discount(d)
	{}

	Discount(int dr, float d) : discount_rule1(dr), discount(d)
	{}

	// Copy constructor
	Discount(Discount &d) : discount_rule1(d.getdiscount_rule1()), discount(d.getdiscount()), discount_rule2()
	{}

	// Destructor
	~Discount() = default;

	// Mutators
	void setdiscount(float dc)
	{ discount = dc; }

	void setdiscount_rule1(int dr)
	{ discount_rule1 = dr; }

	void setdiscount_rule2(int dr)
	{ discount_rule2 = dr; }

	// Accessors
	float getdiscount() const
	{ return discount; }

	int getdiscount_rule1() const
	{ return discount_rule1; }

	int getdiscount_rule2() const
	{ return discount_rule2; }
};

#endif //DISCOUNT_H