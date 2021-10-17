#ifndef TODO_H
#define TODO_H

#include <stddef.h> /* For size_t */

#define SORT_OPTION_AMOUNT 6

extern int sort_options[SORT_OPTION_AMOUNT];
extern int sort_order;

typedef struct todo_t {
	char *name;
	long long timestamp;
	long long deadline;
	unsigned isDone;
	size_t priority;
} todo_t;

todo_t *todo_new(char *name, long long deadline, size_t priority);
void todo_print(todo_t *todo);
int todo_sort_name(const void *a, const void *b);
int todo_sort_timestamp(const void *a, const void *b);
int todo_sort_deadline(const void *a, const void *b);
int todo_sort_priority(const void *a, const void *b);

#endif
