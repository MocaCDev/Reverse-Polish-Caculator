#include <stdio.h> //printf
//Libreadline 
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h> //Black magic
#include <stdlib.h> //atoi
#include <math.h> //sqrt
#include <stdint.h> /* needed to declare MAX_SIZE variable
	uint8_t, uint16_t, uint32_t, uint64_t
*/
#include <limits.h> /* May be needed for declaring MAX_SIZE
	INT_MIN, INT_MAX, LONG_MIN, LONG_MAX, LLONG_MIN, LLONG_MAX
	ULONG_MAX, ULLONG_MAX, UINT_MAX
*/
#include <stdbool.h> // Needed for IsNegative


/* 
	How can we use this in setting the max size?
*/
uint64_t MAX_SIZE = 1844674407370955169;
static int AddSize=100;
#define STACK_SIZE 100 // 100 will be the comfy zone
#define RESET "\033[0m"

/* 
	Developer Comments:
		TO-DO:
			- Need to work on max sizes of STACK_SIZE and the arrays.
			- There is a problem..I put abs/fabs to make negative values being returned positive
				- the only reason push and pop return negative values is due to the fact they go above
					there max value..
				- We need to fix this!
		
		@CodeLongAndPros #1:
			- I updated allot of the printf statements.
			- I put [INPUT] in front of the >> for the readline function
			- I put [OUTPUT] in front of the printf statements printing the output of the equation
			- I put [Standard Notation] in front of the printf statement that prints the None-Reversed version
				of the equation
			- I put [Reverse Notation] in front of the printf statement that prints the Rever Notation version
				of the equation
		@CodeLongAndPros #2:
			- I made the application negative friendly :)
*/

// float is only 4 bytes, double is 8...I am sure we only need 4 bytes of memory.
static float stack[STACK_SIZE];
static int p = 0;
static int rr = 2;
static int Ammount; // used to keep track on how many numbers are inputted

/* 
	2 arrays are needed, else it would get hellish trying to find
	the index of the symbol and the two numbers in one array.
*/
static float Number[STACK_SIZE*80];// holding both numbers..
static char Symbol[STACK_SIZE*60][2]; // holding the symbol
static bool IsNegative=false; // false by default

int push(int val) {
  if (p < AddSize) {
    stack[p] = val;
    p++;
  } else {
		// Lets just add another 100?
		AddSize+=100;

#undef STACK_SIZE
#define STACK_SIZE AddSize // this will then be 200, 300, 400 and so on

		// Continue with the operation :)
		stack[p]=val;
		p++;
	}
	if(!(IsNegative)) return abs(val);
	else return val;
}
void dump() {
	if(p>0){
		printf("\t---------------------------\n");
		printf("\t\t%s\t%s\t%s\n", "Value", "Index","Symbol");
		for( int i = 0; i < p; ++i) {
			/* 
				_X means the operation took place, just has no symbol to the equation
			*/
			if(!(strcmp(Symbol[i+1],"")==0)) {
				printf("\t\t%6.0f\t%5d\t\t%s\n", stack[i], i,Symbol[i+1]);
			}
			else {
				printf("\t%6.0f\t%5d\t\t%s\n",stack[i],i,"_X");
			}
		}
		printf("\t---------------------------\n");
	} else {
		printf("\t--------------------------------\n");
		printf("\t\t\tNO INDEX STORAGE\n");
		printf("\t--------------------------------\n");
	}
}
void cs() {
	/* 
		Possibility:
			Just use the cs function when p is at 100...it will reset everything..therefore not having to
			deal with sizes of arrays etc...
			What do you think?
	*/
	memset(stack,0,sizeof(stack));
	memset(Number,0,sizeof(Number));
	// For loop needed for setting symbol to an empty string
	for(int i = 0; i < p; i++)strcpy(Symbol[i+1],"");
	p=0; // Shouldn't we reset p as well since everything is being set back to zero?
}
int pop() {
	// Memory allocation just seems more secure when setting recent index to zero
	memset(&stack[p],0,sizeof(double));
	
	if(!(IsNegative)) return fabs(stack[(--p)]);
	else return stack[(--p)];
}

