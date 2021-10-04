#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdlib.h>

#define MAX_INPUT 1024

#define count(a) (sizeof(a)/sizeof(*a))
#define max(a, b) ((a<b)?b:a)
#define panic(msg) do {						\
	if (DEBUG) printf("[" __FILE__ ": !]: %s", msg);	\
	else printf("[!] %s", msg);				\
	exit(1);						\
} while (0)

char *input(char *display);
char *time_readable(time_t time);
long long time_from_readable(char *readable);
long long time_now();
int sum_int(int array[], size_t length);

#endif
