//Name: Samuel Leonard
//Lab: Lab 3b
//Date: Feb 15 2016
//Lab Time: 2:30 - 5:30

//Include header files needed
#include<iostream>
#include<cstdlib>
#include<cmath>
#include<string>
#include<iomanip>
#include<algorithm>
#include<ctime>
#include<vector>
#include<fstream>
#include<cstring>

using namespace std;

//Smart pointer class 
template <typename T>
class sptr 
{
	public:
		//Constructor
		sptr(T *_ptr = NULL) { ptr = _ptr; }
		
		//Overloads the less than operator
		bool operator<(const sptr &rhs)const
		{
			return *ptr < *rhs.ptr;
		}
		
		//Overloads the * operator for dereferencing
		operator T*()const {return ptr; }
		
	private:
		//Template type pointer
		T *ptr;
};

//Slist class to hold a list of some data
template <class T>
class slist 
{
	private:
		struct node 
		{
			//Constructor
			node() { data=T(); next=NULL; }

			// add overloaded operator< code
			bool operator<(const node &rhs)const
			{
				return data < rhs.data;
			}
			//Generic type that holds data
			T data;
			//Points to the next node
			node *next;
		};

	//Iterator class to allow accessing a list
	public:
		class iterator 
		{
			public:
				//Constructor
				iterator() : p(NULL) {}
				//Overloads the * operator for dereferencing
				T & operator*() { return p->data; }
				//Overloads the ++ operator to increment through the list
				iterator & operator++() { p = p->next; return *this; }
				//Overloads the != operator for controlling loop
				bool operator!=(const iterator & rhs) const { return p != rhs.p; }

			private:
				friend class slist<T>;
				iterator(node *p) : p(p) {}
				node *p;
		};

	public:
		slist(); //Calls consructor
		~slist(); //Calls destructor

		void push_back(const T &);
		void sort();

		//Iterator functions for list
		iterator begin() { return iterator(head->next); }
		iterator end() { return iterator(NULL); }

	private:
		node *head;
		node *tail;
};

//Function that initializes the list
template <typename T>
slist<T>::slist()
{
    head = new node();
    tail = head;
}

//Function that deletes the linked list
template <typename T>
slist<T>::~slist()
{
    while (head->next != NULL) 
	{
      node *p = head->next;
      head->next = p->next;
      delete p;
    }
	
    delete head;
    
    head = NULL;
    tail = NULL;
}

//Function to populate linked list
template <typename T>
void slist<T>::push_back(const T &din)
{
    tail->next = new node;
    tail = tail->next;
    tail->data = din;
}

//Function to sort the list
template <typename T>
void slist<T>::sort()
{
	int i = 0;
	vector<sptr<node> > Aptr;
	node *temp;

	// set up smart pointer array for list
	temp = head->next;
	while(temp != NULL)
	{
		Aptr.push_back(temp);
		temp = temp->next;
	}

	// apply std::sort
	std::sort(Aptr.begin(), Aptr.end());

	// relink linked list using sort result
	temp = head;
	while(i < Aptr.size())
	{
		temp->next = Aptr[i];
		temp = temp->next;
		i++;
	}
	temp->next = NULL;
}

//class record
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

//This function overloads the insertion operator to be able to read in
//all elements of a record at once.
istream & operator>>(istream &in, record &temp)
{
	return in >> temp.firstname >> temp.lastname >> temp.phonenum;
}

//This function overloads the extraction operator to output the elements
//of a record in proper format all at once.
ostream & operator<<(ostream &out, const record &temp)
{
	string name;
	name = temp.lastname + " " + temp.firstname;
	return out << setw(24) << left << name << temp.phonenum << endl;
}

//This function overloads the less than operator so that records can be
//compared when called in the quicksort function
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

int main(int argc, char *argv[])
{
	//Variables
	size_t check;
	string file;
	record temp;
	ifstream fin;
	slist<record> A; //Holds list of records
	slist<record>::iterator ait; //Allows for iteration of list
	
	//Parse command-line argument
	//Checks number of arguments
	if(argc != 2)
	{
		cerr << "No file name was entered." << endl;
		exit(1);
	}

	//Checks to make sure file entered is a text file
	file = argv[1];
	check = file.find(".txt");
	if(check == string::npos)
	{
		cerr << "File entered should be a text file." << endl;
		exit(1);
	}

	//Open file
	fin.open(argv[1]);
	
	//Check that file opened successfully
	if(fin.fail())
	{
		cerr << "The file entered does not exist." << endl;
		exit(1);
	}
 
	//Read data/store data
	while(fin >> temp)
	{
		A.push_back(temp);
	}
	
	//Close file
	fin.close();

	//Sort data
	A.sort();
	
	//Write data to stdout (slist iterator based)
	ait = A.begin();
	while(ait != A.end())
	{
		cout << *ait;
		++ait;
	}
	
	return 0;
}