void Menu() {
	printf("%s%s\n","\033[3;36m\t\t=======  Reverse Polish Calc  =======\n\t\t\t   CodeLongAndPros, CTALENT\033[0;0m\n\n\t\tHOW TO USE:\n\033[3;33m\t\tEnter any number, then press enter\n\t\tAfter your second number, press enter, then give it \n\t\ta symbol(+,-,*,%,/)\n\t\tTYPE \"o\" to see the equation\n\t\tType \"f\" to see Index Storage\n\t\tType \"v\" to Square Root a number\n", RESET);

	printf("\n\n%s\n", 

   " <\?\?\?\?>  Copyright (C) 2020 <\?\?\?>"
   " \n\tThis program comes with ABSOLUTELY NO WARRANTY;"
   " \n\tThis is free software, and you are welcome to redistribute it "
   " \n\tunder certain conditions;"
   " \n\tFor details, invoke with --about\n"
	);
}

void parse_args(int ammount,char** args) {
	if(ammount>1) {
		// Updated: Starts at 1
		for(int i = 1; i < ammount; i++) {
			if(strcmp(args[i], "--about")) {
				// To-Do: Finish this printf statement
				/*printf("\n%s\n", 
					"

			THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION."
					)*/
			}
		}
	}
}

int main(int argc, char** argv) {

	Menu();
	parse_args(argc,argv);

 	while (1!=2) {
   	char* input = readline("\033[5;32m[INPUT]>> \033[0m"  ); //Get user input without dealing with getch();
		if (*input == EOF)  break;
		if (strcmp(input, "+") == 0) {

			printf("\n\t[OUTPUT]>> %d\n\n", push(pop() + pop()));
			strcpy(Symbol[p],input);
			Ammount=0;
			IsNegative=false;

		}
		else if (strcmp(input, "-") == 0) {

			int temp = pop();
			printf("\n\t[OUTPUT]>> %d\n\n", push(pop() - temp));

			strcpy(Symbol[p],input);
			Ammount=0;
			IsNegative=false;

		}
		else if (strcmp(input, "*") == 0) {

			printf("\n\t[OUTPUT]>> %d\n\n", push(pop() * pop()));
			strcpy(Symbol[p],input);
			Ammount=0;
			IsNegative=false;

		} else if (strcmp(input, "/") == 0) {

			int temp = pop();
			printf("\n\t[OUTPUT]>> %d\n\n", push(pop() / temp));

			strcpy(Symbol[p],input);
			Ammount=0;
			IsNegative=false;

		} else if (strcmp(input, "v") == 0) { // I want dc comatiblaity. Look at dc.man
			printf("\n\t[OUTPUT]>> %d\n\n", push(sqrt(pop())));
			strcpy(Symbol[p],"_S"); // _S as in SquareRoot
			Ammount=0;
			IsNegative=false;

		} else if(strcmp(input, "%") == 0) {

			int temp = pop();

			printf("\n\t[OUTPUT]>> %d\n\n", push( pop() % temp));
			strcpy(Symbol[p],input);

		} else if (strcmp(input, "d") == 0) {

			pop();

		} else if (strcmp(input, "f") == 0) { 

			dump();

		} else if (strcmp(input, "p") == 0) {

			printf("\n\t[OUTPUT]>> %d\n\n", push(pop()));

		} else if (strcmp(input, "cs") == 0) {

			cs();

		} else if (strcmp(input, "n") == 0) {

			printf("\n\t[OUTPUT]>> %d\n\n", pop());

		} else if(strcmp(input,"o") == 0) {
			
			if(strcmp(Symbol[p],"")==0) {
				printf("No equations have been found :/\n");
			} else {
				printf("\n\t[Standard Notation]>> %.0f %s %.0f",Number[p],Symbol[p],Number[p-1]);
				printf("\n\t[Reverse Notation]>> %.0f %.0f %s\n\n",Number[p],Number[p-1],Symbol[p]);
			}

		} else if ( input[0] == 's' ) {
			if (strlen(input) > 2 && input[1] == 'r' && isdigit(input[2]) ) {
				rr = atof(&input[2]);
			}
		}
		else if (*input != EOF && isdigit(*input)) {
			ALG:
			++Ammount;

			if(Ammount<=2) {
				Number[p]=atoi(input);
				push(Number[p]);
			}

		} else {
			// It could be a negative
			if(strlen(input)>1&&input[0]=='-'&&isdigit(input[1])) {
				IsNegative=true;
				goto ALG;
			} else {
				printf("\n\t\033[4;3;31mError: Unexpected -> %s <- in input%s\n\n", input, RESET);
			}
		}

		if (strlen(input) > 0) add_history(input);
	}
}