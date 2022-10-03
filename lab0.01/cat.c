#include "cat_functions.h"
#include "unistd.h"
 
int main(int argc, char** argv) {
	if (argc < 2 || argc > 3 || (argc == 2 && argv[1][0] == '-')) {
		printf("Incorrect input.\nRight usage: ./cat filename\nOR ./cat filename -option\n");
		return 1;
	}

	int file;
	for (int i  = 1; i < argc; i++) {
		if (argv[i][0] != '-') {
			file = i;
		}
	}

	FILE* fp = fopen(argv[file], "r");
	 
	if(fp == NULL) {
		perror("Error occured while opening file");
		return 1;
	}

	if (argc == 2) {
		char str[256];
		while((fgets(str, 256, fp)) != NULL) {
			printf("%s", str);
		}
	}

	char option;
	while ((option = getopt(argc, argv, "nbes")) != -1) {
		switch(option) {
		case 'n':
			fprintf(stdout, "Flag -n: number lines\n\n");
			number(fp);
			break;
		case 'b':
			fprintf(stdout, "Flag -b: number only non-empty lines\n\n");
			number_nonblank(fp);
			break;
		case 'e':
			fprintf(stdout, "Flag -e: display a $ (dollar sign) at the end of each line\n\n");
			dollar_sign(fp);
			break;
		case 's':
			fprintf(stdout, "Flag -s: replace multiple consecutive empty lines with one empty line.\n\n");
			multiple_empty_lines(fp);
			break;
		default:
			fprintf(stderr, "Error. Unknown flag\n");
			break;
		}
	}

	 
	fclose(fp);
	return 0;
}
