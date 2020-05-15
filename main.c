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

/* 
 * this is for STACK_SIZE and the index size of 
 * the arrays...don't get this mixed up with 
 * the max size of the integer being HELD!!!
 */
uint16_t MAX_SIZE=65536-1;

// Ideals for the array sizes(goes off of MAX_SIZE)
static int AddSize=100;
#define STACK_SIZE 100 // 100 will be the comfy zone

// Ideals for printf statements
#define RESET "\033[0m"
char* OUTPUT = "\n\t[OUTPUT]>> %d\n\n";
char* INPUT = "\033[5;32m[INPUT] >> \033[0m";

// Ideals for Arrays
static int p = 0;
static int rr = 2;
static int Ammount; // used to keep track on how many numbers are inputted

// Arrays needed to store information
static float *Number;// holding both numbers..
static char *SymbolA; // holding the symbol for 2 number equations
static char *SymbolB; // holding symbol for 2+ number equations
static float *stack;

// Ideals for checking if there is a muti numer equation(EX: 1 + 1 + 1 + 1)
static bool IsMulti=false;// false by default..we are assuming there are just 2 numbers
static bool WasMulti=false;// this will be used for the "p"
static float *MultiEqStack; // Used for macro below
static int MES=0; // used for MultiEqStack

// Macro checking to see if there is a multi equation.
#define MultiEquation(ammount,symbol)\
double TOTAL=1;\
if(ammount>2) {\
	IsMulti=true;\
	for(int i = 0; i < ammount; i++) {\
		if(strcmp(symbol,"+")==0) {\
			TOTAL+=Number[i];\
			if(i == ammount-1) TOTAL--;\
		} else if(strcmp(symbol,"-")==0) {\
			if(i<1) {TOTAL=Number[i];}\
			TOTAL-=Number[i+1];\
		} else if(strcmp(symbol,"*")==0) {\
			TOTAL = TOTAL * Number[i];\
		}\
		/* Division can't be done :( */\
		memset(&Number[i],0,sizeof(float));\
	}\
	MultiEqStack[MES]=TOTAL;\
	TOTAL=0;\
	if(MES>=AddSize) {\
		/*Chances are..MultiEqStack will be used more than stack so we will just re-allocate all memory*/\
		AddSize+=100;\
		stack=realloc(stack,sizeof(float)*AddSize);\
		Number=realloc(Number,sizeof(float)*AddSize);\
		SymbolA=(char *)realloc(SymbolA,sizeof(char*)*AddSize);\
		SymbolB=(char *)realloc(SymbolB,sizeof(char*)*STACK_SIZE);\
		MultiEqStack=realloc(MultiEqStack,sizeof(float)*AddSize);\
	}\
	/*DO NOT EDIT, THIS IS TO MAKE SURE THE TWO STACKS DON'T RUN INTO EACH OTHER*/\
	p-=ammount;\
	/* If the user wants to print the previous value, we need to check if the last equation had
	multiple numbers or not */\
	WasMulti=true;\
}

// Ideals to check and see if inputted number is negative
static bool IsNegative=false; // false by default
static bool WasNegative=false; // true if IsNegative is true
static bool RUN=true; // true by default until the STACK_SIZE is above MAX_SIZE

// Clearing all allocated memory stored in the arrays
void cs() {

	if(!(RUN)) {
		if(IsMulti||WasMulti) {
			printf("\t\033[3;33mNOTE:%s Deleting %d of %d items from \033[4mMulti Equation stack%s\n",RESET,MES,MES,RESET);
		}
		if(p>0) printf("\t\033[3;33mNOTE:%s Deleting %d of %d from \033[4mNormal Stack\n%s\n",RESET,p,p,RESET);
	}

	// They are all pointers..we can now just use "free" on them
	free(stack);
	free(Number);
	free(SymbolA);
	free(SymbolB);
	free(MultiEqStack);
	p=0;
}

// Pushing answer of equation onto the stack.
// Function also re-allocates memory for the arrays if STACK_SIZE is reached
int push(int val) {
  if (p < AddSize) {
		if(!(IsMulti)) {
			stack[p++] = val;
		}
  } else {
		// Lets just add another 100?
		if(!(AddSize>MAX_SIZE)) {
			AddSize+=100;

#undef STACK_SIZE
#define STACK_SIZE AddSize // this will then be 200, 300, 400 and so on

			// Re-Allocating memory for arrays since STACK_SIZE has been updated
			stack = realloc(stack, sizeof(float)*STACK_SIZE);
			Number = realloc(Number, sizeof(float)*STACK_SIZE);
			SymbolA = (char *) realloc(SymbolA, sizeof(char*)*STACK_SIZE);
			SymbolB = (char *) realloc(SymbolB, sizeof(char*)*STACK_SIZE);

			// Continue with the operation :)
			stack[p]=val;
			p++;
		} else {
			fprintf(stderr,"\033[0;31mError: Stack is full.\nSTACK_SIZE:%d",STACK_SIZE);
			RUN=false;
		}
	}

	if(stack[p-1] > 0 && (IsNegative)) {
		return val;
	} else {
		if(stack[p] < 0 && !(IsNegative)&&!(WasNegative)) {
			cs();
			printf("\n\t\033[0;31mCalculator overflow error:\n\tThat integer value was above 64-bits...\n\tCalculator reset success%s\n",RESET);
			return 0;
		} else {
			return val;
		}
	}
}

