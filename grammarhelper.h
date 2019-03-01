#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct {
	int id;
	bool isterminal;
	struct list * next;
} list;
typedef struct list * List;

List createNode(int id, bool isterminal);
List addNode(List l, int id, bool isterminal);
List printList(List l);

