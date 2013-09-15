#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "main.h"
#include "unit.h"

int (*unit_tests[/*array size automatic*/]) () = {unit_test0,unit_test1,unit_test2,unit_test3,unit_test4,unit_test5,unit_test6,unit_test7,unit_test8,unit_test9}; 


void (*states[/*array size automatic*/]) (char,int) = {s0,s1,s2,s3,s4,s5,s6}; 
void (*curr_state) (char,int); 
const int number_of_states = 7;
const int ASCII_SLASH = 47;
int trim_start;
int trim_end;


void s0(char chVal,int i) {
//	printf("s0 %d %c\n",i,chVal);
	if ('*' == chVal) {
		curr_state = s1;
		// We have a opening pair, need to save position 
		trim_start = i-1;
	} else if (ASCII_SLASH == chVal) {
		curr_state = s6;
		// We have a double slash, need to save position 
		if (-1 == trim_end) {
			// if we have a c comment on the line already, then don't modify
			trim_start = i-1;
		}
		trim_end = 254;  // buffer goes 0-255 and last position is the null for string. 254 is last trim position.
	} else  {
		curr_state = s4;
	}
}

void s1(char chVal,int i) {
//	printf("s1 %d %c\n",i,chVal);
	if ('*' == chVal) {
		curr_state = s3;
	} else if (ASCII_SLASH == chVal) {
		curr_state = s0;
	} else  {
		curr_state = s2;
	}
}

void s2(char chVal,int i) {
//	printf("s2 %d %c\n",i,chVal);
	if ('*' == chVal) {
		curr_state = s3;
	} else if (ASCII_SLASH == chVal) {
		curr_state = s0;
	} else  {
		curr_state = s2;
	}
}

void s3(char chVal,int i) {
//	printf("s3 %d %c\n",i,chVal);
	if (ASCII_SLASH == chVal) {
		curr_state = s5;
		trim_end = i;
	} else if (ASCII_SLASH == chVal) {
		curr_state = s0;
	} else  {
		curr_state = s3;
	}
}

void s4(char chVal,int i) {
//	printf("s4 %d %c\n",i,chVal);
	if (ASCII_SLASH == chVal) {
		curr_state = s0;
	}
	
}

void s5(char chVal,int i) {
//	printf("s5 %d %c\n",i,chVal);
	if (ASCII_SLASH == chVal) {
		curr_state = s0;
	} else {
		curr_state = s4;
	}
}


// extra state added for c++ comments.
void s6(char chVal,int i) {
//	printf("s6 %d %c\n",i,chVal);
	// The rest of the line is a c++ comment
}


int main(int argc, char *argv[]) {

	int iRC,i;
	iRC=EXIT_SUCCESS;

	// This program takes no args
	if (argc != 1) {
		fprintf(stderr, "Usage: %s \n",
		argv[0]);
		iRC=EXIT_FAILURE;
		exit(iRC);
	}


	for (i=0;i<number_of_tests;i++) {
		printf("unit test %d ",i);
		iRC = unit_tests[i]();
		if (EXIT_SUCCESS == iRC) {
			printf("\t Passed\n");
		} else {
			printf("\t Failed\n");
			break;
		}
	}

	if (number_of_tests == i) {
		printf("All tests passed.\n");
	}

	return (iRC);

}


// Requirements:
//   No mallocs
//   Simple system calls so that it works on linux or windows.
// Assumptions:
//   Lines with nested c-style comments are not given.
//   Tested with buffer that 256 bytes long.  
// 
int remove_comments(char *str) {

	int i,iLen;

	// init our trim positions
	trim_start = -1;
	trim_end = -1;

	if (NULL == str) {
		// null string.
		return EXIT_FAILURE;
	}

	iLen = strlen(str);
	
	if ('/' == str[0]) {
		curr_state = s0;	
//		printf("s0 %d %c\n",0, str[0]);
	} else {
		curr_state = s4;	
//		printf("s4 %d %c\n",0, str[0]);
		
	}
	
	// Look for C comments
	for (i=1;i<iLen;i++) {
		curr_state(str[i],i);
	}

//	printf("Trim start = %d\n",trim_start);
//	printf("Trim end = %d\n",trim_end);

	if (-1 != trim_start && -1 != trim_end) {
		if (254 == trim_end ) {
//			printf("special c++ thing\n");
			str[trim_start] = 0;
		} else {
			memmove(&str[trim_start],&str[trim_end+1],trim_end-trim_start);
		}
	}

	// Look for C++ comments

	return EXIT_SUCCESS;

}

