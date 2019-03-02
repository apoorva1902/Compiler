#include "lexer.h"
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
void initialize(table_entry* next)
{
	strcpy(next->key,"-1");
	strcpy(next->value,"-1");
	//next->next=NULL;
}
void add_keyword_table(char key[TOKEN_SIZE],char value[TOKEN_SIZE])
{
	printf("%s\n",key );
	int index=hash(key);
	printf("%d\n",index );
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
	printf("%d\n", index);
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
int main()
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
	for(int i=0;i<100;i++)
	{
		printf("%s\t%d\n",keyword_table[i].key,i);
		//if(keyword_table[i].next!=NULL)
		{
		//	printf("%s\n",keyword_table[i].next->key);
			
		}			
	}
	//add_keyword_table("","");
	//add_keyword_table("","");
	//add_keyword_table("","");
	//add_keyword_table("","");

	printf("%s\n",find_keyword_table("with"));
	printf("%s\n",find_keyword_table("type"));

	return 0;
}