# (c) Copyright 2019 Bartosz Mierzynski

CC=cc
CFLAGS=-Wall -pedantic -std=c99 -O2 -g

.PHONY: all
all:
	@$(CC) horner.c -o horner $(CFLAGS)

.PHONY: clean
clean:
	@rm horner
