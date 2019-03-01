#include "grammarhelper.h"

int main(int argc, char **argv) {
	if(argc !=3) {
		printf("Please enter 2 files!\n");
		return 0;
	}
	printf("reached\n");
	FILE *fp = fopen(argv[1], "r");
	char line[100];
	int i=0;
	while(fscanf(fp, " %[^\n]", line), !feof(fp)) {
		for(int j=0;j<100;j++) {
			
		}
		i++;
	}
	return 0;
}
