#include <stddef.h> /* For size_t */

typedef struct todo_t {
	char *name;
	long long timestamp;
	long long deadline;
	unsigned isDone;
	size_t priority;
} todo_t;

todo_t *todo_new(char *name, long long deadline, size_t priority);
void todo_print(todo_t *todo);
