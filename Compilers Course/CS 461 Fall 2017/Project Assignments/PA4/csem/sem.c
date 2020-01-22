# include <stdio.h>
# include "cc.h"
# include "semutil.h"
# include "sem.h"
# include "sym.h"

#define MAXARGS 50
#define MAXLOCS 50

//Defined Elsewhere
extern int formalnum;
extern int localnum;
extern char formaltypes[MAXARGS];
extern char localtypes[MAXLOCS];
extern int localwidths[MAXLOCS];

/*
 * backpatch - backpatch list of quadruples starting at p with k
 */
void backpatch(struct sem_rec *p, int k)
{
   //Print the backpatch statement
	 printf("B%d=L%d\n", p->s_place, k);
}

/*
 * bgnstmt - encountered the beginning of a statement
 */
void bgnstmt()
{
	int c;
  extern int lineno;
	static int laststmt = 0;
	
	skip();
	c = getchar();
	putbak(c);
	if(c != '}' && lineno != laststmt){
		printf("bgnstmt %d\n", lineno);
		laststmt = lineno;
	}
	else{
    fprintf(stderr, "sem: bgnstmt not implemented\n");
	}
}

/*
 * call - procedure invocation
 */
struct sem_rec *call(char *f, struct sem_rec *args)
{
   struct sem_rec *tmp;
	 struct id_entry *p;
	 
	 p = lookup(f, 0);
	 
	 //Allocate memory
	 tmp = node(nexttemp(), 0, 0, 0);

	 if(p->i_scope == GLOBAL){
	   //Print the call function statement
	   printf("t%d := global %s\n", currtemp(), f);
	 }
	 else if(p->i_scope == LOCAL){
		 printf("t%d := local %s\n", currtemp(), f);
	 }
	 
	 //Set the struct
	 tmp->s_place = currtemp();
	 tmp->s_mode = p->i_type;
	 
   return (tmp);
}

/*
 * ccand - logical and
 */
