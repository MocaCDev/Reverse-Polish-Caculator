#include <stdio.h>
//Libreadline 
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h> //Black magic
#include <stdlib.h> //atoi
#include <math.h> //sqrt
#define STACK_SIZE 100
/* 
	@CodeLongAndPros #1:
		- I added in a if statement that checks if the user presses "o".
		- If "o" is typed, then the operation will be printed to the screen in a non-reverse way(ex:1+2) AND in the reverse way.
		P.S: All it took was 2 arrays, and 2 print statements lol
	@CodeLongAndPros #2:
		- I added some white space in each if statement so they weren't crammed together
		- Also so it was easier to read. Feel free to change it back if you want
*/

static int stack[STACK_SIZE];
static int p = 0;

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
  printf("%s\n", "---");
  printf("%s\t%s\n", "Value", "Index");
  for( int i = 0; i < p; ++i) {
    printf("%6d\t%5d\n", stack[i], i);
  }
  printf("%s\n", "---");
}
void clear() {
  stack[p] = 0;
}
void cs() {
  for (int i = 0; i <= p; i++) {
    stack[i] = 0;
  }
}
int pop() {
  clear();
  return stack[(--p)];
}

int main() {
 while (1!=2) {
   char* input = readline("> "); //Get user input without dealing with getch();
   if (*input == EOF)  break;
   if (strcmp(input, "+") == 0) { // Command is 'add'

     printf("%d\n", push(pop() + pop()));
		 strcpy(Symbol[p],input);

   }
   else if (strcmp(input, "-") == 0) {

     int temp = pop();
     printf("%d\n", push(pop() - temp));

		 strcpy(Symbol[p],input);

   }
   else if (strcmp(input, "*") == 0) {

     printf("%d\n", push(pop() * pop()));
		 strcpy(Symbol[p],input);

   } else if (strcmp(input, "/") == 0) {

     int temp = pop();
     printf("%d\n", push(pop() / temp));

		 strcpy(Symbol[p],input);

   } else if (strcmp(input, "v") == 0) {

     printf("%d\n", push(sqrt(pop())));

   } else if(strcmp(input, "%") == 0) {

		int temp = pop(); // why do we assign it to an integer?

     printf("%d\n", push( pop() % temp));
		 strcpy(Symbol[p],input);

   } else if (strcmp(input, "d") == 0) {

     pop();

   } else if (strcmp(input, "f") == 0) {

    dump();

   } else if (strcmp(input, "p") == 0) {

     printf("%d\n", push(pop()));

   } else if (strcmp(input, "c") == 0) {

     cs();

   } else if (strcmp(input, "n") == 0) {

     printf("%d\n", pop());

   } else if(strcmp(input,"o") == 0) {

		 printf("NORMAL OPERATION: %d %s %d\n",Number[p],Symbol[p],Number[p+1]);
		 printf("Reverse Notation: %d %d %s",Number[p],Number[p+1],Symbol[p]);

	 } else if (*input != EOF && isdigit(*input)) {

    push(atoi(input));
		Number[p]=atoi(input);

  } else {
    putchar('?');
    putchar('\n');
  }

  if (strlen(input) > 0) add_history(input);
 }
}