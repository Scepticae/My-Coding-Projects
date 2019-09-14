//Samuel Leonard
//sleonar5
//Lab 4: Jtar

#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<limits.h>
#include<sys/stat.h>
#include<string.h>
#include<utime.h>
#include"jrb.h"
#include"dllist.h"

//Function Prototypes
char *parse_args(int, char**);
void process_files(char*, JRB, JRB);
void extract_files();

int main(int argc, char **argv){
	int i;
	char *flag;
	JRB inodes, realpaths;
	
	//Looks through arguments and checks for errors and returns
	//flag type
	flag = parse_args(argc, argv);
	
	//Instantiating the 'c' option and processing the files
	if(strcmp(flag, "c") == 0){
		//Create the Red-Black Trees
		inodes = make_jrb();
		realpaths = make_jrb();
		
		for(i = 2; i < argc; i++){
			process_files(argv[i], inodes, realpaths);
		}
	}
	//Instantiating the 'x' option and  extracting files
	else if(strcmp(flag, "x") == 0){
		extract_files();
	}
	
	return 0;
}

/*
	Function Name: parse_args
	Function Description: Checks to make sure there are enough arguments
		and that the flags are correct
	Function Inputs:
		int c : Number of Arguments
		char **f : The Input Arguments
	Function Outputs: Error Messages
	Function Return: The Flags
*/
char *parse_args(int c, char **f){
	//Checks for the correct amount of arguments and the right flags
	if(!(c > 2) && strcmp(f[1], "x") != 0 && strcmp(f[1], "xv") != 0){
		fprintf(stderr, "Not enough arguments\n");
	}
	else{
		if(strcmp(f[1], "c") != 0 && strcmp(f[1], "cv") != 0 && 
			strcmp(f[1], "x") != 0 && strcmp(f[1], "xv") != 0){
			fprintf(stderr, "Incorrect flag option\n");	
		}
		else
			return f[1];
	}
}

/*
	Function Name: process_files
	Function Description: Takes command line arguments and creates a tarfile
		with directories, subdirectories, files and links
	Function Inputs: 
		char *tmp : the file or directory name
		JRB ino : tree of inodes
		JRB rp : tree of real paths
	Function Outputs: stdout (Directories, Subdirectories, Files)
	Function Return: Nothing
*/
void process_files(char *tmp, JRB ino, JRB rp){
	int num, j, exists = 0;
	char *s, *contents, abs_path[PATH_MAX+1];
	char check[1];
	DIR *d;
	FILE *fd;
	struct dirent *de;
	struct stat buf;
	Dllist dy, dnode;
	
	//Check to see if name exists
	exists = lstat(tmp, &buf);
	if(exists < 0){
		fprintf(stderr, "No such file or directory\n");
		exit(1);
	}

	//Check for duplicate entries
	if(jrb_find_str(rp, realpath(tmp, abs_path)) == NULL){
		jrb_insert_str(rp, strdup(abs_path), JNULL);
	}
	else{
		return;
	}

	//Checks to see if it is a symbolic link
	if(S_ISLNK(buf.st_mode)){
		return;
	}
	
	//Checks to see if inode is in list and adds to list if not and writes contents
	if(jrb_find_int(ino, buf.st_ino) == NULL){
		jrb_insert_int(ino, buf.st_ino, JNULL);
	}
	//If inode is there, then its a hardlink, just write the name and link
	else{
		j = strlen(tmp);
		num = fwrite(&j, sizeof(int), 1, stdout);
		num = fwrite(tmp, strlen(tmp), 1, stdout);
		num = fwrite(&buf, sizeof(struct stat), 1, stdout);
		
		return;
	}

	//Check to see if file is a directory or regular file
	if(S_ISDIR(buf.st_mode)){
		dy = new_dllist();
		j = strlen(tmp);
		//Writes the directory names
		num = fwrite(&j, sizeof(int), 1, stdout);
		num = fwrite(tmp, strlen(tmp), 1, stdout);
		num = fwrite(&buf, sizeof(struct stat), 1, stdout);
		s = (char*)malloc(sizeof(char)*(strlen(tmp)+300));
		
		//Reads through the directories and puts them in  a list 
		d = opendir(tmp);
		for (de = readdir(d); de != NULL; de = readdir(d)){
			if(strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
				sprintf(s, "%s/%s", tmp, de->d_name);
				dll_append(dy, new_jval_s(strdup(s)));
			}
		}
		closedir(d);
	}
	else{
		//Writes the regular files stat struct
		j = strlen(tmp);
		num = fwrite(&j, sizeof(int), 1, stdout);
		num = fwrite(tmp, strlen(tmp), 1, stdout);
		num = fwrite(&buf, sizeof(struct stat), 1, stdout);
		
		//Write the file contents
		fd = fopen(tmp, "r");
		contents = (char*)malloc(sizeof(char)*buf.st_size);
		num = fread(contents, 1, buf.st_size, fd);
		num = fwrite(contents, 1, num, stdout);
		fclose(fd);
		
		return;
	}

	//Free up memory 
	dll_traverse(dnode, dy){
		process_files(dnode->val.s, ino, rp);
		free(dnode->val.s);
	}
	
	//Free the dllist and temp name
	free_dllist(dy);
	free(s);
}

