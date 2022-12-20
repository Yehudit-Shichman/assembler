#include "oiput.h"
/*---------------------------*/
void saveamfile(FILE * fdam)/*close the final am file*/
{
	
	fclose(fdam);
}
FILE* openfile(char name [] ,char end[4] , char status[])
{
	int i;
	FILE * fd=NULL;
	char * filename=(char *)malloc(strlen(name)+4);
	for(i=0;name[i]!='\0';i++)
		filename[i]=name[i];
	filename[i]='\0';
	fd=fopen(strcat(filename,end),status);
	if(!fd)
	{
		printf("cannot open %s file.",filename);
		exit(0);
	}
	return fd;
}
void createob(char name[])
{
	FILE * fdob=NULL;
	fdob=openfile(name,".ob","wb");
	writetobj(fdob);
	fclose(fdob);
}
void creatent(char name[])
{
	FILE * fden=NULL;
	fden=openfile(name,".ent","wb");
	writetoen(fden);
	fclose(fden);
}
FILE * creatext(char name[])
{
	FILE * fdex=NULL;
	fdex=openfile(name,".ext","wb");
	return fdex;
}
void saveandcreateoutput(char name[])/*call to create ob,en,ex acoordding to needing.*/
{
	createob(name);
	if(getfentry())
		creatent(name);
	
}
