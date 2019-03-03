#include <string.h>
#include <stdio.h>
#include <stdlib.h>

union treenode;
typedef union treenode * Treenode;

<<<<<<< HEAD
int Terms=54;
int nTerms=51;

void createParseTable(Rule grammar,Rule first,Rule follow,Rule Table[nTerms][nTerms] );
void printParseTable(Rule Table[nTerms][nTerms]);
//List findFirstForList(Rule,List);
//List followid(int);

union treenode;
typedef union treenode * Treenode;


=======
>>>>>>> 17f77b6ba13e2d338c5c902846b96bbe1b5e9a39
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
<<<<<<< HEAD
Treenode insertNode(Treenode parent, Treenode child);
=======
>>>>>>> 17f77b6ba13e2d338c5c902846b96bbe1b5e9a39
