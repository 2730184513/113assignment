//
// Created by 邓初杰 on 24-5-14.
//

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H
#include "Product.h"

class Product_List
{
	int total = 0;
	int size = 0;
	Product** products;
public:
	Product_List() = delete;

	explicit Product_List(int size) : size(size)
	{
		products = new Product* [size];
		for (int i = 0; i < size; i++)
			products[i] = nullptr;
	}

	Product_List(Product_List& product_list) = default;

	Product_List(Product** product_list, int size)
	{
		this->size = size;
		products = new Product* [size];
		for (int i = 0; i < size; i++)
		{
			products[i] = product_list[i];
			total++;
		}
	}

	~Product_List()
	{
		delete[]products;
	}

	int gettotal()
	{ return total; }

	int getsize()
	{ return size; }

	Product** getproducts()
	{ return products; }

	void resize(int newsize)
	{
		Product** temp = new Product* [newsize];
		for (int i = 0; i < size; i++)
			temp[i] = products[i];
		if (newsize > size)
		{
			for (int i = size; i < newsize; i++)
				temp[i] = nullptr;
		}
		size = newsize;
		delete[] products;
		products = temp;
	}

	void addproduct(Product& product)
	{
		if (total == size)
			resize(size + 1);
		products[total] = &product;
		total++;
	}

	void addproduct(Product** product_list, int list_size)
	{
		if (size - total < list_size)
			resize(total + list_size);
		for (int i = 0; i < list_size; i++)
			addproduct(*product_list[i]);
	}

	void addproduct(Product_List& product_list)
	{
		int list_size = product_list.getsize();
		addproduct(product_list.getproducts(), list_size);
	}

	State remove_product(int position)
	{
		if (position < 0 && position > -size)
			position = size + position;
		else if ((position < 0 && position < -size) || position > size)
			throw out_of_range("Out of range");
		products[position] = nullptr;
		total--;
		return SUCCESS;
	}

	Product& operator [](int index)
	{
		if (index > size || (index < 0 && index < -size))
			throw out_of_range("Out of range");
		if (index >= 0)
		{
			if (products[index] == nullptr)
			{
				static Product empty;
				return empty;
			}
			else
				return *products[index];
		}
		else
		{
			if (products[size + index] == nullptr)
			{
				static Product empty;
				return empty;
			}
			else
				return *products[size + index];
		}
	}
};

#endif //PRODUCT_LIST_H
