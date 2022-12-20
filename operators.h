#define OPERATIONLENGTH 3
#define OPERATIONAMOUNT 16
#define NUM_ADDRESSING_METHODS 4
#define NUM_WORDS_0 1
#define NUM_WORDS_1 1
#define NUM_WORDS_2 2
#define NUM_WORDS_3 1
typedef struct operation * opr;
typedef struct operation {
char  *name ;
int binariid;
int operand;
int isvalidsource[NUM_ADDRESSING_METHODS];
int isvaliddestination[NUM_ADDRESSING_METHODS];
} item;
opr operationtable[OPERATIONAMOUNT];

	
	
