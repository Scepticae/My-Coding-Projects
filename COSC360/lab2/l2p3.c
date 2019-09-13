/*
	Samuel Leonard
	sleonar5
	CS 360
	Lab2: l2p3.c
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
	char *tmpName, *tName, *llength, *lName;
	char nameFind[30];
	char nBuff[30];
	unsigned char c[350000],
		swap_c[4],
		tmp[4];
	int fd, 
		num = 0,
		count = 0,
		place = 0,
		i = 0,
		j = 0,
		eofCheck = 0,
		nMachines = 0;
	ip *newEntry, *found;
	JRB ipList, rnode;
	Dllist ipnode;

	//Open file
	fd = open("converted", O_RDONLY);
	
	//Check that file exist
	if(fd < 0){
		printf("File did not open\n");
		exit(1);
	}
	
	//Create the ip tree
	ipList = make_jrb();

	//Read the input until no input is left
	num = read(fd, c, sizeof(c));
	
	//Check to make sure there is input
	if(num < 1){
		printf("No Input");
		exit(1);
	}
	
	//Process all the input
	while(i < num){
		//Create a newEntry struct and it's dllist
		newEntry = (ip*)malloc(sizeof(ip));
		newEntry->names = new_dllist();
		for(j = 0; j < 4; j++){
			if(c[i] != '.'){
				newEntry->address[j] = c[i];
			}
			else{
				j--;
			}
			i++;
		}
		//Gets the number of machines
		for(j = 0; j < 4; j++){
			tmp[j] = c[i];
			i++;
		}
		//Reverse the byte order and convert to an int
		for(j = 0; j < 4; j++){
			swap_c[j] = tmp[3-j];
		}
		nMachines = (int)*swap_c;
		//Continues building names until number of machines is done
		while(nMachines > 0){
			//Insert a null character and copy string
			if(c[i] == '\0'){
				nMachines--;
				nBuff[count] = c[i];
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
				count = 0;
			}
			else{
				nBuff[count] = c[i];
				count++;
			}
			i++;
		}
	}

	//Close the input file
	close(fd);

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
