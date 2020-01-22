#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int smatrix[9][9]; //Holds the puzzle numbers
//Specifies the starting row and column
typedef struct Puzzle{
	int row;
	int col;
	int check; //Holds a validity value
	//int *matrix; // Points to a starting position of smatrix
}PUZZLE;

//Function Prototypes
void *valid_rows(void *p); //Checks that the rows are valid
void *valid_cols(void *p); //Checks that the columns are valid
void *valid_boxes(void *p); //Checks that each of the boxes are valid

int main(int argc, char *argv[])
{
	int i=0, j=0, k=0;
	int valid = 1; //Initial state for whole puzzle is good
	//int smatrix[9][9]; //Holds the puzzle numbers
	PUZZLE puzzle[27]; //Instantiates the puzzle structure
	pthread_t tid[27]; //Thread id variable
	pthread_attr_t attr; //Set of thread attributes
	//FILE *in;
	
	//in = fopen(argv[1], "r");
	
	//Read in matrix from the command line
	/*do
	{
		c = fgetc(in);
		if(c != '\n' && c != EOF)
		{
			smatrix[i] = c;
			printf("%c", smatrix[i]);
			i++;
		}
	}while(c != EOF);
	*/
	//Fill a sudoku puzzle for test purposes, will need to be removed
	//in order to allow filling from input
	for(i = 0; i < 9; i++)
	{
		for(j = 0; j < 9; j++)
		{
			smatrix[i][j] = j+1;
			printf("%d. %d\n", k+1, smatrix[i][j]);
			k++;
		}
	}
	
	//Memory Allocation for Puzzle Structures and Threads
	//tid = (pthread_t *) malloc(sizeof(pthread_t) * 27);
	//puzzle = (PUZZLE *) malloc(sizeof(PUZZLE) * 27);
	
	//Thread Creation
	for(i = 0; i < 9; i++)
	{
		//Set rows and columns for starting rows
		puzzle[i].row = i;
		puzzle[i].col = 0;
		puzzle[i].check = 1; //For a true condition
		//puzzle[i].matrix = &smatrix[i][0]; //Points to the starting position
		
		//Initialize attributes
		pthread_attr_init(&attr);
		
		//Create the pthreads for the row checks
		pthread_create(&tid[i], &attr, valid_rows, &puzzle[i]);
	}
	for(i = 9; i < 18; i++)
	{	
		//Set rows and columns for starting columns
		puzzle[i].row = 0;
		puzzle[i].col = i;
		puzzle[i].check = 1; //For a true condition
		//puzzle[i].matrix = &smatrix[0][i]; //Points to the starting position
		
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
			puzzle[i].check = 1; //For a true condition
			//puzzle[i].matrix = &smatrix[j][k]; //Points to the starting position
			
			//Initialize attributes
			pthread_attr_init(&attr);
			
			//Create the pthreads for the row checks
			pthread_create(&tid[i], &attr, valid_boxes, &puzzle);
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
		}
	}
	
	//Display valid or not message
	if(valid == 0)
	{
		printf("Sudoku Puzzle is invalid.\n");
	}
	else
	{
		printf("Sudoku Puzzle is valid.\n");
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
	for(num = ((puz->row) * 9); num < (puz->row + 8); num++)
	{
		for(i = (num + 1); i < (puz->row + 9); i++)
		{
			if(smatrix[num] == smatrix[i])
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
	for(num = puz->col; num <= (63 + puz->col); num+=9)
	{
		for(i = (num + 1); i <= (72 + puz->col); i+=9)
		{
			if(smatrix[num] == smatrix[i])
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
	int i, num;
	int validity = 1; 
	PUZZLE *puz = (PUZZLE *)p;
	
	//Checks each number to verify only appears once 
	for(num = ((puz->row) * 9); num < (num + 8); num++)
	{
		for(i = (num + 1); i < (num + 9); i++)
		{
			if(smatrix[num] == smatrix[i])
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
