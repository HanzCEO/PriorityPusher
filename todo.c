#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "todo.h"

long long time_now() {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return tv.tv_sec;
}

todo_t *todo_new(char *name, long long deadline, size_t priority) {
	todo_t *todo = malloc(sizeof(todo_t));

	todo->name = name;
	todo->timestamp = time_now();
	todo->deadline = deadline;
	todo->isDone = 0;
	todo->priority = priority;

	return todo;
}

void todo_print(todo_t *todo) {
	printf("== TODO =====================\n");
	printf("Name\t\t: %s\n", todo->name);
	printf("Timestamp\t: %lld\n", todo->timestamp);
	printf("Deadline\t: %lld\n", todo->deadline);
	printf("isDone\t\t: %d\n", todo->isDone);
	printf("Priority\t: %ld\n", todo->priority);
}
