#include "lexer.h"

int main() {
	FILE *fp = fopen("code.txt", "r");
	fp = getStream(fp);
	token_info * tok = getNextToken(fp);
	printf("First token is %s\n", tok->token);
	return 0;
}
