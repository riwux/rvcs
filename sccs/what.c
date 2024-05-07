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
	die("sccs-what: [-s] file...");
}

static int
what(char const *file, FILE *fp, bool sflag)
{
	char c;
	int ret = -1;

	printf("%s:\n", file);
	for (int i = 0; (c = fgetc(fp)) != EOF;) {
		i = (c == ID[i]) ? i + 1 : (c == '@') ? 1 : 0;
		if (i == 4) { /* Match found! */
			i = ret = 0;
			putchar('\t');
			while ((c = fgetc(fp)) != EOF && !strchr(STOP, c))
				putchar(c);
			putchar('\n');
			if (sflag)
				break;
		}
	}

	return ret;
}

int
sccs_what(int argc, char *argv[])
{
	bool sflag;
	int opt;
	int ret = 1;
	FILE *fp;

	optind = 0;
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
			die("sccs-what: fopen: cannot open '%s':", *argv);
		if (what(*argv, fp, sflag))
			ret = 0;
		fclose(fp);
	}

	return ret;
}
