//Associative files
#include "support.h"

//RGB Constructor
RGB::RGB()
{
	R = 0;
	G = 0;
	B = 0;
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
	int i = 0;//loop control variables
	int npixels;
	ifstream fin;
	RGB *temp;

	//Open the input file
	fin.open(fname.c_str());

	//Check to see if the file failed to open
	if(fin.fail())
	{
		cerr << "The file did not open." << endl;
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

	img.assign(nrows, ncols);

	for(i = 0; i < npixels; i++)
	{
		temp = new RGB;
		temp->R = *bp++;
		temp->G = *bp++;
		temp->B = *bp++;
		*(img.data() + i) = *temp;
	}

	//Check the amount of bits read in
	//if((i*j) != npixels)
	{
		//cerr << "Incorrect number of bytes read in from file." << endl;
		//exit(1);
	}
	
	// close input file
	fin.close();
}
void PPM::writeNew(const string &fname) 
{
	int i, j;

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

	for(i = 0; i < nrows; i++)
	{
		for(j = 0; j < ncols; j++)
		{
			fout << img[i][j].R << img[i][j].G << img[i][j].B;
		}
	}

	// close output file
	fout.close();
}

void PPM::write(const string &fname) 
{
	// new_fname: image.ppm -> image_addon.ppm
	string new_fname, name1;
	int position;

	position = fname.find('.');
	name1 = fname.substr(0, (position));
	
	new_fname = name1 + "_wmsg.ppm";
	
	// call write(new_fname);
	writeNew(new_fname);
}

