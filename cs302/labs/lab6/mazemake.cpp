//Samuel Leonard
//CS302 Lab 6
//sleonar5

#include<iostream>
#include<vector>
#include<map>
#include<cstdlib>
#include<ctime>

using namespace std;

//Node that contains a rank and a root
struct node
{
	int rank;
	int parent;
	node() { rank = 0; parent = -1; }
};

//Disjoint set for the graph formation
class djset
{
public:
	djset(int);
	int get_size() { return Nsets; }
	bool merge(int, int);
	int find(int);
	node get_node(int i) { return sets[i]; }
private:
	int Nsets;
	vector<node> sets;
};

//Constructor for the disjoint set
djset::djset(int n)
{
	if (n > 0)
	{
		sets.insert(sets.end(), n, node());
		Nsets = n;
	}
}

bool djset::merge(int i, int j)
{
	//Declarations
	bool merged;
	i = find(i);
	j = find(j);

	if (i != j)
	{
		merged = true;
		node &seti = sets[i];
		node &setj = sets[j];

		//Merge the sets
		if (seti.rank > setj.rank) { setj.parent = i; }
		else if (seti.rank < setj.rank) { seti.parent = j; }
		else { setj.parent = i; seti.rank += 1; }

		Nsets -= 1;
	}
	else { merged = false; }

	return merged;
}

int djset::find(int i)
{
	if (sets[i].parent == -1) { return i; }

	//Recursively call for path compression
	sets[i].parent = find(sets[i].parent);
	return sets[i].parent;
}

//Create adjacency list
vector<vector<int> > adj_list(int rows, int cols)
{
	//Declarations
	int i;
	vector<int> adj_edge;
	vector<vector<int> > edges;

	//Fill the adjacency list
	for (i = 0; i < (rows*cols); i++)
	{
		//Checks for 0 column
		if ((i%cols) == 0)
		{
			//Check Above
			if ((i - cols) >= 0) { adj_edge.push_back(i - cols); }
			//Add right
			adj_edge.push_back(i + 1);
			//Check Below
			if ((i + cols) < (rows*cols)) { adj_edge.push_back(i + cols); }
		}
		//Check for last column
		else if (((i%cols) - (cols - 1)) == 0)
		{
			//Check Above
			if ((i - cols) > 0) { adj_edge.push_back(i - cols); }
			//Add left
			adj_edge.push_back(i - 1);
			//Check Below
			if ((i + cols) < (rows*cols)) { adj_edge.push_back(i + cols); }
		}
		else
		{
			//Check Above
			if ((i - cols) > 0) { adj_edge.push_back(i - cols); }
			//Add Left
			adj_edge.push_back(i - 1);
			//Add right
			adj_edge.push_back(i + 1);
			//Check Below
			if ((i + cols) < (rows*cols)) { adj_edge.push_back(i + cols); }
		}

		//Fill edges with adj_edges and empty the adj_edges vector
		edges.push_back(adj_edge);
		adj_edge.clear();
	}

	return edges;
}

//Removes the walls from the adjacency list
void find_walls(vector<vector<int> > &adj_list, int total)
{
	//Declarations
	int v, e, num;
	int num_sets = total;
	bool merged;

	//Seed the Random Number Generator
	srand(time(NULL));

	//Initialize the field for the disjoint set
	djset dset(total);

	//Continue until all disjoint sets have been condensed to one
	while (num_sets > 1)
	{
		v = rand() % adj_list.size();
		if (adj_list[v].size() != 0)
		{
			e = rand() % adj_list[v].size();
			num = adj_list[v][e];
			merged = dset.merge(v, num);

			//Removes edge from list if merged
			if (merged)
			{
				adj_list[v].erase(adj_list[v].begin() + e);
				for (int i = 0; i < adj_list[num].size(); i++)
				{
					if (adj_list[num][i] == v)
					{
						adj_list[num].erase(adj_list[num].begin() + i);
						break;
					}
				}
			}

			//Update the number of sets
			num_sets = dset.get_size();
		}
	}
}

int main(int argc, char *argv[])
{
	//Declarations
	int nRows, nCols, total;
	vector<vector<int> > edges;
	vector<int> adj;

	//Initialize nRows and nCols
	nRows = atoi(argv[1]);
	nCols = atoi(argv[2]);
	total = nRows*nCols;

	//Set the adjacency list
	edges = adj_list(nRows, nCols);

	//Find the walls in the list
	find_walls(edges, total);

	//Print Walls
	cout << "MAZE " << nRows << " " << nCols << endl;
	for (int i = 0; i < edges.size(); i++)
	{
		adj = edges[i];
		if (adj.size() != 0)
		{
			for (int j = 0; j < adj.size(); j++)
			{
				//Print only wall i, j and not wall j, i since they are
				//the same wall
				if (adj[j] > i)
				{
					cout << i << " " << adj[j] << endl;
				}
			}
		}
	}

	return 0;
}