#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 50
#define TOKEN_SIZE 30
#define BUFFER_SIZE 512
#define END_SRC_CODE '|'
union value
	{
		int vali;
		float valf;
	};
typedef struct {
	char lexeme[MAX_SIZE];
	char token[TOKEN_SIZE];
	long line_number;
	union value val;

	//char value[MAX_SIZE];
} token_info;

char buf1[BUFFER_SIZE];
char buf2[BUFFER_SIZE];
int currPtr;
int line_number;
char *buf;
int flag_backtrack_to_prev_buff;
FILE *getStream(FILE *fp);
token_info * getNextToken(FILE *fp);
void initializekt();
void writeErrorToFile (char * error);
