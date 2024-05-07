/* See LICENSE file for copyright and license details. */
#include <string.h>
#include <unistd.h>

#include "util.h"

/* Avoid unnecessary header. */
extern int sccs_what(int, char **);

static void
usage(void)
{
	die("usage: sccs [-r] [-d path] command [options...] [operands...]");
}

int
main(int argc, char *argv[])
{
	int opt;
	int ret= 0;
	char const *cmd;

	while ((opt = getopt(argc, argv, "rd:p:")) != -1) {
		switch (opt) {
		case 'r':
			break;
		case 'd':
			break;
		case 'p':
			break;
		default:
			usage();
			break;
		}
	}
	argc -= optind;
	argv += optind;

	if (argc == 0)
		usage();

	cmd = *argv;
	if (cmd[0] == '-') {
		warn("sccs: missing SCCS command");
		usage();
	}

	/* Select command. */
	if (!strcmp(cmd, "what"))
		ret = sccs_what(argc, argv);
	else
		die("sccs: invalid SCCS command '%s'", cmd);

	return ret;
}
