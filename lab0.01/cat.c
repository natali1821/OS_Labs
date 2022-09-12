#include "cat_functions.h"
#include "unistd.h"
 
int main(int argc, char** argv) {
	if (argc < 2 || argc > 3 || (argc == 2 && argv[1][0] == '-')) {
		printf("Incorrect input. Right usage: ./cat filename or ./cat filename -option");
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

	int option;
	while ((option = getopt(argc, argv, "nbes")) != -1) {
		switch(option) {
		case 'n':
			number(fp);
			break;
		case 'b':
			number_nonblank(fp);
			break;
		case 'e':
			dollar_sign(fp);
			break;
		case 's':
			multiple_empty_lines(fp);
			break;
		}
	}

	 
	fclose(fp);
	return 0;
}
