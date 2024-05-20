#include "Trade_Manager.h"
#include "Interact_System.h"
#include <iostream>
#include <string>

using namespace std;

int main()
{
	Trade_Manager shop;
	enum State state;
	do
	{
		int choice;
		state = show_start_menu(choice);
		if (choice != 1 && shop.unique_products() == 0)
		{
			ifstream remaining_inventory("remaining_inventory.txt");
			if (remaining_inventory.is_open())
			{

				shop.inbound(remaining_inventory);
			}
			else
			{
				system("cls");
				cout << "open" << endl;
				cout << "You haven't initialize the warehouse, please use check_in function to initialize first"
					 << endl;
				continue;
			}
		}
		if (choice == 1)
		{
			State state_menu1;
			State state_function = NO_INITIALIZED;
			do
			{
				if (state_function == NO_INITIALIZED)
					system("cls");
				state_menu1 = show_check_in_menu(choice);
				if (choice == 1)
				{
					state_function = check_in_function1(shop);
					if (state_function == SUCCESS)
					{
						system("cls");
						cout << "You have successfully added them into warehouse" << endl;
					}
					else if (state_function == FAILED)
					{
						system("cls");
						cout << "There has some problems in adding these products into the warehouse " << endl;
					}
				}
				else if (choice == 2)
				{
					state_function = check_in_function2(shop);
					if (state_function == SUCCESS)
					{
						system("cls");
						cout << "You have successfully added them into warehouse" << endl;
					}
					else if (state_function == FAILED)
					{
						system("cls");
						cout << "There has some problems in adding these products into the warehouse " << endl;
					}
					else if (state_function == NOT_FIND)
					{
						system("cls");
						cout << "The filename you entered can't be find, "
								"please check whether the filename is correct or not" << endl;
					}
				}
				else if (choice == 3)
				{
					check_in_function3(shop);
				}
			} while (state_menu1 != QUIT);
		}
		else if (choice == 2)
		{
			State state_menu2;
			do
			{
				system("cls");
				state_menu2 = show_trade_menu(choice, shop);
				State state_function;
				if (choice == 1)
				{
					do
					{
						state_function = trade_function1(shop);
					} while (state_function != QUIT);
				}
				else if (choice == 2)
				{
					do
					{
						state_function = trade_function2(shop);
					} while (state_function != QUIT);
				}
				else if (choice == 3)
				{
					do
					{
						state_function = trade_function3(shop);
					} while (state_function != QUIT);
				}
				else if (choice == 4)
				{
					do
					{
						state_function = trade_function4(shop);
					} while (state_function != QUIT);
				}
				else if (choice == 5)
				{
					do
					{
						state_function = trade_function5(shop);
					} while (state_function != QUIT);
				}
				else if (choice == 6)
					trade_function6(shop);
			} while (state_menu2 != QUIT);
		}
		else if (choice == 3)
		{
			State state_menu3;
			do
			{
				system("cls");
				state_menu3 = show_search_menu(choice);
				if (choice == 1)
				{
					system("cls");
					search_function1(shop);
				}
				else if (choice == 2)
				{
					system("cls");
					search_function2(shop);
				}
				else if (choice == 3)
				{
					system("cls");
					search_function3(shop);
				}
				else if (choice == 4)
				{
					system("cls");
					search_function4(shop);
				}
				else if (choice == 5)
				{
					system("cls");
					search_function5(shop);
				}
				else if (choice == 6)
				{
					system("cls");
					search_function6(shop);
				}
				else if (choice == 7)
				{
					system("cls");
					search_function7(shop);
				}
				else if (choice == 8)
				{
					system("cls");
					search_function8(shop);
				}
				else if (choice == 9)
				{
					system("cls");
					search_function9(shop);
				}
			} while (state_menu3 != QUIT);
		}
	} while (state != QUIT);
}
