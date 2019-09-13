#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "jmalloc1.h"

//Global Variables to handle size, beginning, and ending
char *jmalloc_begin = NULL;
char *jmalloc_end = NULL;
int mem_size;

//Function Name: jmalloc1
//Description: jmalloc1 returns requested memory 
//Inputs: An unsigned integer for the total memory requested
//Outputs: None
//Returns: a pointer to the head of memory requested or null if no more 
//		memory is available
void *jmalloc1(unsigned int size){
	int check_mem = 0;
	unsigned int needed;
	char *mem_begin;
	void *set_ptr;
	
	//Pad the size if needed to handle 8 byte increments
	if((size % 8) != 0){
		size = (size + 8) - ((size +8) % 8);
	}
		
	//Accounts for bookkeeping memory space
	needed = size + 8;
	
	//Check to see if sbrk needs to get more memory
	if(jmalloc_begin == NULL){
		mem_begin = sbrk(8192);
		mem_size = 8192; //sets the initial total memory left
		
		//Set the beginning and ending point of the allocated memory by sbrk
		jmalloc_begin = mem_begin;
		jmalloc_end = sbrk(0);
	}
	
	//Check to see if there is enough room for requested memory
	while(check_mem == 0){
		if(needed < (mem_size - 16)){
			*(int*)jmalloc_begin = needed; //set the beginning to the size needed
			set_ptr = jmalloc_begin + 8;
			jmalloc_begin = jmalloc_begin + needed;
			mem_size -= needed;
			check_mem = 1;
		}
		//If not enough room, get more memory
		else{
			sbrk(8192);
			jmalloc_end = sbrk(0);
			mem_size += 8192;
		}
	}
	
	//Return the memory allocated
	return set_ptr;
}
