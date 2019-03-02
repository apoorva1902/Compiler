#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
	Rule grammarRules = createGrammarFromFile(argv[1], argv[2]);
	// printRule(grammarRules);
	//printf("Firsts->\n");
	Rule firsts = computeFirsts(grammarRules);
	//List l  = findFirstForList(grammarRules, grammarRules->rhs);
	//printList(l);
	printf("Firsts:\n");
	printRule(firsts);
	printf("\n");
	Rule followSet=NULL;
	for(int i=NONTERMINALLOW;i<=NONTERMINALHI;i++){
		Rule tempfollowSet=(Rule)malloc(sizeof(struct rule));
		tempfollowSet->lhs=i;
		tempfollowSet->rhs=NULL;
		followSet=addRule(followSet,tempfollowSet);
	}
	// printf("RHS rule: \n");
	// Rule temp =findInRuleRhs(grammar,57);
	// printRule(temp);
	printf("My follow: \n");
	followSet=computeFollow(grammarRules,firsts,followSet);
	printRule(followSet);
	return 0;
}

//62,66,105,106

//Check for follow of 68