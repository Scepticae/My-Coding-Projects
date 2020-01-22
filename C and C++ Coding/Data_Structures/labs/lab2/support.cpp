//Associative files
#include<algorithm>
#include "support.h"

using namespace std;

//RGB Constructor
RGB::RGB()
{
	R = 0;
	G = 0;
	B = 0;
	closest = 0;
}

bool RGB::operator<(RGB rgb)const
{
	if(R < rgb.R)
	{
		return true;
	}
	else if(G < rgb.G)
	{
		return true;
	}
	else if(B < rgb.B)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// RGB::distance()
double RGB::distance(RGB rgb)
{
	//Variables for the difference in points
	int diff_R, diff_G, diff_B;
	double euc_dist;

	//Calculates the distance between two azimuths
	diff_R = abs((int)rgb.R - (int)R);
	diff_G = abs((int)rgb.G - (int)G);
	diff_B = abs((int)rgb.B - (int)B);

	//Calculates the euclidean distance between two points
	euc_dist = sqrt((diff_R * diff_R) + (diff_G * diff_G) + (diff_B * diff_B));

	return euc_dist;
}

PPM::PPM() 
{
  magicid = "P6";
  nrows = 0;
  ncols = 0;
  maxvalue = 255;
}

PPM::~PPM() { }

void PPM::read (const string &fname) 
{
	int i = 0, j;//loop control variables
	int npixels, n = 5;
	string suffix = ".ppm";
	ifstream fin;
	RGB *temp;
	
	//extract suffix: must be ppm
	if(fname.find(suffix) == string::npos)
	{
		cerr << "The file is not a PPM file." << endl;
		exit(1);
	}
	// open fname: check status
	fin.open(fname.c_str());
	if(fin.fail())
	{
		cerr << "The file does not exist." << endl;
		exit(1);
	}

	// read magicid: must be P6
	fin >> magicid;
	// read ncols, nrows: check status
	fin >> ncols >> nrows;
	// read maxvalue: must be 255
	fin >> maxvalue;

	while(fin.get() != '\n'){}

	npixels = ncols*nrows;

	// allocate space for 3*npixels in img vector
	uchar buf[3 * npixels];
	
	// read 3*npixels bytes into img: check status
	fin.read((char*)buf, 3 * npixels);
	
	uchar *bp = buf;

	while(i < npixels)
	{
		for(j = 0; j < n && i < npixels; i++, j++)
		{
			temp = new RGB;
			temp->R = *bp++;
			temp->G = *bp++;
			temp->B = *bp++;
			img.push_back(*temp);
		}
	}
	
	//Check the amount of bits read in
	if(i != npixels)
	{
		cerr << "Incorrect number of bytes read in from file." << endl;
		exit(1);
	}
	
	// close input file
	fin.close();
}
void PPM::write(const string &fname) 
{
	unsigned int i;

	// open fname: check status
	ofstream fout;
	fout.open(fname.c_str(), ofstream::binary);
	
	if(fout.fail())
	{
		cerr << "The file did not open." << endl;
		exit(1);
	}

	// write header
	fout << magicid << '\n'
		 << ncols << " " << nrows << '\n'
		 << maxvalue << '\n';

	for(i = 0; i < img.size(); i++)
	{
		fout << img[i].R << img[i].G << img[i].B;
	}

	// close output file
	fout.close();
}

void PPM::write(const string & fname, const string & addon) 
{
	// new_fname: image.ppm -> image_addon.ppm
	string new_fname, name1, add1;
	int position, position2;

	position = fname.find('.');
	name1 = fname.substr(0, (position));
	position = addon.find('_');
	position2 = addon.find('.');
	add1 = addon.substr((position + 1), (position2 - (position + 1)));

	if(mode == run_process1)
	{
		new_fname = name1 + "_" + add1 + "_m1.ppm";
	}
	else
	{
		new_fname = name1 + "_" + add1 + "_m2.ppm";
	}
	
	// call write(new_fname);
	write(new_fname);
}

void PPM::process(pmode_t pmode, const string &fname) 
{
	mode = pmode;
	
	// read qcolors in fname
	read_qcolors(fname);

	// run proper process mode
	if(pmode == run_process1)
	{
		process1();
	}
	else if(pmode == run_process2)
	{
		process2();
	}
}

void PPM::process1()
{
	int i = 0;
	unsigned int j;
	int npixels = nrows * ncols;
	double dist;
	map<double, RGB> newcolor;
	map<double, RGB>::iterator nit;
	
	//For each pixel find  closest qcolor
	while(i < npixels)
	{
		for(j = 0; j < qcolors.size(); j++)
		{
			dist = img[i].distance(qcolors[j]);
			newcolor.insert(make_pair(dist, qcolors[j]));
		}
		
		//Set pixel color to closest qcolor
		nit = newcolor.begin();
		img[i] = nit->second;

		//Clear the map for the next pixel
		newcolor.clear();
		i++;
	}
}

void PPM::process2()
{
	int i = 0, k = 0, q = 8, count = 0;
	double dist, prev_dist;
	unsigned int j;
	int npixels = nrows * ncols;
	vector<map<RGB, int> > histo;
	map<RGB, int>::iterator hit;
	map<RGB, int>::iterator sit;

	//Resize the histo vector to the size of the qcolor array
	histo.resize(qcolors.size());

	//For each pixel find  closest qcolor
	while(i < npixels)
	{
		//Update qcolor histogram of pixel color/8 counts
		img[i].R = q * (img[i].R / q);
		img[i].G = q * (img[i].G / q);
		img[i].B = q * (img[i].B / q);
	
		//Set previous distance to sentinel euc dist for 256 256 256
		prev_dist = 443.4;

		//Compare the eucl distances between pixel and each qcolor value
		for(j = 0; j < qcolors.size(); j++)
		{
			dist = img[i].distance(qcolors[j]);
			if(dist < prev_dist)
			{
				prev_dist = dist;
				k = j;
			}			
		}
		
		//Set Pixels closest qcolor
		img[i].closest = k;
		
		//Fill the histogram with like qcolor rgb and increment count
		hit = histo[k].find(img[i]);
		if(hit != histo[k].end())
		{
			hit->second++;
		}
		else
		{
			histo[k].insert(make_pair(img[i], 1));
		}

		//Increment i
		i++;
	}
	
	//For each qcolor find highest count pixel value
	//Set that qcolor to that value
	for(i = 0; i < (int)histo.size(); i++)
	{
		for(hit = histo[i].begin(); hit != histo[i].end(); hit++)
		{
			if(hit->second > count)
			{
				sit = hit;
				count = hit->second;
			}
		}
		qcolors[i] = sit->first;
		count = 0;
	}

	//Set every pixel to their new quantized qcolor
	while(i < npixels)
	{
		img[i] = qcolors[img[i].closest];
		i++;
	}
}

void PPM::read_qcolors(const string &fname)
{
	int r, g, b;
	char c;
	string colorset;
	RGB *temp;
	ifstream fin;
	
	// open fname: check status
	fin.open(fname.c_str());
	
	if(fin.fail())
	{
		cerr << "The file does not exist." << endl;
		exit(1);
	}
   
	//Read in the qc colors to a vector of rgb structs
	while(fin >> r)
	{
		fin >> g >> b >> c >> colorset;
		temp = new RGB;
		temp->R = r;
		temp->G = g;
		temp->B = b;
		temp->color = colorset;

		qcolors.push_back(*temp);
	}
	
	// close input file
	fin.close();
}
