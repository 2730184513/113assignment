//
// Created by 邓初杰 on 24-5-14.
//

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "Product.h"

Product const Empty;

class Product_List
{
protected:
	int size = 0;
	int total = 0;
	Product **products;

public:
	Product_List() : size(20)
	{
		products = new Product *[size];
		for (int i = 0; i < size; i++)
			products[i] = nullptr;
	}

	explicit Product_List(int size) : size(size)
	{
		products = new Product *[size];
		for (int i = 0; i < size; i++)
			products[i] = nullptr;
	}

	Product_List(const Product_List &product_list)
	{
		size = product_list.size;
		products = new Product *[size];
		addback(product_list);
	}

	Product_List(const Product *product_list, int size)
	{
		this->size = size * 2;
		products = new Product *[this->size];
		addback(product_list, size);
	}

	Product_List(const Product *const *const product_list, int size)
	{
		this->size = size * 2;
		products = new Product *[this->size];
		addback(product_list, size);
	}

	~Product_List()
	{
		for (int i = 0; i < total; i++)
			delete products[i];
		delete[] products;
	}

	int gettotal() const
	{ return total; }

	bool is_empty() const
	{
		if (total == 0)
			return true;
		else
			return false;
	}

	void swap(int position1, int position2)
	{
		Product *temp = products[position1];
		products[position1] = products[position2];
		products[position2] = temp;
	}

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

	void addback(const Product *const product_list, int list_size)
	{
		for (int i = 0; i < list_size; i++)
			addback(product_list[i]);
	}

	void addback(const Product *const *const product_list, int list_size)
	{
		for (int i = 0; i < list_size; i++)
			addback(*product_list[i]);
	}

	void addback(const Product_List &product_list)
	{
		int list_size = product_list.size;
		addback(product_list.products, list_size);
	}

	void insert(Product &product, int position)
	{
		total++;
		for (int i = total; i >= position; i--)
			products[i] = products[i - 1];
		products[position] = &product;
	}

	void pop()
	{ products[--total] = nullptr; }

	const Product &front()
	{
		if (total == 0)
			return Empty;
		return *products[0];
	}

	const Product &back()
	{
		if (total == 0)
			return Empty;
		return *products[total - 1];
	}

	void clear()
	{
		for (int i = 0; i < total; i++)
			products[i] = nullptr;
		total = 0;
	}

	void remove(int position)
	{
		if (position < 0 || position >= total)
			throw out_of_range("Out of range");
		products[position] = nullptr;
		total--;
		for (int i = position; i <= total; i++)
			products[i] = products[i + 1];
	}

	const Product *operator[](int index) const
	{
		if (index > total || index < 0)
			throw out_of_range("Out of range");
		return products[index];
	}

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

	Product_List &operator+(const Product_List &list)
	{
		addback(list);
		return *this;
	}

	friend ostream &print(const Product_List &product_list);
};

ostream &print(const Product_List &product_list)
{
	for (int i = 0; i < product_list.total; i++)
	{
		print(*product_list[i]) << endl;
	}
	return cout;
}

#endif //PRODUCT_LIST_H
