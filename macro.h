#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "generaldata.h"
static int countermacro=0;/*the ammount of the macros*/
/*-------in this file----------------------*/
int preprosessor(char * filename);
int ismacro(char [],tmcr);/*gets a string and returns its number in the macro table and 0 if its not a macro*/
void writemacro(tmcr,int,FILE**);/*remove the macro name and pufs its content to the am*/
char * ismacrodec(char * currentline);/*checks if it a declaretion of a new macro and returns its name else returns null*/
int addmacroname(char* ,tmcr *,int);/* adds anew macro to the macro label and returns 1 if it is not a valid name returns 0*/
int isendmacro(char *);/*is it the label "endmacro"*/
 void addlinetomacro(char * ,tmcr );/*adds a line to a macro in the macro table*/
 void writetoam(char * ,FILE** );/*copy a line to the am file*/

void freetmcr(tmcr headmtbl);/*free the memory alloction*/
void freemcr(mcr hmcr);/*free the memory alloction*/
/*---in other files------------------------*/


void saveamfile(FILE * fdam);/* in oiput.c*/
FILE * openfile(char *,char[4],char *);/* in oiput.c*/
int isnewmacro(char macroname[],tmcr m,int);/* in validation.c*/
int isnotreservedword(char name[],int line,char * type);/* in validation.c*/
