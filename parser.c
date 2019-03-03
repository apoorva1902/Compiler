#include "parser.h"

int main(int argc, char **argv) {
	currPtr=511;
	line_number=1;
	buf=buf2;
	Rule grammar=createGrammarFromFile(argv[1],argv[2]);
	Rule firsts = computeFirsts(grammar);
	Rule follow = newFollow(grammar, firsts);
	Rule ** parsetable = createEmptyParseTable(NUMBEROFNONTERMS, NUMBEROFTERMS);
	parsetable = populateParseTable(grammar, follow, parsetable);
	// printParseTable(parsetable/);
	return 0;
}

void p() {
	printf("\n");
}

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

List deleteNode(List l, List node){
	if (l==NULL){
		return l;
	}else{
		if(l->next==NULL && l->id == node->id){
			return NULL;
		}else{
			List temp=l;
			List curr=NULL;
			if(temp->id==node->id){
				curr=temp;
				l=temp->next;
				free(curr);
			}else{
				while(temp->next!=NULL && temp->next->id !=node->id){
					temp=temp->next;
				}
				curr=temp->next;
				if(curr!=NULL && curr->id==node->id){
					temp->next=curr->next;
					free(curr);
				}else if(curr==NULL){
					return l;
				}
			}
		}
	}
	return l;
}

void printList(List l) {
	List temp = l;
	char s[100];
	for(; temp!=NULL; printf( "%3d [%d] -> ", temp->id, temp->isterminal), temp=temp->next);
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
	for(; temp!=NULL; printf("%3d ===> ", temp->lhs), printList(temp->rhs), printf("\n"), temp=temp->next);
}

void printSingleRule(Rule r) {
	printf("%3d ===> ", r->lhs); 
	printList(r->rhs); 
}

