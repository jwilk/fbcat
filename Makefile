CFLAGS = -Wall -O2 -g

C_FILES = $(wildcard *.c)
O_FILES = $(C_FILES:.c=.o)

.PHONY: all
all: fbcat

fbcat: $(O_FILES)

.PHONY: clean
clean:
	$(RM) fbcat *.o

# vim:ts=4 sw=4 noet
