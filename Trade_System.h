#ifndef TRADE_SYSTEM_H
#define TRADE_SYSTEM_H

#include "Product_List.h"

class Trade_System
{
	// Function to ban trading (to be implemented by derived classes)
	virtual void ban() = 0;

	// Constant for tax rate
	static const float TAX_RATE;

	// Static function to calculate discount based on rule 1
	static float calculate_discount1(const Product &product)
	{
		float discount = 0.0;
		if (product.getquantity() >= product.getdiscount_rule1())
			discount = (1 - product.getdiscount()) * product.getprice() * product.getquantity();
		return discount;
	}

	// Static function to calculate discount based on rule 2
	static float calculate_discount2(const Product &product)
	{
		float discount = 0.0;
		if (product.getquantity() >= product.getdiscount_rule2())
		{
			int type = product.gettype();
			if(type == CAKE)// Cakes are 25% off
				discount =0.25f*product.getprice() * product.getquantity();
			else if (type == COOKIE) // Cookies are 20% off
				discount =0.2f*product.getprice() * product.getquantity();
		}
		return discount;
	}

public:
	// Static function to calculate the amount for a single product
	static float calculate_amount(const Product &product)
	{
		return product.getprice() * product.getquantity();
	}

	// Static function to calculate the total amount for a list of products
	static float calculate_total(const Product_List &product_list)
	{
		int count = product_list.gettotal();
		float total = 0.0;
		for (int i = 0; i < count; i++)
		{
			float amount = calculate_amount(*product_list[i]);
			total += amount;
		}
		return total;
	}

	// Static function to calculate the total discount for a product
	static float calculate_discount(const Product &product)
	{
		float discount = max(calculate_discount1(product), calculate_discount2(product));
		return discount;
	}

	// Static function to calculate the tax based on net total
	static float calculate_tax(float net_total)
	{ return net_total * TAX_RATE; }
};

// Definition of the tax rate
const float Trade_System::TAX_RATE = 0.06f;
#endif //TRADE_SYSTEM_H
