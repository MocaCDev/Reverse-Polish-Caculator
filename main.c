#include <stdio.h>

/* 
	@CodeLongAndPros:
		I did some commenting to try and fully understand the program.
		Sorry if it is a bit messy..also I left a few comments about some things we should add, and I changed the assignment of ret in pop.

		You can delete all the comments if you want.
*/

int stack[100];
int p; /*
	Possible TO-DO: Make this static?
	Possible TO-DO: Assign it defaulty to 0?
*/

void push(int val) {
	// So we are only pushing values less than 100?
  if (p < 100) {
    stack[p] = val;
    p++; /* 
			So, if p=2 and val=100, then stack[2]=100, then p will be 3 afterwards?
			My understanding: Since we are pushing, we are going to be increasing the index each time we push..right?
		*/
  }
}

int pop() {
  int ret = stack[p-2]; /* 
		Are we wanting ret to be zero?
		We have to remember, we are increasing it in push, and each value of the array stack is
		defaulty zero..so we assigned index of p to value of val, then we increased p to the next index..being
		a default of zero...

		-2 works..look at main..here is a brief review of what is going on:
			we push 1, then 3, then 4.
			p will then be 4, after pushing 4 onto the stack.
			So in order to get 3, we need to -2, because if we -1..then we will get index of 3, which is what we had just
			pushed onto the stack..so subtracting 2 skips 4, which is what we are removing, and gets 3.(I don't know if that makes sense)
	*/

	// Since we are removing the last index, we should re-assign it to its default value..zero
	// Possible TO-DO: stack[p-1]=0;?
  p--;
  return ret;
}

int main(void) {
  p=0; // We can just assign it defaulty when creating the global variable...
  push(1);
  push(3);
	// See, if we push(4), then stack[p-2] would then be 3
	push(4);
  printf("%d\n", pop());
}