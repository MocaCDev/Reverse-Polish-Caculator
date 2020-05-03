#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/* 
	@CodeLongAndPros:
		This file is created to single handedly handle CLA's.
*/
// Easier way to do this?
char* F_ARG_OUT = "\n%d %s %d = %d\nReverse Polish Notation: %d %d %s";

#define F_ARG_PRINT(numone,numtwo,symbol)\
if(strcmp(symbol,"+")==0) {\
	printf(F_ARG_OUT,numone,symbol,numtwo,numone+numtwo,numone,numtwo,symbol);\
	exit(EXIT_SUCCESS);\
} else if(strcmp(symbol,"-")==0) {\
	printf(F_ARG_OUT,numone,symbol,numtwo,numone-numtwo,numone,numtwo,symbol);\
	exit(EXIT_SUCCESS);\
} else if(strcmp(symbol,"mult")==0) {\
	printf(F_ARG_OUT,numone,"*",numtwo,numone*numtwo,numone,numtwo,"*");\
	exit(EXIT_SUCCESS);\
} else if(strcmp(symbol,"%")==0) {\
	printf(F_ARG_OUT,numone,symbol,numtwo,numone%numtwo,numone,numtwo,symbol);\
	exit(EXIT_SUCCESS);\
} else if(strcmp(symbol,"/")==0) {\
	printf(F_ARG_OUT,numone,symbol,numtwo,numone/numtwo,numone,numtwo,symbol);\
	exit(EXIT_SUCCESS);\
}

void parse_args(int ammount,char** args) {
	if(ammount>1) {
		for(int i = 1; i < ammount; i++) {
			if(strcmp(args[i], "--about")==0) {
				printf("\n%s\n", 

			"\t\tWARRANTY INFORMATION\n\t\t____________________________________________________\n\t\t\033[3mTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT\n"
			"\t\tPERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE\n"
			"\t\tSTATED IN WRITING THE COPYRIGHT HOLDERS AND/OR\n"
			"\t\tOTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT\n"
			"\t\tWARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,\n" 
			"\t\tINCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
			"\t\tWARRANTIES OF MERCHANTABILITY AND FITNESS FOR A\n"
			"\t\tPARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE\n"
			"\t\tQUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.\n"
			"\t\tSHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE\n"
			"\t\tCOST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\033[0m\t\t____________________________________________________\n"
					);
				exit(0);
			} else if(strcmp(args[i],"-fe")==0)/*f as in fast equation*/ {
				/* 
					-f x1 x2 symbol
				*/
				if(strcmp(args[i+1],"help")==0) {
					printf("\t-f x1 x2 symbol\n\tx1 and x2 will be the two numbers in the operations\n\tsymbol will be the action with the 2 numbers\n\tThe symbols are as follows:\n\t\t+,-,%%,/\n\tWhen multiplying with -f, use the word mult\n");
					exit(EXIT_SUCCESS);
				} else {
					if(args[i+1]&&args[i+2]&&!(atoi(args[i+1])==0&&atoi(args[i+2])==0)) {
						if(args[i+3]) {
							int num1 = atoi(args[i+1]), num2 = atoi(args[i+2]);
							// Checking to see if the symbol is valid
							if(!(
								strcmp(args[i+3],"+")==0||
								strcmp(args[i+3],"-")==0||
								strcmp(args[i+3],"mult")==0||
								strcmp(args[i+3],"%")==0||
								strcmp(args[i+3],"/")==0
								)) {
									fprintf(stderr,"\033[0;31mError: 3rd argument of -f %d %d ->%s<- is an invalid symbol",num1,num2,args[i+3]);
									exit(EXIT_FAILURE);
								}
							F_ARG_PRINT(num1, num2, args[i+3]);
						} else {
							fprintf(stderr,"\033[0;31mError: -f %d %d needs a symbol..\n",atoi(args[i+1]),atoi(args[i+2]));
							exit(EXIT_FAILURE);
						}
					} else {
						fprintf(stderr,"\033[0;31mError: -f needs 2 number arguments\n");
						exit(EXIT_FAILURE);
					}
				}
			}
		}
	}
}