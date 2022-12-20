
#include "validation.h"

/*--------------------------------------------*/
int isnewlabel(char labelname[],ptr p,int line)
{
	int i;
	while(p)
	{
		for(i=0;i<MAXLENGTHLABEL;i++)
		{	if (labelname[i]!=p->namelabel[i])
			{
				if (labelname[i]==':')
				{
				
					return 0;
				}
				p=p->next;
				i=MAXLENGTHLABEL;
			}
			else ;
		}
	}
	return 1;
}
int isnewmacro(char macroname[],tmcr m,int line)
{
	int i;
	while(m)
	{
		for(i=0;i<MAXLENGTH;i++)
		{	if (macroname[i]!=m->namemacro[i])
			{
				m=m->next;
				i=MAXLENGTH;
			}
			else if (macroname[i]=='\0')
				{
					printf("error in line: %d. the macro %s is already exist.",line,macroname);
					return 0;
				}
		}
	}
	return 1;
}
int isnotreservedword(char name[],int line,char * type)
{
	int i;
	for(i=0;i<RESERVEDWORDS;i++)
		if(!strcmp(reservedwords[i],name))
		{
			printf("\n error in line %d: the %s %s is not valid. the word %s is a reserved word.",line,type,name,name);
			return 0;
		}
	return 1;
}
int isinteger(char * num,int line)
{
	long double number=atof(num);
	if((number-(int)number)==0)
		return 1;
	printf("\nerror in line %d. %s is not an integer.\n",line,num);
	return 0;
}
int isvalidaddressingmethod(opr operator,int method,int issource, int line)
{
	if(issource)
	{
		if(!(operator->isvalidsource[method]))
			printf("\nerror in line %d:%d is not a valid addressing method for the source operand in %s.\n",line,method,operator->name);
		return operator->isvalidsource[method];
	}
	else 
	{
		if(!(operator->isvaliddestination[method]))
			printf("\nerror in line %d:%d is not a valid addressing method for the destination operand in %s.\n",line,method,operator->name);
		return operator->isvaliddestination[method];
	}	
}
