/*
	Samuel Leonard
	sleonar5
	CS 360
	Lab2: l2p1.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include "jrb.h"
#include "dllist.h"

//A data structure to hold four chars that are the numbers
//for the ip address and a list of host names
typedef struct{
	unsigned char address[4];
	Dllist names;
}ip;

int main(int argc, char **argv)
{
	FILE *fd;
	char *tmpName, *tName, *llength, *lName;
	char nameFind[30];
	char nBuff[30];
	unsigned char c,
		swap_c[4],
		tmp[4];
	int num = 0,
		count = 1,
		place = 0,
		i = 0,
		j = 0,
		n = 0,
		eofCheck = 0,
		nMachines = 0,
		nNames = 0;
	ip *newEntry, *found;
	JRB ipList, rnode;
	Dllist ipnode;

	//Open file
	fd = fopen("converted", "rb");
	
	//Check that file successfully opened
	if(fd == NULL){
		printf("File did not open\n");
		exit(1);
	}
	
	//Create the ip tree
	ipList = make_jrb();

	//Read the input until no input is left
	num = fread(&c, 1, 1, fd);
	
	//Check to make sure there is input
	if(num < 1){
		printf("No input\n");
		exit(1);
	}
	
	//Process Input
	while(num > 0){
		if(count < 5){
			//Start a new struct when new ip begins
			if(count == 1){
				newEntry = (ip*)malloc(sizeof(ip));
				newEntry->names = new_dllist();
			}
			newEntry->address[count-1] = c;
		}
		//Reverse the byte order and convert to an int
		else if(count == 5){
			num = fread(swap_c, (size_t)1, (size_t)4, fd);
			for(i = 0; i < 4; i++){
				tmp[i] = swap_c[3-i];
			}
			nMachines = (int)*tmp;
			nNames = nMachines;
		}
		//Insert a null character and copy string
		else if(c == '\0'){
			if(nNames == 1){
				count = 0;
			}
			else{
				nNames--;
			}
			nBuff[j] = c;
			tName = strdup(nBuff);
			
			//Extract the local name if needed, otherwise append and add to tree
			llength = strchr(tName, '.');
			if(llength != NULL){
				place = llength-tName+1;
				lName = (char*)malloc(sizeof(char)*place);
				strncpy(lName, tName, place-1);
				lName[place] = '\0';
				dll_append(newEntry->names, new_jval_v(lName));
				jrb_insert_str(ipList, lName, new_jval_v(newEntry));
			}
			dll_append(newEntry->names, new_jval_v(tName));
			jrb_insert_str(ipList, tName, new_jval_v(newEntry));
			j = 0;
		}
		//Continue to copy the char while its not the null character
		else{
			nBuff[j] = c;
			j++;
		}

		//Update the count and read the next character if not reading
		//the 4 byte number
		count++;
		if(count != 5){
			num = fread(&c, 1, 1, fd);
		}
	}
	
	//Close the input file
	fclose(fd);

	//Display that the names of hosts are read
	printf("Hosts all read in\n\n");
	
	//Prompt User for a machine name and give the IP address and other
	//machine names
	while(1){
		printf("Enter host name: ");
		eofCheck = scanf("%s", nameFind);
		if(eofCheck == EOF){
			exit(0);
		}
		rnode = jrb_find_str(ipList, nameFind);
		if(rnode != NULL){
			found = (ip*)rnode->val.v;
			printf("%d.%d.%d.%d: ", found->address[0], found->address[1], found->address[2], found->address[3]);
			dll_traverse(ipnode, found->names){
				tmpName = (char*)ipnode->val.v;
				printf("%s ", tmpName);
			}
			printf("\n\n");
		}
		//Print out a no match and the name looked for
		else{
			printf("no key %s\n\n", nameFind);
		}
	}
	
	free_tree(ipList);

	return 0;
}
