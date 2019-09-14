//Samuel Leonard
//Lab 7

#include<iostream>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<stack>
#include<utility>

using namespace std;

template<typename Tbuf>
class matrix 
{
	public:
		matrix(){buf = NULL;}
		~matrix(){if(buf) delete [] buf;}
		void assign(int new_rows, int new_cols)
		{
			Nrows = new_rows;
			Ncols = new_cols;
			buf = new Tbuf[Nrows*Ncols];
		}

		int get_Nrows()const{return Nrows;}
		int get_Ncols()const{return Ncols;}

		Tbuf *operator[](int i){return &buf[i*Ncols];}

	private:
		int Nrows, Ncols;
		Tbuf *buf;
};

class LCS 
{
	public:
		LCS():DELMOVE(1), INSMOVE(2), MATCHMOVE(0){}
		void text1_push_back(const char*);
		void text2_push_back(const char*);
		void compute_alignment();
		void show_alignment();

	private:
		vector<string> text1;
		vector<string> text2;
		vector<string>::iterator t1it;
		vector<string>::iterator t2it;
		matrix<int> cost;
		matrix<int> link;
		const int DELMOVE;
		const int INSMOVE;
		const int MATCHMOVE;
		
		// private member functions
		int matchCost(const string, const string);
		void show_alignment(int);
};

void LCS::text1_push_back(const char *in)
{
	//Declarations
	int check = 0;
	ifstream fin;
	string temp;
	
	//Open the input file
	fin.open(in);

	//Populate the text1 buffer
	while(1)
	{
		check = fin.peek();
		if(check == EOF){break;}
		getline(fin, temp);
		text1.push_back(temp);
	}

	//Close the input file
	fin.close();
}

void LCS::text2_push_back(const char *in)
{
	//Declarations
	int check = 0;
	ifstream fin;
	string temp;
	
	//Open the input file
	fin.open(in);

	//Populate the text2 buffer
	while(1)
	{
		check = fin.peek();
		if(check == EOF){break;}
		getline(fin, temp);
		text2.push_back(temp);
	}

	//Close the input file
	fin.close();
}

int LCS::matchCost(const string t1, const string t2)
{
	if(t1.compare(t2) == 0) return 1;
	else return 0;
}

void LCS::compute_alignment()
{
	//Declarations
	int i, j, t1_size, t2_size;
	int delcost, inscost, mcost;
	
	//Assign variables the sizes of the buffers
	t1_size = text1.size();
	t2_size = text2.size();
	
	//Insert "-" at the beginning of each buffer
	t1it = text1.begin();
	t2it = text2.begin();
	text1.insert(t1it, "-");
	text2.insert(t2it, "-");
	
	//Initialize the cost and link matrix
	cost.assign(text1.size(), text2.size());
	link.assign(text1.size(), text2.size());
	
	//Set 0 values to the first cell in the matrix for cost and link
	cost[0][0] = 0;
	link[0][0] = 0;
	
	//Initialize the Deletes and Insertions
	for(i = 1; i <= t1_size; i++)
	{
		cost[i][0] = cost[i-1][0] + 1;
		link[i][0] = DELMOVE;
	}
	for(j = 1; j <= t2_size; j++)
	{
		cost[0][j] = cost[0][j-1] + 1;
		link[0][j] = INSMOVE;
	}
	
	//Set cost and link for remainder of matrix
	for(i = 1; i <= t1_size; i++)
	{
		for(j = 1; j <= t2_size; j++)
		{
			//Evaluate for match or non-match
			mcost = matchCost(text1[i], text2[j]);
			if(mcost == 1){mcost = 0;}
			else {mcost = t1_size + t2_size;}
			cost[i][j] = cost[i-1][j-1] + mcost;
			link[i][j] = MATCHMOVE;
			
			//Check to see if delete cost is less and set link
			delcost = cost[i-1][j] + 1;
			if(delcost < cost[i][j])
			{
				cost[i][j] = delcost;
				link[i][j] = DELMOVE;
			}
			
			//Check to see if insert cost is less and set link
			inscost = cost[i][j-1] + 1;
			if(inscost < cost[i][j])
			{
				cost[i][j] = inscost;
				link[i][j] = INSMOVE;
			}
		}
	}
}

void LCS::show_alignment()
{
	//Declarations
	int grid_size;
	
	//Set grid size
	grid_size = text1.size() * text2.size();
	
	//Call Private Member Function Show Alignment
	show_alignment(grid_size);
}

void LCS::show_alignment(int grid_size)
{
	//Declarations
	int i, j, move;
	pair<int, int> indices;
	vector<int> seq;
	vector<pair<int, int> > line;
	vector<vector<int> > moves;
	vector<vector<pair<int, int> > > moved_lines;
	
	//Holds whether it is deletion insertion or match
	stack<pair<int, int> >temp;
	stack<int>type;
	
	//Set i and j to the matrix sizes
	i = text1.size();
	j = text2.size();

	//Push back the types of moves and corresponding lines
	while(grid_size != 0)
	{
		if(link[i][j] == MATCHMOVE)
		{
			type.push(MATCHMOVE);
			indices = make_pair(i, j);
			temp.push(indices);
			grid_size = ((i-1)*j) + (j-1);
			i = i-1;
			j = j-1;
		}
		else if(link[i][j] == DELMOVE)
		{
			type.push(DELMOVE);
			indices = make_pair(i, j);
			temp.push(indices);
			grid_size = ((i-1)*j) + j;
			i = i-1;
		}
		else
		{
			type.push(INSMOVE);
			indices = make_pair(i, j);
			temp.push(indices);
			grid_size = (i*j) + (j-1);
			j = j-1;
		}
	}
	
	//Extract the sequences off the stack
	while(!type.empty())
	{
		move = type.top();
		type.pop();
		if(move == MATCHMOVE)
		{
			temp.pop();
			if(!seq.empty())
			{
				moves.push_back(seq);
				moved_lines.push_back(line);
				seq.clear();
				line.clear();
			}
		}
		else if(move == DELMOVE)
		{
			seq.push_back(move);
			line.push_back(temp.top());
			temp.pop();
		}
		else
		{
			seq.push_back(move);
			line.push_back(temp.top());
			temp.pop();
		}
	}
	
	for(i = 0; i < (int)moves.size(); i++)
	{
		for(j = 0; j < (int)seq.size(); j++)
		{
			if(moves[i][j] == DELMOVE)
			{
				cout << "< " << text1[moved_lines[i][j].second] << endl;
			}
			if(moves[i][j] == INSMOVE)
			{
				cout << "> " << text2[moved_lines[i][j].second] << endl;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	// check two input files are specified on command line
	if(argc < 3)
	{
		cerr << "Not enough arguments on the command line." << endl;
	}

	// instantiate your "lcs based diff" object
	LCS lcs;

	// read the text from file1 into the lcs.text1 buffer
	lcs.text1_push_back(argv[1]);

	// read the text from file2 into the lcs.text2 buffer
	lcs.text2_push_back(argv[2]);
	
	// cout << "Sorry was not able to get it to print." << endl;

	//Compute the alignment of the strings
	lcs.compute_alignment();

	//Show the alignment of the strings
	lcs.show_alignment();
	
	return 0;
}
