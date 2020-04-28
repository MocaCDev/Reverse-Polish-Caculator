#include <stdio.h>
//#include <readline.h>
//TODO: Link against libreadline for input.

/* 
	@CodeLongAndPros:
		I did some commenting to try and fully understand the program.
		Sorry if it is a bit messy..also I left a few comments about some things we should add, and I changed the assignment of ret in pop.

		You can delete all the comments if you want.
		Also...I created a GitHub repo:
			- https://github.com/ARACADERISE/Reverse-Polish-Caculator

  @CTALENT:

*/

int stack[100];
int p =0; /*
	Possible TO-DO: Make this static? This is the stack pointer, and needs to be global.
*/

void push(int val) {
	// So we are only pushing values less than 100?
  // We can only have 100 vals in the stack. 
  if (p < 100) {
    stack[p] = val;
    p++; /* 
			So, if p=2 and val=100, then stack[2]=100, then p will be 3 afterwards?
			My understanding: Since we are pushing, we are going to be increasing the index each time we push..right?
      Yes
		*/
  }
}
void dump() {
  printf("%s\n", "START");
  for( int i = 0; i < p; ++i) {
    printf("%d\t%d\n", stack[i], i);
  }
  printf("%s\n", "END");
}
void clear() {
  stack[p] = 0;
}
int pop() {
  clear();
  return stack[(--p)]; /* 
		Are we wanting ret to be zero?
		We have to remember, we are increasing it in push, and each value of the array stack is
		defaulty zero..so we assigned index of p to value of val, then we increased p to the next index..being
		a default of zero...

		-2 works..look at main..here is a brief review of what is going on:
			we push 1, then 3, then 4.
			p will then be 4, after pushing 4 onto the stack.
			So in order to get 3, we need to -2, because if we -1..then we will get 4, which is what we had just
			pushed onto the stack..so subtracting 2 skips 4, which is what we are removing, and gets 3.(I don't know if that makes sense)
	*/

	// Since we are removing the last index, we should re-assign it to its default value..zero
	// Possible TO-DO: stack[p-1]=0;?
}

int main(void) {
  push(1);
  push(3);
	// See, if we push(4), then stack[p-2] would then be 3
	push(4);
  dump();
  printf("%d\n", pop());
  printf("%d\n", pop());
  printf("%d\n", pop());
  
}