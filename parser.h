#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int Terms=54;
int nTerms=51;

void createParseTable(Rule grammar,Rule first,Rule follow,Rule Table[nTerms][nTerms] );
void printParseTable(Rule Table[nTerms][nTerms]);
List firstList(List);
List followid(int);

