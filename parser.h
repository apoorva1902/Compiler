#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int Terms=54;
int nTerms=51;

void createParseTable(Rule grammar,Rule first,Rule follow,Rule Table[nTerms][nTerms] );
void printParseTable(Rule Table[nTerms][nTerms]);
//List findFirstForList(Rule,List);
//List followid(int);

union treenode;
typedef union treenode * Treenode;


struct leafnode {
	int id;
};
typedef struct leafnode * Leafnode;

struct nonleafnode {
	int id;
	Treenode children;
};
typedef struct nonleafnode * Nonleafnode;


union treenode {
	Leafnode leaf;
	Nonleafnode nonleaf;
};

struct stack {
	int id;
	Treenode tnode;
	struct stack * next;
};
typedef struct stack * Stack;

Treenode createLeafnode(int id);
Treenode createNonleafnode(int id, Treenode children);
Treenode insertNode(Treenode parent, Treenode child);
