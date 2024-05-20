
#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "Product.h" // Include Product header file.
#include <algorithm> // Include algorithm header for sorting.

// Declaration of an empty Product.
Product const Empty;

// Class to represent a list of products.
class Product_List
{
protected:
	int size = 0; // Total size of the product list.
	int total = 0; // Total number of products in the list.
	Product **products; // Pointer to an array of product pointers.

public:
	// Default constructor to initialize the product list with a default size.
	Product_List() : size(20)
	{
		products = new Product *[size];
		for (int i = 0; i < size; i++)
			products[i] = nullptr;
	}

	// Parameterized constructor to initialize the product list with a specified size.
	explicit Product_List(int size) : size(size)
	{
		products = new Product *[size];
		for (int i = 0; i < size; i++)
			products[i] = nullptr;
	}

	// Copy constructor to create a new product list by copying another product list.
	Product_List(const Product_List &product_list)
	{
		size = product_list.size;
		products = new Product *[size];
		addback(product_list);
	}

	// Constructor to create a new product list from an array of products with a specified size.
	Product_List(const Product *product_list, int size)
	{
		this->size = size * 2;
		products = new Product *[this->size];
		addback(product_list, size);
	}

	// Constructor to create a new product list from an array of pointers to products with a specified size.
	Product_List(const Product *const *const product_list, int size)
	{
		this->size = size * 2;
		products = new Product *[this->size];
		addback(product_list, size);
	}

	// Destructor to free memory allocated for products.
	~Product_List()
	{
		for (int i = 0; i < total; i++)
			delete products[i];
		delete[] products;
	}

	// Function to get the total number of products in the list.
	int gettotal() const
	{ return total; }

	// Function to check if the product list is empty.
	bool is_empty() const
	{
		if (total == 0)
			return true;
		else
			return false;
	}

	// Function to swap the positions of two products in the list.
	void swap(int position1, int position2)
	{
		Product *temp = products[position1];
		products[position1] = products[position2];
		products[position2] = temp;
	}

	// Function to add a product to the end of the list.
	void addback(const Product &product)
	{
		if (total == size)
		{
			int newsize = size * 2;
			auto **temp = new Product *[newsize];
			for (int i = 0; i < size; i++)
				temp[i] = products[i];
			for (int i = size; i < newsize; i++)
				temp[i] = nullptr;
			delete[] products;
			products = temp;
			size = newsize;
		}
		products[total++] = new Product(product);
	}

	// Function to add multiple products to the end of the list.
	void addback(const Product *const product_list, int list_size)
	{
		for (int i = 0; i < list_size; i++)
			addback(product_list[i]);
	}

	// Function to add multiple products to the end of the list.
	void addback(const Product *const *const product_list, int list_size)
	{
		for (int i = 0; i < list_size; i++)
			addback(*product_list[i]);
	}

	// Function to add all products from another product list to the end of this list.
	void addback(const Product_List &product_list)
	{
		int list_size = product_list.size;
		addback(product_list.products, list_size);
	}

	// Function to insert a product at a specified position in the list.
	void insert(Product &product, int position)
	{
		total++;
		for (int i = total; i >= position; i--)
			products[i] = products[i - 1];
		products[position] = &product;
	}

	// Function to remove the last product from the list.
	void pop()
	{ products[--total] = nullptr; }

	// Function to get the first product in the list.
	const Product *front()
	{
		if (total == 0)
			return &Empty;
		return products[0];
	}

	// Function to get the last product in the list.
	const Product *back()
	{
		if (total == 0)
			return &Empty;
		return products[total - 1];
	}

	// Function to clear all products from the list.
	void clear()
	{
		for (int i = 0; i < total; i++)
			products[i] = nullptr;
		total = 0;
	}

	// Function to remove a product at a specified position from the list.
	State remove(int position)
	{
		if (position < 0 || position >= total)
			return OUT_OF_RANGE;
		products[position] = nullptr;
		total--;
		for (int i = position; i <= total; i++)
			products[i] = products[i + 1];
		return SUCCESS;
	}

	// Function to get a product at a specified position from the list.
	Product &getproduct(int position)
	{ return *products[position]; }

	// Function to set the quantity of all products in the list.
	void setquantity(int quantity)
	{
		for (int i = 0; i < total; i++)
		{
			products[i]->setquantity(quantity);
		}
	}

	// Overloaded subscript operator to access products by index.
	const Product *operator[](int index) const
	{
		if (index > total || index < 0)
			throw out_of_range("Out of range");
		return products[index];
	}

	// Overloaded assignment operator to assign one product list to another.
	Product_List &operator=(const Product_List &list)
	{
		if (this == &list)
			return *this;
		else
		{
			for (int i = 0; i < total; i++)
				delete products[i];
			delete[] products;
			size = list.size;
			total = list.total;
			products = new Product *[size];
			for (int i = 0; i < list.total; i++)
				products[i] = new Product(*list[i]);
			return *this;
		}
	}

	// Overloaded addition operator to concatenate two product lists.
	Product_List &operator+(const Product_List &list)
	{
		addback(list);
		return *this;
	}

	// Function to compare products by name in ascending order.
	void compare_by_name_ascend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getname() < product2->getname();
		});
	}

	// Function to compare products by name in descending order.
	void compare_by_name_descend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getname() > product2->getname();
		});
	}

	// Function to compare products by price in ascending order.
	void compare_by_price_ascend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getprice() < product2->getprice();
		});
	}

	// Function to compare products by price in descending order.
	void compare_by_price_descend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getprice() > product2->getprice();
		});
	}

	// Function to compare products by quantity in ascending order.
	void compare_by_quantity_ascend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getquantity() < product2->getquantity();
		});
	}

	// Function to compare products by quantity in descending order.
	void compare_by_quantity_descend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getquantity() > product2->getquantity();
		});
	}

	// Function to compare products by discount in ascending order.
	void compare_by_discount_ascend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getdiscount() < product2->getdiscount();
		});
	}

	// Function to compare products by discount in descending order.
	void compare_by_discount_descend()
	{
		sort(products, products + total, [](Product *product1, Product *product2)
		{
			return product1->getdiscount() > product2->getdiscount();
		});
	}

	// Friend function to print the product list.
	friend ostream &print(const Product_List &product_list);
};

// Overloaded stream insertion operator to print the product list.
ostream &print(const Product_List &product_list)
{
	for (int i = 0; i < product_list.total; i++)
	{
		print(*product_list[i]);
	}
	return cout;
}

#endif // PRODUCT_LIST_H