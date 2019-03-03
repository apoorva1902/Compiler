#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

#define MAX_RULES 100
#define MAXSIZE 30
#define EPS 1
// #define STARTSYMBOL 8	//56
// #define STARTSYMBOL 56
#define STARTSYMBOL 10
// #define DOLLAR 7
// #define DOLLAR 2
#define DOLLAR 9
// #define NUMBEROFNONTERMS 5  //51
// #define NUMBEROFNONTERMS 51
#define NUMBEROFNONTERMS 5
// #define NUMBEROFTERMS 6  //54
// #define NUMBEROFTERMS 54
#define NUMBEROFTERMS 8
// #define NONTERMLOW 8 //56
// #define NONTERMLOW 56
#define NONTERMLOW 10

char **symbols;
int numSymbols;

struct list{
	int id;
	bool isterminal;
	struct list * next;
};

typedef struct list * List;

struct rule {
	int lhs;
	List rhs;
	struct rule * next;
};

typedef struct rule * Rule;

struct rule grammar[MAX_RULES];

void p();
List createNode(int id, bool isterminal);
List addNode(List l, List node);
List deleteNode(List l, List node);
void printList(List l);

Rule createRule(int lhs, List rhs);
Rule addRule(Rule r, Rule rule);
void printRule(Rule r);
void printSingleRule(Rule r);

Rule createGrammarFromFile(char *filename, char *mappername);
struct list wordToNode(char* word);
char** readFromFile(int *num, char *mappername);
List findInList(List l, int id);
Rule findInRule(Rule r, int id);
Rule findInRuleRhs(Rule r, int id);

List findFirstForList(Rule grammar, List l);
Rule computeFirsts(Rule grammar);
List localFirst(Rule grammar, Rule parentProduction, Rule firsts);

Rule computeSingleFollow(Rule grammar,Rule firstSet, Rule followSet, int id);
Rule computeFollow(Rule grammar,Rule firsts);
Rule newFollow(Rule grammar, Rule firsts);
List localFollow(Rule grammar, Rule firsts, Rule follows, Rule callingFunctions, Rule tocompute);
Rule findNextOccurence(Rule grammar, int id);
List noduplicateadd(List parent, List toadd);

union treenode;
struct treechildren;
typedef struct treechildren * Treechildren;
typedef union treenode * Treenode;

struct leafnode {
	int id;
};
typedef struct leafnode * Leafnode;

struct nonleafnode {
	int id;
	Treechildren children;
};
typedef struct nonleafnode * Nonleafnode;


union treenode {
	Leafnode leaf;
	Nonleafnode nonleaf;
};

struct treechildren {
	Treenode child;
	struct treechildren * next;
};
typedef struct treechildren * Treechildren;

struct stacknode_ {
	int id;
	Treenode tnode;
};
typedef struct stacknode_ stacknode;

struct stack {
	stacknode node;
	struct stack * next;
};
typedef struct stack * Stack;


Rule ** populateParseTable(Rule grammar,Rule follows,Rule **ParseTable);
void printParseTable(Rule **ParseTable);
Rule **createEmptyParseTable(int m, int n);

Leafnode createLeafnode(int id);
Nonleafnode createNonleafnode(int id, Treechildren children);
Treenode insertNode(Treenode parent, Treenode child);

stacknode createStackNode(int id, Treenode node);
Stack push(Stack s, stacknode node);
Stack pop(Stack s);
stacknode top(Stack s);
bool isempty(Stack s);

Treenode parseTreeGenerator(char *filename);