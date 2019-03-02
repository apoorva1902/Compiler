#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
	Rule grammarRules = createGrammarFromFile(argv[1]);
	printRule(grammarRules);
	//Rule findv = findInRule(grammarRules, 102);
	//rintList(findv->rhs);
	return 0;
}
