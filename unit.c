#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "unit.h"
#include "main.h"

char pTesty[256]; // no mallocs
const int number_of_tests = 10;

int unit_test0(void) {
	int iRC;
	printf(" - test of null string\n");
	iRC = remove_comments(NULL);
	if (EXIT_FAILURE == iRC) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}


int unit_test1(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string without comments\n");
	strcpy(pTesty,"no comments string.");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL == iMSL) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}

/* test of line with c style comment inside string */
int unit_test2(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string with valid comment\n");
	strcpy(pTesty,"this remains, /* this is removed */ this also remains.");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"this remains,  this also remains.")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}

/* non closing c style comment test     */
int unit_test3(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string with non matching comments\n");
	strcpy(pTesty,"this remains, /* this is not removed .");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL == iMSL) {
		return EXIT_SUCCESS;
	} else {
		return EXIT_FAILURE;
	}
}


/* boundary test. Entire input string is c-style comment.    */
int unit_test4(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string which is entirely a c-sytle comment\n");
	strcpy(pTesty,"/* this entire line is a comment */");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}


/* boundary test. Entire input string is c++ comment.    */
int unit_test5(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string which is entirely a c++ comment\n");
	strcpy(pTesty,"// this entire line is a c++ comment");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}


/* Partial input string is c++ comment.    */
int unit_test6(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string which ends with a  c++ comment\n");
	strcpy(pTesty,"this part remains// this part is a c++ comment");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"this part remains")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}


/* Partial input string is leading c comment with ending c++ comment.    */
int unit_test7(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string which has both a c and  c++ comment\n");
	strcpy(pTesty,"/* this part is removed */// this part is a c++ comment. result is empty string");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}


/* input string is partial leading c comment with ending c++ comment.    */
int unit_test8(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string which has both a c and  c++ comment\n");
	strcpy(pTesty,"/* this part is kept // this part is a c++ comment. result is empty string");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"/* this part is kept ")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}


/* input string from email    */
/*
 * Comments start with /* and end with opposite
 * (// is for C++ comments)
 */
int unit_test9(void) {
	int iRC;
	int iOSL; // orig string len
	int iMSL; // modified string len
	printf(" - test of string from email\n");
	strcpy(pTesty,"/* \
* Comments start with  /* and end with the opposite \
* (// is for C++ comments) \
*/");
	iOSL = strlen(pTesty);
	iRC = remove_comments(pTesty);
	iMSL = strlen(pTesty);
	printf("testy is now (%s)\n",pTesty);
	if (EXIT_SUCCESS == iRC && iOSL != iMSL) {
		if (0 == strcmp(pTesty,"")) {
			return EXIT_SUCCESS;
		} else {
			return EXIT_FAILURE;
		}
	} else {
		return EXIT_FAILURE;
	}
}


