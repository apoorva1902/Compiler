#include "hardcode.h"
#include "parser.h"

int main() {
	Rule grammar=createGrammarFromFile("backgrammar.txt","backmapper.txt");
	//printRule(grammar);
	Rule firsts = computeFirsts(grammar);
	Rule follow = newFollow(grammar, firsts);
	//printRule(follow);
	Rule ** parsetable = createEmptyParseTable(51, 54);
	parsetable = populateParseTable(grammar, follow, parsetable);
	printParseTable(parsetable);
	return 0;
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
			ParseTable[R->lhs - 56][rfirst->id - 2] = R;				// change 56 hardcoded value
			printf("[%d] ",R->lhs);			
			printSingleRule(R);
			printf("\n");
			rfirst = rfirst->next;
		}
		if(findInList(firstRight, 1)) {
			Rule followLeft = findInRule(follows, R->lhs);
			Rule followItr = followLeft;
			printf("Printing follow set for %d -> ", R->lhs);
			printSingleRule(followLeft);
			printf("\n");
			while(followItr!=NULL) {
				ParseTable[R->lhs - 56][followItr->lhs - 2] = R;			// change 56 hardcoded value
				followItr = followItr->next;
				printf("[%d] ",R->lhs);
				printSingleRule(R);
				printf("\n");

			}
		}
		R = R->next;
	}
	return ParseTable;
}
void printParseTable(Rule **ParseTable) {
	for (int i = 0; i < nTerms; ++i) {
		for (int j = 0; j < Terms; ++j) {
			if(ParseTable[i][j] == NULL) {
				//printf("NULL");
			}
			else {
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

Treenode createLeafnode(int id) {
	Leafnode node = (Leafnode) malloc (sizeof(struct leafnode));
	node->id = id;
	Treenode tnode;
	tnode->leaf = node;
	return tnode;
}


Treenode createNonleafnode(int id, Treenode children) {	
	Nonleafnode node = (Nonleafnode) malloc (sizeof(struct nonleafnode));
	node->id = id;
	node->children = children;
	Treenode tnode;
	tnode->nonleaf = node;
	return tnode;
}
