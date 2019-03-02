#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
	char line[100];
	int i=0;
	List lh = createNode(1, 1);
	List lh2 = createNode(2, 1);
	List lh3 = createNode(3, 1);
	List lh4 = createNode(4, 1);
	List lh5 = createNode(5, 1);
	addNode(lh, lh2);
	addNode(lh, lh3);
	addNode(lh, lh4);
	addNode(lh, lh5);
	printList(lh);
	printf("\n");
	Rule grammarRules = createGrammarFromFile("grammar.txt");
	printRule(grammarRules);
	Rule findv = findInRule(grammarRules, 102);
	//rintList(findv->rhs);
	return 0;
}
