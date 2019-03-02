#include "hardcode.h"
#include "parser.h"

int main() {
	printf("Firsts are:\n");
	Rule first = createFirsts();
	printRule(first);
	printf("Follow are:\n");
	Rule follow = createFollow();

	printRule(follow);
	
	Rule Table[nTerms][Terms];
	Rule *null=NULL;
	memset(Table,NULL,nTerms*Terms*sizeof(Rule));
	Rule grammar=createGrammarFromFile("grammar2.txt","mapper2.txt");
	printf("grammar\n" );
	printRule(grammar);
	
	createParseTable(grammar,first,follow,Table);
	printf("parse Table\n");
	printParseTable(Table);
	return 0;
}
void createParseTable(Rule grammar,Rule first,Rule follow,Rule Table[nTerms][nTerms] )
{		Rule R=grammar;
		while(R!=NULL)
		{
			printf("Inside 1st while\n");
			int left=R->lhs;
			List right=R->rhs;
			List firstRight=findFirstForList(grammar,right);
			printf("firstRight\n");
			printList(firstRight);
			int flageps=0;
			while(firstRight!=NULL)
			{
				int id=firstRight->id;
				if(id!=1)
				{
					Table[left-(Terms+1)][id-1]=R;
					printf("\nTable value\n");
					printList(Table[left-(Terms+1)][id-1]->rhs);
				}
				else
				{
					flageps=1;
				}
				firstRight=firstRight->next;
			}
			if(flageps==1)
			{
				flageps=0;
				List followleft=findInRule(follow,left)->rhs;//followid(left);
				printf("followleft\n");
				printList(followleft);
				while(followleft!=NULL)
				{
					int id=followleft->id;
					if(id!=1)
					{	
						Table[left-(Terms+1)][id-1]=R;
						printf("Table value 2\n");
						printRule(Table[left-(Terms+1)][id-1]);
					}
					else
					{
						flageps=1;
					}
					followleft=followleft->next;
				}
				if(flageps==1)
				{
					Table[left-(Terms+1)][Terms]=R;
				}


			}
			
			R=R->next;
			
		}
		


}
void printParseTable(Rule Table[nTerms][nTerms])
{
	for (int i = 0; i < nTerms; ++i)
	{
		/* code */
		for (int j = 0; j < Terms; ++j)
		{
			/* code */
			printRule(Table[i][j]);
		}
		printf("\n");
	}
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
