#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define MAX_RULES 100
#define MAXSIZE 30

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

List createNode(int id, bool isterminal);
List addNode(List l, List node);
void printList(List l);

Rule createRule(int lhs, List rhs);
Rule addRule(Rule r, Rule rule);
void printRule(Rule r);

Rule createGrammarFromFile(char *filename, char *mappername);
struct list wordToNode(char** symbols,char* word,int numSymbols);
char** readFromFile(char** symbols,int *num, char *mappername);
List findInList(List l, int id);
Rule findInRule(Rule r, int id);

Rule computeFirsts(Rule grammar);
List localFirst(Rule parentProduction, Rule firsts);
