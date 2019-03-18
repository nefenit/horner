# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -std=c99 -O2

all:
	@$(CC) $(CFLAGS) horner.c -o horner

clean:
	@rm horner
