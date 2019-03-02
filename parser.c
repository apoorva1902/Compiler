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
	Rule grammar=createGrammarFromFile("grammar2.txt","mapper2.text");
	printRule(grammar);
	createParseTable(grammar,first,follow,Table);
	printParseTable(Table);
	return 0;
}
void createParseTable(Rule grammar,Rule first,Rule follow,Rule Table[nTerms][nTerms] )
{		
		Rule R=grammar;
		while(R!=NULL)
		{
			int left=R->lhs;
			List right=R->rhs;
			List firstRight=firstList(right);

			int flageps=0;
			while(firstRight!=NULL)
			{
				int id=firstRight->id;
				if(id!=1)
				{
					Table[left-(Terms+1)][id-1]=R;
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
				List followleft=followid(left);
				while(followid!=NULL)
				{
					int id=followleft->id;
					if(id!=1)
					{	
						Table[left-(Terms+1)][id-1]=R;
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
			else
			{
				break;
			}
			R=R->next;
			
		}
		


}
void printParseTable(Rule Table[nTerms][nTerms])
{
	for (int i = 0; i < nTerms; ++i)
	{
		/* code */
		for (int j = 0; j < Terms; ++i)
		{
			/* code */
			printRule(Table[i][j]);
		}
		printf("\n");
	}
}