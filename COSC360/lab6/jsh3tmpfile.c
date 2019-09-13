void prompt(int n);

main(int c, char **argv){
	int i, j, pid, status;
	int is_pipe = 0,
	     check = -1,
			 look = 0;
	int fd1, fd2, pipefd[2];
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
			
			//Parse the input
			for(i = 0, j = 0; i < is->NF; i++, j++){
				//Check for pipes
				if(strcmp(is->fields[i], "|") == 0){
					tmp[i] = NULL;
					is_pipe = 1;
					check = pipe(pipefd);
					if(check < 0){
						perror("pipe");
						exit(1);
					}
										
					//Fork the process
					pid = fork();
			
					//Enter into childs process and execute command
					if(pid == 0){
						//Dup the stdout to pipe
						if(dup2(pipefd[1], 1) != 1){
							perror("dup2(pipefd[1])");
							exit(1);
						}
						//close the pipes for the child
						close(pipefd[1]);
						close(pipefd[0]);
						
						//Check for redirection, and appending
						for(j = 0; j < i; j++){
							if(strcmp(tmp[i], "<") == 0){
								fd1 = open(tmp[j+1], O_RDONLY);
								if(fd1 < 0){
									perror(tmp[j+1]);
									exit(1);
								}
								if(dup2(fd1, 0) != 0){
									perror("dup2");
									exit(1);
								}
								tmp[j] = NULL;
								//Close the fd1 file descriptor
								close(fd1);
							}
							else if(strcmp(tmp[j], ">") == 0){
								fd2 = open(tmp[i+1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
								if(fd2 < 0){
									perror(tmp[j+1]);
									exit(2);
								}
								if(dup2(fd2, 1) != 1){
									perror("dup2");
									exit(1);
								}
								tmp[j] = NULL;
								//Close the fd2 file descriptor
								close(fd2);
							}
							else if(strcmp(tmp[j], ">>") == 0){
								fd2 = open(tmp[j+1], O_WRONLY | O_APPEND);
								if(fd2 < 0){
									perror(tmp[j+1]);
									exit(2);
								}
								if(dup2(fd2, 1) != 1){
									perror("dup2");
									exit(1);
								}
								tmp[j] = NULL;
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
								//close pipes in parent
								close(pipefd[1]);
								close(pipefd[0]);
								//Wait for child process to return
								while(wait(&status) != pid);
							}
						}
						prompt(c);
					}
				}
				//Build the arguments
				else{
					tmp[j] = malloc(sizeof(char) * strlen(is->fields[i]));
					tmp[j] = strdup(is->fields[i]);
				}
			}
				
			if(is_pipe == 0){
				if(strcmp(is->fields[is->NF-1], "&") == 0){
					tmp[is->NF-1] = NULL;
				}
				else{
					tmp[is->NF] = NULL;
				}
				//Check for redirection
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