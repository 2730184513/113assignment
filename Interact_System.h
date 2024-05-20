
//
// Created by dengchujie on 24-5-18.
//
#ifndef INTERACT_SYSTEM_H
#define INTERACT_SYSTEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include "Product.h"

using namespace std;

State show_start_menu(int &choice)
{
	cout << "\t\t\t\t\t\tWelcome to Use This Trading System\n";
	cout << "Please select the function you want (Enter the number in front of the desired function to proceed):\n";
	cout << "(If you are using it for the first time, please initialize first, "
			"otherwise the program may not run properly)\n";
	cout << "1.Check in\n";
	cout << "2.Trade\n";
	cout << "3.Search Product\n";
	cout << "Your choice(Enter /-1 to quit): ";
	cin >> choice;
	getchar();
	while (cin.fail() || choice < 1 || choice > 3)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
				return QUIT;
		}
		cout << "You have entered a wrong value for choice, pleas enter again:\t";
		cin >> choice;
		getchar();
	}
	return SUCCESS;
}

State show_check_in_menu(int &choice)
{

	cout << "1.Add items one by one\n";
	cout << "2.Add items from a file\n";
	cout << "3.Replenish products\n";
	cout << "Your choice (Enter /-1 to quit):";
	cin >> choice;
	while (cin.fail() || choice < 1 || choice > 3)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value for choice, pleas enter again:\t";
		cin >> choice;
		getchar();
	}
	return SUCCESS;
}

State user_input_product(Product &product)
{
	string name, user_choice;
	bool type;
	float price, discount_percentage;
	int quantity, discount_rule1;
	cout << "Please choose the type of the product you want to add (CAKE or COOKIE):\t";
	cin >> user_choice;
	getchar();
	user_choice = toupper(user_choice);
	if (user_choice.find("-1") != string::npos)
	{

		return QUIT;
	}
	while (whichtype(user_choice) == WRONG_TYPE)
	{

		if (user_choice.find("-1") != string::npos)
		{

			return QUIT;
		}

		cout << "You have entered a wrong type, please choose again:\t";
		cin >> user_choice;
		getchar();
	}
	type = whichtype(user_choice);

	cout << "Please enter the name of the product you want to add:\t";
	getline(cin, user_choice);
	name = title(user_choice);
	if (user_choice.find("-1") != string::npos)
	{
		return QUIT;
	}

	cout << "Please enter its price:\t";
	cin >> price;
	getchar();
	while (cin.fail() || price <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value for price, pleas enter again:\t";
		cin >> price;
		getchar();
	}

	cout << "Please enter its quantity:\t";
	cin >> quantity;
	getchar();
	while (cin.fail() || quantity <= 0)
	{
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value for quantity, pleas enter again:\t";
		cin >> quantity;
		getchar();
	}

	cout << "Please enter its discount rule.\n";
	cout << "If it doesn't have discount rule, please enter 0.\n";
	cout << "The discount rule:\t";
	cin >> discount_rule1;
	getchar();
	while (cin.fail() || discount_rule1 < 0)
	{
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value for discount rule, pleas enter again:\t";
		cin >> discount_rule1;
		getchar();
	}
	if (discount_rule1 == 0)
	{
		discount_rule1 = INT_MAX;
		discount_percentage = 0;
	}
	else
	{

		cout << "Please enter its discount percentage(between 0 and 1):\t";
		cin >> discount_percentage;
		while (cin.fail() || !(0 < discount_percentage && discount_percentage < 1))
		{
			if (cin.fail())
			{
				cin.clear();
				getline(cin, user_choice);
				if (user_choice.find("-1") != string::npos)
				{

					return QUIT;
				}
			}


			cout << "You have entered a wrong value for discount percentage, pleas enter again:\t";
			cin >> discount_percentage;
			getchar();
		}
	}
	product.setproduct(name, type, price, quantity, discount_rule1, discount_percentage);

	cout << "Here is the information of the product you want to add. Please check whether it is correct or not.\n";
	print(product);
	cout << "If correct enter Y, if not enter N:\t";
	getchar();
	getline(cin, user_choice);
	if (user_choice.find("-1") != string::npos)
	{

		return QUIT;
	}
	user_choice = toupper(user_choice);
	while (user_choice != "Y" && user_choice != "N")
	{

		if (user_choice.find("-1") != string::npos)
		{

			return QUIT;
		}
		cout << "You have entered a wrong choice, please enter again:\t";
		getline(cin, user_choice);
	}
	if (user_choice == "Y")
	{
		cout << "This product has been successfully created " << endl;
		return SUCCESS;
	}
	else
	{
		cout << "The information of the product that you entered has been cleared" << endl;
		return QUIT;
	}
}

