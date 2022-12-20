#include "direction.h"
/*-------------------------------------------*/
int isdiraction(char * word)/*gets a string and returns 1 if data,string or struct direction else returns 0*/
{
	if(isdata(word)||isstring(word)||isstruct(word))
		return 1;
	return 0;
}
int isdata(char* word)/*gets a string and returns 1 if data direction else returns 0*/
{
	int flag=1;
	char data[]={"data"};
	int i;
	if((*word)!='.')
		return 0;	

	for(i=1;i<MAXLENGTH&&i<strlen(data)+1;i++)
		if(!(word[i]==data[i-1]))
			{
				flag=0;
				break;
			}

	return flag;
}
int isstring(char* word)/*gets a string and returns 1 if string direction else returns 0*/
{
	int flag=1;
	char string[]={"string"};
	int i;
	if((*word)!='.')
		return 0;
	

	for(i=1;i<MAXLENGTH&&i<strlen(string)+1;i++)
		if(!(word[i]==string[i-1]))
			{
				flag=0;
				break;
			}

	return flag;
}
int isstruct(char* word)/*gets a string and returns 1 if  struct direction else returns 0*/
{
	int flag=1;
	char str[]={"struct"};
	int i;
	if((*word)!='.')
		return 0;

	for(i=1;i<MAXLENGTH&&i<strlen(str)+1;i++)
		if(!(word[i]==str[i-1]))
			{
				flag=0;
				break;
			}

	return flag;
}
int isentry(char* word)/*gets a string and returns 1 if  entry direction else returns 0*/
{
	char entry[]="entry";
	int flag=1;
	int i;
	if((*word)!='.')
		return 0;
	
	for(i=1;i<MAXLENGTH&&i<strlen(entry)+1;i++)
		if(!(word[i]==entry[i-1]))
			{
				flag=0;
				break;
			}

	return flag;
}
int isextern(char* word)/*gets a string and returns 1 if  extern direction else returns 0*/
{
	
	int flag=1;
	char ex[]={"extern"};
	int i;
	if((*word)!='.')
		return 0;
	
	
	for(i=1;i<MAXLENGTH&&i<strlen(ex)+1;i++)
		if(!(word[i]==ex[i-1]))
			{
				flag=0;
				break;
			}

	return flag;
}	
int codediraction(wrd words,int line)/*gets a direction line and makes its code*/
{
	char * w=NULL;
	if(words&&words->next)
	{	w=words->string;
		if(isdata(w))
			return codedata(words->next,line);
		if(isstring(w))
			return codestring(words->next,line);
		if(isstruct(w))
			return codestruct(words->next,line);
	}
	return 0;
}
int codedata(wrd words,int line)/*gets a data direction line and makes its code*/
{
	char var[MAXLENGTH];
	int i,x,j,num;
	int DC=getDC();
	int ok=1;
	while(words)
	{
		if(words->string[0]!=','&&!ok)
		{
			printf("error in line : %d. requird ','",line);
			return 0;
		}
		for(i=0;words->string[i]!='\0';i++)
		{	
			ok=0;
			for(x=0;words->string[i]!=','&&words->string[i]!='\0';x++,i++)
				var[x]=words->string[i];
			var[x]='\0';
			if(!isinteger(var,line))
				return 0;
			num=atoi(var);
			num=converttobinary(num,10);
			for(j=9;j>=0;j--)
			{
				binarycodedata [DC][j]=num%10;
				num/=10;
			}
			DC++;
			updateDC(1);
			if(words->string[i]==',')
				ok=1;
			if(words->string[i]=='\0')
				i--;
		}
		words=words->next;
	}
	return 1;
}
int codestring(wrd words,int line)/*gets a string direction line and makes its code*/
{
	int i,j,num,x=0;
	int DC=getDC();
	if (words)
		if(words->string[0]!='"')
		{
			printf("\nerror in line: %dthis is not a valid string.\n",line);
			return 0;
		}
	i=1;
	while(words)
	{
		if(!words->next)
		{
			x=1;
			if((words->string[strlen(words->string)-1])!='"')
			{
				printf("\nerror in line: %dthis is not a valid string.\n",line);
				return 0;
			}
		}
		for(;i<(strlen(words->string)-x);i++)
		{
			num=converttobinary(words->string[i],10);
			for(j=9;j>=0;j--)
			{
				binarycodedata [DC][j]=num%10;
				num/=10;
			}
			DC++;
			updateDC(1);
			
		}
		words=words->next;
		i=0;
	}
	for(j=9;j>=0;j--)
		binarycodedata [DC][j]=0;
	DC++;
	updateDC(1);
	return 1;
}
int codestruct(wrd words,int line)/*gets a struct direction line and makes its code*/
{
	int ok=1;
	char * stringnum=NULL;
	int i,j,num=0;
	int DC=getDC();
	if(words)
	{
		stringnum=words->string;
		stringnum++;
		for(i=1;i<strlen(words->string)-1&&words->string[i]!=',';i++)
		{
			stringnum++;
		}
		if(*stringnum==',')
			*stringnum='\0';
		if(!isinteger(words->string,line))
			return 0;
		num=converttobinary(atoi(words->string),10);
		if(stringnum)
			*stringnum=',';
		for(j=9;j>=0;j--)
		{
			binarycodedata [DC][j]=num%10;
			num/=10;
		}
		DC++;
		updateDC(1);
		if(words->string[i]==',')
		{
			i++;
			ok=1;
			if(i==strlen(words->string))
			{
				words=words->next;
				i=0;
			}
			else 
				words->string+=i;

		}
		else
		{
			words=words->next;
			i=0;
			ok=0;
		}
		if(words)
		{
			if(!ok)
			{
				if(words->string[i]!=',')
				{
					printf("error in line: %d:  ',' required.",line);
					return 0;
				}
			}
			codestring(words,line);
		}
	}
	return 1;
}		
