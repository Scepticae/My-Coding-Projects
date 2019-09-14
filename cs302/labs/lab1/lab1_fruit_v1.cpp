//Name: Samuel Leonard
//User: sleonar5
//Date: 1/18/16
//Lab 1
//Lab Time: 2:30-5:00 pm

#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	//Variables to hold fruit info
	double amount = 0, price = 0, total_amount = 0, total_price = 0;
	string filename, fruit;

	//Reads in info from stdin using redirect
	while (cin >> fruit)
	{
		cin >> amount >> price;
		total_amount += amount;
		total_price += (amount * price);
	}

	//Displays the fruit totals in a properly formatted list
	if (floor(total_amount) == total_amount)
	{
		cout << "Total amount = " << total_amount << endl;
	}
	else
	{
		cout << "Total amount = " << fixed << setprecision(2) << total_amount << endl;
	}

	cout << "Total price  = " << fixed << setprecision(2) << total_price << endl;

	return 0;
}
