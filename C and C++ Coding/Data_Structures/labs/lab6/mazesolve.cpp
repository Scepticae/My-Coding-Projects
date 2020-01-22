//Samuel Leonard
//Lab 6
//sleonar5

#include<iostream>
#include<vector>
#include<stack>

using namespace std;

typedef enum {WHITE, GRAY, BLACK} vcolor_t;

class node
{
	public:
		int v;
		bool visited;
		vector<int>edges;
		node();
};

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

//Removes all the wall edges
void remove_edges(vector<vector<int> > &edges, int v1, int v2)
{
	for(int i = 0; i < edges[v1].size(); i++)
	{
		if(edges[v1][i] == v2)
		{
			edges[v1].erase(edges[v1].begin() + i);
			break;
		}
	}
	for(int i = 0; i < edges[v2].size(); i++)
	{
		if(edges[v2][i] == v1)
		{
			edges[v2].erase(edges[v2].begin() + i);
			break;
		}
	}
}

vector<int> dfs(vector<vector<int> > edges)
{
	//Declarations
	int i, k, num;
	bool more = false;
	vector<vcolor_t> vcolor;
	vector<int> path;
	stack<int> V;
	
	//Initialize vcolor_t
	vcolor.assign(edges.size(), WHITE);
	
	//Start Search from source to sink
	V.push(0);
	while(!V.empty())
	{
		i = V.top();
		if(vcolor[i] == WHITE)
		{
			vcolor[i] = GRAY;
			if(i == edges.size()){cout << "test" << endl; break;}
		}
		if(vcolor[i] == GRAY)
		{
			for(k = 0; k < edges[i].size(); k++)
			{
				num = edges[i][k];
				if(vcolor[num] == WHITE)
				{
					more = true;
				}
			}
			if(more == false)
			{
				vcolor[i] = BLACK;
				V.pop();
				continue;
			}
			else{more = false;}
		}
		if(edges[i].size() == 0)
		{
			vcolor[i] = BLACK;
			V.pop();
			continue;
		}
		for(k = (edges[i].size()-1); k >= 0; k--)
		{
			num = edges[i][k];
			if(vcolor[num] == WHITE)
			{
				V.push(edges[i][k]);
			}
		}
	}
	while(!V.empty())
	{
		i = V.top();
		if(vcolor[i] == GRAY)
		{
			path.push_back(i);
			V.pop();
		}
		else
		{
			V.pop();
		}
	}
	
	return path;
}

//Prints the pathway through the maze
void print(vector<int> vert, int nRows, int nCols)
{
	cout << "PATH " << nRows << " " << nCols << endl;
	for (int i = 0; i < vert.size(); i++)
	{		
		cout << vert[i] << endl;
	}
}

int main(int argc, char *argv[])
{
	//Declarations
	int i, j, rows, cols, total;
	string title;
	vector<vector<int> > edges;
	vector<int> v;

	//Read in header and rows and columns
	cin >> title >> rows >> cols;
	total = rows*cols;
	
	//Create Adjacency List
	edges = adj_list(rows, cols);
	
	//Read in text file
	while(!cin.eof())
	{
		//Read in components
		cin >> i >> j;
		
		//Remove edges that correspond to walls
		remove_edges(edges, i, j);
	}
	
	//Perform Depth-First-Search
	v = dfs(edges);
	
	//Print non-wall edges
	print(v, rows, cols);
	
	return 0;
}
		
		
