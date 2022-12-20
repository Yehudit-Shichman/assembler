#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "operators.h"
#include "generaldata.h"
#include "memoryimage.h"

/*in this file-------------------------------*/
void datalouding();/*loud the data of the assembler*/
opr findoperation(char *,int);/*gets operators name and returns its structure*/
int findL(int ,...);/*gets the number of the operands and their addressing method and returns the number of the mashine code's lines*/
int decoding(char *,int);/*gets  operand and checks his addressing mathods*/
void codefirst(int,opr,...);/*gets operator and addressing methods and build the first word of the mashine-code*/
int codesecond(wrd,FILE *,int);/*gets the continue of the line- theoperands and make the code of the other lines-create and write to the external file-if it required*/
int immediateaddress(char * operand,int IC,int x,int);/*sub-function of code second*/
int directaddress(char * operand,int IC,int x,FILE * fdex,int);/*sub-function of code second*/
int structaddress(char * operand,int IC,int x,int);/*sub-function of code second*/
int static sourceregister( char * operand, int IC, int x);/*sub-function of code second*/
int static distinationregister(char * operand,int IC,int x,int freg);/*sub-function of code second*/
int static adddatacode(int,int,int);/*sub-function of code second*/
void validsource(int ,int ,int ,int ,int );/*sub-function of datalouding*/
void validdestination(int ,int ,int ,int ,int );/*sub-function of datalouding*/
int coding(wrd,int);/*analyzing the structure of the operands and caaalling the coding function*/
/*-------------------------------------------*/
/*in other files-----------------------------*/
/*-------------------------------------------*/
int islabel(char []);/*in label.c*/
int converttobinary(int,int);/*in general.c*/
int getaddress(char *);/*in label.c*/
int gettype(char*);/*in label.c*/
int islabelincode(char []);/*in label.c*/
void updateIC(int );/*in general.c*/
void writetoex(char *,int,FILE * );/*in general.c*/
int getIC();/*in general.c*/
int isinteger(char *,int);/*in validation.c*/
int isvalidaddressingmethod(opr,int,int issource,int );/*in validation.c*/
