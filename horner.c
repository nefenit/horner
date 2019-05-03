/* horner.c - Evaluates polynomial using Horner's scheme
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C99
 */

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

#define STREQ(a, b) (strcmp(a, b) == 0)

typedef long double ld_t;

void usage(int status) {
	printf(
	"usage: %s [MODE] X AN...\n"
	"       %s [-h|--help]\n"
	"       %s [-v|--version]\n"
	"Evaluates polynomial using Horner's scheme\n"
	"Modes\n"
	"  -i, --iterative\n"
	"  -r, --recursive\n",
	PROGRAM_NAME,	
	PROGRAM_NAME,	
	PROGRAM_NAME);
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

ld_t hornerr(ld_t a[], ld_t x, uintmax_t n) {
	if(n)
		return x * hornerr(a, x, n-1) + a[n];
	return *a;
}

ld_t horneri(ld_t a[], ld_t x, uintmax_t n) {
	ld_t p = *a;

	for(int i = 1; i <= n; ++i)
		p = p*x + a[i];
	
	return p;
}

int main(int argc, char *argv[]) {
	if(argc == 2) {
		++argv;
		if(STREQ(*argv, "-h") || STREQ(*argv, "--help"))
			usage(EXIT_SUCCESS);	
		else if(STREQ(*argv, "-v") || STREQ(*argv, "--version"))
			version(PROGRAM_NAME, PROGRAM_VERSION);
		else
			usage(EXIT_FAILURE);	
	} else if(argc < 3) {
		usage(EXIT_FAILURE);
	}

	--argc;
	++argv;

	bool iterative = true;
	if(STREQ(*argv, "-i") || STREQ(*argv, "--iterative")) {
		iterative = true;	
		--argc;
		++argv;
		if(argc < 2)
			usage(EXIT_FAILURE);
	} else if(STREQ(*argv, "-r") || STREQ(*argv, "--recursive")) {
		iterative = false;	
		--argc;
		++argv;
		if(argc < 2)
			usage(EXIT_FAILURE);
	}

	const ld_t x = strtold(*argv, NULL);
	--argc;
	++argv;
	ld_t *a = (ld_t*)malloc(sizeof(ld_t) * argc);

	for(int i = 0; i < argc; ++i)
		a[i] = strtold(argv[i], NULL);

	--argc;
	printf("%Lf\n", iterative ? horneri(a, x, argc) : hornerr(a, x, argc));

	free(a);

	return EXIT_SUCCESS;
}
