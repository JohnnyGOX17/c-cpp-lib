CC=gcc
CFLAGS=-Wall

# Build all C files as independent programs
SRCS=$(wildcard *.c)
PROGS=$(patsubst %.c,%,$(SRCS))

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	-rm -f $(PROGS)
