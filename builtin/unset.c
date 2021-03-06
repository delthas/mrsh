#define _POSIX_C_SOURCE 200809L
#include <mrsh/builtin.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

static const char unset_usage[] = "unset: unset [-fv] name...\n";

int builtin_unset(struct mrsh_state *state, int argc, char *argv[]) {
	int funcs = 0;

	int opt;
	while ((opt = getopt(argc, argv, "fv")) != -1) {
		switch (opt) {
		case 'f':
			funcs = 1;
			break;
		case 'v':
			funcs = 0;
			break;
		default:
			fprintf(stderr, unset_usage);
			return EXIT_FAILURE;
		}
	}
	if (optind >= argc) {
		fprintf(stderr, unset_usage);
		return EXIT_FAILURE;
	}
	for (int i = optind; i < argc; ++i) {
		if (!funcs) {
			uint32_t prev_attribs = 0;
			if (mrsh_env_get(state, argv[i], &prev_attribs)) {
				if ((prev_attribs & MRSH_VAR_ATTRIB_READONLY)) {
					fprintf(stderr,
						"unset: cannot modify readonly variable %s\n", argv[i]);
					return EXIT_FAILURE;
				}
				mrsh_env_unset(state, argv[i]);
			}
		} else {
			// TODO: functions
		}
	}
	return EXIT_SUCCESS;
}
