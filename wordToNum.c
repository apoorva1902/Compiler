#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "grammarhelper.h"

#define MAXSIZE 30

char** readFromFile(char** symbols,int *num){
	FILE* fp=fopen("mapper.txt","r");
	int i=0;
	while(!feof(fp)){
		symbols= (char **)realloc(symbols,sizeof(char*)*(i+1));
		symbols[i]=(char*)malloc(sizeof(char)*MAXSIZE);
		fscanf(fp,"%s\n",symbols[i]);
		i++;
	}
	*num=i;
	fclose(fp);
	return symbols;
}

struct list wordToNode(char** symbols,char* word,int numSymbols){
	struct list numNode;
	int i=0;
	for(i=0;i<numSymbols;i++){
		if (strcmp(word,symbols[i])==0){
			numNode.id=i+1;
			if(word[0] =='<')
				numNode.isterminal=false;
			else
				numNode.isterminal=true;
			numNode.next=NULL;
			return numNode;
		}
	}
	return numNode;
}

int main(){
	char **symbols=NULL;
	int *numSymbols=(int*)malloc(sizeof(int));
	symbols=readFromFile(symbols,numSymbols);
	struct list numNode=wordToNode(symbols,"TK_AND",*numSymbols);
	printf("%s %d %d\n","TK_AND",numNode.id,numNode.isterminal);
	return 0;
}

