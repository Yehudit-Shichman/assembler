#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generaldata.h"
#include "operators.h"
#define RESERVEDWORDS 32
/*--------------------------------------------*/
/*for macro file------------------------------*/
int isnewmacro(char macroname[],tmcr m,int line);
int isnotreservedword(char name[],int line,char * type);/*uses in label.c and in macro.c*/
/*--------------------------------------------*/
/*general-------------------------------------*/
int isinteger(char * num,int line);
/*--------------------------------------------*/
/*label.c-------------------------------------*/
int isnewlabel(char labelname[],ptr p,int line); 
/*command.c-------------------------------------*/
int isvalidaddressingmethod(opr operator,int method,int issource, int line);
char * reservedwords[]={"r0","r1","r2","r3","r4","r5","r5","r7","macro","endmacro","PSW","string","extern","struct","data","entry","mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","get","prn","jsr","rst","hlt"};
