#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "memoryimage.h"
#include "generaldata.h"
int IC=0;
int DC=0;
char currentline[MAXLENGTH+1];
int i=0;/*index in current line*/
int  binary[32][5]={{0,0,0,0,0},{0,0,0,0,1},{0,0,0,1,0},{0,0,0,1,1},{0,0,1,0,0},{0,0,1,0,1},{0,0,1,1,0},{0,0,1,1,1},{0,1,0,0,0},{0,1,0,0,1},{0,1,0,1,0},{0,1,0,1,1},{0,1,1,0,0},{0,1,1,0,1},{0,1,1,1,0},{0,1,1,1,1},{1,0,0,0,0},{1,0,0,0,1},{1,0,0,1,0},{1,0,0,1,1},{1,0,1,0,0},{1,0,1,0,1},{1,0,1,1,0},{1,0,1,1,1},{1,1,0,0,0},{1,1,0,0,1},{1,1,0,1,0},{1,1,0,1,1},{1,1,1,0,0},{1,1,1,0,1},{1,1,1,1,0},{1,1,1,1,1}};
char base32[32]={'!','@','#','$','%','^','&','*','<','>','a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v'};
char okword[2];
/*---------------------------------*/
void startsecondpassIC();
void zeroIC();
void zeroDC();
int getDC();
int getIC();
void updateIC(int);
void updateDC(int);
void whitespace();/*skip on whitespaces*/
int readline(FILE *,int );/* reads the next line from the am file*/
char * readword();/*from currentline*/
wrd divtowords();/*divides into words*/
/*int whitespacemac(int ,char *);skip on whitespaces- for macro*/
char * convertto32wrd(unsigned short int []);/*get a binary code word and converts it to 32 code*/
char findbase32(unsigned short int []);/*sub-function of convertto32wrd*/
void printaddress(int ,FILE * );/*prints address in 32 code to object, extern or entry file*/
int converttobinary(int,int);/* gets a decimal number and length (8 or 10 bits)*/
int iswhitespace(char );/* gets a char and return 1 if it a whitespace else returns 0*/
void freewrd(wrd );/*free the memory alloction*/
