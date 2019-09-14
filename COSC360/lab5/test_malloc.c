#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "malloc.h"

int main()
{
	char *s, *r;
  int *buf, *buf2;
  int i, sz;
	unsigned int heap;
	double *nums;

  i = 1000;
	
	//Address of heap before malloc
	heap = sbrk(0);
  printf("\nBeginning Heap = 0x%x\n", sbrk(0));
	
	//Address of end of heap after malloc
	s = (char*)malloc(sizeof(char)*20);
	printf("End of Heap = 0x%x\n", sbrk(0));
	
	//Show use of strings
	printf("\n\n***Show use of strings***\n\n");
	strcat(s, "Hello World");
	printf("Allocated 20 bytes for string s = %s, Total Allocated %d bytes, Address = 0x%x\n\n", s, s[-8], (unsigned int)&s[0]);
	
	//Shows Memory being reused
	printf("***Showing Reused Memory***\n");
	
	//Show malloc'd memory allocation
  for (sz = 4; sz < 32; sz += 4) {
    buf = (int *) malloc(sz);
    buf[0] = i;
    i++;
		printf("\nAllocated %d bytes.  buf = 0x%x, buf[-1] = %d, buf[-2] = %d, buf[0] = %d\n", 
			sz, (unsigned int) buf, buf[-1], buf[-2], buf[0]);
		//Free the pointers
		printf("Freeing %d bytes.  buf = 0x%x, buf[-1] = %d, buf[-2] = %d, buf[0] = %d\n", 
			sz, (unsigned int) buf, buf[-1], buf[-2], buf[0]);
		free(buf);
		printf("Allocated %d bytes Again.  buf = 0x%x, buf[-1] = %d, buf[-2] = %d, buf[0] = %d\n", 
			sz, (unsigned int) buf, buf[-1], buf[-2], buf[0]);
  }
	
	//Create some space
	printf("\n\n");
	
	//Shows some reuse of memory and new addresses for some memory
	printf("***First two showing reuse and then new memory for the rest***\n\n");
	
	//Show malloc'd memory allocation after free for same amounts
  for (sz = 4; sz < 32; sz += 4) {
    buf = (int *) malloc(sz);
    buf[0] = i;
    i++;
		printf("Allocated %d bytes.  buf = 0x%x, buf[-1] = %d, buf[-2] = %d, buf[0] = %d\n", 
			sz, (unsigned int) buf, buf[-1], buf[-2], buf[0]);
	}

  //Showing calloc for some doubles
	printf("\n***Showing Calloc for Doubles***\n");
	
	nums = (double*)calloc(4, sizeof(double));
	printf("\nAllocated %d bytes.\n", nums[-1]);
	for (i = 0; i < 4; i++){
		printf("nums[%d]:  address = 0x%x, value = %d\n", i,
			 (unsigned int) &nums[i], nums[i]);
	}
	
	//Add values to the allocated spaces for nums
	printf("\n***Add values to nums***\n\n");
	for (i = 0; i < 4; i++){
		nums[i] = (float)i;
		printf("nums[%d]:  address = 0x%x, value = %f\n", i,
			 (unsigned int) &nums[i], nums[i]);
	}
	
	//Show that realloc is used
	printf("\n***Showing use of Realloc***\n\n");
	printf("s before calling realloc = %s, Total Allocated %d bytes, Original Address = 0x%x\n", s, s[-8], (unsigned int)&s[0]);
	printf("Compare that to above allocation.\n");
	r = (char*)realloc(s, sizeof(char)*40);
	printf("s after calling realloc = 0x%x\n", *s);
	printf("Allocated 40 bytes for string r = %s, Total Allocated %d bytes, Address = 0x%x\n\n", r, r[-8], (unsigned int)&r[0]);
	
	//Show mallocing over the current heap space
	printf("***Show Malloc over the current heap space***\n\n");
	printf("Beginning Heap = 0x%x\n", heap);
	buf2 = (int*)malloc(9000);
	printf("Ending Heap after malloc(9000) = 0x%x\n", sbrk(0));
}
