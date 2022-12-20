#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "generaldata.h"
int fentry=0;/*is there an entry in that file*/
int fextern=0;/*is there an extern in that file*/
ptr headl=NULL;
/*---------in this files------------------------*/
int islabel(char[],int);/*gets a string and number of line anr return 1 if it a label declaretion 0 if itdeclaretion of non valid label and -1 else*/
int islabelincode(char []);/*gets a string return 1 if it use of a labelelse returns 0 */
int addtolabeltable(char[],tlb,int);/*gets a name of a label, type and line number and insert the label to the label table return 1 if there is an error returns 0*/
int getaddress(char *);/*gets a name of a label, and returns its address*/
int gettype(char *);/*gets a name of a label, and returns its type*/
ptr findlabel(char *);/*gets a name of a label, and returns it if its not exist returns null*/
void markentry(char *);/*gets a name of alabel that is entry and mark it*/
void updatelabeltable(int );/*gets the final IC and adds it to the addresses in the label table*/
void writetoen(FILE * fden);
int getfentry();
int getfextern();
void freelbl();/*free the memory alloction*/
/*---------in other files------------------------*/
int converttobinary(int,int);/*in general.c*/
char * convertto32wrd(unsigned short int []);/*in general.c*/
int isnewlabel(char*,ptr,int);/*in validation.c*/
int getDC();/*in general.c*/
int getIC();/*in general.c*/
int isnotreservedword(char name[],int line,char * type);/*in validation.c*/
void printaddress(int,FILE * );/*in general.c*/
/*----------------------------------------------*/



