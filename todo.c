#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "utils.h"
#include "todo.h"

int *sort_options = NULL;
int sort_options_count = 0;

todo_t *todo_new(char *name, long long deadline, size_t priority) {
	todo_t *todo = malloc(sizeof(todo_t));

	todo->name = name;
	todo->timestamp = time_now();
	todo->deadline = deadline;
	todo->isDone = 0;
	todo->priority = priority;

	return todo;
}

void todo_print(todo_t *todo, size_t id) {
	char *tmp;
	printf("== TODO == %ld\n", id + 1);
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

void todo_swap(todo_t *a, todo_t *b) {
	todo_t tmp = *a;
	*a = *b;
	*b = tmp;
}

void todo_add_sort_option(enum sort_option opt) {
	sort_options = realloc(sort_options, sizeof(int) * (++sort_options_count));
	sort_options[sort_options_count - 1] = opt;
}


/*
	I use bubble sort because it is one of the simplest,
	even if it is very slow. Because, i could add custom
	ordering rules when i know how the algorithm works.
*/
void todo_start_sort(todo_t **todos, size_t n) {
	for (size_t i = 0; i < n-1; i++) {
		for (size_t j = 0; j < n-i-1; j++) {
			todo_t *a = todos[j];
			todo_t *b = todos[j+1];

			/*
				Custom ordering rules, made by the user by
				putting some command line flags.
			*/
			int isAscending = 1;

			for (size_t c = 0; c < sort_options_count; c++) {
				enum sort_option opt = sort_options[c];
				switch (opt) {
					case SO_NORMAL:
						// Nothing lol
						break;
					case SO_NAME:
						if (isAscending && strcmp(a->name, b->name) > 0)
							todo_swap(todos[j], todos[j+1]);
						if (!isAscending && strcmp(a->name, b->name) < 0)
							todo_swap(todos[j+1], todos[j]);
						break;
					case SO_TIME:
						if (isAscending && a->timestamp > b->timestamp)
							todo_swap(todos[j], todos[j+1]);
						if (!isAscending && a->timestamp < b->timestamp)
							todo_swap(todos[j+1], todos[j]);
						break;
					case SO_DEAD:
						if (isAscending && a->deadline > b->deadline)
							todo_swap(todos[j], todos[j+1]);
						if (!isAscending && a->deadline < b->deadline)
							todo_swap(todos[j+1], todos[j]);
						break;
					case SO_PRIORITY:
						if (isAscending && a->priority > b->priority)
							todo_swap(todos[j], todos[j+1]);
						if (!isAscending && a->priority < b->priority)
							todo_swap(todos[j+1], todos[j]);
						break;
					case SO_DEADPRIO:
						// Coming soon
						break;
					case SOO_ASC:
						isAscending = 1;
						break;
					case SOO_DESC:
						isAscending = 0;
						break;
				}
			}
		}
	}
}
