VERSION ?= 1.0

CC = gcc
CFLAGS ?= -std=c17 -Wall -Wextra -Werror -O2
LDFLAGS := -lX11 $(LDFLAGS)

PREFIX ?= ~/.local
BINDIR ?= $(PREFIX)/bin

all: xgetres

xgetres: xgetres.c
	$(CC) $(CFLAGS) $(LDFLAGS) $? -o $@

install: xgetres
	mkdir -p $(BINDIR)
	install -D $< $(BINDIR)

clean:
	rm -f xgetres

.PHONY: all install clean
