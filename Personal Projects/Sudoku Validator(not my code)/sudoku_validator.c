#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

//Global variables for thread access
int check = 1;
int smatrix[81];

//Specifies the starting row and column
typedef struct{
	int row;
	int col;
}PUZZLE;

//Function Prototypes
void *valid_rows(void *p); //Checks that the rows are valid
void *valid_cols(void *p); //Checks that the columns are valid
void *valid_boxes(void *p); //Checks that each of the boxes are valid

int main(int argc, char *argv[])
{
	int i, j, k;
	PUZZLE *puzzle; //Instantiates the puzzle structure
	pthread_t *tid; //Thread id variable
	pthread_attr_t attr; //Set of thread attributes
	
	//Thread Creation
	for(i = 0; i < 9; i++)
	{
		//Set rows and columns for starting rows
		puzzle[i].row = i;
		puzzle[i].col = 0;
		
		//Initialize attributes
		pthread_attr_init(&attr);
		
		//Create the pthreads for the row checks
		pthread_create(&tid[i], &attr, valid_rows, (void *)&puzzle[i]);
	}
	for(i = 9; i < 18; i++)
	{	
		//Set rows and columns for starting columns
		puzzle[i].row = 0;
		puzzle[i].col = i;
		
		//Initialize attributes
		pthread_attr_init(&attr);
		
		//Create the pthreads for the row checks
		pthread_create(&tid[i], &attr, valid_cols, (void *)&puzzle[i]);
	}
	for(j = 0; j < 7; j+=3)
	{	
		for(k = 0; k < 7; k+=3)
		{
			//Set rows and columns for starting columns
			puzzle[i].row = j;
			puzzle[i].col = k;
			
			//Initialize attributes
			pthread_attr_init(&attr);
			
			//Create the pthreads for the row checks
			pthread_create(&tid[i], &attr, valid_boxes, (void *)&puzzle[i]);
			i++;
		}
	}
	
	return 0;
}

void *valid_rows(void *p)
{
	int i, num;
	
	num = p->row * 9;
	
	for(num; num < (num + 8); num++)
	{
		for(i = (num + 1); i < (num + 9); i++)
		{
			if(smatrix[num] == smatrix[i])
			{
				check = 0;
			}
		}
	}
	pthread_exit(0);
}

void *valid_cols(void *p)
{
	int i, num;
	
	num = p->col * 9;
	
	for(num; num < (num + 8); num++)
	{
		for(i = (num + 1); i < (num + 9); i++)
		{
			if(smatrix[num] == smatrix[i])
			{
				check = 0;
			}
		}
	}
	pthread_exit(0);
}

void *valid_boxes(void *p)
{
	int i, num;
	
	num = p->row * 9;
	
	for(num; num < (num + 8); num++)
	{
		for(i = (num + 1); i < (num + 9); i++)
		{
			if(smatrix[num] == smatrix[i])
			{
				check = 0;
			}
		}
	}
	pthread_exit(0);
}