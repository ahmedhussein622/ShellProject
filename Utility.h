#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "Constants.h"




// concatinte the two strings in a new string
void strConcatenate(char * r,char *a, char *b);

//split string a using charachter c the resutl is put in resutl
int splitOnChar(char *a, char c, char result[][maxStringLength]);

//remove white spaces and tabs from the begining and the end
//of char a, the result is put in same string
void trim(char *a);




#endif // UTILITY_H_INCLUDED







