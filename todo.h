#ifndef TODO_H
#define TODO_H

#include <stddef.h> /* For size_t */

extern int *sort_options;
extern int sort_options_count;

enum sort_option {
	SO_NORMAL,
	SO_NAME,
	SO_TIME,
	SO_DEAD,
	SO_PRIORITY,
	SO_DEADPRIO,
	SOO_ASC,
	SOO_DESC
};

typedef struct todo_t {
	char *name;
	long long timestamp;
	long long deadline;
	unsigned isDone;
	size_t priority;
} todo_t;

todo_t *todo_new(char *name, long long deadline, size_t priority);
void todo_print(todo_t *todo, size_t id);
void todo_swap(todo_t *a, todo_t *b);
void todo_add_sort_option(enum sort_option opt);
void todo_start_sort(todo_t **todos, size_t n);

#endif