bool ask_do_again()
{
	string user_choice;
	cout << "Do you want to do again?" << endl;
	cout << "Enter Y to do again or enter N to reject (Enter /-1 to quit):\t";
	getline(cin, user_choice);
	if (user_choice.find("-1") != string::npos)
	{

		return QUIT;
	}
	user_choice = toupper(user_choice);
	while (user_choice != "Y" && user_choice != "N")
	{
		if (user_choice.find("-1") != string::npos)
		{

			return QUIT;
		}

		cout << "You have entered a wrong choice, please enter again (Enter /-1 to quit):\t";
		getline(cin, user_choice);
		user_choice = toupper(user_choice);
	}
	if (user_choice == "N")
	{

		cout << "Thank you for use." << endl;
		return false;
	}
	else
	{

		return true;
	}
}

State check_in_function1(Trade_Manager &tm)
{
	cout << "Please enter the information of the product that you want to add\n";
	cout << "You can quit through entering /-1 whenever you want\n";
	Product input_product;
	if (user_input_product(input_product) == SUCCESS)
		return tm.inbound(input_product);
	else
		return QUIT;
}

State check_in_function2(Trade_Manager &tm)
{
	string filename;
	cout << "Please enter the filename that you want to add\n";
	cout << "The filename is (Enter /-1 to quit): ";
	cin >> filename;
	getchar();
	ifstream product_list(filename);
	if (product_list.is_open())
	{
		State state = tm.inbound(product_list);
		return state;
	}
	else
		return NOT_FIND;
}

State check_in_function3_1(Trade_Manager &tm, Product_List &need_replenish)
{
	string separator(100, '=');
	cout << "The products which need to replenish is as the following:" << endl;
	cout << separator << endl;
	for (int i = 0; i < need_replenish.gettotal(); i++)
	{
		if (i != 0 && i % 3 == 0)
			cout << endl;
		cout << setw(3) << setfill('0') << i + 1 << "-" << need_replenish[i]->getname() << " ("
			 << need_replenish[i]->getquantity() << ") " << "\t\t";
	}
	cout.clear();
	cout.fill(' ');
	if ((need_replenish.gettotal() - 1) % 3 != 0)
		cout << endl;

	cout << separator << endl;
	cout << "Please enter an integer as the replenishment quantity. "
			"This will be the replenishment quantity for all items in this list.\n";
	cout << "The replenishment quantity is (Enter /-1 to quit): ";
	int quantity;
	string user_choice;
	cin >> quantity;
	getchar();
	while (cin.fail() || quantity <= 0)
	{

		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> quantity;
		getchar();
	}
	need_replenish.setquantity(quantity);
	tm.inbound(need_replenish);
	cout << "You have successfully add " << quantity << " to all of them" << endl;
	return SUCCESS;
}

State check_in_function3_2(Trade_Manager &tm, Product_List &need_replenish)
{
	string separator(100, '=');
	string user_choice;
	do
	{
		cout << "The products which need to replenish is as the following:" << endl;
		cout << separator << endl;
		for (int i = 0; i < need_replenish.gettotal(); i++)
		{
			if (i != 0 && i % 3 == 0)
				cout << endl;
			cout << setw(3) << setfill('0') << i + 1 << "-" << need_replenish[i]->getname() << " ("
				 << need_replenish[i]->getquantity() << ") " << "\t";
		}
		cout.clear();
		cout.fill(' ');
		if (need_replenish.gettotal() % 3 != 0)
			cout << endl;
		cout << separator << endl;
		int index;
		cout << "Which product you want to replenish?\n";
		cout << "Please enter its index to choose it\n";
		cout << "Your choice (Enter /-1 to quit): ";
		cin >> index;
		getchar();
		while (cin.fail() || index < 0)
		{
			if (cin.fail())
			{
				cin.clear();
				getline(cin, user_choice);
				if (user_choice.find("-1") != string::npos)
				{

					return QUIT;
				}
			}


			cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
			cin >> index;
		}

		index--;
		cout << "Please enter an integer as the quantity that you replenished for it (Enter /-1 to quit): ";
		int quantity;
		cin >> quantity;
		getchar();
		while (cin.fail() || quantity < 0)
		{
			if (cin.fail())
			{
				cin.clear();
				getline(cin, user_choice);
				if (user_choice.find("-1") != string::npos)
				{

					return QUIT;
				}
			}

			cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
			cin >> quantity;
		}

		need_replenish.getproduct(index).setquantity(quantity);
		tm.inbound(*need_replenish[index]);
		int code = need_replenish[index]->getcode();
		need_replenish.remove(index);
		cout << "You have successfully set the quantity of " << tm.getproduct(code).getname() << " to "
			 << tm.getproduct(code).getquantity() << endl;
	} while (ask_do_again());
	return SUCCESS;
}

