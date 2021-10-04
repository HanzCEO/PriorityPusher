#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

#include "utils.h"
#include "todo.h"

int sort_options[SORT_OPTION_AMOUNT] = {
	1, // Normal, sort by todo location in save file
	0, // Name
	0, // Timestamp
	0, // Deadline
	0, // Priority

	/* Custom algorithms */
	0  // ALGO: Deadly Prioritized
};
int sort_order = 0; // 0 = ASC; 1 == DESC

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
	char *tmp;
	printf("== TODO =====================\n");
	printf("Name\t\t: %s\n", todo->name);

	tmp = time_readable(todo->timestamp);
	printf("Timestamp\t: %s\n", tmp);
	free(tmp);

	tmp = time_readable(todo->deadline);
	printf("Deadline\t: %s\n", tmp);
	free(tmp);

	printf("isDone\t\t: %d\n", todo->isDone);
	printf("Priority\t: %ld\n", todo->priority);
}

int todo_sort(const void *av, const void *bv) {
	const todo_t *a = (const todo_t*)av;
	const todo_t *b = (const todo_t*)bv;
	int sum = sum_int(sort_options, count(sort_options));

	if (sum == 1 && sort_options[0] == 1) {
		return 0;
	}

	return 0;
}
