//Samuel Leonard
//sleonar5
//Lab 5

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
#include<cmath>
#include<string>
#include<sstream>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<utility>
#include<set>

using namespace std;

typedef set <int> jvals;

//A class that holds city information and ways of accessing it
class city
{
private:
	string name;
	string type;
	float latitude;
	float longitude;
	int population;
public:
	city();
	string get_name() { return name; }
	string get_type() { return type; }
	float get_lat() { return latitude; }
	float get_long() { return longitude; }
	int get_pop() { return population; }
	void convertRad(float, float);
	void convertDeg(float, float);
	friend istream &operator>>(istream &, city &);
	friend ostream &operator<<(ostream &, const city &);
};

//A class that computes distance and stores it in a table
class dtable
{
private:
	vector<int> distance;
public:
	dtable() {}
	void computeD(vector<city>);
	int operator()(int i, int j)
	{
		if (j>i) { swap(i, j); }
		return distance[((i*(i + 1)) / 2) + j];
	}
};

//Default constructor
city::city()
{
	name = "";
	type = "";
	latitude = 0.0;
	longitude = 0.0;
	population = 0;
}

//Converts radians to degrees
void city::convertRad(float lat, float lon)
{
	latitude = lat*(180 / M_PI);
	longitude = lon*(180 / M_PI);
}

//Converts degrees to radians
void city::convertDeg(float lat, float lon)
{
	latitude = lat*(M_PI / 180);
	longitude = lon*(M_PI / 180);
}

//Overloads the insertion operator in order to read data in
//more simply
istream &operator>>(istream &in, city &temp)
{
	return in >> temp.name >> temp.type >> temp.latitude
		>> temp.longitude >> temp.population;
}

//This overloads the extraction operator so that the city info can be
//output simply
ostream &operator<<(ostream &out, const city &temp)
{
	return out << setw(20) << left << temp.name << setw(9) << temp.type
		<< setw(10) << right << temp.population << setw(8) << setprecision(2)
		<< fixed << temp.latitude << setw(8) << setprecision(2) << fixed <<
		temp.longitude << endl;
}

//This computes the distance in miles rounded to the nearest 5 and stores
//it in an array
void dtable::computeD(vector<city> temp)
{
	int whole = 0, size = 0;
	float dlat = 0.0, dlon = 0.0, change = 0.0;
	float dist = 0.0;

	size = temp.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j <= i; j++)
		{
			//Computes the difference in latitude and longitude
			dlat = temp[j].get_lat() - temp[i].get_lat();
			dlon = temp[j].get_long() - temp[i].get_long();

			//Compute distance using haversine formula
			dist = 7964 * asin(sqrt(pow(sin(dlat / 2), 2) + (cos(temp[i].get_lat())*
				cos(temp[j].get_lat())*pow(sin(dlon / 2), 2))));

			//Round value to nearest 5
			whole = ((int)floor(dist) % 5);
			change = dist - floor(dist) + whole;
			if (change < 2.5) { distance.push_back(dist - change); }
			else { distance.push_back(dist + (5 - change)); }
		}
	}
}

//Set the graph up
map<int, jvals*> set_city_adj(vector<city> temp, dtable dist)
{
	int i, j, jset = 0, k = 0, size = 0;
	jvals *m;
	vector<int>local;
	vector<int>regional;
	vector<int>global;
	pair<int, jvals*>edge;
	map<int, jvals*>graph;
	map<int,jvals*>::iterator jit;

	//Extract lists of all three types
	size = temp.size();
	for (i = 0; i < size; i++)
	{
		if (temp[i].get_type() == "LOCAL")
		{
			local.push_back(i);
		}
		else if (temp[i].get_type() == "REGIONAL")
		{
			regional.push_back(i);
		}
		else
		{
			global.push_back(i);
		}
	}

	//Set the edges for the graph
	size = temp.size();
	for (i = 0; i < size; i++)
	{
		if (i == 0) { m = new jvals; }
		else
		{
			jit = graph.find(i);
			if (jit == graph.end())
			{
				m = new jvals;
			}
			else { m = jit->second; }
		}
		if (temp[i].get_type() == "LOCAL")
		{
			//Iterate through local distances
			size = local.size();
			for (j = 0; j < size; j++)
			{
				if (dist(i, local[j]) < 500 && dist(i, local[j]) > 0)
				{
					m->insert(local[j]);
				}
			}

			//Reset K
			k = 20000;

			//Iterate through regional distances
			size = regional.size();
			for (j = 0; j < size; j++)
			{
				if (dist(i, regional[j]) < k)
				{
					k = dist(i, regional[j]);
					jset = regional[j];
				}
			}
			//Set the closest regional to current local and set that
			//local to the regional
			m->insert(jset);
			edge = make_pair(i, m);
			graph.insert(edge);

			jit = graph.find(jset);
			if (jit == graph.end())
			{
				m = new jvals;
			}
			else { m = jit->second; }
			
			m->insert(i);
			edge = make_pair(jset, m);
			graph.insert(edge);
		}
		else if (temp[i].get_type() == "REGIONAL")
		{
			//Iterate through regional to regional
			size = regional.size();
			for (j = 0; j < size; j++)
			{
				if (dist(i, regional[j]) < 1000 && dist(i, regional[j]) > 0)
				{
					m->insert(regional[j]);
				}
			}

			//Reset k
			k = 20000;

			//Iterate through global distances
			size = global.size();
			for (j = 0; j < size; j++)
			{
				if (dist(i, global[j]) < k)
				{
					k = dist(i, global[j]);
					jset = global[j];
				}
			}
			//Set the closest global to current regional and that regional
			//to that global
			m->insert(jset);
			edge = make_pair(i, m);
			graph.insert(edge);

			jit = graph.find(jset);
			if (jit == graph.end())
			{
				m = new jvals;
			}
			else { m = jit->second; }

			m->insert(i);
			edge = make_pair(jset, m);
			graph.insert(edge);
		}
		else
		{
			//Iterate through global to global distance
			size = global.size();
			for (j = 0; j < size; j++)
			{
				if (dist(i, global[j]) < 5200 && dist(i, global[j]) > 0)
				{
					m->insert(global[j]);
				}
			}

			edge = make_pair(i, m);
			graph.insert(edge);
		}
	}
	//Return the Graph
	return graph;
}