struct sem_rec *ccand(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccand not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccexpr - convert arithmetic expression to logical expression
 */
struct sem_rec *ccexpr(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccexpr not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccnot - logical not
 */
struct sem_rec *ccnot(struct sem_rec *e)
{
   fprintf(stderr, "sem: ccnot not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * ccor - logical or
 */
struct sem_rec *ccor(struct sem_rec *e1, int m, struct sem_rec *e2)
{
   fprintf(stderr, "sem: ccor not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * con - constant reference in an expression
 */
struct sem_rec *con(char *x)
{
	 struct sem_rec *tmp;
	 
	 //Allocate memory
	 tmp = node(nexttemp(), 0, 0, 0); 
   
	 //Print the constant
	 printf("t%d := %s\n", currtemp(), x);
	 
	 //Set and return struct
	 tmp->s_place = currtemp();
	 tmp->s_mode = T_INT;
	 
   return (tmp);
}

/*
 * dobreak - break statement
 */
void dobreak()
{
   fprintf(stderr, "sem: dobreak not implemented\n");
}

/*
 * docontinue - continue statement
 */
void docontinue()
{
   fprintf(stderr, "sem: docontinue not implemented\n");
}

/*
 * dodo - do statement
 */
void dodo(int m1, int m2, struct sem_rec *e, int m3)
{
   fprintf(stderr, "sem: dodo not implemented\n");
}

/*
 * dofor - for statement
 */
void dofor(int m1, struct sem_rec *e2, int m2, struct sem_rec *n1,
           int m3, struct sem_rec *n2, int m4)
{
   fprintf(stderr, "sem: dofor not implemented\n");
}

/*
 * dogoto - goto statement
 */
void dogoto(char *id)
{
   fprintf(stderr, "sem: dogoto not implemented\n");
}

/*
 * doif - one-arm if statement
 */
void doif(struct sem_rec *e, int m1, int m2)
{
    fprintf(stderr, "sem: doif not implemented\n");
}

/*
 * doifelse - if then else statement
 */
void doifelse(struct sem_rec *e, int m1, struct sem_rec *n,
                         int m2, int m3)
{
   fprintf(stderr, "sem: doifelse not implemented\n");
}

/*
 * doret - return statement
 */
void doret(struct sem_rec *e)
{
	 //Print the return statement for record
   printf("reti t%d\n", e->s_place);
}

/*
 * dowhile - while statement
 */
void dowhile(int m1, struct sem_rec *e, int m2, struct sem_rec *n,
             int m3)
{
   fprintf(stderr, "sem: dowhile not implemented\n");
}

/*
 * endloopscope - end the scope for a loop
 */
void endloopscope(int m)
{
   fprintf(stderr, "sem: endloopscope not implemented\n");
}

/*
 * exprs - form a list of expressions
 */
struct sem_rec *exprs(struct sem_rec *l, struct sem_rec *e)
{
   //struct sem_rec *tmp;
	 
	 //Allocate memory
	 //tmp = node(nexttemp(), 0, 0, 0);
	 
	 //Print args list
	 printf("argsi t%d\n", l->s_place);
	 printf("argsi t%d\n", e->s_place);
	 
	 
   return ((struct sem_rec *) NULL);
}


/*
 * fhead - beginning of function body
 */
void fhead(struct id_entry *p)
{
   printf("func %s\n", p->i_name);
   unsigned int i;
   for (i = 0; i < formalnum; i++) {
       if (formaltypes[i] == 'f') {
           printf("formal 8\n");
       } else if (formaltypes[i] == 'i') {
           printf("formal 4\n");
       } else {
           yyerror("formal type somehow stored incorrectly");
       }
   }
   for (i = 0; i < localnum; i++) {
       if (localtypes[i] == 'f') {
           printf("localloc %d\n", 8 * localwidths[i]);
       } else if (localtypes[i] == 'i') {
           printf("localloc %d\n", 4 * localwidths[i]);
       } else {
           yyerror("formal type somehow stored incorrectly");
       }
   }
}

/*
 * fname - function declaration
 */
struct id_entry *fname(int t, char *id)
{
	 struct id_entry *p;
	 
	 if((p = lookup(id, 0)) == NULL){
		 p = install(id, 0);
	 }
	 else if(p->i_defined){
		 yyerror("procedure previously declared");
	 }
	 else if(p->i_type != t){
		yyerror("function declaration types do not match");
	 }
	 
	 //Set the struct values
	 p->i_type = t;
	 p->i_scope = GLOBAL;
	 p->i_defined = 1;
	 enterblock();
	 formalnum = 0;
	 localnum = 0;
	 
	 return p;
}

/*
 * ftail - end of function body
 */
void ftail()
{
	//Print the fend label
   printf("fend\n");
	 
	 //Leave the block
	 leaveblock();
}

/*
 * id - variable reference
 */
struct sem_rec *id(char *x)
{
	 //Create a semantic record and table entry
	 struct sem_rec *tmp;
	 struct id_entry *p;
	 
	 //Check to make sure x can be found in table
	 if((p = lookup(x, 0)) == NULL){
		 yyerror("%s has not been declared\n", x);
	 }
	 
	 //Allocate memory for tmp
	 tmp = node(nexttemp(), 0, 0, 0);
	 
	 //Check to see if local, global or a param
	 if(p->i_scope == LOCAL){
		 printf("t%d := local %d\n", currtemp(), p->i_offset);
	 }
	 else if(p->i_scope == GLOBAL){
		 printf("t%d := global %s\n", currtemp(), p->i_name);
	 }
	 else if(p->i_scope == PARAM){
		 printf("t%d := param %d\n", currtemp(), p->i_offset);
	 }
	 
	 //Set the semantic record
	 tmp->s_place = currtemp();
	 tmp->s_mode = p->i_type;
	 
   return (tmp);
}

/*
 * indx - subscript
 */
struct sem_rec *indx(struct sem_rec *x, struct sem_rec *i)
{
	 char c;
   struct sem_rec *tmp;
	 
	 //Allocate memory
	 tmp = node(nexttemp(), 0, 0, 0);
	
	 //Checks to see if array of doubles or ints
	 if(x->s_mode == T_DOUBLE){ c = 'f'; }
	 else { c = 'i'; }
	 
	 //Print the indexed statement
	 printf("t%d := t%d []%c t%d\n", currtemp(), x->s_place, c, i->s_place);
	 
   return (tmp);
}

/*
 * labeldcl - process a label declaration
 */
void labeldcl(char *id)
{
   fprintf(stderr, "sem: labeldcl not implemented\n");
}

/*
 * m - generate label and return next temporary number
 */
int m()
{
   static int num = 0;
	 
	 //Set increments
	 num++;
	 
	 //Print the label number
	 printf("label L%d\n", num);
	 
	 //Return next temporary number
   return (num);
}

/*
 * n - generate goto and return backpatch pointer
 */
struct sem_rec *n()
{
   fprintf(stderr, "sem: n not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * op1 - unary operators
 */
struct sem_rec *op1(char *op, struct sem_rec *y)
{
		char t; // type
    struct sem_rec *tmp;
	 
	 //Allocate memory
	 tmp = node(nexttemp(),  0, 0, 0);
	 
	 //Check for whether type is int or float
	 if(y->s_mode == 1){ t = 'i'; }
	 else if(y->s_mode == 4){ t = 'f'; }
	 
	 //Print the unary operation
	 printf("t%d := %s%c t%d\n", currtemp(), op, t, y->s_place);
	 
	 //Set the tmp structure
	 tmp->s_place = currtemp();
	 tmp->s_mode = y->s_mode;
	 
   return (tmp);
}

/*
 * op2 - arithmetic operators
 */
struct sem_rec *op2(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: op2 not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * opb - bitwise operators
 */
struct sem_rec *opb(char *op, struct sem_rec *x, struct sem_rec *y)
{
   fprintf(stderr, "sem: opb not implemented\n");
   return ((struct sem_rec *) NULL);
}

/*
 * rel - relational operators
 */
struct sem_rec *rel(char *op, struct sem_rec *x, struct sem_rec *y)
{
	 int check = 0, t_val;
	 char *t = "cv";
	 char c;
   struct sem_rec *tmp;
	 
	 //Allocate memory
	 tmp = node(nexttemp(), 0, 0, 0);
	 
	 //Check to see if types match
	 if(x->s_mode != y->s_mode){
		 if(x->s_mode == T_DOUBLE){
			 c = 'f';
		 }
		 else if(x->s_mode == T_INT){
			 c = 'i';
		 }
		 
		 //Print out the conversion statement
		 printf("t%d := %s%c t%d\n", currtemp(), t, c, y->s_place);
		 
		 //set a flag that this was entered
		 check = 1;
	 }
	 else{
		  if (x->s_mode == T_DOUBLE){
		   c = 'f';
	   }
	   else if(x->s_mode == T_INT){
		   c = 'i';
	   }
	 }

	 //Change the number the record is on based on whether there are 1 or two statements
	 if(check == 1){
		 //Print out the relationship statement
	   printf("t%d := t%d %s%c t%d\n", nexttemp(), x->s_place, op, c, currtemp());
	 }
	 else{
		 //Print out the relationship statement
	   printf("t%d := t%d %s%c t%d\n", currtemp(), x->s_place, op, c, y->s_place);
	 }
	 
	 //Set and return record
	 tmp->s_place = currtemp();
	 tmp->s_mode = x->s_mode;
	 
   return (tmp);
}

/*
 * set - assignment operators
 */
struct sem_rec *set(char *op, struct sem_rec *x, struct sem_rec *y)
{
	 char c;
   struct sem_rec *tmp;
	 
	 //Allocate memory
	 tmp = node(nexttemp(), 0, 0, 0);
	 
	 //Check type if float or int
	 if(x->s_mode == T_INT){ c = 'i'; }
	 else { c = 'f'; }
	 
	 //Check for null value for just =
	 if(op == ""){
		 //Print the assignment statement
		 printf("t%d := t%d %s=%c t%d\n", currtemp(), x->s_place, op, c, y->s_place);
	 }
	 else {
		 //Print the assignment statement
		 printf("t%d := t%d %s%c t%d\n", currtemp(), x->s_place, op, c, y->s_place);
	 }
	 
	 //Set and return the struct
	 tmp->s_place = currtemp();
	 tmp->s_mode = x->s_mode;
	 
   return (tmp);
}

/*
 * startloopscope - start the scope for a loop
 */
void startloopscope()
{
   fprintf(stderr, "sem: startloopscope not implemented\n");
}

/*
 * string - generate code for a string
 */
struct sem_rec *string(char *s)
{
   struct sem_rec *tmp;
	 
	 //Allocate memory
	 tmp = node(nexttemp(),  T_STR, 0, 0);
	 
	 //Print the semantic action of current record
	 printf("t%d = %s\n", currtemp(), s);
	 
	 //Set the semantic record
	 tmp->s_place = currtemp();
	 tmp->s_mode = T_STR;
	 
   return (tmp);
}
