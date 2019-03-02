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

Rule createGrammarFromFile(char *filename, char *mappername) {
	char** symbols=NULL;
	int num=0;
	symbols=readFromFile(symbols,&num, mappername);
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

char** readFromFile(char** symbols,int *num, char *mappername){
	FILE* fp=fopen(mappername,"r");
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

Rule computeFirsts(Rule grammar) {
	Rule temp = grammar;
	Rule firsts = NULL;
	while(temp!=NULL) {
		//if(temp->lhs == 102)
		//	return firsts;
		Rule inFirsts = findInRule(firsts, temp->lhs);
		if(!inFirsts) {
			List fst = NULL;
			fst = localFirst(grammar, temp, firsts);
			Rule newrule = createRule(temp->lhs, fst);
			firsts = addRule(firsts, newrule);
		}
		temp=temp->next;
	}
	return firsts;
}

List findFirstForList(Rule grammar, List l) {
	Rule rule = createRule(-1, l);
	List newlist = NULL;
	Rule firsts = NULL;
	newlist = localFirst(grammar, rule, firsts);
	return newlist;
}

List localFirst(Rule grammar, Rule parentProduction, Rule firsts) {
	Rule retval = findInRule(firsts, parentProduction->lhs);
	if(retval) {
		return retval->rhs;
	}
	List l = NULL;
	Rule production = parentProduction;
	while(production!=NULL && production->lhs == parentProduction->lhs) {
		List temp = production->rhs;
		while(temp!=NULL) {
			if(temp->isterminal) {
				List node = createNode(temp->id, temp->isterminal);
				l = addNode(l, node);
				break;
			}
			else {								// non terminal encountered
				Rule nonterm = findInRule(grammar, temp->id);
				List aheadList = NULL;
				aheadList = localFirst(grammar, nonterm, firsts);
				if(!findInRule(firsts, nonterm->lhs)) {
					Rule newrule = createRule(nonterm->lhs, aheadList);
					firsts = addRule(firsts, newrule);
				}
				if(findInList(aheadList, 1)) {				// if eps in encountered non terminal
					if(temp->next == NULL) {			// if it was the last non terminal (eps should be added in firsts list)
						l = addNode(l, aheadList);
						break;
					}
					else {						// if not the last, (no need to add eps)
						List newtemp;
						for(newtemp = aheadList; newtemp!=NULL; newtemp = newtemp->next) {
							if(newtemp->id != 1) {
								List newnode = createNode(newtemp->id, newtemp->isterminal);
								l = addNode(l, newnode);
							}
						}
						temp = temp->next;
					}
				}
				else {
					l = addNode(l, aheadList);
					break;
				}
			}
		}
		production = production->next;
	}
	return l;
}
