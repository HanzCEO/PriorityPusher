#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "persistence.h"
#include "utils.h"
#include "todo.h"

int main(int argc, char *argv[]) {
	/* Ignore command execution argument */
	argc--;
	argv++;

	/* Pre argument check */
	if (argc == 0) { // Bruh
		printf(	"USAGE:\n"
			"prioritypusher <ACTION>\n\n"
			"Current available actions:\n"
			"new -- Create new todo\n");
		exit(1);
	}

	/* Variables */
	todo_t **todos = NULL;
	size_t todos_length = 0;

	/* Variables init */
	save_detail_t *tmpsdt = read_todos();
	todos = tmpsdt->todos;
	todos_length = tmpsdt->length;
	if (todos == NULL) panic("Error initializing todo array.\n");

	/* Argument parsing */
	/* `new` todo command */
	if (argc == 1 && strcmp(argv[0], "new") == 0) {
		printf("You are about to add new activity\n");
		printf("Deadline format is \"DD/MM/YYYY HH:MM:SS\"\n");

		char *name = input("Name\t\t: ");
		char *deadlineStr = input("Deadline\t: ");
		char *priorityStr = input("Priority\t: ");

		char *trashPtr;
		/*
			Convert priorityStr to long long
			with radix of 10
		*/
		long long priority = strtoll(priorityStr, &trashPtr, 10);

		long long deadline = time_from_readable(deadlineStr);

		/* Finally, make the ToDo thingy */
		todo_t *newTodo = todo_new(name, deadline, priority);
		todo_print(newTodo);

		todos_length++;
		todos = realloc(todos, sizeof(todo_t *) * todos_length);
		if (todos == NULL) panic("Cannot realloc more todos.\n");
		todos[max(todos_length - 1, 0)] = newTodo;

		/* Save all todos */
		save_detail_t savedetail = { todos, todos_length };
		save_todos(savedetail);

		free(deadlineStr);
		free(priorityStr);
	} else if (strcmp(argv[0], "list") == 0) {
		for (size_t i = 0; i < argc; i++) {
			char *arg = argv[i];

			if (strcmp(arg, "-d") == 0 || strcmp(arg, "--desc") == 0) {
				sort_order = 1;
			} else if (strcmp(arg, "-a") == 0 || strcmp(arg, "--asc") == 0) {
				sort_order = 0;
			}
		}

		qsort(todos, todos_length, sizeof(todo_t), todo_sort);

		if (sort_order == 0) {
			for (size_t i = 0; i < todos_length; i++) {
				todo_print(todos[i]);
			}
		} else {
			for (size_t i = todos_length - 1; i != -1; i--) {
				todo_print(todos[i]);
			}
		}
	}

	/* Free todos */
	for (size_t i = 0; i < todos_length; i++) {
		free(todos[i]->name);
		free(todos[i]);
	}

	free(todos);
	free(tmpsdt);

	return 0;
}
