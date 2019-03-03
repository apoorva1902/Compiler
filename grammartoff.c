#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
	Rule grammarRules = createGrammarFromFile(argv[1], argv[2]);
<<<<<<< HEAD
	//printRule(grammarRules);
	printf("Firsts->\n");
	Rule firsts = computeFirsts(grammarRules);
	printRule(firsts);
	//List l  = findFirstForList(grammarRules, grammarRules->rhs);
	//printList(l);
=======
	// printRule(grammarRules);
	//printf("Firsts->\n");
	Rule firsts = computeFirsts(grammarRules);
	//List l  = findFirstForList(grammarRules, grammarRules->rhs);
	//printList(l);
	printf("Firsts:\n");
	printRule(firsts);
>>>>>>> 17f77b6ba13e2d338c5c902846b96bbe1b5e9a39
	printf("\n");
	// printf("RHS rule: \n");
	// Rule temp =findInRuleRhs(grammar,57);
	// printRule(temp);
	printf("My follow: \n");
	Rule followSet=computeFollow(grammarRules,firsts);
	printRule(followSet);
	return 0;
}

//62,66,105,106

//Check for follow of 68