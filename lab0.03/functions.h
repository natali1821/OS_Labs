#pragma once
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <dirent.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

int find(const char* str, const char* substr, int position);
void printDir(char option);
void fileInfo(const char* str);
void printDirInfo(char option);