#include "main.h"
/* ------------------------------------------ */
/* ----------------main---------------------- */
/* ------------------------------------------ */
int main (int argc,char * argv[])
{
	int i,fvalidation;
	FILE * fdam=NULL;
	FILE * fdex=NULL;
	datalouding();
	
	for (i=1;i<argc;i++)
	{
		printf("\nthe file: %s.as ",argv[i]);
		fvalidation=preprosessor(argv[i]);
		if (fvalidation)
		{
			fdam=openfile(argv[i],".am", "rb");
			fvalidation=firstpass(fdam);
			if (fvalidation)
			{
				rewind(fdam);
				if(getfextern())
					fdex=creatext(argv[i]);
				if(secondpass(fdam,fdex))
				{
					saveandcreateoutput(argv[i]);
					printf("is ok\n");
				}
				if (fdex)
				{
					fclose(fdex);
					fdex=NULL;
				}
				
			}
			fclose(fdam);
		}
		freelbl();
	}
	
	return 1;
}
/*---------------------------*/

int firstpass(FILE * fdam)
{
	int flabel=0;
	int var,i=1,isvalid=1;
	wrd words=NULL,wordshead=NULL;
	zeroIC();
	zeroDC();
	var=readline(fdam,i);
	if(var>i)/*update i if there was a comment or a empty line*/
		i=var;                                                               
	while(!var)
	{
		var=readline(fdam,i);
		if(var>i)
			i=var;
		isvalid=0;
		i++;
	}
	words=divtowords();
	wordshead=words;
	while(!feof(fdam))
	{
		if(words)
			flabel=islabel(words->string,i);
		if(flabel==1)
			words=words->next;
		if(flabel==0)
			isvalid=0;
		if(words)
		{
			if(isdiraction(words->string))
			{
				if(flabel==1)
					{
						if(!addtolabeltable(wordshead->string,data,i))
						{	printf("error in line %d the label %s is already exist\n",i, wordshead->string);
							isvalid=0;
						}
						flabel=-1;		
					}
				if(!(codediraction(words,i)))
					isvalid=0;
			}
			else 
			{
				if(isextern(words->string))
				{
					if(words->next)
						if(!addtolabeltable(words->next->string,ext,i))
						{
							printf("error in line %d the label %s is already exist\n",i, words->next->string);
							isvalid=0;
						}
				}
				else
					if(isentry(words->string));
					else 
					{
						if(flabel==1)
						{
							if(!addtolabeltable(wordshead->string,code,i))
							{
								printf("\nerror in line %d the label %s is already exist\n",i, words->next->string);
								isvalid=0;
								
							}
							flabel=-1;
						}
						if(words)
							if(!coding(words,i))
								isvalid=0;
					}
			}
		} 
		var=readline(fdam,i);
		if(var>i)/*update i if there was a comment or a empty line*/
			i=var;
                                                                               
		while(!var)
		{
			var=readline(fdam,i);
			if(var>i)
				i=var;
			isvalid=0;
			i++;
		}
		i++;
		freewrd(words);
		words=divtowords();
		wordshead=words;
	}
	
	updatelabeltable(getIC()+START_ADDRESS);
	
	return isvalid;
}
 
int secondpass(FILE * fdam,FILE * fdex)
{
	int i=0;
	int isvalid=1;
	wrd words=NULL;
	startsecondpassIC();
	readline(fdam,i);
	words=divtowords();
	while(!feof(fdam))
	{
		i++;
		if(words)
		{
			if (islabel(words->string,i)==1)
				words=words->next;
			if (!(isdiraction(words->string)||isextern(words->string)))
			{
				if (isentry(words->string))
				{
					words=words->next;
					if(words)
					{
						if(!(gettype(words->string)==ext))
							markentry(words->string);
						else
						{
							printf("\nerror in line %d: the label %s cannot be both extern and entry.\n",i,words->string);
							isvalid=0;
						}
					}
				}
				else
					if(!codesecond(words,fdex,i))
						isvalid=0;	
			}
		}
		readline(fdam,i);
		freewrd(words);
		words=divtowords();
	}
	return isvalid;
}
