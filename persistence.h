#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "utils.h"
#include "todo.h"

#define MAX_NAME_LENGTH MAX_INPUT
#define SAVE_FILE "todos.dat"

typedef struct save_detail_t {
	todo_t **todos;
	size_t length;
} save_detail_t;

unsigned save_todos(save_detail_t detail);
save_detail_t *read_todos();

#endif