State check_in_function3(Trade_Manager &tm)
{
	int rule;
	string user_choice;
	cout << "Please enter an positive integer as the rule of replenishment\n";
	cout << "Products' quantity lower than this rule will be showing in following\n";
	cout << "The rule is (Enter /-1 to quit): ";
	cin >> rule;
	getchar();
	while (cin.fail() || rule < 0)
	{
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> rule;
		getchar();
	}
	Product_List need_replenish;
	tm.need_replenishment(need_replenish, rule);
	cout << "Please choose to replenish one by one or replenish them uniformly\n";
	cout << "1.Replenish uniformly\n";
	cout << "2.Replenish one by one\n";
	cout << "Your choice (Enter /-1 to quit): ";
	bool wrong_flag = false;
	do
	{
		getline(cin, user_choice);
		if (user_choice.find("-1") != string::npos)
			return QUIT;
		else if (user_choice == "1")
			return check_in_function3_1(tm, need_replenish);
		else if (user_choice == "2")
			return check_in_function3_2(tm, need_replenish);
		else
		{
			wrong_flag = true;

			cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		}
	} while (wrong_flag);
	return SUCCESS;
}

State show_trade_menu(int &choice, Trade_Manager &tm)
{
	cout << "1.Enter the code of product to add it into bill\n";
	cout << "2.Enter the name of product to add it into bill\n";
	cout << "3.Remove a product that is in the bill\n";
	cout << "4.Set quantity of a product that is in the bill\n";
	cout << "5.Pay the bill\n";
	cout << "6.Get daily sales data\n";
	cout << "Your choice (Enter /-1 to quit): ";
	cin >> choice;
	getchar();
	while (cin.fail() || choice < 1 || choice > 6)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos && !tm.bill_is_empty())
			{
				system("cls");
				cout << "You have an unpaid bill, can't quit now\n";
				cout << "Please pay it at first" << endl;
				show_trade_menu(choice, tm);
			}
			else if (user_choice.find("-1") != string::npos && tm.bill_is_empty())
			{ return QUIT; }
			else
			{
				cout << "You have entered a wrong value for choice, pleas enter again:\t";
				cin >> choice;
				getchar();
			}
		}

	}
	return SUCCESS;
}

State trade_function1(Trade_Manager &tm)
{
	cout << "Please enter the code of the product you want to add (Enter /-1 to quit):\t";
	int code;
	cin >> code;
	getchar();
	string user_choice;
	while (cin.fail() || code < 0 || code > Warehouse::getcapacity())
	{

		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> code;
		getchar();
	}
	State state = tm.addbill(code);
	tm.showbill();
	return state;
}

State trade_function2(Trade_Manager &tm)
{
	cout << "Please enter the code or name of the product you want to add (Enter /-1 to quit):\n";
	string user_choice;
	getline(cin, user_choice);
	if (user_choice.find("-1") != string::npos)
	{

		return QUIT;
	}
	while (tm.getproduct(user_choice) == Empty)
	{
		cout << "Warehouse doesn't have this product, please enter again (Enter /-1 to quit): \t";
		getline(cin, user_choice);
	}
	State state = tm.addbill(user_choice);
	tm.showbill();
	return state;
}

