#include "cat_functions.h"

void number(FILE* file) {
	char str[256];
	int i = 1;
	while((fgets(str, 256, file)) != NULL) {
		printf("%d ", i);
		++i;
		printf("%s", str);
	}
}

void number_nonblank(FILE* file) {
	char str[256];
	int i = 1;
	while((fgets(str, 256, file)) != NULL) {
		if (str[0] == '\n' || str[0] == '\r' || str[0] == '\0') {
			printf("%s", str);
			continue;
		}
		printf("%d ", i);
		++i;
		printf("%s", str);
	}
}

void dollar_sign(FILE* file) {
	char str[256];
	while((fgets(str, 256, file)) != NULL) {
		int len = strlen(str);
		if (str[len - 2] == '\r') {  // for Windows (CR LF)
			str[len - 2] = '$';
			str[len - 1] = '\r';
		}
		else { 
		 	str[len - 1] = '$';
		}
		printf("%s\n", str);
	}
}

void multiple_empty_lines(FILE* file) {
	char str[256];
	bool previous_empty = false;
	while((fgets(str, 256, file)) != NULL) {
		if (str[0] == '\n' || str[0] == '\r' || str[0] == '\0') {
			if (!previous_empty) {
				printf("%s", str);
			}
			previous_empty = true;
			continue;
		}
		printf("%s", str);
		previous_empty = false;
	}
}
