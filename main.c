#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "utils.h"
#include "todo.h"

int main(int argc, char *argv[]) {
	/* Ignore command execution argument */
	argc--;
	argv++;

	/* Argument parsing */
	/* `new` todo command */
	if (argc == 1 && strcmp(argv[0], "new") == 0) {
		printf("You are about to add new activity\n");
		char *name = input("Name\t\t: ");
		char *deadlineStr = input("Deadline\t: ");
		char *priorityStr = input("Priority\t: ");

		char *trashPtr;
		/*
			Convert deadlineStr and priorityStr to long long
			with radix of 10
		*/
		long long deadline = strtoll(deadlineStr, &trashPtr, 10);
		long long priority = strtoll(priorityStr, &trashPtr, 10);

		todo_t *newTodo = todo_new(name, deadline, priority);
		todo_print(newTodo);

		free(newTodo);
		free(name);
		free(deadlineStr);
		free(priorityStr);
	}

	return 0;
}
