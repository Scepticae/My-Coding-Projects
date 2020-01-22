#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <fstream>

using namespace std;

//Data too be shared by all threads
int smatrix[9][9]; //Holds the puzzle numbers

//Specifies the starting row and column
typedef struct Puzzle{
int row;
int col;
int state;
int check; //Holds a validity value
}PUZZLE;

//Function Prototypes
void *valid_rows(void *p); //Checks that the rows are valid
void *valid_cols(void *p); //Checks that the columns are valid
void *valid_boxes(void *p); //Checks that each of the boxes are valid

int main(int argc, char *argv[])
{
	int i=0, j=0, k=0, p=0, l=0;
	int valid = 1; //Initial state for whole puzzle is good
	string argu;
	PUZZLE puzzle[27]; //Instantiates the puzzle structure
	pthread_t tid[27]; //Thread id variable
	pthread_attr_t attr; //Set of thread attributes

	//Check for input error
	if(argv[2] != NULL) 
	{
		printf("Please input the text file you wish to read.");
		exit(1);
	}

	//Get input from user
	argu = argv[1];

	//Read File
	ifstream gb;
	gb.open(argu.c_str());

	for(p = 0; p < 9; p++) 
	{
		for(l = 0; l < 9; l++) 
		{
			gb >> smatrix[p][l];
		}
	}
	gb.close();
	
	//Prints the matrix that was inputed
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			printf("%d ", smatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//Thread Creation
	for(i = 0; i < 9; i++)
	{
		//Set rows and columns for starting rows
		puzzle[i].row = i;
		puzzle[i].col = 0;
		puzzle[i].state = 1;
		puzzle[i].check = 1; //For a true condition

		//Initialize attributes
		pthread_attr_init(&attr);

		//Create the pthreads for the row checks
		pthread_create(&tid[i], &attr, valid_rows, &puzzle[i]);
	}
	for(i = 9; i < 18; i++)
	{
		//Set rows and columns for starting columns
		puzzle[i].row = 0;
		puzzle[i].col = i-9;
		puzzle[i].state = 2;
		puzzle[i].check = 1; //For a true condition

		//Initialize attributes
		pthread_attr_init(&attr);

		//Create the pthreads for the row checks
		pthread_create(&tid[i], &attr, valid_cols, &puzzle[i]);
	}
	for(j = 0; j < 7; j+=3)
	{
		for(k = 0; k < 7; k+=3)
		{
			//Set rows and columns for starting columns
			puzzle[i].row = j;
			puzzle[i].col = k;
			puzzle[i].state = 3;
			puzzle[i].check = 1; //For a true condition

			//Initialize attributes
			pthread_attr_init(&attr);

			//Create the pthreads for the row checks
			pthread_create(&tid[i], &attr, valid_boxes, &puzzle[i]);
			i++;
		}
	}

	//Join the threads and check if all are valid
	for(i = 0; i < 27; i++)
	{
		pthread_join(tid[i], NULL);

		//Check row, column, box validity
		if(puzzle[i].check == 0)
		{
			valid = 0;
			
			//Print Invalid Row, Column or Box
			if(puzzle[i].state == 1)
			{
				printf("Row: %d is INVALID\n", (puzzle[i].row)+1);
			}
			else if(puzzle[i].state == 2)
			{
				printf("Col: %d is INVALID\n", (puzzle[i].col)+1);
			}
			else if(puzzle[i].state == 3)
			{
				printf("Box: %d is INVALID\n", (i%9)+1);
			}
		}
	}

	//Display valid or not message
	if(valid == 0)
	{
		printf("\nSudoku Puzzle is invalid.\n");
	}
	else
	{
		printf("\nSudoku Puzzle is valid.\n");
	}

	return 0;
}

//Function that checks validity of the rows
void *valid_rows(void *p)
{
	int i, num;
	int validity = 1;
	PUZZLE *puz = (PUZZLE *)p;

	//Checks each number to verify only appears once
	for(num = puz->col; num < 8; num++)
	{
		for(i = (num + 1); i < 9; i++)
		{
			if(smatrix[puz->row][num] == smatrix[puz->row][i])
			{
				validity = 0;
			}
		}
	}

	//Set the Check to Validity
	puz->check = validity;

	//Exits the Thread
	pthread_exit(0);
}

//Function that checks the validity of the columns
void *valid_cols(void *p)
{
	int i, num;
	int validity = 1;
	PUZZLE *puz = (PUZZLE *)p;
	
	//Checks each number to verify only appears once
	for(num = 0; num < 8; num++)
	{
		for(i = (num + 1); i < 9; i++)
		{
			if(smatrix[num][puz->col] == smatrix[i][puz->col])
			{
				validity = 0;
			}
		}
	}

	//Set the Check to Validity
	puz->check = validity;

	//Exits the Thread
	pthread_exit(0);
}

//This function is not built correctly for the boxes
//Function that checks the validity of the boxes
void *valid_boxes(void *p)
{
	int i, j, k=0;
	int validity = 1;
	int matrix[9];
	PUZZLE *puz = (PUZZLE *)p;
	
	//printf("Row: %d Col: %d\n", puz->row, puz->col);
	for(i = 0; i < 3; i++)
	{
		for(j = 0; j < 3; j++)
		{
			matrix[k] =  smatrix[puz->row+i][puz->col+j];
			k++;
		}
	}

	//Checks each number to verify only appears once
	for(i = 0; i < 8; i++)
	{
		for(j = (i + 1); j < 9; j++)
		{
			if(matrix[i] == matrix[j])
			{
				validity = 0;
			}
		}
	}

	//Set the Check to Validity
	puz->check = validity;

	//Exits the Thread
	pthread_exit(0);
}