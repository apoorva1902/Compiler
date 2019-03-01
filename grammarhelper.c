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
	for(; temp!=NULL; printf("%d [%d] -> ", temp->id, temp->isterminal), temp=temp->next);
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
	FILE *fp = fopen(filename, "r");
	Rule r=NULL;
	char line[500], word[30];
	fscanf(fp, "%[^\n]", line);
	while(!feof(fp)) {
		printf("new while line=%s\n", line);
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

struct list wordToNode(char *word) {
	List l = createNode(1, 1);
	return *l;
}
