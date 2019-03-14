/* horner.c - Evaluates polynomial using Horner's scheme
 * (c) Copyright 2019 Bartosz Mierzynski
 * Written in C99
 */

#include <stdio.h>
#include <stdlib.h>

void usage(int status) {
	fprintf(stderr, "usage: horner X AN...\n");
	exit(status);
}

int main(int argc, char **argv) {
	long double p, x;
	int i;
	
	if(argc < 3)
		usage(EXIT_FAILURE);
	
	x = strtold(argv[1], NULL);
	p = strtold(argv[2], NULL);
	
	for(i = 3; i < argc; ++i)
		p = p*x + strtold(argv[i], NULL);
	
	printf("%Lf\n", p);
	
	return EXIT_SUCCESS;
}
