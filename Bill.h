//
// Created by dengchujie on 24-5-16.
//

#ifndef BILL_H
#define BILL_H

#include "Product_List.h"
#include "Trade_System.h"
#include <ctime>
#include <iomanip>

class Bill : public Product_List
{
	double total_amount = 0.0;
	double discount = 0.0;
	double net_total = 0.0;
	double tax = 0.0;
	double grand_total = 0.0;
	double cash = 0.0;
	/*int size = 0;
	int total = 0;
	Product **products;*/
	using Product_List::addback;
	using Product_List::insert;
public:
	Bill() = default;

//	Bill(const Product *products_array, int size) : Product_List(size * 2)
//	{
//		for (int i = 0; i < size; i++)
//			addproduct(products_array[i]);
//		total_amount = Trade_System::calculate_total(*this);
//		discount = Trade_System::calculate_discount(*this);
//		net_total = total_amount - discount;
//		tax = Trade_System::calculate_tax(net_total);
//		grand_total = net_total + tax;
//	}
//
//	Bill(const Product *const *const products_array, int size) : Bill(*products_array,size)
//	{ }
//
//	Bill(const Product_List &product_list)
//	{
//		size = product_list.gettotal()*2;
//		products = new Product * [size];
//		for (int i = 0; i < size; i++)
//			addproduct(*product_list[i]);
//		total_amount = Trade_System::calculate_total(*this);
//		discount = Trade_System::calculate_discount(*this);
//		net_total = total_amount - discount;
//		tax = Trade_System::calculate_tax(net_total);
//		grand_total = net_total + tax;
//	}

	Bill(const Bill &bill) = delete;

	~Bill() = default;

	void setcash(double payment)
	{ cash = payment; }

	double gettotal_amount() const
	{ return total_amount; }

	double get_discount() const
	{ return discount; }

	double getnet_total() const
	{ return net_total; }

	double gettax() const
	{ return tax; }

	double getgrand_total() const
	{ return grand_total; }

	double getcash() const
	{ return cash; }

	double getchange()
	{ return cash - grand_total; }

	const Product *getproduct(int index) const
	{
		return products[index];
	}

	void addproduct(const Product &product)
	{ addback(product); }

	void setunit(int index, int new_unit)
	{ products[index]->setquantity(new_unit); }

	friend ostream &print(Bill &bill);
};

ostream &print(Bill &bill)
{
	time_t now = time(nullptr);
	tm *local_time = localtime(&now);
	char buffer1[80], buffer2[80];
	strftime(buffer1, 80, "%x", local_time);
	strftime(buffer2, 80, "%X", local_time);
	string date = buffer1;
	string time = buffer2;
	string separator1(60, '=');
	string separator2(60, '-');
	string separator3(33, '-');

	cout << left << setw(24) << " " << "INVOICE" << endl;
	cout << separator1 << endl;
	cout << left << setw(10) << "| Date:" << left << setw(30) << date << left << setw(10)
		 << "Time:" << time << right << setw(10 - time.length()) << "|" << endl;
	cout << separator2 << endl;
	cout << "| Unit" << left << setw(4) << " " << "Unit Price(RM)" << left << setw(5) << " " << "Discount(RM)" << left
		 << setw(7) << " " << "Amount(RM)" << " |" << endl;
	cout << separator2 << endl;
	int qty = 0;
	for (int i = 0; i < bill.gettotal(); i++)
	{
		qty += bill.getproduct(i)->getquantity();
		string product = to_string(bill.getproduct(i)->getcode());
		product += "-" + bill.getproduct(i)->getname();
		cout << "| " << left << setw(56) << product << " |" << endl;
		cout << "| " << left << setw(11) << bill.getproduct(i)->getquantity()
			 << left << setw(19) << fixed << setprecision(2) << bill.getproduct(i)->getprice()
			 << left << setw(20) << Trade_System::calculate_discount(*bill.getproduct(i))
			 << right << setw(5) << Trade_System::calculate_amount(*bill.getproduct(i)) << " |" << endl;
	}
	cout << separator2 << endl;
	cout << "| " << left << setw(11) << "Qty:" << left << setw(13) << qty << left << setw(22) << "Total_Amount:"
		 << right << setw(10) << fixed << setprecision(2) << bill.total_amount << " |" << endl;
	cout << left << setw(30) << "| " << "Discount:" << right << setw(19) << bill.discount << " |" << endl;
	cout << left << setw(25) << "| " << separator3 << " |" << endl;
	cout << left << setw(29) << "| " << "Net_Total:" << right << setw(19) << bill.net_total << " |" << endl;
	cout << left << setw(32) << "| " << "Tax 6%:" << right << setw(19) << bill.tax << " |" << endl;
	cout << left << setw(25) << "| " << separator3 << " |" << endl;
	cout << left << setw(27) << "| " << "Grand_Total:" << right << setw(19) << bill.grand_total << " |" << endl;
	cout << left << setw(31) << "| " << "Payment:" << right << setw(19) << bill.cash << " |" << endl;
	cout << left << setw(32) << "| " << "Change:" << right << setw(19) << bill.cash - bill.grand_total << " |" << endl;
	cout << separator1 << endl;
	return cout;
}

#endif //BILL_H
