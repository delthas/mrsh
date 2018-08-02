#include <assert.h>
#include <mrsh/builtin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"

struct builtin_map {
	const char *name;
	mrsh_builtin_func_t func;
};

static struct builtin_map builtins[] = {
	// Keep alpha sorted
	{ "exit", builtin_exit },
};

static int builtin_compare(const void *_a, const void *_b) {
	const struct builtin_map *a = _a;
	const struct builtin_map *b = _b;
	return strcmp(a->name, b->name);
}

mrsh_builtin_func_t get_builtin(const char *name) {
	struct builtin_map key = { .name = name };
	struct builtin_map *builtin = bsearch(&key, builtins,
			sizeof(builtins) / sizeof(builtins[0]),
			sizeof(builtins[0]), builtin_compare);
	return builtin ? builtin->func : NULL;
}

int mrsh_has_builtin(const char *name) {
	return get_builtin(name) != NULL;
}

int mrsh_run_builtin(struct mrsh_state *state, int argc, char *argv[]) {
	assert(argc > 0);

	const char *name = argv[0];
	mrsh_builtin_func_t builtin = get_builtin(name);
	if (builtin == NULL) {
		return -1;
	}

	return builtin(state, argc, argv);
}