//Samuel Leonard
//sleonar5
//CS 360
//Lab 3: Fakemake

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include"fields.h"
#include"dllist.h"

//Function Prototypes
int process_H(Dllist);
long process_C(Dllist, Dllist, Dllist, long, int*);
void free_list(Dllist);

int main(int argc, char **argv){
	//Declarations
	int i = 0, check = 0, remade = 0, exists = 0;
	long max_header = 0, c_time = 0, co_time = 0;
	char *tmp_str, *exe_file, *f_str, *l_str, comp_str[100];
	IS is;
	Dllist c_files, headers, libs, flags, o_files, dnode, fnode, lnode;
	struct stat buf2;
	
	//Figures out the name of the description file
	if (argc < 2){
		is = new_inputstruct("fmakefile");
		if(is == NULL){
			fprintf(stderr, "fakemake: fmakefile No such file or directory\n");
			exit(1);
		}
	}
	else{
		is = new_inputstruct(argv[1]);
	}
	
	//Create the Dllist's for each type of input
	c_files = new_dllist();
	headers = new_dllist();
	libs = new_dllist();
	flags = new_dllist();
	o_files = new_dllist();
	
	//Read the input lines from the description file
	while(get_line(is) >= 0){
		if(is->NF != 0){
			if(strcmp(is->fields[0], "C") == 0){
				for(i = 1; i < is->NF; i++){
					dll_append(c_files, new_jval_s(strdup(is->fields[i])));
				}
			}
			else if(strcmp(is->fields[0], "H") == 0){
				for(i = 1; i < is->NF; i++){
					dll_append(headers, new_jval_s(strdup(is->fields[i])));
				}
			}
			else if(strcmp(is->fields[0], "L") == 0){
				for(i = 1; i < is->NF; i++){
					dll_append(libs, new_jval_s(strdup(is->fields[i])));
				}
			}
			else if(strcmp(is->fields[0], "F") == 0){
				for(i = 1; i < is->NF; i++){
					dll_append(flags, new_jval_s(strdup(is->fields[i])));
				}
			}
			else if(strcmp(is->fields[0], "E") == 0){
					exe_file = strdup(is->fields[1]);
					check++;
					if(check == 2){
						fprintf(stderr, "fmakefile (%d) cannot have more than one E line\n", is->line);
						exit(1);
					}
			}
			else{
				fprintf(stderr,"Invalid Input\n");
				exit(1);
			}
		}
	}
	
	//Checks to see if missing the E field
	if(check == 0){
		fprintf(stderr, "No executable specified\n");
		exit(1);
	}

	//Process the Header files and check for updates
	max_header = process_H(headers);
	
	//Process the C files and look for .o files that may be older
	co_time = process_C(c_files, flags, o_files, max_header, &remade);
	
	//Check to see if executable needs created or recreated by looking at whether
	//the .o files were remade or the .o files are newer than the executable
	strcpy(comp_str, "gcc -o ");
	strcat(comp_str, exe_file);
	dll_traverse(fnode, flags){
		f_str = (char*)fnode->val.s;
		strcat(comp_str, " ");
		strcat(comp_str, f_str);
	}
	dll_traverse(dnode, o_files){
		tmp_str = (char*)dnode->val.s;
		strcat(comp_str, " ");
		strcat(comp_str, tmp_str);
	}
	dll_traverse(lnode, libs){
		l_str = (char*)lnode->val.s;
		strcat(comp_str, " ");
		strcat(comp_str, l_str);
	}
	
	if((int)remade == 1){
		printf("%s\n", comp_str);
		check = system(comp_str);
		if(check != 0){
			fprintf(stderr, "Command failed.  Fakemake exiting\n");
			exit(1);
		}
	}
	else{
		exists = stat(exe_file, &buf2);
		if(exists < 0 || buf2.st_mtime < co_time){
			printf("%s\n", comp_str);
			check = system(comp_str);
			if(check != 0){
				fprintf(stderr, "Command failed.  Fakemake exiting\n");
				exit(1);
			}
		}
		else{
			printf("%s up to date\n", exe_file);
			exit(1);
		}
	}
	
	jettison_inputstruct(is);

	return 0;
}

//Function Name: process_H
//Description: Processes the Header files and check for updates
//Inputs: Takes a Dllist of header files
//Outputs: None
//Returns: Returns the maximum update time of all headers
int process_H(Dllist h){
	Dllist dnode;
	char *tmp_str;
	long max_header = 0, exists = 0;
	struct stat buf;
	
	dll_traverse(dnode, h){
		tmp_str = (char*) dnode->val.s;
		exists = stat(tmp_str, &buf);
		if(exists < 0){
			fprintf(stderr, "fmakefile: %s: No such file or directory\n", tmp_str);
			exit(1);
		}
		else{
			if(max_header < buf.st_mtime){
				max_header = buf.st_mtime;
			}
		}
	}
	return max_header;
}

//Function Name: process_C
//Description: Processes the C files and look for .o files that may be older
//Inputs: Takes Dllists for the c files, o files and flags. Also the max
//		header time and a pointer to the remade variable
//Outputs: Fills the o_files dllist and updates the remade variable
//Returns: Returns the max o file update time
long process_C(Dllist c, Dllist f, Dllist o_files, long max_header, int *remade){
	int check = 0;
	Dllist dnode, fnode;
	char *tmp_str, *f_str, tmp[100], comp_str[100];
	long exists = 0, c_time = 0, co_time = 0;
	struct stat buf, buf1;
	dll_traverse(dnode, c){
		tmp_str = (char*) dnode->val.s;
		exists = stat(tmp_str, &buf);
		if(exists < 0){
			fprintf(stderr, "fmakefile: %s: No such file or directory\n", tmp_str);
			exit(1);
		}
		else{
			c_time = buf.st_mtime;
			//Build the .o string
			strcpy(tmp, tmp_str);
			tmp[strlen(tmp_str)-1] = 'o';
			dll_append(o_files, new_jval_s(strdup(tmp)));
			exists = stat(tmp, &buf1);
			if(exists < 0 || buf1.st_mtime < c_time || buf1.st_mtime < max_header){
				strcpy(comp_str, "gcc -c ");
				dll_traverse(fnode, f){
					f_str = (char*)fnode->val.s;
					strcat(comp_str, f_str);
					strcat(comp_str, " ");
				}
				strcat(comp_str, tmp_str);
				printf("%s\n", comp_str);
				*remade = 1;
				//Make the system call on the .c file
				check = system(comp_str);
				if(check != 0){
					fprintf(stderr, "Command failed.  Exiting\n");
					exit(1);
				}
			}
			if(co_time < buf1.st_mtime){
				co_time = buf1.st_mtime;
			}
		}
	}
	return co_time;
}

//Function Name: free_list
//Description: Frees whichever list is passed include
//Inputs: A Dllist
//Outputs: None
//Returns: None
void free_list(Dllist x){
	Dllist xnode;
	dll_traverse(xnode, x){
		free(xnode);
	}
}