State trade_function3(Trade_Manager &tm)
{
	tm.showbill();
	cout << "Please enter the index of the product that you want to remove (Enter /-1 to quit):\t";
	int index;
	cin >> index;
	getchar();
	string user_choice;
	while (cin.fail() || index < 0 || index > tm.getbill_count())
	{

		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> index;
		getchar();
	}
	State state = tm.remove(index - 1);
	tm.showbill();
	return state;
}

State trade_function4(Trade_Manager &tm)
{
	tm.showbill();
	cout << "Please enter the index of the product that you want to set its quantity (Enter /-1 to quit):\t";
	int index;
	cin >> index;
	getchar();
	string user_choice;
	while (cin.fail() || index < 0 || index > tm.getbill_count())
	{

		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}
		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> index;
		getchar();
	}
	int quantity;
	cout << "Please enter the quantity that you want to set (Enter /-1 to quit):\t";
	cin >> quantity;
	while (cin.fail() || quantity < 0)
	{

		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> quantity;
		getchar();
	}
	State state = tm.setunit(index - 1, quantity);
	return state;
}

State trade_function5(Trade_Manager &tm)
{
	float cash;
	do
	{
		tm.showbill();
		cout << "Enter the receipt: (Enter /-1 to quit)";
		cin >> cash;
		getchar();
		while (cin.fail() || cash < 0)
		{
			string user_choice;
			if (cin.fail())
			{
				cin.clear();
				getline(cin, user_choice);
				if (user_choice.find("-1") != string::npos)
				{

					return QUIT;
				}
			}


			cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
			cin >> cash;
			getchar();
		}
	} while (!tm.paybill(cash));
	return SUCCESS;
}

State trade_function6(Trade_Manager &tm)
{
	string filename = getdate() + "-outbound_list.txt";
	ifstream outbound_list(filename);
	bool end_flag = false;
	cout << "The daily sales data is as following:\n";
	string separator(100, '=');
	cout << separator << endl;
	if (outbound_list.is_open())
	{
		string line;

		while (!outbound_list.eof())
		{
			getline(outbound_list, line);
			if (line == "\0")
			{
				end_flag = true;
				break;
			}
			cout << line << endl;
		}
		cout << separator << endl;
	}
	else
		return NOT_FIND;
	if (end_flag)
	{
		outbound_list.close();
		return SUCCESS;
	}
	else
		return FAILED;
}

State show_search_menu(int &choice)
{
	cout << "1.Get all products\n";
	cout << "2.Get all cakes\n";
	cout << "3.Get all cookies\n";
	cout << "4.Get all products that its price is lower than one price\n";
	cout << "5.Get all products that its price is higher than one price\n";
	cout << "6.Get products that need to replenish\n";
	cout << "7.Fuzzy search for some certain products\n";
	cout << "8. Accurate search for one certain product (code)\n";
	cout << "9. Accurate search for one certain product (name)\n";
	cout << "Your choice (Enter /-1 to quit): ";
	cin >> choice;
	getchar();
	while (cin.fail() || choice < 1 || choice > 9)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value for choice, pleas enter again:\t";
		cin >> choice;
		getchar();
	}
	return SUCCESS;
}

State search_function1(Trade_Manager &tm)
{
	int size = tm.unique_products();
	Product_List all(size);
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	tm.getall(all, static_cast<Commands>(sort_base), static_cast<Commands>(order));
	print(all);
	string user_input;
	cout << "Press enter key to go back to search menu.";
	getline(cin, user_input);
	return SUCCESS;
}

State search_function2(Trade_Manager &tm)
{
	int size = tm.unique_products();
	Product_List cakes(size / 2);
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	tm.getcakes(cakes, static_cast<Commands>(sort_base), static_cast<Commands>(order));
	print(cakes);
	string user_input;
	cout << "Press enter key to go back to search menu.";
	getline(cin, user_input);
	return SUCCESS;
}

State search_function3(Trade_Manager &tm)
{
	Product_List cookies(tm.unique_products() / 2);
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	tm.getcookies(cookies, static_cast<Commands>(sort_base), static_cast<Commands>(order));
	print(cookies);
	string user_input;
	cout << "Press enter key to go back to search menu.";
	getline(cin, user_input);
	return SUCCESS;
}

