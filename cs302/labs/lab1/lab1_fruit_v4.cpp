//Name: Samuel Leonard
//Date: 1/20/16
//Lab 1
//Lab Time: 2:30-5:00 PM
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <cmath>

using namespace std;

//A structure named ap_pair that contains a fruits total amount and total price
struct ap_pair
{
	double total_amount;
	double total_price;
};

//A class named APC that reads in a file, computes the info total and display
//the info in a formatted list
class APC
{
	private:
		ifstream fin;
		ap_pair fruit_talley;
	public:
		APC(char*);
		void compute_total();
		void print_total();
		~APC();
};

int main(int argc, char *argv[])
{
	APC fruit_count(argv[1]);

	//Computes and prints out total amount and price
	fruit_count.compute_total();
	fruit_count.print_total();

	return 0;
}

//APC constructor that opens an input file
APC::APC(char* filename)
{
	fin.open(filename);
	if (fin.fail())
	{
		cout << "Error opening file." << endl;
		exit(0);
	}
}

//APC member function that computes the total amount and price
void APC::compute_total()
{
	double amount, price;
	string fruit;
	
	while (fin >> fruit)
	{
		fin >> amount >> price;
		fruit_talley.total_amount += amount;
		fruit_talley.total_price += (amount * price);
	}
}

//APC member function that prints out fruit total by count or weight in a
//formatted list
void APC::print_total()
{
	if (floor(fruit_talley.total_amount) == fruit_talley.total_amount)
	{
		cout << "Total amount = " << fruit_talley.total_amount << endl;
	}
	else
	{
		cout << "Total amount = " << fixed << setprecision(2) << fruit_talley.total_amount << endl;
	}

	cout << "Total price  = " << fixed << setprecision(2) << fruit_talley.total_price << endl;
}

//APC destructor that closes the input file
APC::~APC()
{
	fin.close();
}
