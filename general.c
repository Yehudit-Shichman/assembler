#include "general.h"
/*---------------------------------------*/
int getDC()
{
	return DC;
}
int getIC()
{
	return IC;
}
void updateIC(int L)
{
	IC+=L;
}
void updateDC(int L)
{
	DC+=L;
}
void startsecondpassIC()
{
	IC=START_ADDRESS;
}
void zeroIC()
{
	IC=0;
}
void zeroDC()
{
	DC=0;
}
void whitespace()/*skip on whitespaces*/
{
	for(; i<MAXLENGTH;i++)
		if (!(currentline[i]==' '||currentline[i]=='\t'))
			break;
}
/*int whitespacemac(int i,char * currentline)skip on whitespaces- for macro
{
	for(; i<MAXLENGTH&&currentline[i]!='\n';i++)
		if (!(currentline[i]==' '||currentline[i]=='\t'))
			return i;
	return i;
}*/
int readline(FILE * fd,int line)
{
	int i=0,okline=0;
	if(!feof(fd))
	{
		currentline[i]=fgetc(fd);
		if(currentline[i]==';')
		{
			line++;
			readline(fd,line);
		}
		for(i=1;i<MAXLENGTH&&currentline[i-1]!='\n'&&currentline[i-1]!=EOF;i++)
		{
			currentline[i]=fgetc(fd);
			if(!iswhitespace(currentline[i]))
				okline=1;
		}
		if(i==MAXLENGTH&&(currentline[i-1]!='\n')&&okline)
		{
			while(fgetc(fd)!='\n');
				fgetc(fd);
			printf("error in line %d: line %d is too long line.",line,line);
			return 0;
		}
		if(!okline)
			readline(fd,++line);
	}
	return line;
}

wrd divtowords()
{
	wrd w2,w3;
	i=0;
	whitespace();
	head=(wrd)malloc(sizeof(w1));
	head->string=readword();
	w3=head;
	while(i<MAXLENGTH&&currentline[i]!='\n'&&currentline[i]!=EOF)
	{
		whitespace();
		w2=(wrd)malloc(sizeof(w1));
		w2->string=readword();
		w3->next=w2;
		w3=w3->next;
	}
	w3->next=NULL;
	return head;
}
char * readword()/*from currentline*/
{
	int j;
	char* string=(char*)malloc(MAXLENGTH*(sizeof(char)));
	for(j=0;(!iswhitespace(currentline[i]))&&currentline[i]!='\n'&&currentline[i]!=EOF;j++,i++)
		string[j]=currentline[i];
	string[j]='\0';
	return string;
}
int converttobinary(int num,int cdigit)
{
	int var=1,bin=0,isnegative=0,mask=1,start=0;
	long divider=10;
	if(num<0)
	{
		isnegative=1;
		num=-num;
	}
	while(num>0)
	{
		bin=bin+((num%2)*var);
		num/=2;
		var*=10;
	}
	if(isnegative)
	{
		for(i=0;i<cdigit&&i<9;i++)
		{
			if(!start)
			{
				if(bin%divider)
					start=1;
				divider*=10;
				
			}
			else
			{
				mask=divider/10;
				if((bin%divider)/mask==1)
					bin-=mask;
				else
					bin+=mask;
				divider*=10;
			}
		}
		if(cdigit==10&&start)
			bin+=1000000000;
	}		
	return bin;
}
char * convertto32wrd(unsigned short int binaryword[])
{
	okword[0]=findbase32(binaryword);
	okword[1]=findbase32(binaryword+5);
	return okword;
}
char findbase32(unsigned short int binaryword[5])
{
	int degel=0;
	int i,j;
	for(j=0;j<32&&!degel;j++)
	{
		degel=1;
		for(i=0;i<5;i++)
			if(binaryword[i]!=binary[j][i])
				degel=0;
		
	}
	return base32[j-1];
}
int iswhitespace(char c)
{
	if(c=='\t'||c==' ')
		return 1;
	return 0;
} 
void writetoex(char * label,int useaddress,FILE * fdex)
{
	fputs(label,fdex);
	fputc('\t',fdex);
	printaddress(useaddress,fdex);/*tochange to base 32*/
	fputc('\n',fdex);

}
void printaddress(int add,FILE * fd)
{
	int y,binaddress;
	unsigned short int address[10];
	binaddress=converttobinary(add,10);
	for(y=9;y>=0;y--)
		if (binaddress!=0)
		{
			address[y]=binaddress%10;
			binaddress/=10;
		}
		else 	
			address[y]=0;
			
		fputs(convertto32wrd(address),fd);
		fputc('\t',fd);
}
void writetobj(FILE * fdob)
{
	int i,y,binaddress;
	unsigned short int address[10];
	binaddress=converttobinary(IC-START_ADDRESS,10);
	for(y=9;y>=0;y--)
		if (binaddress!=0)
		{
			address[y]=binaddress%10;
			binaddress/=10;
		}
		else 	
			address[y]=0;
			
		fputs(convertto32wrd(address),fdob);
		fputc(' ',fdob);
	binaddress=converttobinary(DC,10);
	for(y=9;y>=0;y--)
		if (binaddress!=0)
		{
			address[y]=binaddress%10;
			binaddress/=10;
		}
		else 	
			address[y]=0;
			
		fputs(convertto32wrd(address),fdob);
		fputc('\n',fdob);
		fputc('\n',fdob);
		
	for(i=0;i<(IC-START_ADDRESS);i++)
	{
		binaddress=converttobinary(i+START_ADDRESS,10);
		
		for(y=9;y>=0;y--)
			if (binaddress!=0)
			{
				address[y]=binaddress%10;
				binaddress/=10;
			}
			else 	
				address[y]=0;
			
			fputs(convertto32wrd(address),fdob);
			fputc('\t',fdob);
			fputs(convertto32wrd(binarycode[i]),fdob);
			fputc('\n',fdob);			
	}
	for(i=0;i<DC;i++)
	{
		binaddress=converttobinary(i+IC,10);
		
		for(y=9;y>=0;y--)
			if (binaddress!=0)
			{
				address[y]=binaddress%10;
				binaddress/=10;
			}
			else 	
				address[y]=0;
			
			fputs(convertto32wrd(address),fdob);
			fputc('\t',fdob);
			fputs(convertto32wrd(binarycodedata[i]),fdob);
			fputc('\n',fdob);			
	}
}
void freewrd(wrd hwrd)
{
	wrd h=NULL;
	while(hwrd)
	{
		h=hwrd;
		hwrd=hwrd->next;
		free(h);
	}
}
