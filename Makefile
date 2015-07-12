CFLAGS ?= -g -O2
CFLAGS += -Wall -Wextra

c_files = $(wildcard *.c)
o_files = $(c_files:.c=.o)

.PHONY: all
all: fbcat

fbcat: $(o_files)

.PHONY: clean
clean:
	rm -f fbcat *.o

# vim:ts=4 sts=4 sw=4 noet
