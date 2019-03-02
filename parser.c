#include "hardcode.h"

int main() {
	printf("Firsts are:\n");
	Rule firsts = createFirsts();
	printRule(firsts);
	printf("Follow are:\n");
	Rule follow = createFollow();
	printRule(follow);
	return 0;
}