// Showing information about the added information from last equation
void dump() {
	if(RUN) {
		if(IsMulti||WasMulti) {
			printf("\n\tMULTI EQUATION\n\t----------------------\n\tValue\tIndex\tSymbol\n");
			for(int i = 0; i < MES; i++) {
				printf("\t%.0f\t\t%d\t\t%c\n",MultiEqStack[i],i,SymbolB[i]);
			}
			printf("\t----------------------\n\n");
		} else if(!(IsMulti)||!(WasMulti)) {
			if(p>0){
				printf("\t---------------------------\n");
				printf("\t\t%s\t%s\t%s\n", "Value", "Index","Symbol");
				for( int i = 0; i < p; ++i) {
					/* 
						_X means the operation took place, just has no symbol to the equation
					*/
					if(!(strcmp(&SymbolA[i+1],"")==0)) {
						printf("\t\t%6.0f\t%5d\t\t%c\n", stack[i], i,SymbolA[i+1]);
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
	} else {
		if(p>0||MES>0) {
			cs();
			printf("Stack cleared. Come back again!\n");
		} else {
			printf("Exited with nothing to free. Come back again!\n");
		}
	}
}

// Accessing last inputted number that was previously put onto the stack
int pop() {
	memset(&stack[p],0,sizeof(double));

	return stack[(--p)];
}

// Printing the welcome menu, as well as simple instructions on how the calculator works
void Menu() {
	printf("%s%s\n","\033[3;36m\t\t=======  Reverse Polish Calc  =======\n\t\t\t   CodeLongAndPros, CTALENT\033[0;0m\n\n\t\tHOW TO USE:\n\033[3;33m\t\tEnter any number, then press enter\n\t\tAfter your second number, press enter, then give it \n\t\ta symbol(+,-,*,%,/)\n\t\tTYPE \"o\" to see the equation\n\t\tType \"f\" to see Index Storage\n\t\tType \"v\" to Square Root a number\n\t\tAdditonal commands:\n\t\tp: Print the top value off the stack, without popping \n\t\tit off\n\n\t\t\033[0mWant a faster way to get just a fast and easy\n\t\tequation out of the way?\n\t\t\033[3;33mUse: ./main.o --fe x1 x2 symbol:\n\t\tx1 and x2 are both going to be the numbers going into the equation.\n\t\tThe symbol will be one of the following:\n\t\t+,-,%,/ and mult.\n\t\tCommand Example: ./main.o --fe 50 50 mult, would return value of \n\t\t50 * 50", RESET);

	printf("\n\n%s\n", 

   " <insert program name here> Copyright (C) 2020 @CodeLongAndPros & @CTALENT"
   " \n\tThis program comes with ABSOLUTELY NO WARRANTY;"
   " \n\tThis is free software, and you are welcome to redistribute it "
   " \n\tunder certain conditions;"
   " \n\tFor details, invoke with --about\n"
	);
}

// Running the application
int main(int argc, char** argv) {

	// Allocating memory for arrays
	stack = calloc(STACK_SIZE,sizeof(float));
	Number = calloc(STACK_SIZE*2/*holding 2 numbers each time the array is updated*/,sizeof(float));
	SymbolA = (char *) calloc(STACK_SIZE,sizeof(char*));
	SymbolB = (char *) calloc(STACK_SIZE,sizeof(char*));
	MultiEqStack = calloc(STACK_SIZE,sizeof(float));

	parse_args(argc,argv);
	Menu();
	
 	while (RUN) {
		char* input = readline(INPUT); //Get user input without dealing with getch();
			if (*input == EOF)  break;
			if (strcmp(input, "+") == 0) {
			
				MultiEquation(Ammount, "+");
				Ammount=0;

				if(!(IsMulti)) {
					printf(OUTPUT, push(pop() + pop()));
					strcpy(&SymbolA[p],input);
				} else {
					strcpy(&SymbolB[MES],input);
					MES++;dump();
					IsMulti=false;
				}
				if(IsNegative) {
					IsNegative=false;
					WasNegative=true;
				}

			}
			else if (strcmp(input, "-") == 0) {
				
				MultiEquation(Ammount, "-");
				Ammount=0;
				if(!(IsMulti)) {
					int temp = pop();
          int t2 = pop();
//          IsNegative = (abs(temp) != temp) && (abs(t2) != t2);

					printf(OUTPUT, push(t2 - temp));
					strcpy(&SymbolA[p],input);
				} else {
					strcpy(&SymbolB[MES],input);
          MES++;
          dump();
          IsMulti=false;
        }
				if(IsNegative) WasNegative = true;

			}
			else if (strcmp(input, "*") == 0) {
				/*
					I need help with this...
				*/

				MultiEquation(Ammount, "*");
				Ammount=0;

				if(!(IsMulti)) {
					printf(OUTPUT, push(pop() * pop()));
					strcpy(&SymbolA[p],input);
				} else {
					strcpy(&SymbolB[MES],input);
					MES++;
					dump();
					IsMulti=false;
				}
				if(IsNegative) {
					IsNegative=false;
					WasNegative=true;
				}

			}
       else if (strcmp(input, "/") == 0) {
				
				MultiEquation(Ammount,"/");
				Ammount=0;

				if(!(IsMulti)) {
					int temp = pop();
					printf(OUTPUT, push(pop() / temp));
					strcpy(&SymbolA[p],input);
				} else {
					strcpy(&SymbolB[MES],input);
					MES++;
					dump();
					IsMulti=false;
				}
				if(IsNegative) {
					IsNegative=false;
					WasNegative=true;
				}

			} else if (strcmp(input, "v") == 0) {

				printf(OUTPUT, push(sqrt(pop())));

				strcpy(&SymbolA[p],"_S"); // _S as in SquareRoot
				Ammount=0;
				if(IsNegative) {
					IsNegative=false;
					WasNegative=true;
				}

			} else if(strcmp(input, "%") == 0) {

				int temp = pop();

				printf(OUTPUT, push( pop() % temp));
				strcpy(&SymbolA[p],input);

			} else if (strcmp(input, "d") == 0) {
			
				double tmp = pop();
				push(tmp);
				push(tmp);

			} else if (strcmp(input, "f") == 0) { 

				dump();

			} else if (strcmp(input, "p") == 0) {
				
				if(!(WasMulti)) {
					printf(OUTPUT,push(pop()));
				} else {
					printf("\n\t[OUTPUT]>> %.0f\n\n",MultiEqStack[MES-1]);
					WasMulti=false;
				}

			} else if (strcmp(input, "cs") == 0) {

				cs();

			} else if (strcmp(input, "n") == 0) {

				printf("\n\t[OUTPUT]>> %d\n\n", pop());

			} else if(strcmp(input, "fe")==0) {

				if(MES>0) {
					IsMulti=true;
					dump();
					IsMulti=false;
				} else {
					dump();
				}
				
			} else if(strcmp(input,"o") == 0) {
				
				if(strcmp(&SymbolA[p],"")==0) {
					printf("No equations have been found :/\n");
				} else {
					if(!(IsMulti)) {
						printf("\n\t[Standard Notation] >> %.0f %s %.0f",Number[p],&SymbolA[p],Number[p-1]);
						printf("\n\t[Reverse Notation ] >> %.0f %.0f %s\n\n",Number[p],Number[p-1],&SymbolA[p]);
					}
				}

			} else if ( input[0] == 's' ) {
				if (strlen(input) > 2 && input[1] == 'r' && isdigit(input[2]) ) {
					rr = atof(&input[2]);
				}
			}
			else if (*input != EOF && isdigit(*input)!=0) {
				ALG:
				/*
					We're just gonna go off of Ammount..using the index of p got confusing when getting into
					the MultiEqStack array..
				*/
				if(IsMulti) {
					Number[Ammount]=atoi(input);
				} else {
					Number[Ammount]=atoi(input);
					push(Number[Ammount]);
				}
				++Ammount;
			} else if(strcmp(input,"e")==0) {
				RUN=false;
				dump();
			} else {
				// It could be a negative
				if(strlen(input)>1 && input[0]=='-'&& atoi(&input[1])!=0) {
					IsNegative=true;
					goto ALG;
				} else {
					if(input[0]=='\0') {
						printf("\n\t\033[4;3;31mError: Unexpected space in input%s\n\n", RESET);
					} else printf("\n\t\033[4;3;31mError: Unexpected -> %s <- in input%s\n\n", input, RESET);
				}
			}

			if (strlen(input) > 0) add_history(input);

	}

	// This will run since RUN is false and only if the arrays are freed
	if((int)stack[0]==0&&(int)MultiEqStack[0]==0&&SymbolA[0]==0&&SymbolB[0]==0) {
		exit(EXIT_SUCCESS);
	}
}