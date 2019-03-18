# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -std=c99 -O2 -g

all:
	@$(CC) $(CFLAGS) horner.c -o horner

.PHONY: clean

clean:
	@rm horner
