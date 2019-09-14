//Name: Samuel Leonard
//Date: 1/20/16
//Lab1
//Lab Time: 2:30-5:00 PM
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>

using namespace std;

//ap_pair object that holds a total amount and total price
//for the fruit count.
struct ap_pair
{
	double total_amount;
	double total_price;

	//Overloads the += operator to add a new total to a previous
	//total for an ap_pair structure
	ap_pair& operator+=(const ap_pair&);
};

//APC class that can read in a file and set its fruit name, amount and price
class APC
{
private:
	ifstream fin;
	ap_pair fruit_talley;
	ap_pair *fruit_subT;
	string fruit;
	double amount, price;
public:
	APC(char*);//constructor
	map<string, ap_pair*> ind_fruit;
	map<string, ap_pair*>::iterator mit;
	void compute_total();//adds up all the amounts and prices
	void print_summary();//prints out a subtotal and totals
	~APC();//destructor
};

int main(int argc, char *argv[])
{
	APC fruit_count(argv[1]);

	//Displays the properly formatted fruit info
	fruit_count.compute_total();
	fruit_count.print_summary();

	return 0;
}

//Default constructor for the APC class that takes only one argument
//which is the name of the input file.
APC::APC(char* filename)
{
	fin.open(filename);
	if (fin.fail())
	{
		cerr << "Error opening file." << endl;
		exit(1);
	}
}

//Member function that reads all the info from a file and calculates the
//fruit subtotals and totals
void APC::compute_total()
{
	while (fin >> fruit)
	{
		fin >> amount >> price;

		//Initializes a new ap_pair with each read
		fruit_subT = new ap_pair;

		//Initializes the variables of the ap_pair
		fruit_subT->total_amount = amount;
		fruit_subT->total_price = (amount * price);

		//Uses the overloaded operator to add the variables of the
		//two ap_pairs
		fruit_talley += *fruit_subT;

		//Searches the map to see if fruit is in the map, if it isnt
		//the fruit is inserted into the map, if it already exists then
		//only the totals are updated
		mit = ind_fruit.find(fruit);
		if (mit == ind_fruit.end())
		{
			ind_fruit.insert(make_pair(fruit, fruit_subT));
		}
		else
		{
			//uses the overloaded operator again to add to the total already
			//in the present ap_pair with the keyed map position
			*mit->second += *fruit_subT;
		}
	}
}

//A member function that properly displays the fruits info in a formatted list
void APC::print_summary()
{
	for (mit = ind_fruit.begin(); mit != ind_fruit.end(); mit++)
	{
		cout << setw(14) << left << mit->first << setw(8) << right << fixed << setprecision(2)
			<< mit->second->total_amount << setw (9) << mit->second->total_price << endl;	
	}
	
	cout << setw(15) << left << "\nTotals:" << setw(8) << fixed << setprecision(2) 
		<< right << fruit_talley.total_amount << setw(9) << fruit_talley.total_price << endl;
}

//An ap_pair member function that overloads the += operator to update an
//existing ap_pair total and amount
ap_pair& ap_pair::operator+=(const ap_pair &a)
{
	this->total_amount = this->total_amount + a.total_amount;
	this->total_price = this->total_price + a.total_price;

	return *this;
}

//APC member destructor, closes the input file
APC::~APC()
{
	fin.close();
}
