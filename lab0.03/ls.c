#include "functions.h"

int main(int argc, char** argv) {
	switch(argc) {
		case 1: {
			char option = '0';
			printDir(option);
			break;
		}
		case 2: {
			char option;
			while ((option = getopt(argc, argv, "l:a")) != -1) {
				switch(option) {
				case 'l':
					if (strcmp(optarg, "a") == 0) {
						printDirInfo('a');
						break;
					}
					printDirInfo(option);
					break;
				case 'a':
					printDir(option);
					break;
				}
			}
			break;
		}
		case 3: {
			int file;
			for (int i  = 1; i < argc; i++) {
				if (argv[i][0] != '-') {
					file = i;
				}
			}

			char option;
			while ((option = getopt(argc, argv, "l")) != -1) {
				fileInfo(argv[file]);
			}
			break;
		}
		default:
			printf("Incorrect number of arguments.");
			break;
	}
	return 0;
}
