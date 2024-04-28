/* See LICENSE file for copyright and license details. */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "util.h"

#define STOP "\">\n\\\0"
#define ID   "@(#)"

static void
usage(void)
{
	die("what: [-s] file...");
}

static bool
sccs_what(char const *file, FILE *fp, bool sflag)
{
	char c;
	bool found = false;

	printf("%s:\n", file);
	for (int i = 0; (c = fgetc(fp)) != EOF;) {
		i = (c == ID[i]) ? i + 1 : (c == '@') ? 1 : 0;
		if (i == 4) { /* Match found! */
			i = 0;
			found = true;
			putchar('\t');
			while ((c = fgetc(fp)) != EOF && !strchr(STOP, c))
				putchar(c);
			putchar('\n');
			if (sflag)
				break;
		}
	}

	return found;
}

int
main(int argc, char *argv[])
{
	bool sflag;
	int opt;
	int ret = 1;
	FILE *fp;

	while ((opt = getopt(argc, argv, "s")) != -1) {
		switch (opt) {
		case 's':
			sflag = true;
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

	for (; *argv; ++argv) {
		if (!(fp = fopen(*argv, "r")))
			die("what: fopen: cannot open '%s' for reading:", *argv);
		if (sccs_what(*argv, fp, sflag))
			ret = 0;
	}

	return ret;
}
