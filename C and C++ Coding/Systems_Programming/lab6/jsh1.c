#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include"fields.h"

main(int c, char **argv){
	int i, j, pid, check = -1, status;
	char *tmp[100];
	IS is;
	
	//Print the prompt
	if(c < 2){
		printf("jsh1: ");
	}
		
	//Create the new inputstruct
	is = new_inputstruct(NULL);
	
	//Read in the shell input
	while(get_line(is) >= 0){
		for(i = 0, j = 0; i < is->NF; i++, j++){
			if(strcmp(is->fields[i], "&") != 0){
				tmp[j] = malloc(sizeof(char) * strlen(is->fields[i]));
				tmp[j] = strdup(is->fields[i]);
			}
			//Do not add the '&' to the tmp array
			else{
				j--;
			}
		}
		tmp[j] = NULL;
		
		//Fork the process
		pid = fork();
		
		//Enter into childs process and execute command
		if(pid == 0){
			if(is->NF != 0){
				execvp(tmp[0], tmp);
				perror(tmp[0]);
				exit(1);
			}
		}
		//Continue with parent process
		else{
			if(strcmp(is->fields[is->NF-1], "&") != 0){
				//Wait for child process to return
				while(wait(&status) != pid);	
			}

			if(c < 2){
				printf("jsh1: ");
			}
		}
	}
	
	//Free the input struct
	jettison_inputstruct(is);
	
	exit(0);
}
