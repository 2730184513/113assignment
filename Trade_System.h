//
// Created by dengchujie on 24-5-16.
//

#ifndef TRADE_SYSTEM_H
#define TRADE_SYSTEM_H

#include "Product_List.h"

class Trade_System
{
	virtual void ban() = 0;

	static const float TAX_RATE;

	static double calculate_discount1(const Product &product)
	{
		double discount = 0.0;
		if (product.getquantity() >= product.getdiscount_rule1())
			discount = (1 - product.getdiscount()) * product.getprice() * product.getprice();
		return discount;
	}

	static double calculate_discount2(const Product &product)
	{
		double discount = 0.0;
		if (product.getquantity() >= product.getdiscount_rule2())
		{
			int free = product.getquantity() / product.getdiscount_rule2();
			discount = product.getprice() * free;
		}
		return discount;
	}

public:
	static double calculate_amount(const Product &product)
	{
		return product.getprice() * product.getquantity();
	}

	static double calculate_total(const Product_List &product_list)
	{
		int count = product_list.gettotal();
		double total = 0.0;
		for (int i = 0; i < count; i++)
		{
			double amount = calculate_amount(*product_list[i]);
			total += amount;
		}
		return total;
	}

	static double calculate_discount(const Product_List &product_list)
	{
		int count = product_list.gettotal();
		double total_discount = 0.0;
		for (int i = 0; i < count; i++)
		{
			double discount = max(calculate_discount1(*product_list[i]), calculate_discount2(*product_list[i]));
			total_discount += discount;
		}
		return total_discount;
	}

	static double calculate_discount(const Product &product)
	{
		double discount = max(calculate_discount1(product), calculate_discount2(product));
		return discount;
	}

	static double calculate_tax(double net_total)
	{ return net_total * TAX_RATE; }
};

const float Trade_System::TAX_RATE = 0.06f;
#endif //TRADE_SYSTEM_H
