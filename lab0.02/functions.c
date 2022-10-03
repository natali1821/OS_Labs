#include "functions.h"

int find(const char* str, const char* substr, int pos) {
	int strLen = strlen(str);
	int subLen = strlen(substr);
	if (pos <= strLen) {
		for (int i = pos; i < strLen - subLen + 1; ++i) {
			bool flag = true;
			for (int j = 0; j < subLen; ++j) {
				if (str[j + i] != substr[j]) {
					flag = false;
					break;
				}
			}
			if (flag) {
				return i;
			}
		}
		return -1;
	}
	return -1;
}				
