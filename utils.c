#include <stdlib.h> /* malloc, exit */
#include <stdio.h> /* printf, fgets */
#include <string.h> /* memset, strlen */

#include "utils.h"

char *input(char *display) {
	char *buf = malloc(sizeof(char) * MAX_INPUT);
	if (!buf) {
		printf("Error allocating buffer.\n");
		exit(1);
	}
	memset(buf, 0, MAX_INPUT);

	printf("%s", display);
	fgets(buf, MAX_INPUT, stdin);

	size_t buflen = strlen(buf);
	char last = buf[buflen - 1];
	if (last == '\n') buf[buflen - 1] = 0;

	return buf;
}
