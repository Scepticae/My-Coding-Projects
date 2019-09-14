/*
Samuel Leonard
sleonar5
Lab 1
famtree.c : This program takes an unsorted list of people
	and places them in order according to their family tree
	hierarchy.
*/

//Included Header Files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fields.h"
#include"jrb.h"
#include"dllist.h"

//Struct with Person information
typedef struct{
	int visited;//for cycle checks
	int printed;//for to_print function
	char *name;
	char *sex;
	char *father;
	char *mother;
	Dllist children;

}Person;

//Function to test for cycles declaration
int is_descendant(Person*);

//Print the names and information
void to_Print(Person*);

int main(int argc, char *argv[])
{
	int i, placed;
	char fname[1000]; 
	char *p_name;
	Person *p, *per, *s, *parent;
	Person *f, *m;
	Dllist iter, toprint;
	JRB snode, srch, people;
	IS is;
	
	is = new_inputstruct(NULL);
	people = make_jrb();
	
	//Read in the input
	while(get_line(is) >= 0){
		//Makes sure it is not the field "SEX"
		if(strcmp(is->fields[0], "SEX") != 0 && is->NF > 0){
			
			//Construct the persons name
			strcpy(fname, is->fields[1]);
			for(i = 2; i < is->NF; i++){
				strcat(fname, " ");
				strcat(fname, is->fields[i]);
			}
		
			//Search for name
			snode = jrb_find_str(people, fname);
			
			placed = 0;

			//Puts the information in for the appropriate person
			if(snode == NULL){
				p = (Person*)malloc(sizeof(Person));
				p->name = strdup(fname);
				p->sex = "Unknown";
				p->father = "Unknown";
				p->mother = "Unknown";
				p->visited = 0;
				p->printed = 0;
				p->children = new_dllist();
			
				//Insert the person into the tree
				jrb_insert_str(people, p->name, new_jval_v(p));
			}
			else{
				//Set a pointer to the node field in the tree for editing
				p = (Person*) snode->val.v;
			}
			
			//Make changes to the node based on first field type
			if(strcmp(is->fields[0], "PERSON") == 0){
				p_name = strdup(p->name);
			}
			else if(strcmp(is->fields[0], "FATHER") == 0){
				//Find the person in the tree to set links
				srch = jrb_find_str(people, p_name);
				per = (Person*) srch->val.v;
				per->father = p->name;
				
				//Check the sex to make sure there is not a mismatch
				if(strcmp(p->sex, "Unknown") == 0){
					p->sex = "Male";
				}
				else{
					if(strcmp(p->sex, "Male") != 0){
						fprintf(stderr, "Bad input: sex mismatch on line %d", is->line);
					}
				}
			
				dll_traverse(iter, p->children){
					s = (Person*)iter->val.v;
					if(strcmp(s->name, per->name) == 0){
						placed = 1;
					}
				}
				if(placed == 0){
					dll_append(p->children, new_jval_v(per));
				}
			}
			else if(strcmp(is->fields[0], "MOTHER") == 0){
				srch = jrb_find_str(people, p_name);
				per = (Person*) srch->val.v;
				per->mother = p->name;
				
				//Check the sex to make sure there is not a mismatch
				if(strcmp(p->sex, "Unknown") == 0){
					p->sex = "Female";
				}
				else{
					if(strcmp(p->sex, "Female") != 0){
						fprintf(stderr, "Bad input: sex mismatch on line %d", is->line);
					}
				}
			
				dll_traverse(iter, p->children){
					s = (Person*)iter->val.v;
					if(strcmp(s->name, per->name) == 0){
						placed = 1;
					}
				}
				if(placed == 0){
					dll_append(p->children, new_jval_v(per));
				}
			}
			else if(strcmp(is->fields[0], "FATHER_OF") == 0){
				srch = jrb_find_str(people, p_name);
				per = (Person*) srch->val.v;
				p->father = per->name;
				
				//Check the sex to make sure there is not a mismatch
				if(strcmp(per->sex, "Unknown") == 0){
					per->sex = "Male";
				}
				else{
					if(strcmp(per->sex, "Male") != 0){
						fprintf(stderr, "Bad input: sex mismatch on line %d", is->line);
					}
				}
				
				dll_traverse(iter, p->children){
					s = (Person*)iter->val.v;
					if(strcmp(s->name, p->name) == 0){
						placed = 1;
					}
				}
				if(placed == 0){
					dll_append(per->children, new_jval_v(p));
				}
			}
			else if(strcmp(is->fields[0], "MOTHER_OF") == 0){
				srch = jrb_find_str(people, p_name);
				per = (Person*) srch->val.v;
				p->mother = per->name;
				
				//Check the sex to make sure there is not a mismatch
				if(strcmp(per->sex, "Unknown") == 0){
					per->sex = "Female";
				}
				else{
					if(strcmp(per->sex, "Female") != 0){
						fprintf(stderr, "Bad input: sex mismatch on line %d", is->line);
					}
				}

				dll_traverse(iter, p->children){
					s = (Person*)iter->val.v;
					if(strcmp(s->name, p->name) == 0){
						placed = 1;
					}
				}
				if(placed == 0){
					dll_append(per->children, new_jval_v(p));
				}
			}
		}
		else if(strcmp(is->fields[0], "SEX") == 0 && is->NF > 0){
			srch = jrb_find_str(people, p_name);
			per = (Person*) srch->val.v;
			if(strcmp(is->fields[1], "M") == 0){
				//Check the sex to make sure there is not a mismatch
				if(strcmp(per->sex, "Unknown") == 0){
					per->sex = "Male";
				}
				else{
					if(strcmp(per->sex, "Male") != 0){
						fprintf(stderr, "Bad input: sex mismatch on line %d", is->line);
					}
				}
			}
			else if(strcmp(is->fields[1], "F") == 0){
				//Check the sex to make sure there is not a mismatch
				if(strcmp(per->sex, "Unknown") == 0){
					per->sex = "Female";
				}
				else{
					if(strcmp(per->sex, "Female") != 0){
						fprintf(stderr, "Bad input: sex mismatch on line %d", is->line);
					}
				}
			}
		}
	}
	
	free(p_name);

	//Check for Cycles
	jrb_traverse(snode, people){
		p = (Person*)snode->val.v;
		if(is_descendant(p) == 1){
			fprintf(stderr, "Bad input -- cycle in specification\n");
			exit(1);
		}
	}
	
	//Create a new dllist
	toprint = new_dllist();
	
	//Put all the people in a dllist
	jrb_traverse(snode, people){
		p = (Person*)snode->val.v;
		dll_append(toprint, new_jval_v(p));
	}
	
	//Print the people structs with no person able to be printed unless
	//parents have been printed
	while(toprint->flink != toprint){
		iter = toprint->flink;
		parent = (Person*)iter->val.v;
		if(parent->printed == 0){
			//Search for persons parent nodes
			if(strcmp(parent->father, "Unknown") != 0){
				srch = jrb_find_str(people, parent->father);
				f = (Person*) srch->val.v;
			}
			if(strcmp(parent->mother, "Unknown") != 0){
				srch = jrb_find_str(people, parent->mother);
				m = (Person*) srch->val.v;
			}
			
			//After checking the parents status print node accordingly
			if(parent->father == "Unknown" && parent->mother == "Unknown"){
				to_Print(parent);
				parent->printed = 1;

				dll_delete_node(iter);
				printf("\n\n");
			}
			else if(parent->father == "Unknown" && m->printed == 1){
				to_Print(parent);
				parent->printed = 1;

				dll_delete_node(iter);
				printf("\n\n");
			}
			else if(parent->mother == "Unknown" && f->printed == 1){
				to_Print(parent);
				parent->printed = 1;

				dll_delete_node(iter);
				printf("\n\n");
			}
			else if(f->printed == 1 && m->printed == 1){
				to_Print(parent);
				parent->printed = 1;

				dll_delete_node(iter);
				printf("\n\n");
			}
			else{
				dll_append(toprint, new_jval_v(parent));
				dll_delete_node(iter);
			}
		}
	}
	
	//Free the lists after finished
	free_dllist(toprint);
	free_dllist(p->children);
	
	//Put all the people in a dllist
	jrb_traverse(snode, people){
		p = (Person*)snode->val.v;
		free(p);
	}
	jrb_free_tree(people);
	
	//Clean the inputstruct
	jettison_inputstruct(is);
	
	return 0;
}
//Function definition for checking cycles
int is_descendant(Person *p){
	Dllist it;
	Person *srch;
	
	if (p->visited == 1) return 0;  	//I.e. we've processed this 
										//person before and he/she's ok
	if (p->visited == 2) return 1;	//I.e. the graph is messed up
	
	p->visited = 2;
	
	//if(peop->children->flink != peop->children)
	if(dll_empty(p->children) != 1){
		dll_traverse(it, p->children){
			srch = (Person*)it->val.v;
			if(is_descendant(srch)) return 1;
		}
	}
	
	p->visited = 1;
	
	return 0;
}
//Function to print out the people
void to_Print(Person *p){
	Person *nP;//person needs printed
	Dllist it;
	
	printf("%-40s\n", p->name);
	printf("  Sex: %-10s\n", p->sex);
	printf("  Father: %-40s\n", p->father);
	printf("  Mother: %-40s\n", p->mother);
	printf("  Children:");
		
	if(p->children->flink != p->children){
		dll_traverse(it, p->children){
			nP = (Person*)it->val.v;
			printf("\n    %-40s", nP->name);
		}
	}
	else printf(" None");
}
