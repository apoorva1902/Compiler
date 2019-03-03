#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_SIZE 50
#define TOKEN_SIZE 15
#define BUFFER_SIZE 512

typedef struct {
	char lexeme[MAX_SIZE];
	char token[TOKEN_SIZE];
	long line_number;
	char value[MAX_SIZE];
} token_info;

char buf1[BUFFER_SIZE];
char buf2[BUFFER_SIZE];
int currPtr=511;//later put in main shndt be initiazed here
int line_number=1;
char *buf=buf2;
FILE *getStream(FILE *fp);
token_info * getNextToken(FILE *fp);
