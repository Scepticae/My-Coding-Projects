#ifndef SUPPORT_H
#define SUPPORT_H

// header files
#include<iostream>
#include<vector>
#include<string>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<map>

using namespace std;

typedef unsigned char uchar;
typedef enum { run_process1, run_process2 } pmode_t;

struct RGB {  
	RGB();
	bool operator<(RGB)const;
	double distance(RGB);
	uchar R, G, B;
	string color;
	int closest;
};

class PPM {
  public:
    PPM();
    ~PPM();

	void read(const string &);
	void write(const string &);
	void write(const string &, const string &);
	void process(pmode_t, const string &);

  private:
	string magicid;
    int nrows, ncols;
	int maxvalue;
	pmode_t mode;
	vector<RGB> img;
	vector<RGB> qcolors;

	void read_qcolors(const string &);
	void process1();
	void process2();
};

#endif
