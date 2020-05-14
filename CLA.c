#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Easier way to do this?
char* F_ARG_OUT = "\n%d %s %d = %d\nReverse Polish Notation: %d %d %s\n";

// To-Do:
/* 
	Gives negative response due to integer overflow,
	fix this
*/
#define F_ARG_PRINT(numone,numtwo,symbol)\
if(strcmp(symbol,"+")==0) {\
	printf(F_ARG_OUT,numone,symbol,numtwo,numone+numtwo,numone,numtwo,symbol);\
	exit(EXIT_SUCCESS);\
} else if(strcmp(symbol,"-")==0) {\
	printf(F_ARG_OUT,numone,symbol,numtwo,numone-numtwo,numone,numtwo,symbol);\
	exit(EXIT_SUCCESS);\
} else if(strcmp(symbol,"m")==0) {\
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

			"\t\tWARRANTY INFORMATION\n\t\t____________________________________________________\n\t\tTHERE IS NO WARRANTY FOR THE PROGRAM, TO THE EXTENT\n"
			"\t\tPERMITTED BY APPLICABLE LAW. EXCEPT WHEN OTHERWISE\n"
			"\t\tSTATED IN WRITING. THE COPYRIGHT HOLDERS AND/OR\n"
			"\t\tOTHER PARTIES PROVIDE THE PROGRAM “AS IS” WITHOUT\n"
			"\t\tWARRANTY OF ANY KIND, EITHER EXPRESSED OR IMPLIED,\n" 
			"\t\tINCLUDING, BUT NOT LIMITED TO, THE IMPLIED\n"
			"\t\tWARRANTIES OF MERCHANTABILITY AND FITNESS FOR A\n"
			"\t\tPARTICULAR PURPOSE. THE ENTIRE RISK AS TO THE\n"
			"\t\tQUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.\n"
			"\t\tSHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE\n"
			"\t\tCOST OF ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n\t\t____________________________________________________\n"
					);
				exit(0);
			} else if(strcmp(args[i],"--fe")==0)/*fe as in fast equation*/ {
				/* 
					--fe x1 x2 symbol
				*/
				if(strcmp(args[i+1],"--help")==0) {
					printf("\t--fe x1 x2 symbol\n\tx1 and x2 will be the two numbers in the operations\n\tsymbol will be the action with the 2 numbers\n\tThe symbols are as follows:\n\t\t+,-,%%,/\n\tWhen multiplying with --fe, use the word mult\n");
					exit(EXIT_SUCCESS);
				} else {
					if(args[i+1] && args[i+2] && !(atoi(args[i+1])==0 && atoi(args[i+2]) == 0)) {
						if(args[i+3]) {
							int num1 = atoi(args[i+1]), num2 = atoi(args[i+2]);
							// Checking to see if the symbol is valid
							if(!(
								strcmp(args[i+3],"+")==0||
								strcmp(args[i+3],"-")==0||
								strcmp(args[i+3],"m")==0||
								strcmp(args[i+3],"%")==0||
								strcmp(args[i+3],"/")==0
								)) {
									fprintf(stderr,"\033[0;31mError: 3rd argument of -f %d %d ->%s<- is an invalid symbol\n",num1,num2,args[i+3]);
									exit(EXIT_FAILURE);
								}
							F_ARG_PRINT(num1, num2, args[i+3]);
							exit(EXIT_SUCCESS);
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
      else if(strcmp(args[i], "--help") == 0) {
        printf(
          "Usage: rpc [--fe] [fe-args] "
          "Simple reverse polish caculator. For info on postfix notations, run man dc\n"
          "\t-q\t\t\t\tQuiet, suppress help messages\n"
          "\t-v (Default)\tVerbose, add user help messages\n"
          "\t-fe\t\t\t\tFast Equation. Additional args: [int] [int] [+|-|*|/]\n"
          "\t--about\t\t\tLicense info\n"
          "\n"
          "This program is licensed under the GNU GPLv3. For more info, invoke with --about\n"
          "(c) 2020 <Scott Little> and <>\n"
          "\n"
        );
        exit(EXIT_SUCCESS);
      }
		}
	}
}