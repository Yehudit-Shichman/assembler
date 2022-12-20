#include "command.h"
/*-------------------------------------------*/
/*-------------------------------------------*/
/*-------------------------------------------*/
void datalouding()/*loud the data of the assembler*/
{
	int i;
	for (i=0;i<OPERATIONAMOUNT;i++)
		operationtable[i]= (opr)malloc ( sizeof(item));
	operationtable[0]->name="mov";
	operationtable[0]->binariid=0;
	operationtable[0]->operand=2;
	validsource(0,1,1,1,1);
	validdestination(0,0,1,1,1);
	operationtable[1]->name="cmp";
	operationtable[1]->binariid=1;
	operationtable[1]->operand=2;
	validsource(1,1,1,1,1);
	validdestination(1,1,1,1,1);
	operationtable[2]->name="add";
	operationtable[2]->binariid=10;
	operationtable[2]->operand=2;
	validsource(2,1,1,1,1);
	validdestination(2,0,1,1,1);
	operationtable[3]->name="sub";
	operationtable[3]->binariid=11;
	operationtable[3]->operand=2;
	validsource(3,1,1,1,1);
	validdestination(3,0,1,1,1);
	operationtable[4]->name="not";
	operationtable[4]->binariid=100;
	operationtable[4]->operand=1;
	validsource(4,0,0,0,0);
	validdestination(4,0,1,1,1);
	operationtable[5]->name="clr";
	operationtable[5]->binariid=101;
	operationtable[5]->operand=1;
	validsource(5,0,0,0,0);
	validdestination(5,0,1,1,1);
	operationtable[6]->name="lea";
	operationtable[6]->binariid=110;
	operationtable[6]->operand=2;
	validsource(6,0,1,1,0);
	validdestination(6,0,1,1,1);
	operationtable[7]->name="inc";
	operationtable[7]->binariid=111;
	operationtable[7]->operand=1;
	validsource(7,0,0,0,0);
	validdestination(7,0,1,1,1);
	operationtable[8]->name="dec";
	operationtable[8]->binariid=1000;
	operationtable[8]->operand=1;
	validsource(8,0,0,0,0);
	validdestination(8,0,1,1,1);
	operationtable[9]->name="jmp";
	operationtable[9]->binariid=1001;
	operationtable[9]->operand=1;
	validsource(9,0,0,0,0);
	validdestination(9,0,1,1,1);
	operationtable[10]->name="bne";
	operationtable[10]->binariid=1010;
	operationtable[10]->operand=1;
	validsource(10,0,0,0,0);
	validdestination(10,0,1,1,1);
	operationtable[11]->name="get";
	operationtable[11]->binariid=1011;
	operationtable[11]->operand=1;
	validsource(11,0,0,0,0);
	validdestination(11,0,1,1,1);
	operationtable[12]->name="prn";
	operationtable[12]->binariid=1100;
	operationtable[12]->operand=1;
	validsource(12,0,0,0,0);
	validdestination(12,1,1,1,1);
	operationtable[13]->name="jsr";
	operationtable[13]->binariid=1101;
	operationtable[13]->operand=1;
	validsource(13,0,0,0,0);
	validdestination(13,0,1,1,1);
	operationtable[14]->name="rts";
	operationtable[14]->binariid=1110;
	operationtable[14]->operand=0;
	validsource(14,0,0,0,0);
	validdestination(14,0,0,0,0);
	operationtable[15]->name="hlt";
	operationtable[15]->binariid=1111;
	operationtable[15]->operand=0;
	validsource(15,0,0,0,0);
	validdestination(15,0,0,0,0);
}
void validsource(int i,int a,int b,int c,int d)/*loud the valid addressing method of the source operand*/
{
	operationtable[i]->isvalidsource[0]=a;
	operationtable[i]->isvalidsource[1]=b;
	operationtable[i]->isvalidsource[2]=c;
	operationtable[i]->isvalidsource[3]=d;
}
void validdestination(int i,int a,int b,int c,int d)/*loud the valid addressing method of the destination operand*/
{
	operationtable[i]->isvaliddestination[0]=a;
	operationtable[i]->isvaliddestination[1]=b;
	operationtable[i]->isvaliddestination[2]=c;
	operationtable[i]->isvaliddestination[3]=d;
}
opr findoperation(char *op,int line)/*gets operators name and returns its structure*/
{
	int flag=1;
	int j,x;
	for(j=0;j<OPERATIONAMOUNT;j++)
	{
		flag=1;
		for(x=0;x<OPERATIONLENGTH;x++)
		{
			if(operationtable[j]->name[x]!=op[x])
				flag=0;
		}
		if(flag)
			return operationtable[j];
	}
	printf("\nerror in line: %d. the operation %c%c%c is not exist\n",line,*op,op[1],op[2]);
	return NULL;
}
int findL(int numoperands,...)/*gets the number of the operands and their addressing method and returns the number of the mashine code's lines*/
{
	int L=1;
	int i,isreg=0;
	va_list p;
	va_start(p,numoperands);
	for(i=0;i<numoperands;i++)
		switch(va_arg(p,int)){
		case 0: L+=NUM_WORDS_0;break;
		case 1: L+=NUM_WORDS_1;break;
		case 2: L+=NUM_WORDS_2;break;
		case 3: L+=NUM_WORDS_3;isreg++;}
	if(isreg==2)
		L--;
	return L;
}
int decoding(char * operand1,int line)/*gets  operand and checks his addressing mathods*/
{
	int method1;
	char * operand;
	if((*operand1)=='#')
		method1=0;
	else
		if((*operand1)=='r'&&(atoi(operand1+1)==0||atoi(operand1+1)==1||atoi(operand1+1)==2||atoi(operand1+1)==3||atoi(operand1+1)==4||atoi(operand1+1)==5||atoi(operand1+1)==6||atoi(operand1+1)==7))/*is register*/
				method1=3;
		else if (islabelincode(operand1))
			method1=1;
			else 
			{
				operand=operand1;
				while ((*operand1)!='.'&&(*operand1)!='\0')
					operand1++;
				*operand1='\0';
				if(islabelincode(operand)&&((atoi(operand1+1)==1)||(atoi(operand1+1)==2)))
					method1=2;
				else
				{
					printf("\nerror in line %d: invalid operand.\n",line);
					return -1;
				}
				*operand1='.';
			}
	return method1;
}
void codefirst(int L,opr operator,...)/*gets operator and addressing methods and build the first word of the mashine-code*/
{
	int method;
	int IC=getIC();
	va_list p;
	va_start(p,operator);
	/*the operator code*/
	binarycode[IC][0]=operator->binariid/1000;
	binarycode[IC][1]=operator->binariid%1000/100;
	binarycode[IC][2]=operator->binariid%100/10;
	binarycode[IC][3]=operator->binariid%10;
	
	/*the addressing method code*/
	if(operator->operand==0)
	{
		binarycode[IC][4]=0;
		binarycode[IC][5]=0;
		binarycode[IC][6]=0;
		binarycode[IC][7]=0;
	}
	if(operator->operand==1)
	{
		binarycode[IC][4]=0;
		binarycode[IC][5]=0;
		method=converttobinary(va_arg(p,int),2);
		binarycode[IC][6]=(method)/10;
		binarycode[IC][7]=(method)%10;
	}
	if(operator->operand==2)
	{
		method=converttobinary(va_arg(p,int),2);
		binarycode[IC][4]=(method)/10;
		binarycode[IC][5]=(method)%10;	
		method=converttobinary(va_arg(p,int),2);
		binarycode[IC][6]=(method)/10;
		binarycode[IC][7]=(method)%10;
	}

	/*the A-R-E*/
	binarycode[IC][8]=0;
	binarycode[IC][9]=0;
	binarycode[IC][10]=L;
	updateIC(L);
}
int codesecond(wrd words,FILE * fdex,int line)
{
	char * operand=NULL;
	char * operand1=NULL;
	char * operand2=NULL;
	int j,freg=0,x=1,ok=0;
	int IC=getIC()-START_ADDRESS;
	opr oprtr=findoperation(words->string,line);
	int L=binarycode [IC][10];
	if (L>1)
	{
		if (oprtr->operand==1)
			j=6;
		else
			j=4;
		operand=words->string;
		for(;j<=6;j+=2)
		{
			if(words->next)
			{
				words=words->next;
				operand=words->string;
				if (oprtr->operand==1)
					ok=1;
			}
			else
			{
				operand1=operand;
				while(operand1&&(*(operand1))!=',')
					operand1++;
				if(operand1)
					operand=operand1;
			}
			operand1=operand;
			if(*operand==',')
			{
				operand1=operand;				
				operand+=1;
				ok=1;
			}
			while(*operand1!='\0')
			{
				if(*(operand1)==',')
					{
						*operand1='\0';
						operand2=operand1;
						ok=1;
						break;
					}
				operand1++;
			}
			operand1=operand;	
			if(!operand)
			{
				if(words->next)
				{
					words=words->next;
					operand=words->string;
				}
				else
				{
					printf("\nerror in line: %d: indalid syntax.\n",line);
					return 0;
				}	
			}
	/* check the addressing method*/
			if(binarycode[IC][j]==0)
			{	if(binarycode[IC][j+1]==0)/*immediate address case*/
				{
					x=immediateaddress(operand+1,IC,x,line);
					if(!x)
						return 0;
				}
				else/* direct address case*/
				{
					x=directaddress(operand,IC,x,fdex,line);
					if(!x)
						return 0;
				}
			}
			else
			{
				if(binarycode[IC][j+1]==0)/*address of struct*/
				{
					x=structaddress(operand,IC,x,line);
					if(!x)
						return 0;
				}
				else /*register*/
					if(j==4)/*the source operand is register*/
					{
						x=sourceregister(operand,IC,x);
						freg=1;
					}
					else /*the destination operand is register*/
						x=distinationregister(operand,IC,x,freg);
						
			}
			if(ok&&operand2)
				*operand2=',';
		}
		if(!ok)
		{
			printf("\nerror in line: %d: indalid syntax.\n",line);
			return 0;
		}
	}
	updateIC(L);
	return 1;
}
int immediateaddress(char * operand,int IC,int x,int line)/*sub-function of code second*/
{
	int binop;
	if(isinteger(operand,line))
	{
		binop=converttobinary(atoi(operand),8);
		binarycode[IC+x][8]=0;
		binarycode[IC+x][9]=0;
		x=adddatacode(binop,x,IC);
		return x;
	}
	return 0;
}
int directaddress(char * operand,int IC,int x, FILE * fdex,int line)/*sub-function of code second*/
{
	int binop,address=getaddress(operand);
	if(address>=0)
	{
		binop=converttobinary(address,8);
		if(gettype(operand)==ext)
		{
			binarycode[IC+x][8]=0;
			binarycode[IC+x][9]=1;
			writetoex(operand,IC+x+START_ADDRESS,fdex);
		}
		else
		{
			binarycode[IC+x][8]=1;
			binarycode[IC+x][9]=0;
		}
		x=adddatacode(binop,x,IC);
	}
	else
	{
		printf("\nerror in line %d: the label %s is not exist\n",line,operand);
		return 0;
	}
	return x;
}
int structaddress(char * operand,int IC,int x,int line)/*sub-function of code second*/
{
	int binop,address;
	char * operand1=operand;
	while ((*operand1)!='.'&&(*operand1)!='\0')
		operand1++;
	*operand1='\0';
	address=getaddress(operand);
	if(address)
	{/*the first info word*/
		binop=converttobinary(address,8);
		binarycode[IC+x][8]=1;
		binarycode[IC+x][9]=0;
		x=adddatacode(binop,x,IC);
		*operand1='.';
	/*the second info word*/
		binop=converttobinary(atoi(operand1+1),8);
		binarycode[IC+x][8]=0;
		binarycode[IC+x][9]=0;
		x=adddatacode(binop,x,IC);
	}
	else
	{
		printf("error in line: %d the label %s is not exist",line,operand);
		return 0;
	}
	return x;
}
int sourceregister( char * operand, int IC, int x)/*sub-function of code second*/
{
	int binop=converttobinary(atoi(operand+1),8);
	binarycode[IC+x][8]=0;
	binarycode[IC+x][9]=0;
	x=adddatacode(binop*10000,x,IC);/*to get to the lefter bits*/
	return x;
}
int distinationregister(char * operand,int IC,int x,int freg)/*sub-function of code second*/
{
	int y, binop=converttobinary(atoi(operand+1),8);
	if(freg)/*both the two operands are register*/
	{
		x--;
		for(y=7;y>=4;y--)
			if (binop!=0)
			{
				binarycode[IC+x][y]=binop%10;
				binop/=10;
			}
			else
			 	binarycode[IC+x][y]=0;
		x++;
	}
	else
	{
	binarycode[IC+x][8]=0;
	binarycode[IC+x][9]=0;
	x=adddatacode(binop,x,IC);
	}
	return x;
}
int adddatacode(int binop,int x,int IC)/*sub-function of code second*/
{
	int y;
	for(y=7;y>=0;y--)
		if (binop!=0)
		{
			binarycode[IC+x][y]=binop%10;
			binop/=10;
		}
		else 	binarycode[IC+x][y]=0;
	return x+1;
}		
int coding(wrd w,int line)/*analyzing the structure of the operands and caaalling the coding function*/
{
	int L,method1,method2;
	if(w)
	{
		opr op=findoperation(w->string,line);
		if(!op)
			return 0;
		if(op->operand==1)
		{
			w=w->next;
			if(w)
			{
				method1=decoding(w->string,line);
				if(method1==-1)
					return 0;
				if(!isvalidaddressingmethod(op,method1,0, line))
					return 0;
				while(*(w->string)!=','&&(*(w->string)!='\0'))
					(w->string)++;
				if(*(w->string)=='\0')
					w=w->next;
				if(w)
				{
					if(*(w->string)==',')
						(w->string)++;
					if(*(w->string)=='\0')
						w=w->next;
					if(w)
					{					
							printf("\nerror in line %d: there is too many operands.\n",line);
							return 0;
					}
				}
				L=findL(op->operand,method1);
				codefirst(L,op,method1);
				
			}
		}
		if(op->operand==0)
		{
			if(w->next)
			{
				printf("\nerror in line %d: there is too many operands.\n",line);
						return 0;
			}
				L=findL(op->operand);
			codefirst(L,op);
		}
		if(op->operand==2)
		{
			w=w->next;
			if(w)
			{
				method1=decoding(w->string,line);
				if(method1==-1)
					return 0;
				if(!isvalidaddressingmethod(op,method1,1, line))
					return 0;
				while(*(w->string)!=','&&(*(w->string)!='\0'))
					(w->string)++;
				if(*(w->string)=='\0')
					w=w->next;
				if(*(w->string)==',')
					(w->string)++;
				if(*(w->string)=='\0')
					w=w->next;
				if(w)
				{				
					method2=decoding(w->string,line);
					if(method2==-1)
						return 0;
					if(!isvalidaddressingmethod(op,method1,0, line))
						return 0;
					L=findL(op->operand,method1,method2);
					codefirst(L,op,method1,method2);
				}
			}
		}
	}
	return 1;
}
	
	
