#include "lexer.h"

//Key word table hash table implementation adjust this code in lexer.h 
typedef struct 
{
	char key[TOKEN_SIZE];
	char value[TOKEN_SIZE+3];
	//struct table_entry* next;	
}table_entry;
int keyword_table_size=100;
table_entry keyword_table[100];

int hash(char str[TOKEN_SIZE])//,int keyword_table_size)
{
	int i=0,sum=0;
	while(str[i]!='\0')
	{
		sum+=str[i];
		i++;
	}
	return sum%keyword_table_size;
} 


void add_keyword_table(char key[TOKEN_SIZE],char value[TOKEN_SIZE])
{
	//printf("%s\n",key );
	int index=hash(key);
	//printf("%d\n",index );
	if(strcmp(keyword_table[index].key,"-1")!=0)
	{
		int j=index+1;
		for(;j!=index;)
		{
			if(strcmp(keyword_table[j].key,"-1")==0)
			{	
				index=j;
				break;
			}
			j=j+1<100?j+1:0;
	
		}
	}	
	table_entry* temp=&keyword_table[index];
	/*while(temp->next!=NULL)
	{
		temp=temp->next;
	}*/

	strcpy(temp->key,key);
	strcpy(temp->value,value);
	//temp->next=(table_entry*)malloc(sizeof(table_entry));
	//initialize(temp->next);//->next=NULL;

}
char* find_keyword_table(char key[TOKEN_SIZE])
{
	int index=hash(key);
	//printf("%d\n", index);
	/*table_entry* temp=&keyword_table[index];
	table_entry* prev=NULL;//keyword_table[index];
	
	while(temp->next!=NULL)
	{
		prev=temp;
		temp=temp->next;
	}
	if(prev!=NULL)
		return prev->value;
	else
		return "-1";*/
	int j=index,flag=0,i=0;
	
		for(i=0;i<100;i++)
		{
			if(strcmp(keyword_table[j].key,key)==0)
			{	
				index=j;
				flag=1;
				break;
			}
			j=j+1<100?j+1:0;
	
		}
		if(flag==1)
			return keyword_table[index].value;
		else
			return "-1";

}
void initializekt()
{
	for(int i=0;i<100;i++)
	{
		strcpy(keyword_table[i].key,"-1");
		//keyword_table[i].next=NULL;
	}
	add_keyword_table("with","TK_WITH");
	add_keyword_table("parameters","TK_PARAMETERS");
	add_keyword_table("end","TK_END");
	add_keyword_table("while","TK_WHILE");
	add_keyword_table("type","TK_TYPE");
	add_keyword_table("_main","TK_MAIN");
	add_keyword_table("global","TK_GLOBAL");
	add_keyword_table("parameter","TK_PARAMETER");
	add_keyword_table("list","TK_LIST");
	add_keyword_table("input","TK_INPUT");
	add_keyword_table("output","TK_OUTPUT");
	add_keyword_table("int","TK_INT");
	add_keyword_table("real","TK_REAL");
	add_keyword_table("endwhile","TK_ENDWHILE");
	add_keyword_table("if","TK_IF");
	add_keyword_table("then","TK_THEN");
	add_keyword_table("endif","TK_ENDIF");
	add_keyword_table("read","TK_READ");
	add_keyword_table("write","TK_WRITE");
	add_keyword_table("return","TK_RETURN");
	add_keyword_table("call","TK_CALL");
	add_keyword_table("record","TK_RECORD");
	add_keyword_table("endrecord","TK_ENDRECORD");
	add_keyword_table("else","TK_ELSE");
}
int isbcd(char x)
{
	if(x=='b'||x=='c'||x=='d')
		return 1;
	return 0;
}
int isLa(char x)
{	
	if(x>='a'&&x<='z')
		return 1;
	return 0;
}
int isLA(char x)
{
	if(x>='A'&& x<='Z')
		return 1;
	return 0;
}
int isD1(char x)
{
	if(x>='0' && x<='9' )
		return 1;
	return 0;
}
int isD2(char x)
{
	if(x>='2' && x<='7')
		return 1;
	return 0;
}

FILE *getStream(FILE *fp) {
	//printf("%u %u %u\n", buf, buf1,buf2);
	
	if(buf == buf1)
	{
		if(flag_backtrack_to_prev_buff==0)
		{
			memset(buf2,'\0',sizeof(buf2)*sizeof(char));
			int char_read = fread(buf2, sizeof(char), sizeof(buf2)-1, fp);
			if(feof(fp))
	    	{
				buf2[char_read] = '$';
			}
			printf("Buffer 2:\n%s\n",buf2);
		}
		else
		{
			flag_backtrack_to_prev_buff=0;
		}	
		buf = buf2;
	}
	else 
	{
		memset(buf1,'\0',sizeof(buf1)*sizeof(char));
		int char_read = fread(buf1, sizeof(char), sizeof(buf1)-1, fp);
		if(feof(fp))
	    {
		 	buf1[char_read] = '$';
		}
		printf("Buffer 1:\n%s\n",buf1);
		
		buf = buf1;
	}
	//printf("%u %u %u\n", buf, buf1,buf2);
	
	
	return fp;
}

