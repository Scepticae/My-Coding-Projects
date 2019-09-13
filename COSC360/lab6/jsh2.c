//Samuel Leonard
//sleonar5
//Lab 6: Jsh


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/wait.h>
#include"fields.h"

void prompt(int n);

main(int c, char **argv){
	int i, j, pid, check = -1, status;
	int fd1, fd2;
	char *tmp[100];
	IS is;
	
	//Print the prompt
	prompt(c);
		
	//Create the new inputstruct
	is = new_inputstruct(NULL);
	
	//Read in the shell input
	while(get_line(is) >= 0){
		//Check for no input on the shell and exit if exit
		if(is->NF != 0){
			if(strcmp(is->fields[0], "exit") == 0){exit(0);}
			
			//Fork the process
			pid = fork();
			
			//Enter into childs process and execute command
			if(pid == 0){
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
				
				//Check for redirection, and appending
				for(i = 0; i < j; i++){
					if(strcmp(tmp[i], "<") == 0){
						fd1 = open(tmp[i+1], O_RDONLY);
						if(fd1 < 0){
							perror(tmp[i+1]);
							exit(1);
						}
						if(dup2(fd1, 0) != 0){
							perror("dup2");
							exit(1);
						}
						tmp[i] = NULL;
						//Close the fd1 file descriptor
						close(fd1);
					}
					else if(strcmp(tmp[i], ">") == 0){
						fd2 = open(tmp[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
						if(fd2 < 0){
							perror(tmp[i+1]);
							exit(2);
						}
						if(dup2(fd2, 1) != 1){
							perror("dup2");
							exit(1);
						}
						tmp[i] = NULL;
						//Close the fd2 file descriptor
						close(fd2);
					}
					else if(strcmp(tmp[i], ">>") == 0){
						fd2 = open(tmp[i+1], O_WRONLY | O_APPEND);
						if(fd2 < 0){
							perror(tmp[i+1]);
							exit(2);
						}
						if(dup2(fd2, 1) != 1){
							perror("dup2");
							exit(1);
						}
						tmp[i] = NULL;
						//Close the file descriptor
						close(fd2);
					}	
				}

				execvp(tmp[0], tmp);
				perror(tmp[0]);
				exit(1);
			}
			//Continue with parent process
			else{
				if(is->NF != 0){
					if(strcmp(is->fields[is->NF-1], "&") != 0){
						//Wait for child process to return
						while(wait(&status) != pid);
					}
				}
				prompt(c);
			}
		}
		else{
			prompt(c);
		}
	}
	
	//Free the input struct
	jettison_inputstruct(is);
	
	exit(0);
}

//Name: prompt
//Description: prompts the user for input
//Inputs: n, num of args on command line
//Outputs: None
//Return: None
void prompt(int n){
	if(n < 2){
		printf("jsh2: ");
	}
}
