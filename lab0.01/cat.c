#include "cat_functions.h"
 
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

	for (int i  = 1; i < argc; i++) {
		int option;
		if (strcmp(argv[i], "-n") == 0) {
			option = 1;
		}
		if (strcmp(argv[i], "-b") == 0) {
			option = 2;
		}
		if (strcmp(argv[i], "-e") == 0) {
			option = 3;
		}
		if (strcmp(argv[i], "-s") == 0) {
			option = 4;
		}
		switch (option) {
		case 1:
			number(fp);
			break;
		case 2:
			number_nonblank(fp);
			break;
		case 3:
			dollar_sign(fp);
			break;
		case 4:
			multiple_empty_lines(fp);
			break;
		}
	}
	 
	fclose(fp);
	return 0;
}
