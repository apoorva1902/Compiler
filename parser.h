#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define nTerms 51
#define Terms 54
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
Rule ** populateParseTable(Rule grammar,Rule follows,Rule **ParseTable);
void printParseTable(Rule **ParseTable);
Rule **createEmptyParseTable(int m, int n);
