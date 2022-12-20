
#include "macro.h"

int preprosessor(char * filename)
{
	tmcr htable=NULL;
	FILE * fdas;
	FILE * fdam;
	int cmacro=0;/*is it use in macro*/
	int isvalid=1;
	char currentline[MAXLENGTH];
	char * macroname;
	int i=0;
	int fmacro=0;/*is it is line in macro*/

	fdas=openfile(filename,".as","rb");

	fdam=openfile(filename,".am", "wb");

	fgets(currentline,MAXLENGTH,fdas);
	while (!feof(fdas))
	{
		i++;
		cmacro=ismacro(currentline, htable);
		if (cmacro)
		{
			writemacro(htable,cmacro,&fdam);
		}
		else 
		{
			macroname=ismacrodec(currentline);
			if (macroname)
			{
				if(isnewmacro(macroname,htable,i))
				{
					fmacro=1;
					if(!addmacroname(macroname,&htable,i))
						isvalid=0;
				}
				else
					isvalid=0;
			}
			else
			{
				if(fmacro&&(!isendmacro(currentline)))
				{	
					addlinetomacro(currentline,htable);
				}
				if(isendmacro(currentline))
				{
					fmacro=0;
				}
				else 
				{
					if(!fmacro)
					{
						writetoam(currentline,&fdam);
					}
				}
			}
		}
		fgets(currentline,MAXLENGTH,fdas);		
	}
	saveamfile(fdam);
	freetmcr(htable);
	fclose(fdas);
	return isvalid;
}
/*-----------------------------------------------------------------
-------------------------------------------------------------------
-----------------------------------------------------------------*/
int ismacro(char currentline[],tmcr htable)/*gets a string and returns its number in the macro table and 0 if its not a macro*/
{
	int i,j,flag=1;
	while( htable)
	{
		for(i=0; i<MAXLENGTH;i++)
			if (!(currentline[i]==' '||currentline[i]=='\t'))
				break;
		for(j=0;(currentline[i]!= ' '&&currentline[i]!='\t'&&currentline[i]!='\n')&&i<MAXLENGTH;j++,i++)
			{
				if(!(currentline[i]==htable->namemacro[j]))
					flag=0;
			}
		if (flag&&j)
			return htable->nummacro;
		htable=htable->next;
		flag=1;
	}

	return 0;
}
void writemacro(tmcr htable,int macro,FILE** fd)/*remove the macro name and pufs its content to the am*/
{
	int i;
	mcr thismacro=NULL;
	for(i=1;i<macro;i++)
		htable=htable->next;
	thismacro=htable->macrocontent;
	while(thismacro)
	{
		fputs(thismacro->data,*fd);
		thismacro=thismacro->next;
	}
}
char * ismacrodec(char * currentline)/*checks if it a declaretion of a new macro and returns its name else returns null*/
{
	char m[5]= "macro";
	int i,j;
	for(i=0; i<MAXLENGTH;i++)
		if (!(currentline[i]==' '||currentline[i]=='\t'))
			break;
	for(j=0;j<THE_WORD_MACRO&&i<MAXLENGTH;j++,i++)
		if(!(currentline[i]==m[j]))
			return NULL;
	for(; i<MAXLENGTH;i++)
		if (!(currentline[i]==' '||currentline[i]=='\t'))
			break;
	return &currentline[i];
}
int addmacroname(char* namemacro,tmcr * crntmcr,int line)/* adds anew macro to the macro label and returns 1 if it is not a valid name returns 0*/
{
	int i;
	tmcr newmacro;
	if( !isnotreservedword( namemacro, line,"macro"))
		return 0;
	newmacro=(tmcr) malloc (sizeof(macrotable));
	for (i=0;i<MAXLENGTH&&(namemacro[i]!= '\0'&&namemacro[i]!= '\0');i++)
		newmacro->namemacro[i]=namemacro[i];
	newmacro->nummacro=++countermacro;
	newmacro->next=NULL;
	newmacro->macrocontent=NULL;
	if (*crntmcr)
		(*crntmcr)->next=newmacro;
	else(* crntmcr)= newmacro;
	return 1;
}
int isendmacro(char * currentline)/*is it the label "endmacro"*/
{
	char em[THE_WORD_END_MACRO]="endmacro";
	int i,j;
	for(i=0; i<MAXLENGTH;i++)
		if (!(currentline[i]==' '||currentline[i]=='\t'))
			break;
	for(j=0;j<THE_WORD_END_MACRO&&i<MAXLENGTH;j++,i++)
		if(!(currentline[i]==em[j]))
			return 0;
	for(; i<MAXLENGTH;i++)
		if (!(currentline[i]==' '||currentline[i]=='\t'))
			break;
	return 1;
}
void addlinetomacro(char * currentline,tmcr htable)/*adds a line to a macro in the macro table*/
{
	int i;
	mcr thismacro=NULL;
	mcr newline=NULL;
	if (htable)
	{
		while( htable->next)
			htable=htable->next;
		thismacro=htable->macrocontent;
		newline=(mcr)malloc(sizeof(macro));
		for (i=0;i<MAXLENGTH&&(currentline[i]!= '\0'&&currentline[i]!= '\n');i++)
			newline->data[i]=currentline[i];
		if(currentline[i]=='\n')
			newline->data[i]='\n';
		newline->next=NULL;
			newline->data[i+1]='\0';
		if(thismacro)
		{
			while( thismacro->next)
			{
				thismacro=thismacro->next;
			}
			thismacro->next=newline;

		}
		else
			htable->macrocontent=newline;
	}
}
void writetoam(char * currentline,FILE** fd)/*copy a line to the am file*/
{
	fputs(currentline,*fd);
}
void freetmcr(tmcr headmtbl)/*free the memory alloction*/
{
	tmcr h;
	countermacro=0;	
	h=NULL;
	while(headmtbl)
	{
		h=headmtbl;
		headmtbl=headmtbl->next;
		freemcr(h->macrocontent);
		free(h);
	}
}
void freemcr(mcr hmcr)/*free the memory alloction*/
{
	mcr h=NULL;
	while(hmcr)
	{
		h=hmcr;
		hmcr=hmcr->next;
		free(h);
	}
}


