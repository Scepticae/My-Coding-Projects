#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include "malloc.h"

//Struct for free memory
typedef struct flist{
	int size;
	struct flist *flink;
	struct flist *blink;
}*Flist;

//Global Variable
char *malloc_head = NULL;
int mem_size;

//Functions
unsigned int adjust_size(unsigned int);
void set_initial_mem();
void *srch_list(unsigned int);
void fix_list(Flist, Flist);


void *malloc(unsigned int size){
	unsigned int adj_size;
	void *set_ptr;
	
	//Adjust the size for bookkeeping
	adj_size = adjust_size(size);

	//Check to see if free list has been created
	set_initial_mem();
	
	//Search free list for memory
	set_ptr = srch_list(adj_size);
	
	//Return memory to requester
	return set_ptr;
}


//Function Name: calloc
//Description: calloc returns requested memory for n members at n size each 
//Inputs: An unsigned integer for the number of elements and one for the size of each
//Outputs: None
//Returns: a pointer to the head of memory requested or null if no more 
//		memory is available
void *calloc(unsigned int nmemb, unsigned int size){
	void *set_ptr;
	unsigned int total;
	
	//Calculate the total allocation
	total = nmemb * size;
	
	//Request the memory needed
	set_ptr = malloc(total);
	
	//Set the memory to all zeros
	bzero(set_ptr, total);
	
	//Return the pointer to the allocated memory
	return set_ptr;
}

//Function Name: realloc
//Description: realloc returns reallocated memory and frees the previous memory
//Inputs: A pointer for new allocation and an unsigned integer for the new memory requested
//		and frees the old memory
//Outputs: None
//Returns: a pointer to the head of memory requested or null if no more 
//		memory is available
void *realloc(void *ptr, unsigned int size){
	void *set_ptr;
	
	//Acquire the new memory needed
	set_ptr = malloc(size);
	
	//Copy the memory into the new location
	bcopy(ptr, set_ptr, size);
	
	//Free the old memory location
	free(ptr);
	
	//Return the pointer to the new memory
	return set_ptr;
}

//Function Name: free
//Description: free the memory and puts it on the free list
//Inputs: A pointer to the memory needing released
//Outputs: None
//Returns: None
void free(void *ptr){
	char *tmp;
	Flist node;

	//Move freed memory to front of free list
	if(ptr != NULL){
		tmp = (char*)ptr-8;
		node = (Flist)tmp;
		node->flink = (Flist)malloc_head;
		node->blink = NULL;
		node->flink->blink = node;
		
		//Set malloc_head to front
		malloc_head = (char*)node;
		
		ptr = NULL;
	}
}

//Function Name: adjust_size
//Description: pads the size to allow for bookkeeping
//Inputs: tmp: size requested
//Outputs: None
//Returns: needed: the padded size
unsigned int adjust_size(unsigned int tmp){
	unsigned int needed;
	
	//Pad the size if needed to handle 8 byte increments
	if((tmp % 8) != 0){
		tmp = (tmp + 8) - ((tmp +8) % 8);
	}
	
	//Accounts for bookkeeping memory space
	needed = tmp + 8;
	
	//Return adjusted size
	return needed;
}

//Function Name: set_initial_mem
//Description: Gets initial heap space
//Inputs: none
//Outputs: heap space, malloc_head
//Returns: None
void set_initial_mem(){
	Flist f;
	
	//Check to see if sbrk needs to get more memory
	if(malloc_head == NULL){
		malloc_head = sbrk(8192);
		if(malloc_head == NULL){
			fprintf(stderr, "sbrk: insufficient memory\n");
			exit(1);
		}
		
		//Set initial memory size
		mem_size = 8192; //sets the initial total memory
	
		//Add initial memory to free list
		f = (Flist) malloc_head;
		f->size = mem_size;
		f->flink = NULL;
		f->blink = NULL;
	}
}

//Function Name: srch_list
//Description: searches the free list for sufficient block of memory
//Inputs: needed: the padded size block needed
//Outputs: None
//Returns: set_mem: ptr to the memory block needed
void *srch_list(unsigned int needed){
	int check_mem = 0;
	int tmp_size, new_size;
	char *tmp;
	void *set_mem;
	Flist srch, node;
	
	//Set search to head of list
	srch = (Flist)malloc_head;
	
	//Search throught the list for memory needed
	while(check_mem == 0){
		if(needed <= (srch->size - 16)){
			//Hold size of free list and set memory bookkeeping size to needed
			tmp_size = srch->size;
			*(int*)srch = needed;
			
			//Set ptr to memory location to be returned
			set_mem = (char*)srch + 8;
			
			//Calculate the new size for remaining block
			new_size = tmp_size - needed;
			
			//Set the new node and fix the list
			tmp = (char*)srch + needed;
			node = (Flist)tmp;
			node->size = new_size;
			fix_list(srch, node);
	
			check_mem = 1;
		}
		//Not enough memory continue list
		else{
			if(srch->flink == NULL){
				//Get more memory
				sbrk(8192);
				srch->size += 8192;
			}
			//Increment the list
			else{
				srch = srch->flink;
			}
		}
	}
	
	//Return pointer to memory requested
	return set_mem;
}

//Function Name: fix_list
//Description: fix the links after a memory block has been removed from
//		the free list
//Inputs: Flist s, Flist n
//Outputs: malloc_head is changed
//Returns: None
void fix_list(Flist s, Flist n){
	//Fix the linked list after memory was given out
	if(s->flink == NULL && s->blink == NULL){
		//Set the head of the list to the new head node
		malloc_head = (char*)n;
		n->flink = NULL;
		n->blink = NULL;
		s->flink = NULL;
		s->blink = NULL;
		s = NULL;
	}
	//Adjust the linked list for node at beginning of the list
	else if(s->flink != NULL && s->blink == NULL){
		//Set the head of the list to the current node
		malloc_head = (char*)n;
		n->flink = s->flink;
		n->blink = NULL;
		s->flink->blink = n;
		s->flink = NULL;
		s->blink = NULL;
		s = NULL;
	}
	//Adjust the linked list for node at the end
	else if(s->flink == NULL && s->blink != NULL){
		n->blink = s->blink;
		n->flink = NULL;
		s->blink->flink = n;
		s->flink = NULL;
		s->blink = NULL;
		s = NULL;
	}
	//Adjusting for the middle
	else{
		n->blink = s->blink;
		n->flink = s->flink;
		s->blink->flink = n;
		s->flink->blink = n;
		s->flink = NULL;
		s->blink = NULL;
		s = NULL;
	}
}