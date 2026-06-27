
HEADER FILE:
#pragma once
#include <iostream>
#include <string>
using namespace std;

template <class T, class U>
class Inventory{
private:
	string* name;
	T* quantity;
	U* price;
	int count;

public:
	Inventory();
	~Inventory();
	void addProduct(string n, T q, U p);
	void display();
	template <class T, class U>
	friend T getTotalQuantity(Inventory<T, U>& inv);
	template <class T, class U>
	friend U getTotalValue(Inventory<T, U>& inv);
	template <class T, class U>
	friend void displayAboveThreshold(Inventory<T, U>& inv, U t);
};
#include"inventory.cpp"
IMPLEMENTATION FILE:
#include "inventory.h"
template <class T, class U>
Inventory<T, U>::Inventory()
{
	count = 0;
	name = new string[50];
	quantity = new T[50];
	price = new U[50];
}
template <class T, class U>
Inventory<T, U>::~Inventory()
{
	delete[] name;
	delete[] quantity;
	delete[] price;
}

template <class T, class U>
void Inventory<T, U>::addProduct(string n, T q, U p)
{
	if (count < 50)
	{
		name[count] = n;
		quantity[count] = q;
		price[count] = p;
		count++;
	}
	else
	{
		cout << "NO SPACE." << endl;
	}
}
template <class T, class U>
void Inventory<T, U>::display()
{
	for (int i = 0; i < count; i++)
	{
		cout << "Name: " << name[i] << endl;
		cout << "Quantity: " << quantity[i] << endl;
		cout << "Price: " << price[i] << endl;
	}
}
template <class T, class U>
T getTotalQuantity(Inventory<T, U>& inv)
{
	T total = 0;
	for (int i = 0; i < inv.count; i++)
	{
		total += inv.quantity[i];
	}
	return total;
}
template <class T, class U>
U getTotalValue(Inventory<T, U>& inv)
{
	U total = 0;
	for (int i = 0; i < inv.count; i++)
	{
		total = total + (inv.quantity[i] * inv.price[i]);
	}
	return total;
}
template <class T, class U>
void displayAboveThreshold(Inventory<T, U>& inv, U t)
{
	for (int i = 0; i < inv.count; i++)
	{
		U value = inv.quantity[i] * inv.price[i];

		if (value > t)
		{
			cout << inv.name[i]<< " :Total Value: "<< value << endl;
		}
	}
}
MAIN FILE:
#include "inventory.h"

int main()
{
	Inventory<int, float> electronics;
	electronics.addProduct("TV",1,50000);
	electronics.addProduct("WASHING MACHINE", 2, 50000);
	electronics.addProduct("AC", 3,50000);
	cout << "ELECTRONICS" << endl;
	electronics.display();
	cout << "Total Quantity: "<< getTotalQuantity(electronics) << endl;
	cout << "Total Inventory Value: "<< getTotalValue(electronics) << endl;
	displayAboveThreshold(electronics, 20000.0f);
	Inventory<float, float> groceries;
	groceries.addProduct("WHEAT", 20.f, 280.0f);
	groceries.addProduct("RICE", 12.0f, 180.0f);
	cout << "GROCERIES" << endl;
	groceries.display();
	cout << endl;
	cout << "Total Quantity: " << getTotalQuantity(groceries) << endl;
	cout << "Total Inventory Value: " << getTotalValue(groceries) << endl;
	Inventory<int, float>clothing;
	clothing.addProduct("LV", 3, 500000);
	clothing.addProduct("GUCCI", 4, 500000);
	cout << "CLOTHING" << endl;
	clothing.display();
	cout << "Total Quantity: "<< getTotalQuantity(clothing) << endl;
    cout << "Total Inventory Value: "<< getTotalValue(clothing) << endl;
	system("pause");
	return 0;
}
