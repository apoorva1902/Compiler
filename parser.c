#include "hardcode.h"
#include "parser.h"

int main(int argc, char **argv) {
	Rule grammar=createGrammarFromFile(argv[1],argv[2]);
	// printRule(grammar);
	// printList(findFirstForList(grammar, findInRule(grammar, 8)->rhs));
	// p();p();p();
	Rule firsts = computeFirsts(grammar);
	// printRule(firsts);
	// p();p();p();
	Rule follow = newFollow(grammar, firsts);
	// printRule(follow);
	// p();p();p();
	Rule ** parsetable = createEmptyParseTable(NUMBEROFNONTERMS, NUMBEROFTERMS);
	parsetable = populateParseTable(grammar, follow, parsetable);
	// p();p();p();
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
			if(ParseTable[R->lhs - NONTERMLOW][rfirst->id - 2] != NULL) {
				printf("Not first attempt and got [%d] ", R->lhs);
				printSingleRule(ParseTable[R->lhs - NONTERMLOW][rfirst->id - 2]);
				p();
				printf("Not first and want to add ");
				printSingleRule(R);
				p();
			}
			else {
				/*printf("Now adding into the table 1st-1  [%d, %d]: [%d] ", R->lhs - NONTERMLOW, rfirst->id - 2, R->lhs);
				printSingleRule(R);
				p();*/
			}
			ParseTable[R->lhs - NONTERMLOW][rfirst->id - 2] = R;				// change 56 hardcoded value
			rfirst = rfirst->next;
		}
		if(findInList(firstRight, 1)) {
			Rule followLeft = findInRule(follows, R->lhs);					//found follow
			/*printf("Printing follow of left which is %d: ", R->lhs);
			printSingleRule(followLeft);
			p();*/
			List followItr = followLeft->rhs;
			while(followItr!=NULL) {
				/*printf("Now adding into the table 1st-2  [%d, %d]: [%d] ", R->lhs - NONTERMLOW, followItr->id - 2, R->lhs);
				printList(followItr);
				p();*/
				ParseTable[R->lhs - NONTERMLOW][followItr->id - 2] = R;			// change 56 hardcoded value
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
