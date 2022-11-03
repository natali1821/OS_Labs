#include "functions.h"

int main(int argc, char** argv) {
	switch(argc) {
		case 1: {
			char option = '0';
			printDir(option, "");
			break;
		}
		case 2: {
			char option;
			while ((option = getopt(argc, argv, "l::a")) != -1) {
				switch(option) {
				case 'l':
					if (optarg != NULL) {
						printDirInfo('a', "");
						break;
					}
					printDirInfo(option, "");
					break;
				case 'a':
					printDir(option, "");
					break;
				default:
						printf("Error. Unknown flag\n");
					break;
				}
			}
			
			if (argv[1][0] != '-') {
				printDir('0', argv[1]);
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
			while ((option = getopt(argc, argv, "l::a")) != -1) {
				switch(option) {
				case 'l':
				{
					if (optarg != NULL) {
						printDirInfo('a', argv[file]);
						break;
					}
					
					struct stat sb;
					stat(argv[file], &sb);
					if (S_ISDIR(sb.st_mode)) {
						printDirInfo(option, argv[file]);
					}
					else {
						fileInfo(argv[file]);
					}
					break;
				}
				case 'a':
					printDir(option, argv[file]);
					break;
				default:
					printf("Error. Unknown flag\n");
					break;
				}
			}
			break;
		}
		default:
			printf("Incorrect number of arguments.");
			break;
	}
	return 0;
}
