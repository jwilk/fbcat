CFLAGS ?= -g -O2
CFLAGS += -Wall -Wextra
CFLAGS += -D_FILE_OFFSET_BITS=64

c_files = $(wildcard *.c)
o_files = $(c_files:.c=.o)

.PHONY: all
all: fbcat

fbcat: $(o_files)
	$(LINK.c) $(^) $(LDLIBS) -o $(@)

.PHONY: clean
clean:
	rm -f fbcat *.o

# vim:ts=4 sts=4 sw=4 noet
