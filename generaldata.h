#define MAXLENGTH 80/* the max length for line in the sourse file*/

#define MAXLENGTHLABEL 30
#define START_ADDRESS 100

#define THE_WORD_MACRO 5
#define THE_WORD_END_MACRO 8

typedef struct word * wrd;
typedef struct word {
char * string;
wrd next;
} w1;
wrd head;
typedef enum typelabel {data,code,ext,null} tlb;
typedef struct labeltable * ptr;
typedef struct labeltable {
char * namelabel ;
int address;
tlb type ;
int isentry;
ptr next;
} lt;
typedef struct node * mcr;
typedef struct node {
char data [MAXLENGTH];
mcr next;
} macro;
typedef struct table * tmcr;
typedef struct table {
int nummacro;
char namemacro [MAXLENGTH];
mcr macrocontent;
tmcr next;
} macrotable;
