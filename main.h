#include <stdlib.h>
#include <stdio.h>
#include "generaldata.h"
/*#include "macro.h"*/
/*--------in use in main function----*/
void datalouding();/*in general.c*/
int preprosessor(char *);/*in macro.c */
FILE * openfile(char *,char[4],char *);/* in oiput.c */
int firstpass(FILE *);/*in this file*/
int secondpass(FILE *,FILE *);/*in this file*/
void saveandcreateoutput(char *);/* in oiput.c */
FILE * creatext(char*);/* in oiput.c */
int getfextern();/* in label.c*/
void freelbl();/* in label.c*/
/*--------in use in firstpass function----*/
int readline(FILE *,int);/*in general.c*/
wrd divtowords();/*in general.c*/
int islabel(char[],int);/* in label.c */
int isdiraction(char *);/*in direction.c*/
int addtolabeltable(char[],tlb,int);/*in label.c*/
int codediraction(wrd,int);/*in direction.c*/
int isextern(char *);/*in direction.c*/
int isentry(char *);/*in direction.c*/
int isvalid();/* in validion.c */
void updatelabeltable(int);/* in label.c*/
int coding(wrd,int);/*in command.c*/
int getDC();/*in general.c*/
int getIC();/*in general.c*/
void freewrd(wrd);/*in general.c*/
void zeroIC();/*in general.c*/
void zeroDC();/*in general.c*/
int gettype(char *);/* in label.c*/
/*--------in use in secondpass function----*/
void markentry(char *);/* in label.c*/
int codesecond(wrd,FILE *,int);/*in command.c*/
void startsecondpassIC();/*in general.c*/

