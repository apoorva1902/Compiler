#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
<<<<<<< HEAD
	Rule grammarRules = createGrammarFromFile(argv[1]);
	printRule(grammarRules);
	//Rule findv = findInRule(grammarRules, 102);
	//rintList(findv->rhs);
=======
	Rule grammarRules = createGrammarFromFile(argv[1], argv[2]);
	//printRule(grammarRules);
	//printf("Firsts->\n");
	//Rule firsts = computeFirsts(grammarRules);
	List l  = findFirstForList(grammarRules, grammarRules->rhs);
	printList(l);
	printf("\n");
>>>>>>> ae35fb7f026d2e6d5ca55a833e3909a93cbe58db
	return 0;
}
