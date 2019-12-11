/**
 * @file    horner.c
 * @author  Bartosz Mierzynski <nefenit@gmail.com>
 * @date    2019
 * @version 1.0
 * @brief   Evaluates polynomial using Horner's scheme.
 */

#include <getopt.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define	PROGRAM_NAME         "horner"
#define	PROGRAM_VERSION      "1.0"
#define	COPYRIGTH_YEAR       "2019"
#define	COPYRIGTH_HOLDER     "Bartosz Mierzynski"
#define LICENSE_ABBREVIATION ""
#define	LICENSE_LINE         ""

void usage(const char * progname, int status) {
	printf(
	"usage: %s [MODE] X AN...\n"
	"       %s [-h|--help]\n"
	"       %s [-v|--version]\n"
	"Evaluates polynomial using Horner's scheme\n"
	"Modes\n"
	"  -i, --iterative\n"
	"  -r, --recursive\n",
	progname,	
	progname,	
	progname);
	exit(status);
}

void version(const char* program_name, const char* program_version) {
	printf("%s %s\n"
	"Copyright (C) %s %s\n"
	"License %s: %s\n"
	"This is free software: you are free to change and redistribute it.\n"
	"There is NO WARRANTY, to the extent permitted by law.\n",
	program_name,
	program_version,
	COPYRIGTH_YEAR,
	COPYRIGTH_HOLDER,
	LICENSE_ABBREVIATION,
	LICENSE_LINE);
	exit(EXIT_SUCCESS);
}

long double hornerr(long double a[], long double x, uintmax_t n) {
	if(n)
		return x * hornerr(a, x, n-1) + a[n];
	return *a;
}

long double horneri(long double a[], long double x, uintmax_t n) {
	long double p = *a;

	for(int i = 1; i <= n; ++i)
		p = p*x + a[i];
	
	return p;
}

int main(int argc, char *argv[]) {
	const char *progname;
	long double x, *a;
	bool recursive, help, ver;
	int  c, i;

	recursive = help = ver = false;

	for(;;) {
		int option_index = 0;
		static struct option long_options[] = {
		{"help",      no_argument, NULL, 'h'},
		{"iterative", no_argument, NULL, 'i'},
		{"recursive", no_argument, NULL, 'r'},
		{"version",   no_argument, NULL, 'v'},
		{NULL,        no_argument, NULL, 0}
		};

		c = getopt_long(argc, argv, "hirv", long_options, &option_index);

		/* end of options */
		if(c == -1)
			break;

		switch(c) {
			case 'h':
				help = true;
				break;
			case 'i':
				recursive = false;
				break;
			case 'r':
				recursive = true;
				break;
			case 'v':
				ver = true;
				break;
			case '?':
				/* getopt_long printed error message */
				break;
		}

	}

	if(help)
		usage(progname, EXIT_SUCCESS);	
	if(ver)
		version(PROGRAM_NAME, PROGRAM_VERSION);

	argc -= optind;
	argv += optind;

	if(argc < 2) {
		usage(progname, EXIT_FAILURE);	
	} else {
		x = strtold(*argv, NULL);
		--argc;
		++argv;
		
		if((a = (long double *)malloc(argc * sizeof(*a))) == NULL) {
			perror("malloc");
			return EXIT_FAILURE;
		}

		for(i = 0; i < argc; ++i)
			a[i] = strtold(argv[i], NULL);
		
		printf("%Lf\n", (recursive ? hornerr : horneri)(a, x, argc - 1));

		free(a);
	}

	return EXIT_SUCCESS;
}
