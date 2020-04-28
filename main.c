#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>
#include <stdlib.h>

/* 
	@CodeLongAndPros:
		I did some commenting to try and fully understand the program.
		Sorry if it is a bit messy..also I left a few comments about some things we should add, and I changed the assignment of ret in pop.

		You can delete all the comments if you want.
		Also...I created a GitHub repo:
			- https://github.com/ARACADERISE/Reverse-Polish-Caculator

  @CTALENT:
  I switched the compiler to GCC, and added a makefile, so we can debug.
*/

// changed to static to keep value(s)
static int stack[100];
static int p = 0; 

int push(int val) {
	// Why just 100? It's not that importand.
  if (p < 100) { 
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
int pop() {
  clear();
  return stack[(--p)];
}

int main(void) {

 while (1!=2) {
   char* input = readline("> "); //Get user input without dealing with getch();
   if (*input == EOF) 
    break;
   if (strcmp(input, "+") == 0) { // Command is 'add'
     printf("%d\n", push(pop() + pop())); 
   }
   else if (strcmp(input, "-") == 0) {
     int temp = pop();
     printf("%d\n", push(pop() - temp));
   }
   else if (strcmp(input, "*") == 0) {
     printf("%d\n", push(pop() * pop()));
   }
   else if (strcmp(input, "/") == 0) {
     int temp = pop();
     printf("%d\n", push(pop() / temp));
   }
   else if (strcmp(input, "d") == 0) {
     pop();
   }
   else if (strcmp(input, "f") == 0) {
    dump();
   }
   else if (*input != EOF && isdigit(*input)) {
    push(atoi(input));
  }
  else {
    putchar('?');
    putchar('\n');
  }


   if (strlen(input) > 0)
    add_history(input);
 }
}