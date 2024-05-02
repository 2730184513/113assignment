//
// Created by dengchujie on 24-5-2.
//

#ifndef SPECIFIC_DISCOUNT_CLASS_H
#define SPECIFIC_DISCOUNT_CLASS_H
#include "Abstract_Discount_class.h"
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
#endif //SPECIFIC_DISCOUNT_CLASS_H
