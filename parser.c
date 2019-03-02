#include "hardcode.h"
#include "parser.h"

int main() {
	//printf("Firsts are:\n");
	//Rule firsts = createFirsts();
	//printRule(firsts);
	//printf("Follow are:\n");
	//Rule follow = createFollow();
	//printRule(follow);
	return 0;
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
