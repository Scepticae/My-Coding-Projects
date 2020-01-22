//Name: Samuel Leonard
//Date: 1/19/16
//Lab 1
//Lab Time: 2:30-5:00 pm
#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>
#include <iomanip>

using namespace std;

//A stucture named ap_pair that holds the total amount and price
struct ap_pair
{
	double total_amount;
	double total_price;
};

//Reads in text info from stdin using redirect and computes the total amount
//and total price
ap_pair compute_total();

int main()
{
	ap_pair fruit_count;

	//Computes the total amount and price and returns them to an ap_pair 
	//structure
	fruit_count = compute_total();

	//Properly displays formatted info
	if (floor(fruit_count.total_amount) == fruit_count.total_amount)
	{
		cout << "Total amount = " << fruit_count.total_amount << endl;
	}
	else
	{
		cout << "Total amount = " << fixed << setprecision(2) << fruit_count.total_amount << endl;
	}

	cout << "Total price  = " << fixed << setprecision(2) << fruit_count.total_price << endl;

	return 0;
}

//Computes the total amount and price from the info from stdin
ap_pair compute_total()
{
	ap_pair fruit_talley;
	double amount, price;
	string fruit;

	while (cin >> fruit)
	{
		cin >> amount >> price;
		fruit_talley.total_amount += amount;
		fruit_talley.total_price += (amount * price);
	}

	return fruit_talley;
}
