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
#include "CLA.h"

// Changed to 16-bit integer to use memory more wisely
/* 
	*this is for STACK_SIZE and the index size of 
	*the arrays...don't get this mixed up with 
	*the max size of the integer being HELD!!!
	*/
uint16_t MAX_SIZE=65536-1;
static int AddSize=100;
#define STACK_SIZE 100 // 100 will be the comfy zone

#define RESET "\033[0m"
char* OUTPUT = "\n\t[OUTPUT]>> %d\n\n";
char* INPUT = "\033[5;32m[INPUT] >> \033[0m";

/* 
	Developer Comments:
		TO-DO:
			- Work on making outputted numbers, when there is an int overflow, more accurate.
				- IDEA:
					- add a CLA(Command Line Argument) that will allow the user to set a max integer size?
					- or do you want to hard code a way for the value to be above a 64-bit number?
			- Work on making MAX_SIZE usable: DONE...I think

		@CodeLongAndPros:
			I made the stack a pointer to an allocated ammount of memory(of an array).
			I gave it it's size in main, and re-allocate the memory when we re-assign STACK_SIZE in the push function.
			I created a file named CLA.c that will deal with all of the command line arguments
				- I updated Makefile to compile CLA into the application as well
*/

static float *stack;
static int p = 0;
static int rr = 2;
static int Ammount; // used to keep track on how many numbers are inputted

/* 
	2 arrays are needed, else it would be impossible trying to find
	the index of the symbol and the two numbers in one array.
*/
static float Number[STACK_SIZE*80];// holding both numbers..
static char Symbol[STACK_SIZE*60][2]; // holding the symbol
static bool IsNegative=false; // false by default

void cs() {
	memset(&stack,0,sizeof(stack));
	memset(Number,0,sizeof(Number));
	// For loop needed for setting symbol to an empty string
	for(int i = 0; i < p; i++) strcpy(Symbol[i+1],"");
	p=0;
}
int push(int val) {
  if (p < AddSize) {
    stack[p] = val;
    p++;
  } else {
		// Lets just add another 100?
		AddSize+=100;

#undef STACK_SIZE
#define STACK_SIZE AddSize // this will then be 200, 300, 400 and so on

		// Re-Allocating memory for stack since STACK_SIZE has been updated
		stack = realloc(stack, sizeof(float)*STACK_SIZE);

		// Continue with the operation :)
		stack[p]=val;
		p++;
	}

	// Temporary fix..
	if(stack[p-1]>0&&!(IsNegative)) {
		return abs(val);
	} else {
		if(stack[p-1]<0&&!(IsNegative)) {
			cs();
			printf("\n\t\033[0;31mCalculator overflow error:\n\tThat integer value was above 64-bits...\n\tCalculator reset success%s\n",RESET);
			return 0;
		} else {
			return val;
		}
	}
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
				printf("\t\t%6.0f\t%5d\t\t%s\n",stack[i],i,"_X");
			}
		}
		printf("\t---------------------------\n");
	} else {
		printf("\t--------------------------------\n");
		printf("\t\t\tStack Empty\n");
		printf("\t--------------------------------\n");
	}
}
int pop() {
	memset(&stack[p],0,sizeof(double));
	
	// To-Do: Work on if-else statement that makes the outputted number more accurate
	return stack[(--p)];
	
	/*
		if (!(IsNegative)) return stack[(--p)] *-1; may work
		Ran into the same thing I did last night..lol
	*/
	/*
	if( !(IsNegative)) return stack[(--p)] *-1;
	else return stack[(--p)];*/
}

void Menu() {
	printf("%s%s\n","\033[3;36m\t\t=======  Reverse Polish Calc  =======\n\t\t\t   CodeLongAndPros, CTALENT\033[0;0m\n\n\t\tHOW TO USE:\n\033[3;33m\t\tEnter any number, then press enter\n\t\tAfter your second number, press enter, then give it \n\t\ta symbol(+,-,*,%,/)\n\t\tTYPE \"o\" to see the equation\n\t\tType \"f\" to see Index Storage\n\t\tType \"v\" to Square Root a number\n\t\tAdditonal commands:\n\t\tp: Print the top value off the stack, without popping \n\t\tit off\n\t\t", RESET);

	printf("\n\n%s\n", 

   " <insert program name here> Copyright (C) 2020 @CodeLongAndPros & @CTALENT"
   " \n\tThis program comes with ABSOLUTELY NO WARRANTY;"
   " \n\tThis is free software, and you are welcome to redistribute it "
   " \n\tunder certain conditions;"
   " \n\tFor details, invoke with --about\n"
	);
}

int main(int argc, char** argv) {

	// Allocating memory for stack
	stack = calloc(STACK_SIZE,sizeof(float));

	parse_args(argc,argv);
	Menu();
	
 	while (true) {
		char* input = readline(INPUT); //Get user input without dealing with getch();
			if (*input == EOF)  break;
			if (strcmp(input, "+") == 0) {

				printf(OUTPUT, push(pop() + pop()));
				strcpy(Symbol[p],input);
				Ammount=0;
				IsNegative=false;

			}
			else if (strcmp(input, "-") == 0) {

				int temp = pop();
				printf(OUTPUT, push(pop() - temp));

				strcpy(Symbol[p],input);
				Ammount=0;
				IsNegative=false;

			}
			else if (strcmp(input, "*") == 0) {

				printf(OUTPUT, push(pop() * pop()));
				strcpy(Symbol[p],input);
				Ammount=0;
				IsNegative=false;

			} else if (strcmp(input, "/") == 0) {

				int temp = pop();
				printf(OUTPUT, push(pop() / temp));

				strcpy(Symbol[p],input);
				Ammount=0;
				IsNegative=false;

			} else if (strcmp(input, "v") == 0) { // I want dc comatiblaity. Look at dc.man
				printf(OUTPUT, push(sqrt(pop())));

				strcpy(Symbol[p],"_S"); // _S as in SquareRoot
				Ammount=0;
				IsNegative=false;

			} else if(strcmp(input, "%") == 0) {

				int temp = pop();

				printf(OUTPUT, push( pop() % temp));
				strcpy(Symbol[p],input);

			} else if (strcmp(input, "d") == 0) {
				
				double tmp = pop();
				push(tmp);
				push(tmp);

			} else if (strcmp(input, "f") == 0) { 

				dump();

			} else if (strcmp(input, "p") == 0) {

				printf(OUTPUT, push(pop()));

			} else if (strcmp(input, "cs") == 0) {

				cs();

			} else if (strcmp(input, "n") == 0) {

				printf("\n\t[OUTPUT]>> %d\n\n", pop());

			} else if(strcmp(input,"o") == 0) {
				
				if(strcmp(Symbol[p],"")==0) {
					printf("No equations have been found :/\n");
				} else {
					printf("\n\t[Standard Notation] >> %.0f %s %.0f",Number[p],Symbol[p],Number[p-1]);
					printf("\n\t[Reverse Notation ] >> %.0f %.0f %s\n\n",Number[p],Number[p-1],Symbol[p]);
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
				if(strlen(input)>1 && input[0]=='-'&& isdigit(input[1])) {
					IsNegative=true;
					goto ALG;
				} else {
					printf("\n\t\033[4;3;31mError: Unexpected -> %s <- in input%s\n\n", input, RESET);
				}
			}

			if (strlen(input) > 0) add_history(input);

	}
}