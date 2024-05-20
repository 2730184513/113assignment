#ifndef BILL_H
#define BILL_H

#include "Product_List.h"
#include "Trade_System.h"
#include <ctime>
#include <iomanip>

class Bill : public Product_List
{
	double total_amount = 0.0f;
	double discount = 0.0f;
	double net_total = 0.0f;
	double tax = 0.0f;
	double grand_total = 0.0f;
	double adjustment = 0.0f;
	double cash = 0.0f;
	int count = 0;
	using Product_List::addback;
	using Product_List::insert;
	using Product_List::clear;

	// Function to adjust the grand total
	static double adjust(double grand_total1)
	{
		string total = to_string(grand_total1);
		int i = 0;
		for (i; i < total.size(); i++)
		{
			if (total[i] == '.')
				break;
		}
		i += 2;
		if (total[i] < '5')
		{
			char c = total[i];
			total[i] = '0';
			if(total[i+1]>'5')
				c++;
			return (c - '0') / 100.0f;
		}
		else
		{
			char c = total[i];
			total[i] = '5';
			if(total[i+1]>'5')
				c++;
			return (c - '5') / 100.0f;
		}
	}

public:
	Bill() = default;

	Bill(const Bill &bill) = delete;

	~Bill() = default;

	// Function to set cash payment
	void setcash(double payment)
	{ cash += payment; }

	// Function to get total amount
	double gettotal_amount() const
	{ return total_amount; }

	// Function to get total discount
	double get_discount() const
	{ return discount; }

	// Function to get net total
	double getnet_total() const
	{ return net_total; }

	// Function to get tax
	double gettax() const
	{ return tax; }

	// Function to get grand total
	double getgrand_total() const
	{ return grand_total; }

	// Function to get adjustment
	double get_adjustment() const
	{ return adjustment; }

	// Function to get cash payment
	double getcash() const
	{ return cash; }

	int getcount() const
	{ return count; }

	// Function to get product by index
	const Product *getproduct(int index) const
	{
		return products[index];
	}

	// Update data after modifying the bill
	void update_data()
	{
		total_amount = 0.0f;
		discount = 0.0f;
		net_total = 0.0f;
		tax = 0.0f;
		grand_total = 0.0f;
		adjustment = 0.0f;
		cash = 0.0f;
		count = 0;
		for (int i = 0; i < total; i++)
		{
			total_amount += products[i]->getprice() * products[i]->getquantity();
			discount += Trade_System::calculate_discount(*products[i]);
			net_total = total_amount - discount;
			tax = Trade_System::calculate_tax(net_total);
			grand_total = net_total + tax;
			adjustment = adjust(grand_total);
			count += products[i]->getquantity();
		}
	}

	// Function to add a product to the bill
	void addproduct(const Product &product)
	{
		Product item(product);
		item.setquantity(1);
		addback(product);
		update_data();
	}

	// Function to set unit of a product
	void setunit(int index, int new_unit)
	{
		products[index]->setquantity(new_unit);
		update_data();
	}

	// Function to clear the bill
	void clear_bill()
	{
		if (this->is_empty())
			return;
		this->clear();
		update_data();
	}

	// Friend function to print the bill
	friend ostream &print(Bill &bill);
};

// Function to print the bill
ostream &print(Bill &bill)
{
	time_t now = time(nullptr);
	tm *local_time = localtime(&now);
	char buffer1[80], buffer2[80];
	strftime(buffer1, 80, "%x", local_time);
	strftime(buffer2, 80, "%X", local_time);
	string date = buffer1;
	string time = buffer2;
	string separator1(58, '=');
	string separator2(58, '-');
	string separator3(33, '-');

	cout << left << setw(24) << " " << "INVOICE" << endl;
	cout << "|" << separator1 << "|" << endl;
	cout << left << setw(10) << "| Date:" << left << setw(30) << date << left << setw(10)
		 << "Time:" << time << right << setw(10 - time.length()) << "|" << endl;
	cout << "|" << separator2 << "|" << endl;
	cout << "| Unit" << left << setw(4) << " " << "Unit Price(RM)" << left << setw(5) << " " << "Discount(RM)" << left
		 << setw(7) << " " << "Amount(RM)" << " |" << endl;
	cout << "|" << separator2 << "|" << endl;
	for (int i = 0; i < bill.gettotal(); i++)
	{
		string product = "No." + to_string(i + 1) + "  " + to_string(bill.getproduct(i)->getcode());
		product += "-" + bill.getproduct(i)->getname();
		cout << "| " << left << setw(56) << product << " |" << endl;
		cout << "| " << left << setw(11) << bill.getproduct(i)->getquantity()
			 << left << setw(19) << fixed << setprecision(2) << bill.getproduct(i)->getprice()
			 << left << setw(18) << Trade_System::calculate_discount(*bill.getproduct(i))
			 << right << setw(8) << Trade_System::calculate_amount(*bill.getproduct(i)) << " |" << endl;
	}
	cout << "|" << separator2 << "|" << endl;
	cout << "| " << left << setw(11) << "Qty:" << left << setw(13) << bill.count << left << setw(22) << "Total_Amount:"
		 << right << setw(10) << fixed << setprecision(2) << bill.total_amount << " |" << endl;
	cout << left << setw(30) << "| " << "Discount:" << right << setw(19) << -bill.discount << " |" << endl;
	cout << left << setw(25) << "| " << separator3 << " |" << endl;
	cout << left << setw(29) << "| " << "Net_Total:" << right << setw(19) << bill.net_total << " |" << endl;
	cout << left << setw(32) << "| " << "Tax 6%:" << right << setw(19) << bill.tax << " |" << endl;
	cout << left << setw(25) << "| " << separator3 << " |" << endl;
	if (bill.adjustment != 0)
	{
		cout << left << setw(28) << "| " << "Adjustment:" << right << setw(19) << -bill.adjustment << " |" << endl;
	}
	cout << left << setw(27) << "| " << "Grand_Total:" << right << setw(19) <<bill.grand_total-bill.adjustment
		 << " |" << endl;
	if (bill.cash == 0)
	{
		cout << left << setw(31) << "| " << "Payment:" << right << setw(19) << bill.cash << " |" << endl;
		cout << left << setw(32) << "| " << "Change:" << right << setw(21) << "0.00 |" << endl;
	}
	else if (bill.cash != 0 && bill.cash < bill.grand_total - bill.adjustment)
	{
		cout << left << setw(31) << "| " << "Payment:" << right << setw(19) <<setprecision(1)<< bill.cash - bill.grand_total-bill.adjustment << " |"
			 << endl;
		cout << left << setw(32) << "| " << "Change:" << right << setw(21) << "0.00 |" << endl;
	}
	else
	{
		cout << left << setw(31) << "| " << "Payment:" << right << setw(19) << "0.00" << " |"
			 << endl;
		cout << left << setw(32) << "| " << "Change:" << right << setw(19) << bill.cash - bill.grand_total << " |"
			 << endl;
	}
	cout << "|" << separator1 << "|" << endl;
	return cout;
}

string str_adjust(double grand_total1)
{
	string temp = to_string(grand_total1);
	string total;
	int i = 0;
	for (i; i < temp.size(); i++)
	{
		if (temp[i] == '.')
			break;
	}
	i += 2;
	for(int x=0;x<i;x++)
	{
		total+=temp[x];
	}
	if (total[i] < '5')
	{
		total[i] = '0';
		return total;
	}
	else
	{
		total[i] = '5';
		return total;
	}
}

#endif //BILL_H
