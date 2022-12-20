#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

FILE* openfile(char[] ,char[4], char[]);
void saveamfile(FILE * fdam);/*close the final am file*/
void createob(char[]);
void createent();
FILE * creatext();
void saveandcreateoutput();/*call to create ob,en,ex acoordding to needing.*/
/*---------------------------*/
void writetobj(FILE *);/*in general.c*/
void writetoen(FILE *);/*in label.c*/
void writetoex(FILE *);/*in general.c*/
int getfentry();/*in label.c*/
int getfextern();/*in label.c*/