token_info * getNextToken(FILE *fp) {
	token_info * tok = (token_info *) malloc (sizeof(token_info));
	memset(tok->lexeme, '\0', sizeof(tok->lexeme));
	int state=1, lexPtr=0;
	char currChar;
	
	//printf("%u %u %u\n", buf, buf1,buf2);
	
	for(int i=0;i<600;i++) {
		

		if(currPtr<0)
		{
			flag_backtrack_to_prev_buff=1;
			currPtr=BUFFER_SIZE-1+currPtr;
		}
		if(currPtr==BUFFER_SIZE-1)//511=BufferSize-1
		{	
			//printf("Inside currPtr=511 \n");
			fp=getStream(fp);
			currPtr=0;
		}
		//printf("%d %c|\n",currPtr,buf[currPtr] );
		currChar = buf[currPtr++];
		/*if(currChar=='$')
		{	
		}*/
		//printf("%u %u %u %i %c\n", buf, buf1,buf2,i,currChar);
		


		/*vip In each iteration(in each separate case statement) either do 
		* currPtr--(backtracking this character(not using))
		* or
		* tok->lexeme[lexPtr++]=currChar;//putting this char in lexeme
		*/
		switch(state) {
			case 1:
				switch(currChar) {//state =3 incorporated int the same switch later shd be differented  in a different switch
					case '+':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_PLUS");
						state=3;
						return tok;
					case '-':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_MINUS");
						state=3;
						return tok;
					case '*':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_MUL");
						state=3;
						return tok;
					case '/':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_DIV");
						state=3;
						return tok;
					case '[':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_SQL");
						state=3;
						return tok;
					case ']':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_SQR");
						state=3;
						return tok;
					case '.':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_DOT");
						state=3;
						return tok;
					case ',':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_COMMA");
						state=3;
						return tok;
					case ';':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_SEM");
						state=3;
						return tok;
					case ':':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_COLON");
						state=3;
						return tok;
					case '(':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_OP");
						state=3;
						return tok;
					case ')':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_CL");
						state=3;
						return tok;
					case '~':
						tok->lexeme[lexPtr++] = currChar;
						state=2;
						tok->line_number=line_number;
						strcpy(tok->token, "TK_NOT");
						state=3;
						return tok;
					case ' ':case '\t':
						state=1;
						break;
					case '\n':
						state=1;
						line_number++;
						break;
					case '%':
						state=42;
						break;
					case '<':
						tok->lexeme[lexPtr++]=currChar;
						state=36;
						break;
					case '>':
						tok->lexeme[lexPtr++]=currChar;
						state=33;
						break;

					case '!':
						tok->lexeme[lexPtr++]=currChar;
						state=31;
						break;
					case '=':
						tok->lexeme[lexPtr++]=currChar;
						state=29;
						break;
					case '&':
						tok->lexeme[lexPtr++]=currChar;
						state=26;
						break;
					case '@':
						tok->lexeme[lexPtr++]=currChar;
						state=23;
						break;
					case '#':
						tok->lexeme[lexPtr++]=currChar;
						state=20;
						break;
					case '_':
						tok->lexeme[lexPtr++]=currChar;
						state=15;
						break;
					case 'b':case 'c':case 'd':
						tok->lexeme[lexPtr++]=currChar;
						state=11;
						
						break;
					case 'a':case 'e' ... 'z':
						tok->lexeme[lexPtr++]=currChar;
						state=9;
						
						break;
					case '0'... '9':
						tok->lexeme[lexPtr++]=currChar;
						state=4;
						
						break;	














					//add all other cases above

					case '$':
						tok->lexeme[lexPtr++] = currChar;
						tok->line_number=line_number;
						strcpy(tok->token,"Dollar");
						state=100;//source code finish state
						return tok;
						break;	

					default:
						state=112;
						tok->lexeme[lexPtr++] = currChar;
						break;

					
				}
				break;
			case 42:
				switch(currChar)
				{
					case '$':
						currPtr--;//so that in next iteration it goes to state 1 and case '$'
						//fall through
					case '\n':
						tok->lexeme[lexPtr++]='%';							
						tok->line_number=line_number;
						strcpy(tok->token,"TK_COMMENT");
						if(currChar=='\n')
							line_number++;
						state=43;
						
						break;

					default:
						state=42;
						//tok->lexeme[lexPtr++]=currChar;
						//dont return comment just %
						break;
				}
				break;
			case 43:
				switch(currChar)
				{
					default:
						currPtr--;//retract '$'
						//dont write state=1; here and similarly everywhere
						return tok;
						break;
				}
				break;
			case 36:
				switch(currChar)
				{
					case '-':
						tok->lexeme[lexPtr++]=currChar;
						state=38;
						break;
					case '=':
						tok->lexeme[lexPtr++]=currChar;
						state=37;
						break;
					default:
						currPtr--;//retract this character
						state=41;
						break;

				}
				break;
			case 37:
				switch(currChar)
				{
					default:
						tok->line_number=line_number;
						strcpy(tok->token,"TK_LE");
						currPtr--;//backtrack this character
						
						return tok;
						break;
				}
				break;
			case 38:
				switch(currChar)
				{
					case '-':
						tok->lexeme[lexPtr++]=currChar;
						state=39;
						break;
					default:
						currPtr--;//backtrack this character
						state=101;//error state 
						break;


				}
				break;
			case 39:
				switch(currChar)
				{
					case '-':
						tok->lexeme[lexPtr++]=currChar;
						state=40;
						break;
					default:
						currPtr--;//backtrack this character
						state=102;//error state
						break;
				}
				break;
			case 40:
				switch(currChar)
				{
					default:
						tok->line_number=line_number;
						strcpy(tok->token,"TK_ASSIGNOP");
						currPtr--;//backtrack this character
						
						return tok;

						break;
						
				}
				break;
			case 41:
				switch(currChar)
				{
					default:
						tok->line_number=line_number;
						strcpy(tok->token,"TK_LT");
						currPtr--;//bactract this character
						
						return tok;
				}
				break;
			case 33:
				switch(currChar)
				{
					case '=':
						tok->lexeme[lexPtr++]=currChar;
						state=34;
						break;
					default:
						currPtr--;
						state=35;
						break;
				}
				break;
			case 34:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_GE");
						
						return tok;
						break; 
				}
				break;
			case 35:
				switch(currChar)
				{
						default:
							currPtr--;
							tok->line_number=line_number;
							strcpy(tok->token,"TK_GT");
							
							return tok;
							break;

				}
				break;

			case 31:
				switch(currChar)
				{
					case '=':
						tok->lexeme[lexPtr++]=currChar;
						state=32;
						break;
					default:
						currPtr--;
						state=103;//error state
						break;	
				}
				break;
			case 32:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_NE");
						
						return tok;

						break;
				}
				break;
			case 29:
				switch(currChar)
				{
					case '=':
						tok->lexeme[lexPtr++]=currChar;
						state=30;
						break;
					default:
						currPtr--;
						state=104;//error state
						break;
				}
				break;
			case 30:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_EQ");
						return tok;
						break;
				}
				break;
			case 26:
				switch(currChar)
				{
					case '&':
						tok->lexeme[lexPtr++]=currChar;
						state=27;
						break;
					default:
						currPtr--;
						state=105;//error state
						break;
				}
				break;
			case 27:
				switch(currChar)
				{
					case '&':
						tok->lexeme[lexPtr++]=currChar;
						state=28;
						break;
					
					default:
						currPtr--;
						state=106;//error state
						break;

				}
				break;
			case 28:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_AND");
							
						return tok;
						break;

				}
				break;
			case 23:
				switch(currChar)
				{
					case '@':
						tok->lexeme[lexPtr++]=currChar;
						state=24;
						break;
					default:
						currPtr--;
						state=106;//error state
						break;
				}
				break;
			case 24:
				switch(currChar)
				{
					case '@':
						tok->lexeme[lexPtr++]=currChar;
						state=25;
						break;
					
					default:
						currPtr--;
						state=107;//error state
						break;

				}
				break;
			case 25:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_OR");
							
						return tok;
						break;

				}
				break;

			case 20:
				if(isLa(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=21;
				}
				else
				{
					currPtr--;
					state=108;//error state
				}
				break;
			case 21:
				if(isLa(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=21;
				}
				else
				{
					currPtr--;
					state=22;
					
				}
				break;
			case 22:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_RECORDID");
						return tok;
						break;	

				}
				break;
			case 15:
				if(isLa(currChar)|| isLA(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=16;
				}
				else
				{
					currPtr--;
					state=109;//error state
				}
				break;
			case 16:
				if(isLa(currChar)|| isLA(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=16;
				}
				else if(isD1(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=18;
				}
				else 
				{
					currPtr--;
					state=17;
				}	
				break;
			case 18:
				if(isD1(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=18;
				}
				else
				{
					currPtr--;
					state=19;
				}
				break;
			case 19:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_FUNID");
						return tok;
						break;
				}
				break;
			case 17:
				if(strcmp(tok->lexeme,"_main")==0)
				{
					currPtr--;
					tok->line_number=line_number;
					strcpy(tok->token,"TK_MAIN");
					return tok;
				}
				else
				{
					currPtr--;
					tok->line_number=line_number;
					strcpy(tok->token,"TK_FUNID");
					return tok;
							
					
				}
			case 11:
				if(isLa(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=9;
						
				}
				else if(isD2(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=12;
						
				}
				else
				{
					currPtr--;
					state=10;
				}
				break;
			case 12:
				if(isbcd(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=12;
				}
				else if(isD2(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=13;
				}
				else
				{
					currPtr--;
					state=14;
				}
				break;
			case 13:
				if(isD2(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=13;
				}
				else
				{
					currPtr--;
					state=14;
				}
				break;
			case 14:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_ID");
						return tok;
						break;
				}
				break;
			case 9:
				if(isLa(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=9;
				}
				else
				{
					currPtr--;
					state=10;
				}
				break;
			case 10:
				currPtr--;
				
				//do keyword table implementsiom


				char* keyword_token=find_keyword_table(tok->lexeme);
				if(strcmp(keyword_token,"-1")!=0)
				{
					tok->line_number=line_number;
					strcpy(tok->token,keyword_token);
					return tok;
				}	
				else
				{
					tok->line_number=line_number;
					strcpy(tok->token,"TK_FIELDID");
					return tok;

				}
				break;
			case 4:
				if(isD1(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=4;	
				}
				else if (currChar=='.')
				{
					tok->lexeme[lexPtr++]=currChar;
					state=5;
				}
				else
				{
					currPtr--;
					state=8;
				}
				break;
			case 8:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_NUM");
						return tok;
						break;
				}
				break;
			case 5:
				if(isD1(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=6;
					
				}
				else
				{
					currPtr--;
					tok->lexeme[lexPtr-1]='\0';//remove . from lexeme
					lexPtr--; //next position to be filled in lexeme
					currPtr--;
					state=8;
					//shdnt be error like 25.> is no lexical error 
					//25 is TK_NUM . is TK_DOT > is TK_GT
					//shd just retract to return 25
					//i.e. same behavior as from state 4 when encountering other
					//previously we were sending this as error state
					//state=110;//error state
				}
				break;
			case 6:
				if(isD1(currChar))
				{
					tok->lexeme[lexPtr++]=currChar;
					state=7;
					
				}
				else
				{
					currPtr--;
					tok->lexeme[lexPtr-1]='\0';//remove D1 from lexeme
					lexPtr--; //next position to be filled in lexeme
					currPtr--;
					tok->lexeme[lexPtr-1]='\0';//remove . from lexeme
					lexPtr--; //next position to be filled in lexeme
					currPtr--;
					state=8;
					//state=111;//error state
				}
				break;
			case 7:
				switch(currChar)
				{
					default:
						currPtr--;
						tok->line_number=line_number;
						strcpy(tok->token,"TK_RNUM");
						return tok;
						break;
				}






			//add other cases above	
			case 100:
				//source code finish state
				//is never executed
				break;


			/*error states from 101
			 *for now simply return the lexeme with TK_ERROR
			 *later can be modifed case wise	
			*/
			case 101:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						//dont write state=1; here
						return tok;
						break;
				}
				break;
			case 102:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 103:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 104:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 105:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;		
			case 106:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 107:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 108:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 109:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 110:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 111:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
			case 112:
				switch(currChar)
				{
					default:
						currPtr--;//backtract this character
						strcpy(tok->token,"TK_ERROR");//have to print Unknown symbol from state 1 
						tok->line_number=line_number;
						
						return tok;
						break;
				}
				
				break;
		}		
	}
}

int main() {
	//buf = buf1;
	//printf("%u %u %u\n", buf, buf1,buf2);
	initializekt();
	currPtr=511;//Buffersize-1
	line_number=1;
	buf=buf2;
	flag_backtrack_to_prev_buff=0;
	FILE *fp = fopen("testcases/testcase4.txt", "r");
	//fp = getStream(fp);
	//fflush(stdout);
	//currPtr=511;
	token_info * tok ;	
	while(strcmp(tok->token,"Dollar")!=0)
	{
		tok= getNextToken(fp);
		printf("Next token is %s | line_number=%ld | lexeme=%s\n", tok->token,tok->line_number,tok->lexeme);
	}
	//tok = getNextToken(fp);
	//printf("First token is %s\n", tok->token);
	
	return 0;

}
