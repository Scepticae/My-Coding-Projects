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
#include<utility>

using namespace std;

//Included support header files
#include "matrix.h"
#include "support.h"

vector<pair<int, int> > set_pixel_target(int, int);
void encode(const string &);
void decode(const string &);

int main(int argc, char *argv[])
{
	int seedvalue = 0;
	string e_suffix = ".ppm";
	string d_suffix = "wmsg.ppm";
	string img_file;

	//Checks to see if there is enough arguments
	if (argc != 4)
	{
		cerr << "Not enough arguments given. Arguments should be:" << endl;
		cerr << "File Name, Seed: -seed=N, Process: -encode | decode, Image: 'name'.ppm | 'name'_wmsg.ppm" << endl;
		system("pause");
		exit(1);
	}

	//Get the seed value
	sscanf(&argv[1][6], "%d", &seedvalue);

	//-encode|decode: process mode = encode message or decode message
	if (strcmp(argv[2], "-encode") != 0 && strcmp(argv[2], "-decode") != 0)
	{
		cerr << "Incorrect process chosen: Should be '-encode' or '-decode'." << endl;
		system("pause");
		exit(1);
	}
	
	//Set argv[2] to a string for find function
	img_file = argv[3];
	
	//Checks for proper file suffix with proper process
	if (strcmp(argv[2], "-encode") == 0 && (img_file.find(e_suffix) == string::npos || 
			img_file.find(d_suffix) != string::npos))
	{
		cerr << "The file being encoded is not supported, file should be: 'image name'.ppm" << endl;
		system("pause");
		exit(1);
	}
	else if (strcmp(argv[2], "-decode") == 0 && img_file.find(d_suffix) == string::npos)
	{
		cerr << "The file being decoded is not supported, file should be: 'image name'_wmsg.ppm" << endl;
		system("pause");
		exit(1);
	}
	
	//Choose to encode or decode data
	if(strcmp(argv[2], "-encode") == 0){encode(argv[3]);}
	else {decode(argv[3]);}

	return 0;
}

vector<pair<int, int> > set_pixel_target(int rows, int cols)
{
	pair<int, int> indices;
	vector<pair<int, int> >targ;

	for(int i = 1; i < rows; i += 2)
	{
		for(int j = 1; j < cols; j += 2)
		{
			indices = make_pair(i, j);
			targ.push_back(indices);
		}
	}

	return(targ);
}

void encode(const string &fname)
{
	//Instantiate a PPM object
	PPM img;
	int count = 0;
	char c;
	char clr = 0xFE;
	char ETX = 0x3;
	vector<char> msg;
	vector<pair<int, int> > targ_list;
	vector<pair<int, int> >::iterator tlit;

	//Read in the image data
	img.read(fname);

	//Gets user for message to be encrypted
	while(cin.get(c))
	{
		//Fills the character vector
		msg.push_back(c);
		count++;
		if(c == '\n'){break;}
	}

	//Pushes at least one ETX character
	msg.push_back(ETX);
	count++;

	//Checks to see if number of characters are divisible by three
	while((count % 3) != 0)
	{
		msg.push_back(ETX);
		count++;
	}

	//Embeds the text into the image
	targ_list = set_pixel_target(img.get_nRows(), img.get_nCols());
	tlit = targ_list.begin();
	for(int i = 0; i < count; i += 3)
	{
		for(int k = 0; k < 8; k++)
		{
			//Clears the least significant bit
			img.img[tlit->first][tlit->second].R &= clr;
			img.img[tlit->first][tlit->second].G &= clr;
			img.img[tlit->first][tlit->second].B &= clr;

			//Sets the least significant bit with the kth bit of the text
			img.img[tlit->first][tlit->second].R |= ((msg[i] >> k) & 0x1);
			img.img[tlit->first][tlit->second].G |= ((msg[i+1] >> k) & 0x1);
			img.img[tlit->first][tlit->second].B |= ((msg[i+2] >> k) & 0x1);

			//Increments the pixet target list
			tlit++;
		}
	}

	//Write the new image data
	img.write(fname);
}

void decode(const string &fname)
{
	PPM img;
	char c, c1, c2;
	char tmp = 0x0;
	char ETX = 0x3;
	vector<pair<int, int> > targ_list;
	vector<pair<int, int> >::iterator tlit;
	vector<char> msg;
	vector<char>::iterator mit;

	//Read in the image data
	img.read(fname);

	//Gets the target list and extracts the message
	targ_list = set_pixel_target(img.get_nRows(), img.get_nCols());
	tlit = targ_list.begin();
	while(1)
	{
		//Initialize the characters bits
		c = 0x0;
		c1 = 0x0;
		c2 = 0x0;

		for(int k = 0; k < 8; k++)
		{
			tmp = ((img.img[tlit->first][tlit->second].R & 0x1) << k);
			c |= tmp;
			tmp = 0x0;
			tmp = ((img.img[tlit->first][tlit->second].G & 0x1) << k);
			c1 |= tmp;
			tmp = 0x0;
			tmp = ((img.img[tlit->first][tlit->second].B & 0x1) << k);
			c2 |= tmp;
			tmp = 0x0;
			tlit++;
		}

		if(c != ETX) {msg.push_back(c);}
		else {break;}
		if(c1 != ETX) {msg.push_back(c1);}
		else {break;}
		if(c2 != ETX) {msg.push_back(c2);}
		else {break;}
	}

	//Send data to standard out
	for(mit = msg.begin(); mit != msg.end(); mit++)
	{
		cout << *mit;
	}
}
