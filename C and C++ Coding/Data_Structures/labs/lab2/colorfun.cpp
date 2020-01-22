//Samuel Leonard
//Lab2
//Lab: 2:30-5:30

#include"support.h"

using namespace std;

int main(int argc, char *argv[])
{
	pmode_t proc;

	//Instantiate image object
	PPM imgPPM;

	//Perform command line argument checking 
	if(argc != 5)
	{
		cerr << "Not enough arguments given. Arguments should be:" << endl;
		cerr << "Process: -1 | -2, Flag: -c, Color file: 'name'.txt, Image: 'name'.ppm" << endl;
		exit(1);
	}
	//-1|2: process mode = run_process1 or 2
	if(strcmp(argv[1], "-1") != 0 && strcmp(argv[1], "-2") != 0)
	{
		cerr << "Incorrect process chosen: Should be '-1' or '-2'." << endl;
		exit(1);
	}
	//'-c' argument checker 
	if(strcmp(argv[2], "-c") != 0)
	{
		cerr << "Incorrect second argument: Entry should be '-c'." << endl;
		exit(1);
	}
	
	//Read image data
	imgPPM.read(argv[4]);
	
	//Process image data
	if((strcmp(argv[1], "-1")) == 0)
	{
		proc = run_process1;
	}
	else
	{
		proc = run_process2;
	}
	
	//Processes the image
	imgPPM.process(proc, argv[3]);

	//Write result to file
	imgPPM.write(argv[4], argv[3]);

	return 0;
}
