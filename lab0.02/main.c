#include <stdio.h>
#include <string.h>
#include "functions.h"
#include <unistd.h>
#include <malloc.h>


int main(int argc, char** argv) {
	switch(argc) {
	case 3: {
		char substr[50];
		char str[256];

		strncpy(substr, argv[1], 50);

		FILE* file = fopen(argv[2], "r");

		if (file == NULL) {
			perror("Error occured while opening file");
			return 1;
		}

		while (fgets(str, 256, file)) {
			if (!strstr(str, substr)) {
				continue;
			}
			int substrlen = strlen(substr);
			int found = 0;
			for (int i = 0; str[i] != '\0'; ++i) {
				found = find(str, substr, found);
				if (i == found) {
					printf("\033[1;31m%s\033[0m", substr);
					i += substrlen - 1;
					found += substrlen - 1;
					continue;
				}
				putchar(str[i]);
			}
		}
		
		fclose(file);
		break;
	}
	case 4: {
		char option;
		char str[256];
		
		FILE* file = fopen(argv[3], "r");
		FILE* pattern_file = fopen(argv[2], "r");
		
		if (file == NULL || pattern_file == NULL) {
			perror("Error occured while opening file");
			return 1;
		}

		if ((option = getopt(argc, argv, "f")) == -1) {
			printf("Incorrect input.\n Right usage: ./grep -f pattern_file filename");
		return 1;
		}
		
		char* arr[50];
		int count = 0;
		while (fgets(str, 256, pattern_file)) {
			arr[count] = (char*)calloc(256,sizeof(char));
			strncpy(arr[count], str, 256);
			arr[count][strcspn(arr[count], "\r\n")] = 0;
			count++;
		}
		
		while (fgets(str, 256, file)) {
			for(int i = 0; i < count; i++) {
				if (strstr(str, arr[i])) {
					printf("%s", str);
					break;
				}
			
			}
		} 
		
		fclose(file);
		fclose(pattern_file);
		for (int i = 0; i < count; i++) {
			free(arr[i]);
		}
		break;
	}
	default:
		printf("Incorrect input.\n Right usage: ./grep -f pattern_file filename\n OR ./grep 'substr' filename");
		break;
	}
	return 0;
}
