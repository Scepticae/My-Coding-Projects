//Name: Samuel Leonard
//Date: 1/20/16
//Lab 1
//Lab Time: 2:30-5:00 pm
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

//A structure called ap_pair that holds the total amount and total price
//for fruit info
struct ap_pair
{
	double total_amount;
	double total_price;
};

//A function that uses fruit info and computes the total amount and price and
//returns it to an ap_pair structure
ap_pair compute_total(char*);

int main(int argc, char *argv[])
{
	ap_pair fruit_count;//ap_pair structure
	
	if (argc == 0)
	{
		cout << "No file was entered." << endl;
		exit(0);
	}

	//Reads in a file from the command line and computes the infos totals
	fruit_count = compute_total(argv[1]);

	//Displays the totals in a formatted list
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

//Reads in a file from the command line and computes the totals, returns the
//info to a structure
ap_pair compute_total(char* filename)
{
	ap_pair fruit_talley;
	double amount, price;
	string fruit;
	ifstream fin;

	fin.open(filename);

	if (fin.fail())
	{
		cout << "Error opening file." << endl;
		exit(0);
	}

	while (fin >> fruit)
	{
		fin >> amount >> price;
		fruit_talley.total_amount += amount;
		fruit_talley.total_price += (amount * price);
	}

	fin.close();

	return fruit_talley;
}
