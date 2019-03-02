#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
	Rule grammarRules = createGrammarFromFile(argv[1], argv[2]);
	//printRule(grammarRules);
	//printf("Firsts->\n");
	//Rule firsts = computeFirsts(grammarRules);
	List l  = findFirstForList(grammarRules, grammarRules->rhs);
	printList(l);
	printf("\n");
	return 0;
}