Rule createGrammarFromFile(char *filename, char *mappername) {
	symbols=NULL;
	numSymbols = 0;
	symbols=readFromFile(&numSymbols, mappername);
	FILE *fp = fopen(filename, "r");
	Rule r=NULL;
	char line[500], word[30];
	fscanf(fp, "%[^\n]", line);
	while(!feof(fp)) {
		sscanf(line, "%s", word);
		int lhs = wordToNode(word).id;
		List rhs=NULL;
		int i = strlen(word) + 1, maxlimit=strlen(line);
		while(i < maxlimit) {
			int j;
			for(j=0; line[i]!=' ' && i<strlen(line); i++) {
				word[j++] = line[i];
			}
			word[j] = '\0';
			struct list nodeFromWord = wordToNode(word);
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

char** readFromFile(int *num, char *mappername){
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

struct list wordToNode(char* word){
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

Rule findSpecificRule(Rule r, int id, int toexist) {
	Rule startpointer = findInRule(r, id);
	Rule itr = startpointer;
	while(itr->lhs == startpointer->lhs) {
		if(findInList(itr->rhs, toexist) != NULL)
			return itr;
		itr = itr->next;
	}
	return NULL;
}

Rule computeFirsts(Rule grammar) {
	Rule temp = grammar;
	Rule firsts = NULL;
	while(temp!=NULL) {
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
				if(findInList(aheadList, EPS)) {				// if eps in encountered non terminal
					if(temp->next == NULL) {			// if it was the last non terminal (eps should be added in firsts list)
						l = addNode(l, aheadList);
						break;
					}
					else {						// if not the last, (no need to add eps)
						List newtemp;
						for(newtemp = aheadList; newtemp!=NULL; newtemp = newtemp->next) {
							if(newtemp->id != EPS) {
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

Rule newFollow(Rule grammar, Rule firsts) {
	if(!firsts)
		firsts = computeFirsts(grammar);
	Rule follow = NULL;
	Rule temp = grammar;
	while(temp!=NULL) {
		if(!findInRule(follow, temp->lhs)) {
			Rule callingFunctions = NULL;
			List followList = localFollow(grammar, firsts, follow, callingFunctions, temp);
			Rule toadd = createRule(temp->lhs, followList);
			follow = addRule(follow, toadd);
		}
		temp = temp->next;
	}
	return follow;
}

List localFollow(Rule grammar, Rule firsts, Rule follows, Rule callingFunctions, Rule tocompute) {
	if(findInRule(callingFunctions, tocompute->lhs))
		return NULL;
	callingFunctions = addRule(callingFunctions, createRule(tocompute->lhs, tocompute->rhs));
	Rule existingFollow = findInRule(follows, tocompute->lhs);
	if(existingFollow != NULL)
		return existingFollow->rhs;
	List localfollow = NULL;
	if(tocompute->lhs == STARTSYMBOL)
		localfollow = addNode(localfollow, createNode(DOLLAR, 1));
	Rule occurences = findNextOccurence(grammar, tocompute->lhs);
	while(occurences!=NULL) {
		List pointinlist = findInList(occurences->rhs , tocompute->lhs) -> next;
		List localList = findFirstForList(grammar, pointinlist);
		localfollow = noduplicateadd(localfollow, localList);
		if(pointinlist == NULL || findInList(localList, EPS)) {
			Rule followofleft = findInRule(follows,  occurences->lhs);
			if(followofleft == NULL) {
				List followListofLeft = localFollow(grammar, firsts, follows, callingFunctions, occurences);
				if(followListofLeft != NULL) {
					followofleft = createRule(occurences->lhs, followListofLeft);
					follows = addRule(follows, followofleft);
					localfollow = noduplicateadd(localfollow, followofleft->rhs);
				}
			}
			else
				localfollow = noduplicateadd(localfollow, followofleft->rhs);
		}
		occurences = findNextOccurence(occurences->next, tocompute->lhs);
	}
	return localfollow;
}

List noduplicateadd(List parent, List toadd) {
	List itr = toadd;
	while(itr!=NULL) {
		if(itr->id != EPS && findInList(parent, itr->id)==NULL)
			parent = addNode(parent, createNode(itr->id, itr->isterminal));
		itr = itr->next;
	}
	return parent;
}

Rule findNextOccurence(Rule grammar, int id) {
	Rule temp = grammar;
	while(temp!=NULL) {
		List pointinlist = findInList(temp->rhs, id);
		if(pointinlist != NULL)
			return temp;
		temp = temp->next;
	}
	return NULL;
}

Rule ** populateParseTable(Rule grammar,Rule follows,Rule **ParseTable) {
	Rule R=grammar;
	while(R!=NULL)
	{
		int left=R->lhs;
		List right=R->rhs;
		List firstRight=findFirstForList(grammar,right);
		List rfirst = firstRight;							// new code
		while(rfirst!=NULL) {
			if(rfirst->id == 1) {
				rfirst = rfirst->next;
				continue;
			}
			if(ParseTable[R->lhs - NONTERMLOW][rfirst->id - 2] != NULL) {
				printf("Not first attempt and got [%d] ", R->lhs);
				printSingleRule(ParseTable[R->lhs - NONTERMLOW][rfirst->id - 2]);
				p();
				printf("Not first and want to add ");
				printSingleRule(R);
				p();
			}
			ParseTable[R->lhs - NONTERMLOW][rfirst->id - 2] = R;
			rfirst = rfirst->next;
		}
		if(findInList(firstRight, 1)) {
			Rule followLeft = findInRule(follows, R->lhs);					//found follow
			List followItr = followLeft->rhs;
			while(followItr!=NULL) {
				ParseTable[R->lhs - NONTERMLOW][followItr->id - 2] = R;
				followItr = followItr->next;
			}
		}
		R = R->next;
	}
	return ParseTable;
}
void printParseTable(Rule **ParseTable) {
	for (int i = 0; i < NUMBEROFNONTERMS; ++i) {
		for (int j = 0; j < NUMBEROFTERMS; ++j) {
			if(ParseTable[i][j] != NULL) {
				printf("PT[%2d][%2d]: ", i, j);
				printSingleRule(ParseTable[i][j]);
				printf("\n");
			}
		}
	}
}

Rule ** createEmptyParseTable(int m, int n) {
	Rule ** table = (Rule **) malloc (sizeof(Rule *) * m);
	for(int i=0; i<m;i++) {
		table[i] = (Rule *) malloc (sizeof(Rule)*n);
		for(int j=0;j<n;j++)
			table[i][j] = NULL;
	}
	return table;
}

Leafnode createLeafnode(int id) {
	Leafnode node = (Leafnode) malloc (sizeof(struct leafnode));
	node->id = id;
	return node;
}


Nonleafnode createNonleafnode(int id, Treechildren children) {	
	Nonleafnode node = (Nonleafnode) malloc (sizeof(struct nonleafnode));
	node->id = id;
	node->children = children;
	return node;
}

Treenode insertNode(Treenode parent, Treenode child) {			//does add at begin
	Treechildren tchildren = (Treechildren) malloc (sizeof(struct treechildren));
	tchildren->child = child;
	tchildren->next = parent->nonleaf->children->next;
	parent->nonleaf->children = tchildren;
	return parent;
}

stacknode createStackNode(int id, Treenode node) {
	stacknode newnode;
	newnode.id = id;
	newnode.tnode = node;
	return newnode;
}

Stack push(Stack s, stacknode node) {
	Stack newnode = (Stack) malloc (sizeof(struct stack));
	newnode->node = node;
	if(s!=NULL) {
		newnode->next = s->next;
		s->next = newnode;
	}
	else {
		newnode->next = NULL;
		s = newnode;
	}
	return s;
}

Stack pop(Stack s) {			// free the pointer if you don't get any error
	if(s!=NULL) {
		if(s->next == NULL)
			s=NULL;
		else
			s->next = s->next->next;
	}
	return s;
}

stacknode top(Stack s) {
	if(s!=NULL)
		return s->node;
	stacknode nullnode;
	nullnode.id = -1;
	nullnode.tnode = NULL;
	return nullnode;
}

bool isempty(Stack s) {
	return s==NULL;
}

Treenode parseTreeGenerator(char *filename) {
	FILE *fp = fopen(filename, "r");
	Treenode tnode;
	Treechildren children = NULL;
	tnode->nonleaf = createNonleafnode(STARTSYMBOL, children);
	Stack s;
	s = push(s, createStackNode(DOLLAR, NULL));
	s = push(s, createStackNode(STARTSYMBOL, tnode));
	while(!isempty(s)) {
		stacknode snode = top(s);
		token_info * tok = getNextToken(fp);
		// if(snode.id == wordToNode())
	}
}