//Reads in the city information and stores it in a vector
vector<city> read_city_info(int &tot_pop, int &w)
{
	int temp_size = 0;
	string temp;
	ifstream fin;
	char check;
	city C;
	vector<city> cities;

	fin.open("city_list.txt");

	while (1)
	{
		check = fin.peek();
		if (check == '#')
		{
			fin.ignore(1000, '\n');
		}
		else if (check == EOF) { break; }
		else
		{
			fin >> C;

			//Check Biggest Word Size
			temp = C.get_name();
			temp_size = temp.size();
			if (temp_size > w) { w = temp_size; }

			//accumulate population
			tot_pop += C.get_pop();
			C.convertDeg(C.get_lat(), C.get_long());
			cities.push_back(C);
			fin.get();
		}
	}

	fin.close();

	return(cities);
}

//Writes the city info to std out
void write_city_info(vector<city> temp, int tot_pop)
{
	int size = 0;
	ofstream fout;

	//Open the output file
	fout.open("city_info.txt");

	//Writes City Info
	fout << "CITY LIST (N=" << temp.size() << " Population=" << tot_pop
		<< "):" << endl << endl;
	size = temp.size();
	for (int i = 0; i < size; i++)
	{
		temp[i].convertRad(temp[i].get_lat(), temp[i].get_long());
		fout << setw(3) << right << i << " ";
		fout << temp[i];
	}

	//Close the output file
	fout.close();
}

//Writes the distance table
void write_city_dtable(vector<city>temp, int w, dtable dmatrix)
{
	int i, j, size = 0;
	string word1, word2, dist, text;
	ofstream fout;

	//Open the output file
	fout.open("city_dtable.txt");

	//Print dtable Header;
	fout << "DISTANCE TABLE:" << endl << endl;

	//Print Distance Table
	size = temp.size();
	for (i = 0; i < size; i++)
	{
		for (j = 0; j <= i; j++)
		{
			word1 = temp[i].get_name();
			word2 = temp[j].get_name();

			if (dmatrix(i, j) == 0) {}
			else
			{
				text = word1 + " to " + word2 + " ";

				fout << setw(3) << right << i << " " << setw(2 * w + 4) << left << setfill('.')
					<< text << setw(5) << right << setfill(' ') << dmatrix(i, j)
					<< " miles" << endl;
			}
		}
		fout << endl;
	}

	//Close the output file
	fout.close();
}

//Write the city graph to output file
void write_city_graph(map<int, jvals*>graph, vector<city>temp, dtable dist)
{
	//Declarations
	ofstream fout;
	map<int, jvals*>::iterator grit;
	jvals *indices;
	jvals::iterator jit;

	//Open the output file
	fout.open("city_graph.txt");

	//Write Header
	fout << "CITY GRAPH:" << endl << endl;
	//Write the graph data to file
	for (grit = graph.begin(); grit != graph.end(); grit++)
	{
		fout << setw(3) << right << grit->first << " " << temp[grit->first].get_name() << endl;
		indices = grit->second;
		for (jit = indices->begin(); jit != indices->end(); jit++)
		{
			fout << setw(5) << right << *jit << " " << temp[*jit].get_name() << ": "
			<< dist(grit->first, *jit) << " miles" << endl;
		}
		fout << endl;
	}

	//Close the output file
	fout.close();
}

void shortest_route(vector<city>temp, dtable dist, map<int, jvals*>graph, int opt)
{
	string name1, name2;
	//int index1, index2, i, j;
	//vector<city>::iterator cit;

	//User input city names
	cin >> name1 >> name2;

	cout << name1 << " to " << name2 << endl;
	cout << "Didnt finish it." << endl;
}

int main(int argc, char *argv[])
{
	//Declarations
	int total_pop = 0;
	int word_size = 0;
	int opt = 0;
	string option;

	//Object Declarations
	city C;
	vector<city> cities;
	dtable dmatrix;
	map<int, jvals*>graph;

	//Reads in the city info
	cities = read_city_info(total_pop, word_size);

	//Compute and Store the distance table
	dmatrix.computeD(cities);

	//Set up the indices that make up the graph
	graph = set_city_adj(cities, dmatrix);

	//Check for enough arguments
	int check = argc;
	if(check > 0)
	{
		option = argv[1];

		//Writes the city info to std out
		if (option.compare("-write_city_info") == 0)
		{
			write_city_info(cities, total_pop);
		}

		//Writes out the distance table
		if (option.compare("-write_city_dtable") == 0)
		{
			write_city_dtable(cities, word_size, dmatrix);
		}

		//Write the graph info to file
		if (option.compare("-write_city_graph") == 0)
		{
			write_city_graph(graph, cities, dmatrix);
		}

		//Show shortest route for cities chosen
		if(option.compare("-show_route") == 0)
		{
			opt = 1;
			while(1)
			{
				shortest_route(cities, dmatrix, graph, opt);
			}
		}
	}
	return 0;
}
