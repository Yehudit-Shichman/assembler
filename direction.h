#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "generaldata.h"
#include "memoryimage.h"

/*in this file-------------------------------*/
int isdiraction(char * );/*gets a string and returns 1 if data,string or struct direction else returns 0*/
int isdata(char*);/*gets a string and returns 1 if data direction else returns 0*/
int isstring(char* );/*gets a string and returns 1 if string direction else returns 0*/
int isstruct(char* );/*gets a string and returns 1 if  struct direction else returns 0*/
int isentry(char* );/*gets a string and returns 1 if entry direction else returns 0*/
int isextern(char* );/*gets a string and returns 1 if extern direction else returns 0*/
int codediraction(wrd ,int);/*gets a direction line and makes its code*/
int codedata(wrd,int );/*gets a data direction line and makes its code*/
int codestring(wrd ,int);/*gets a string direction line and makes its code*/
int codestruct(wrd,int);/*gets a struct direction line and makes its code*/

/*-------------------------------------------*/
/*in other file------------------------------*/
/*-------------------------------------------*/
int converttobinary(int,int);/*general.c*/
int getDC();/*general.c*/
void updateDC(int);/*general.c*/
int isinteger(char*,int line);/*in validation.c*/
