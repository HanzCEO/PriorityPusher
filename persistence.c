#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "utils.h"
#include "persistence.h"

unsigned save_todos(save_detail_t detail) {
	todo_t **todos = detail.todos;
	size_t length = detail.length;
	FILE *fp = NULL;
	char *currentPath = getpgdfull();

	strcat(currentPath, SAVE_FILE);
	fp = fopen(currentPath, "w");
	if (fp == NULL) {
		panic("Error saving file.\n");
	}
	free(currentPath);
	fputs("", fp); // Lol

	for (size_t i = 0; i < length; i++) {
		todo_t *todo = todos[i];
		if (todo == NULL) continue;

		fprintf(fp,
				"%s\n%lld-%lld-%u-%lu\n",
				todo->name,
				todo->timestamp,
				todo->deadline,
				todo->isDone,
				todo->priority
			);
	}

	fclose(fp);
	return 0;
}

save_detail_t *read_todos() {
	size_t i = 0;
	int ret = 0;
	save_detail_t *detail = NULL;
	todo_t **todos = NULL;
	FILE *fp = NULL;
	char *currentPath = getpgdfull();

	todos = malloc(sizeof(todo_t *));
	if (todos == NULL) panic("Cannot allocate more space for todos array.\n");

	detail = malloc(sizeof(save_detail_t));
	if (detail == NULL) panic("Cannot allocate save_detail_t\n");

	strcat(currentPath, SAVE_FILE);
	fp = fopen(currentPath, "r");
	if (errno == 2) {
		save_detail_t savedet = { NULL, 0 };
		save_todos(savedet);
		fp = fopen(currentPath, "r"); // Re-open file

		if (fp == NULL) panic("Error reading save file.\n");
	} else if (fp == NULL) {
		panic("Error reading save file.\n");
	}
	free(currentPath);

	while (1) {
		int forceBreak = 0;
		todo_t *todo = malloc(sizeof(todo_t));
		if (todo == NULL) panic("Cannot allocate more todo_t.\n");
		todo->name = NULL;

		if (feof(fp) || fgetc(fp) == -1) {
			free(todo);
			break;
		}
		fseek(fp, -1, SEEK_CUR); /* Redeem last fgetc */

		todos = realloc(todos, sizeof(todo_t *) * (i + 1 + (i == 0)));
		if (todos == NULL) panic("Cannot allocate more space for todos array.\n");

		size_t nameLen = 0;
		size_t nameBufLen = 10;
		todo->name = calloc(10, sizeof(char));
		if (todo->name == NULL) panic("Failed to load a ToDo name from file.\n");

		while (1) {
			char ch = 0;

			if (nameLen + 1 == nameBufLen) { // Time to expand
				nameBufLen *= 2; // Logarithmic expansion
				todo->name = realloc(todo->name, sizeof(char) * nameBufLen);
				if (todo->name == NULL) panic("Cannot allocate more char.\n");
				memset(&(todo->name[nameLen]), 0, nameBufLen - nameLen);
			}

			ch = fgetc(fp);
			if (ch == '\n') break;
			if (ch == EOF) {
				free(todo->name);
				free(todo);
				forceBreak = 1;
				break;
			}

			todo->name[nameLen++] = ch;
		}

		if (forceBreak) break;

		ret = fscanf(fp,
				"%lld-%lld-%u-%lu ",
				&todo->timestamp,
				&todo->deadline,
				&todo->isDone,
				&todo->priority
			);

		if (ret == 0) {
			free(todo);
			break;
		}

		todos[i] = todo;
		i++;
	}

	detail->todos = todos;
	detail->length = i;

	fclose(fp);
	return detail;
}
