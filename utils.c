#include <stdlib.h> /* malloc, exit */
#include <stdio.h> /* printf, fgets */
#include <string.h> /* memset, strlen */
#include <sys/time.h>
#include <time.h>
#include <locale.h>

#include "utils.h"

char *input(char *display) {
	char *buf = malloc(sizeof(char) * MAX_INPUT);
	if (!buf) panic("Error allocating buffer.\n");
	memset(buf, 0, MAX_INPUT);

	printf("%s", display);
	fgets(buf, MAX_INPUT, stdin);

	size_t buflen = strlen(buf);
	char last = buf[buflen - 1];
	if (last == '\n') buf[buflen - 1] = 0;

	return buf;
}

char *time_readable(time_t time) {
	char *ret = malloc(sizeof(char) * 64);
	if (ret == NULL) panic("Error allocating buffer.\n");
	memset(ret, 0, 64);

	struct tm *nowtm;
	nowtm = localtime(&time);
	strftime(ret, 64, "%d/%m/%Y %H:%M:%S", nowtm);

	return ret;
}

char *getpgdfull() {
	char *currentPath = malloc(sizeof(char) * FILENAME_MAX);
	memset(currentPath, 0, FILENAME_MAX);
	if (currentPath == NULL) panic("Error allocating currentPath variable.\n");

	if (readlink("/proc/self/exe", currentPath, sizeof(char) * FILENAME_MAX) == -1) {
		panic("Error getting current directory.\n");
	}

	size_t last = strlen(currentPath);
	for (size_t i = last; i > 0; i--) {
		if (currentPath[i] != '/') currentPath[i] = 0;
		else break;
	}

	return currentPath;
}

long long time_from_readable(char *readable) {
	int secs, mins, hours, days, months, year;
	sscanf(readable, "%d/%d/%d %d:%d:%d", &days, &months, &year, &hours, &mins, &secs);

	struct tm nowtm = {
		.tm_sec=secs, .tm_min=mins,
		.tm_hour=hours, .tm_mday=days,
		.tm_mon=months-1, .tm_year=year-1900
	};

	return mktime(&nowtm);
}

long long time_now() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec;
}

int sum_int(int array[], size_t length) {
	int sum = 0;
	for (size_t i = 0; i < length; i++) {
		sum += array[i];
	}

	return sum;
}