/*
	Function Name: extract_files
	Function Description: Extracts the contents of a tarfile and builds the
		appropriate directories, subdirectories and files
	Function Inputs: stdin (tarfile)
	Function Outputs: Files and Directories
	Function Return: Nothing
*/
void extract_files(){
	int num, fnum, n;
	char *tmp, *name, *fcontents;
	struct stat rbuf, *tbuf, *chbuf;
	struct utimbuf ubuf;
	FILE *fd;
	JRB f_links, ds, fnode;
	
	//Create the JRB for finding the hardlink
	f_links = make_jrb();
	ds = make_jrb();
	
	//Reads the tarfile in and extracts the input
	num = fread(&n, sizeof(int), 1, stdin);
	while(num > 0){
		tmp = (char*)malloc(sizeof(char)*(n+1));
		memset(tmp, 0, n+1);
		fread(tmp, sizeof(char), n, stdin);
		name = strdup(tmp);
		fread(&rbuf, sizeof(struct stat), 1, stdin);
		
		//Check the inodes to see if contents need written
		fnode = jrb_find_int(f_links, rbuf.st_ino);
		if(fnode == NULL){
			jrb_insert_int(f_links, rbuf.st_ino, new_jval_s(tmp));
			if(S_ISDIR(rbuf.st_mode)){ 
				mkdir(name, 0777);
				
				//Create a new tmp buf to hold current rbuf value and insert in tree
				tbuf = malloc(sizeof(struct stat));
				*tbuf = rbuf;
				jrb_insert_str(ds, name, new_jval_v(tbuf));
			}
			else {
				//Create the regular files
				fd = fopen(name, "w");
				
				//Change the protection for regular files
				chmod(name, rbuf.st_mode);
				
				//Write the contents of the file
				fcontents = (char*)malloc(sizeof(char)*rbuf.st_size);
				fnum = fread(fcontents, 1, rbuf.st_size, stdin);
				fwrite(fcontents, 1, fnum, fd);
				fclose(fd);
				
				//Modify the Mod and Access Times
				ubuf.modtime = rbuf.st_mtime;
				ubuf.actime = rbuf.st_atime;
				utime(name, &ubuf);
			}
		}
		else{
			//Create the hardlinks
			link(fnode->val.s, tmp);
			
			//Modify the Mod and Access Times
			ubuf.modtime = rbuf.st_mtime;
			ubuf.actime = rbuf.st_atime;
			utime(name, &ubuf);
		}
		//Updates the while loop
		num = fread(&n, sizeof(int), 1, stdin);
	}
	//Change the protection for the directories
	jrb_traverse(fnode, ds){
		chbuf = (struct stat*)fnode->val.v;
		chmod(fnode->key.s, chbuf->st_mode);
		
		//Modify the Mod and Access Times
		ubuf.modtime = chbuf->st_mtime;
		ubuf.actime = chbuf->st_atime;
		utime(fnode->key.s, &ubuf);
	}
}
