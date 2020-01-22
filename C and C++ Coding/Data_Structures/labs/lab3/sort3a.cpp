/Samuel Leonard
//Lab3
//2/7/16

// include header files needed
#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

template <typename Tdata>
void quicksort(vector<Tdata> &temp, int left, int right)
{
	srand(time(NULL));
	
	int pindex, i = 0, j = 0;
	int part_size, not_done = 1;

	part_size = (right - left);
	if (part_size == 0) {not_done = 0; pindex = left;}
	else 
	{
		pindex = (rand() % part_size) + left;
	}

	i = left;
	j = right;
	
	while(not_done == 1)
	{
		while(i <= j && i < right)
		{
			if (temp[i] < temp[pindex]) {++i;}
			else if (i == pindex) {++i;}
			else {break;}
		}
		while(i <= j && j > left)
		{
			if (temp[pindex] < temp[j]) {--j;}
			else if (j == pindex) {--j;}
			else {break;}
		}
		
		if(i >= j)
		{
			swap(temp[j], temp[pindex]);
			pindex = j;
			break;
		}
		else{swap(temp[i], temp[j]); ++i; --j;}
	}
	
	if(left < right)
	{
		if(pindex > left)
		{
			quicksort(temp, left, pindex - 1);
		}
		if(pindex < right)
		{
			quicksort(temp, pindex + 1, right);
		}
	}
}

template<typename Tdata>
void quicksort(vector<Tdata> &temp)
{
	quicksort(temp, 0, temp.size() - 1);
}

class record {
  public:
    record() {}
	string getfirstname(){return firstname;}
	string getlastname(){return lastname;}
	string getphonenum(){return phonenum;}
	void setfirstname(string name){firstname = name;}
	void setlastname(string name){lastname = name;}
	void setphonenum(string num){phonenum = num;}
	
	// implement overloaded operator< to
	// sort by lastname, firstname, phone number
	bool operator<(const record&)const;
	
	// friend declarations
	friend istream& operator>>(istream&, record&);
	friend ostream& operator<<(ostream&, const record&);

  private:
    string firstname;
    string lastname;
    string phonenum;
};

//Non-member functions
istream & operator>>(istream&, record&); 
ostream & operator<<(ostream&, const record&);

int main(int argc, char *argv[])
{	
	int i = 0;
	ifstream fin;
	record temp;
	vector<record> A;

	// open file
	fin.open(argv[1]);

	while (fin >> temp)
	{
		A.push_back(temp);
	}

	// close file
	fin.close();

	//sort data
	quicksort(A);
	//sort(A.begin(), A.end());
	
	// write data to stdout
	while(i < A.size())
	{
		cout << A[i];
		i++;
	}

	return 0;
}

istream & operator>>(istream &in, record &temp)
{
	return in >> temp.firstname >> temp.lastname >> temp.phonenum;
}

ostream & operator<<(ostream &out, const record &temp)
{
	string name;
	name = temp.lastname + " " + temp.firstname;
	return out << setw(24) << left << name << temp.phonenum << endl;
}

bool record::operator<(const record &temp)const
{
	if(lastname < temp.lastname){return true;}
	else if(lastname == temp.lastname)
	{
		if(firstname < temp.firstname){return true;}
		else if(firstname == temp.firstname)
		{
			if(phonenum < temp.phonenum){return true;}
			else {return false;}
		}
		else {return false;}
	}
	else {return false;}
}
