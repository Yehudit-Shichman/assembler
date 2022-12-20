
#include "label.h"
int islabel(char label[],int line)/*gets a string and number of line anr return 1 if it a label declaretion 0 if itdeclaretion of non valid label and -1 else*/
{
	int i=0;
	if(isalpha(label[i]))
	{
		i++;		
		for(; label[i]!='\0'&&i<MAXLENGTH+1;i++)
			if(!(isalnum(label[i])))
			{
				if(label[i]==':'&&label[i+1]=='\0')
				{
					if(i>=MAXLENGTHLABEL)
						{
							printf("\nerror in line %d. the label %s is too long.\n",line,label);
							return 0;
						}
					else
						return 1;
				}
			} 
		
	}
	return -1;
}
int islabelincode(char label[])/*gets a string return 1 if it use of a labelelse returns 0 */
{
	int i=0;
	if(isalpha(label[i]))
	{
		i++;		
		for(; label[i]!='\0'&&i<MAXLENGTHLABEL+1;i++)
			if(!(isalnum(label[i])))
			{
				return 0;
			} 
		if(i==MAXLENGTHLABEL+1)
			return 0;
	}
	return 1;
}
int addtolabeltable(char label[],tlb labeltype,int line)/*gets a name of a label, type and line number and insert the label to the label table return 1 if there is an error returns 0*/
{
	char * ch;
	ptr p,new=NULL;
	p=headl;
	if (!isnewlabel(label,headl,line))
		return 0;
	else
	{
		
		new= (ptr) malloc(sizeof(lt));
		if(!new)
		{
			printf("error in malloc");
			exit(0);
		}
		new->namelabel=label;
		
		if(labeltype==ext)
		{
			fextern=1;
			new->address=0;
		}
		else 
		{
			if(labeltype==code)
				new->address=getIC();
			else
				new->address=getDC();
			ch=new->namelabel;
			while((*ch)!=':')
				(ch)++;
			(*ch)='\0';
		}
		if(!isnotreservedword(new->namelabel, line, "label"))
		{
			free(new);
			return 0;
		}
		new->type=labeltype;
		new-> isentry=0;
		new->next=NULL;
		if(!headl)
			headl=new;
		else
		{
			while(p->next)
				p=p->next;
			p->next=new;
		}

	}
	return 1;
}
int getaddress(char * name)/*gets a name of a label, and returns its address*/
{
	ptr label=findlabel(name);
	if(label)
		return label->address;
	return -1;
}
int gettype(char * name)/*gets a name of a label, and returns its type*/
{
	ptr label=findlabel(name);
	if(label)
		return label->type;
	return null;
}
ptr findlabel(char * name)/*gets a name of a label, and returns it if its not exist returns null*/
{
	ptr label=headl;
	while(label)
		if(!strcmp(name,label-> namelabel))
			return label;
		else
			label=label->next;
	return NULL;
}
void markentry(char * name)/*gets a name of alabel that is entry and mark it*/
{
	ptr p=findlabel(name);
	p->isentry=1;
	fentry=1;
}
void updatelabeltable(int IC)/*gets the final IC and adds it to the addresses in the label table*/
{
	ptr label=headl;
	while(label)
	{
		if(label->type==code)
			label->address+=START_ADDRESS;
		else
			if(label->type==data)
				label->address+=IC;
				
		label=label->next;
	}
}
void writetoen(FILE * fden)
{
	ptr p=headl;
	while(p)
	{
		if(p->isentry)
		{
			fputs(p->namelabel,fden);
			fputc('\t',fden);
			printaddress(p->address,fden);
			fputc('\n',fden);
		}
		p=p->next;
	}
}
int getfentry()
{
	return fentry;
}
int getfextern()
{
	return fextern;
}
void freelbl()/*free the memory alloction*/
{
	ptr h=NULL;
	while(headl)
	{
		h=headl;
		headl=headl->next;
		free(h);
	}
	fextern=0;
	fentry=0;
}
	
