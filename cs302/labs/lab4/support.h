#ifndef SUPPORT_H
#define SUPPORT_H

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

typedef unsigned char uchar;

#include "matrix.h"

struct RGB 
{  
	RGB();
	uchar R, G, B;
};

class PPM 
{
  public:
    PPM();
    ~PPM();
	matrix<RGB> img;

	void read(const string &);
	void write(const string &);
	void writeNew(const string &);
	int get_nRows(){return nrows;}
	int get_nCols(){return ncols;}

  private:
	string magicid;
    int nrows, ncols;
	int maxvalue;
};

#endif

