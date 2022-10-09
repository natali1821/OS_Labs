#include "functions.h"

void printDir(char option)
{	
	char* dir= ".";
	DIR* dp;
	struct dirent* entry;
	struct stat sb;
 
	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "Can`t open directory %s\n", dir);
		return ;
	}
	
	chdir(dir);
	while (entry = readdir(dp)) {
		stat(entry->d_name, &sb);
		if (option == '0') {
			if (find(entry->d_name, ".", 0) == 0) {
				continue;
			}
		}
		if (S_ISDIR(sb.st_mode)) {
			printf("\033[94m%s\033[0m\n", entry->d_name);
			continue;
		}
		if (S_IXUSR & sb.st_mode) {
			printf("\033[92m%s\033[0m\n", entry->d_name);
			continue;
		}
		printf("%s\n", entry->d_name);
	}
	
	closedir(dp);	
}

void printDirInfo(char option) {
	char* dir = ".";
	DIR* dp;
	struct dirent* entry;

	if ((dp = opendir(dir)) == NULL) {
		fprintf(stderr, "Can`t open directory %s\n", dir);
		return ;
	}

	chdir(dir);
	while (entry = readdir(dp)) {
		if (option == 'l') {
			if (find(entry->d_name, ".", 0) == 0) {
				continue;
			}
		}
		fileInfo(entry->d_name);
	}
}

void fileInfo(const char* filename) {
	struct stat sb;
	struct passwd* pwd;
	struct tm* tm;
	char datestring[256];
	struct group* grp;
	stat(filename, &sb);
	printf("-");
	printf((sb.st_mode & S_IRUSR)? "r":"-");
	printf((sb.st_mode & S_IWUSR)? "w":"-");
	printf((sb.st_mode & S_IXUSR)? "x":"-");
	printf((sb.st_mode & S_IRGRP)? "r":"-");
	printf((sb.st_mode & S_IWGRP)? "w":"-");
	printf((sb.st_mode & S_IXGRP)? "x":"-");
	printf((sb.st_mode & S_IROTH)? "r":"-");
	printf((sb.st_mode & S_IWOTH)? "w":"-");
	printf((sb.st_mode & S_IXOTH)? "x":"-");
	printf(" %ld", sb.st_nlink);

	if ((pwd = getpwuid(sb.st_uid)) != NULL) {
		printf(" %-8.8s", pwd->pw_name);
	}
	else {
		printf(" %-8d", sb.st_uid);
	}

	/* Print out group name if it is found using getgrgid(). */
	if ((grp = getgrgid(sb.st_gid)) != NULL) {
		printf(" %-8.8s", grp->gr_name);
	}
	else {
		printf(" %-8d", sb.st_gid);
	}

	printf(" %ld", sb.st_size);
	printf(" %s", ctime(&sb.st_mtime));

	if (S_ISDIR(sb.st_mode)) {
		printf(" \033[94m%s\033[0m\n", filename);
	}
	else if (S_IXUSR & sb.st_mode) {
		printf(" \033[92m%s\033[0m\n", filename);
	}
	else {
		printf(" %s\n", filename);
	}
}

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