State search_function4(Trade_Manager &tm)
{
	Product_List products(tm.unique_products() / 2);
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	cout << "Please enter the price:\t";
	float price;
	cin >> price;
	while (cin.fail() || price < 0)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> price;
		getchar();
	}
	tm.getlower_price(products, price, static_cast<Commands>(sort_base), static_cast<Commands>(order));
	print(products);
	string user_input;
	cout << "Press enter key to go back to search menu.";
	getline(cin, user_input);
	return SUCCESS;
}

State search_function5(Trade_Manager &tm)
{
	Product_List products(tm.unique_products() / 2);
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	cout << "Please enter the price:\t";
	float price;
	cin >> price;
	while (cin.fail() || price < 0)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> price;
		getchar();
	}
	tm.gethigher_price(products, price, static_cast<Commands>(sort_base), static_cast<Commands>(order));
	print(products);
	string user_input;
	cout << "Press enter key to go back to search menu.";
	getline(cin, user_input);
	return SUCCESS;
}

State search_function6(Trade_Manager &tm)
{
	Product_List products(tm.unique_products() / 2);
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	cout << "Please enter the rule of replenishment:\t";
	int rule;
	cin >> rule;
	while (cin.fail() || rule < 0)
	{
		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> rule;
		getchar();
	}
	tm.need_replenishment(products, rule, static_cast<Commands>(sort_base), static_cast<Commands>(order));
	print(products);
	string user_input;
	cout << "Press enter key to go back to search menu.";
	getline(cin, user_input);
	return SUCCESS;
}

State search_function7(Trade_Manager &tm)
{
	Product_List products(20);
	string name;
	cout << "Please enter a part of name of the product that you want to search (Enter /-1 to quit): " << endl;
	getline(cin, name);
	name = title(name);
	if (name.find("-1") != string::npos)
		return QUIT;
	int size = tm.unique_products();
	cout << "Please choose the basis for your ranking\n";
	cout << "BASE_NAME = 0, BASE_PRICE = 1, BASE_QUANTITY = 2, BASE_DISCOUNT = 3,\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int sort_base;
	cin >> sort_base;
	getchar();
	while (cin.fail() || sort_base < 0 || sort_base > 3)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}


		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> sort_base;
		getchar();
	}
	cout << "Please choose your sort order (Enter /-1 to quit)\n";
	cout << "Ascending(0) or Descending(1)\n";
	cout << "Your choice (Enter /-1 to quit): " << endl;
	int order;
	cin >> order;
	getchar();
	while (cin.fail() || order < 0 || order > 1)
	{

		string user_choice;
		if (cin.fail())
		{
			cin.clear();
			getline(cin, user_choice);
			if (user_choice.find("-1") != string::npos)
			{

				return QUIT;
			}
		}
		cout << "You have entered a wrong value, please enter again (Enter /-1 to quit): \t";
		cin >> order;
		getchar();
	}
	tm.fuzzy_search(name, products,static_cast<Commands>(sort_base), static_cast<Commands>(order));
	if (products.gettotal() == 0)
	{
		cout << "No product has this name." << endl;
		string user_input;
		cout << "Press enter key to go back to search menu.";
		getline(cin, user_input);
		return NOT_FIND;
	}
	else
	{
		string user_input;
		print(products);
		cout << "Press enter key to go back to search menu.";
		getline(cin, user_input);
	}
	return SUCCESS;
}

State search_function8(Trade_Manager &tm)
{
	cout << "Please enter the code of product that you want to search (Enter /-1 to quit): " << endl;
	string user_input;
	getline(cin, user_input);
	int code;
	if (user_input.find("-1") != string::npos)
		return QUIT;
	else
		code = stoi(user_input);
	print(tm.getproduct(code));
	cout<<"Press enter key to go back to search menu.";
	getline(cin,user_input);
	return SUCCESS;
}

State search_function9(Trade_Manager &tm)
{
	cout << "Please enter the name of product that you want to search (Enter /-1 to quit): " << endl;
	string user_input;
	getline(cin, user_input);
	user_input = title(user_input);
	if (user_input.find("-1") != string::npos)
		return QUIT;
	else
		print(tm.getproduct(user_input));
	cout<<"Press enter key to go back to search menu.";
	getline(cin,user_input);
	return SUCCESS;
}

#endif //INTERACT_SYSTEM_H
