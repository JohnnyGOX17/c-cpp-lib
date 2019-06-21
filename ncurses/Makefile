CC=gcc
CFLAGS=-Wall
LIBS=-lncurses -lmenu

# Build all C files as independent programs
SRCS=$(wildcard *.c)
PROGS=$(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(LIBS) -o $@ $<

clean:
	-rm -f $(PROGS)
