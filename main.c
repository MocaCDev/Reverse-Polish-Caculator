#include <stdio.h>
//Libreadline 
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h> //Black magic
#include <stdlib.h> //atoi
#include <math.h> //sqrt

#define STACK_SIZE 100
#define RESET "\033[0m"
/* 
	@CodeLongAndPros:
		Added in if-else statement for the "o" operation
		Removed some comments
		Added argument and for loop to the parse_args function
			- We can work on that for loop tomorrow
		Updated .replit file
			- instead of echo 'type make run to run'
				I made it run='clear&&make run'.
				Clear to clear all previous information..unless we don't want to
			- Now all we have to do is ctrl-enter :)
*/

static int stack[STACK_SIZE];
static int p = 0;
static int rr = 2; // Does nothing, WIP. @CodeLongAndPros: What was this for?
static int Ammount; // used to keep track on how many numbers are inputted

/* 
	2 arrays are needed, else it would get hellish trying to find
	the index of the symbol and the two numbers in one array.
*/
static int Number[STACK_SIZE*5];// holding both numbers..
static char Symbol[STACK_SIZE][2]; // holding the symbol

int push(int val) {
  if (p < STACK_SIZE) {
    stack[p] = val;
    p++;
  }
  return val;
}
void dump() {
	/* 
		@CodeLongAndPros:
			Added if statement to check if p is greater than zero.
			Before this, Value and Index would print and nothing else.
			Now, if p is not > zero, "NO INDEX STORAGE" will printed.

			Also, I made the printf statements look a bit better. I also added in the symbol being used
	*/
	if(p>0){
		printf("---------------------------\n");
		printf("\t%s\t%s\t%s\n", "Value", "Index","Symbol");
		for( int i = 0; i < p; ++i) {
			printf("\t%6d\t%5d\t\t%s\n", stack[i], i,Symbol[i+1]);
		}
		printf("---------------------------\n");
	} else {
		printf("--------------------------------\n");
		printf("\t\tNO INDEX STORAGE\n");
		printf("--------------------------------\n");
	}
}
void cs() {
	memset(stack,0,sizeof(stack));
}
int pop() {
	stack[p]=0;

	return stack[(--p)];
}

// Prints how it works
void Menu() {
	printf("%s%s\n","\033[3;36m\t\t=======  Reverse Polish Calc  =======\n\t\t\t   CodeLongAndPros, CTALENT\033[0;0m\n\n\t\tHOW TO USE:\n\033[3;37m\t\tEnter any number, then press enter\n\t\tAfter your second number, press enter, then give it \n\t\ta symbol(+,-,*,%,/)\n\t\tTYPE \"o\" to see the equation", RESET); //@CodeLongAndPros Thank you!! I forgot to reset it :)
	printf("\n\n%s\n", 

   " <\?\?\?\?>  Copyright (C) 2020 <\?\?\?>"
   " This program comes with ABSOLUTELY NO WARRANTY;"
   " This is free software, and you are welcome to redistribute it "
   " under certain conditions;"
   " For details, invoke with --about\n"
	);
}

void parse_args(int ammount,char** args) {
	// @CodeLongAndPros:
	// Added for loop to loop through each CLA(Command Line Argument)
	if(ammount>0) {
		for(int i = 0; i < ammount; i++) {
			if(!(strcmp(args[i],"./main")==0)) {
				if (strcmp(args[i], "--about")) {
					/*printf("\n%s\n", 
					"

			THERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU. SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION."
					)*/
				}
			}
		}
	}
}

int main(int argc, char** argv) {
	Menu();
	parse_args(argc,argv);
	//printf("Ammount of arguments: %d\n",argc);

 	while (1!=2) {
   	char* input = readline("\033[5;32m>> \033[0m"  ); //Get user input without dealing with getch();
		if (*input == EOF)  break;
		if (strcmp(input, "+") == 0) { // Command is 'add'

			printf("%d\n", push(pop() + pop()));
			strcpy(Symbol[p],input);
			Ammount=0;

		}
		else if (strcmp(input, "-") == 0) {

			int temp = pop();
			printf("%d\n", push(pop() - temp));

			strcpy(Symbol[p],input);
			Ammount=0;

		}
		else if (strcmp(input, "*") == 0) {

			printf("%d\n", push(pop() * pop()));
			strcpy(Symbol[p],input);
			Ammount=0;

		} else if (strcmp(input, "/") == 0) {

			int temp = pop();
			printf("%d\n", push(pop() / temp));

			strcpy(Symbol[p],input);
			Ammount=0;

		} else if (strcmp(input, "v") == 0) { // I want dc comatiblaity. Look at dc.man

			printf("%d\n", push(sqrt(pop())));

		} else if(strcmp(input, "%") == 0) {

			int temp = pop();

			printf("%d\n", push( pop() % temp));
			strcpy(Symbol[p],input);

		} else if (strcmp(input, "d") == 0) {

			pop();

		} else if (strcmp(input, "f") == 0) { 

			dump();

		} else if (strcmp(input, "p") == 0) {

			printf("%d\n", push(pop()));

		} else if (strcmp(input, "cs") == 0) {

			cs();

		} else if (strcmp(input, "n") == 0) {

			printf("%d\n", pop());

		} else if(strcmp(input,"o") == 0) {
			
			if(strcmp(Symbol[p],"")==0) {
				printf("No equations have been found :/\n");
			} else {
				printf("Standard Notation: %d %s %d\n",Number[p],Symbol[p],Number[p-1]);
				printf("Reverse Notation: %d %d %s\n",Number[p],Number[p-1],Symbol[p]);
			}

		} else if ( input[0] == 's' ) {
			if (strlen(input) > 2 && input[1] == 'r' && isdigit(input[2]) ) {
				rr = atoi(&input[2]);
			}
		}
		else if (*input != EOF && isdigit(*input)) {

			/*
				@CodeLongAndPros:
					- If Ammount is greater than 2, we won't push any further.
					- I noticed that if we put in 5 numbers it would just get the last 2 numbers of the 5.
					- So..here I made it to where it only gets the first 2 numbers to make it more accurate(also so we don't take up too much array storage)
					- This will change if we improve the applications to take in more than 2 numbers to each equation.
						- If we do this, we will need to increase the stack by allot..probably at least 1000...

			*/
			++Ammount;

			if(Ammount<=2) {
				Number[p]=atoi(input);
				// push(atoi(input));
				push(Number[p]);
			}

		} else {
			/* 
				@CodeLongAndPros:
					I just put a printf statement and prettied it up a bit
			*/
			printf("\n\t\033[4;3;31mCannot create equation with -> %s\n\tNo integer and or symbol found :/\n\n%s",input,RESET);
		}

		// @CodeLongAndPros: What does this do ?
		if (strlen(input) > 0) add_history(input);
	}
}