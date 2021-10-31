#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "persistence.h"
#include "utils.h"
#include "todo.h"

void show_help();

int main(int argc, char *argv[]) {
	/* Ignore command execution argument */
	argc--;
	argv++;

	/* Pre argument parsing check */
	if (argc == 0) {
		show_help();
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
	sort_options = malloc(sizeof(int));
	if (sort_options == NULL) panic("Error initializing sort_options array.\n");

	/* Argument parsing */
	char *action = argv[0];
	/* `new` todo command */
	if (argc == 1 && strcmp(action, "new") == 0) {
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

		/* Cleanup */
		free(deadlineStr);
		free(priorityStr);
	} else if (strcmp(action, "list") == 0 || strcmp(action, "top") == 0) {
		/* Push sorting options */
		for (size_t i = 0; i < argc; i++) {
			char *arg = argv[i];

			/*
				In the previous version, i depend on qsort which turns out
				to be not suitable for the plan. Now, argument positioning
				matters. If you put sorting order flag, the next flags
				until the next sorting order flag will be affected by the
				rule. If you want to get a todo that is important, you
				can put `-pr -dl` to the command, test it out.
			*/

			if (strcmp(arg, "-d") == 0 || strcmp(arg, "--desc") == 0) {
				todo_add_sort_option(SOO_DESC);
			} else if (strcmp(arg, "-a") == 0 || strcmp(arg, "--asc") == 0) {
				todo_add_sort_option(SOO_ASC);


			} else if (strcmp(arg, "-nm") == 0 || strcmp(arg, "--name") == 0) {
				todo_add_sort_option(SO_NAME);
			} else if (strcmp(arg, "-tm") == 0 || strcmp(arg, "--timestamp") == 0) {
				todo_add_sort_option(SO_TIME);
			} else if (strcmp(arg, "-dl") == 0 || strcmp(arg, "--deadline") == 0) {
				todo_add_sort_option(SO_DEAD);
			} else if (strcmp(arg, "-pr") == 0 || strcmp(arg, "--priority") == 0) {
				todo_add_sort_option(SO_PRIORITY);
			}
		}

		/* Start the sorting algorithm */
		todo_start_sort(todos, todos_length);

		/* Print to user */
		if (strcmp(action, "top") == 0) {
			char *trd = time_readable(todos[0]->deadline);
			printf(
				"[%ld] %s - %s",
				todos[0]->priority, todos[0]->name,
				trd
			);
			free(trd);
		} else {
			for (size_t i = 0; i < todos_length; i++) todo_print(todos[i]);
		}
	}

	/* Throw out trashes */
	for (size_t i = 0; i < todos_length; i++) {
		free(todos[i]->name);
		free(todos[i]);
	}

	free(todos);
	free(tmpsdt);
	free(sort_options);

	return 0;
}

void show_help() {
	printf(
		"USAGE:\n"
		"prioritypusher <ACTION>\n\n"
		"Current available actions:\n"
		"new  -- Create new todo\n"
		"list -- Display list of todos\n"
		"top  -- Display the top todo\n"
		"\nToDos Listing Options:\n"
		"-nm --name\tSort by name\n"
		"-tm --timestamp\tSort by todo creation timestamp\n"
		"-dl --deadline\tSort by deadline\n"
		"-pr --priority\tSort by priority\n\n"
		"-d  --descending\tSort the next flags with descending order rule\n"
		"-a  --ascending\tSort the next flags with ascending order rule\n"
		"\nPlease refer to the GitHub repository for more documentation:\n"
		"https://github.com/HanzCEO/PriorityPusher\n"
	);
}
