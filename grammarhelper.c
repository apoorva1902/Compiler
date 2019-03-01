#include "grammarhelper.h"

List createNode(int id, bool isterminal) {
	List node = (List) malloc (sizeof(struct list));
	node->id = id;
	node->isterminal = isterminal;
	node->next = NULL;
	return node;
}

List addNode(List l, List node) {
	List temp = l;
	if(temp==NULL) {
		l = node;
		return l;
	}
	for(; temp->next!=NULL; temp=temp->next);
	temp->next = node;
	return l;
}

void printList(List l) {
	List temp = l;
	char s[100];
	for(; temp!=NULL; printf( "%d [%d] -> ", temp->id, temp->isterminal), temp=temp->next);
}

Rule createRule(int lhs, List rhs) {
	Rule r = (Rule) malloc (sizeof(struct rule));
	r->lhs = lhs;
	r->rhs = rhs;
	r->next = NULL;
	return r;
}


Rule addRule(Rule r, Rule rule) {
	Rule temp = r;
	if(temp==NULL) {
		r = rule;
		return r;
	}
	for(; temp->next!=NULL; temp=temp->next);
	temp->next = rule;
	return r;
}

void printRule(Rule r) {
	Rule temp = r;
	for(; temp!=NULL; printf("%d ===> ", temp->lhs), printList(temp->rhs), printf("\n"), temp=temp->next);
}

Rule createGrammarFromFile(char *filename) {
	char** symbols=NULL;
	int num=0;
	symbols=readFromFile(symbols,&num);
	FILE *fp = fopen(filename, "r");
	Rule r=NULL;
	char line[500], word[30];
	fscanf(fp, "%[^\n]", line);
	while(!feof(fp)) {
		sscanf(line, "%s", word);
		int lhs = wordToNode(symbols,word,num).id;
		List rhs=NULL;
		int i = strlen(word) + 1, maxlimit=strlen(line);
		while(i < maxlimit) {
			int j;
			for(j=0; line[i]!=' ' && i<strlen(line); i++) {
				word[j++] = line[i];
			}
			word[j] = '\0';
			struct list nodeFromWord = wordToNode(symbols,word,num);
			List node = createNode(nodeFromWord.id, nodeFromWord.isterminal);
			rhs = addNode(rhs, node);
			i++;
		}
		Rule rule = createRule(lhs, rhs);
		r = addRule(r, rule);
		fseek(fp, 1, SEEK_CUR);
		fscanf(fp, "%[^\n]", line);
	}
	return r;
}

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

List findInList(List l, int id) {
	List temp=l,prev=l;
	while(temp!=NULL) {
		if(temp->id == id)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

Rule findInRule(Rule r, int id) { 
	Rule temp=r;
	while(temp!=NULL) {
		if(temp->lhs == id)
			return temp;
		temp=temp->next;
	}
	return NULL;
}

/*Rule computeFirsts(Rule grammar) {
	Rule temp = grammar;
	Rule firsts = NULL;
	while(temp!=NULL) {
		if(findInRule(grammar, temp->lhs)) {
			
		}
	}
}*/

void printGrammarArray(Element** grammar){
	int i=0;
	for(;i<NUMRULESGRAMMAR;i++){
		int j=0;
		for(;grammar[i][j].lastElem==false;j++){
			printf("%d ",grammar[i][j].id);
		}
		printf("%d",grammar[i][j].id);
		printf("\n");
	}
}

Element wordToNodeArray(char** symbols,char* word,int numSymbols){
        Element elem;
        int i=0;
        for(i=0;i<numSymbols;i++){
                if (strcmp(word,symbols[i])==0){
                        elem.id=i+1;
                        if(word[0] =='<')
                                elem.isTerminal=false;
                        else
                                elem.isTerminal=true;
                        elem.lastElem=false;
                        return elem;
                }
        }
        return elem;
}

Element** createGrammarArrayFromFile(Element** grammar,char* filename){
	char** symbols=NULL;
        int num=0;
        symbols=readFromFile(symbols,&num);
        FILE *fp = fopen(filename, "r");
        Rule r=NULL;
        char line[500], word[MAXSIZE];
        fscanf(fp, "%[^\n]", line);
	int k=0;
        while(!feof(fp)) {
                sscanf(line, "%s", word);
		grammar=(Element**)realloc(grammar,sizeof(Element*)*(k+1));
		grammar[k]=(Element*)malloc(sizeof(Element));
		grammar[k][0].id=wordToNodeArray(symbols,word,num).id;
		grammar[k][0].isTerminal=false;
		grammar[k][0].lastElem=false;
		int wordIndex=1;
                int i = strlen(word) + 1, maxlimit=strlen(line);
                while(i < maxlimit) {
                        int j;
                        for(j=0; line[i]!=' ' && i<strlen(line); i++) {
                                word[j++] = line[i];
                        }
                        word[j] = '\0';
			grammar[k]=(Element*)realloc(grammar[k],sizeof(Element)*(wordIndex+1));
                        Element nodeFromWord = wordToNodeArray(symbols,word,num);
			grammar[k][wordIndex].id=nodeFromWord.id;
			grammar[k][wordIndex].isTerminal=nodeFromWord.isTerminal;
			grammar[k][wordIndex].lastElem=false;
			wordIndex++;
                        i++;
                }
		grammar[k][wordIndex-1].lastElem=true;
		k++;
               // Rule rule = createRule(lhs, rhs);
               // r = addRule(r, rule);
                fseek(fp, 1, SEEK_CUR);
                fscanf(fp, "%[^\n]", line);
        }
	return grammar;

}

bool checkElementInList(Element* list, int id){
	int j=1;
	for(;;j++){
		if(list[j].id==id){
			return true;
		}
		if(list[j].lastElem)
			break;
	}
	return false;
}

Element** computeFirsts(Element** grammar){
	int i;
	Element** firstSet=NULL;
	for(i=0;i<NUMRULESGRAMMAR;i++){
		if(grammar[i][1].isTerminal){
			firstSet
		}
	}
}
