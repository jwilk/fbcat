# Copyright © 2009-2017 Jakub Wilk
#
# This package is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 dated June, 1991.

CFLAGS ?= -g -O2
CFLAGS += -Wall -Wextra
CFLAGS += -D_FILE_OFFSET_BITS=64

.PHONY: all
all: fbcat

fbcat: fbcat.o
	$(LINK.c) $(^) $(LDLIBS) -o $(@)

.PHONY: clean
clean:
	rm -f fbcat *.o

# vim:ts=4 sts=4 sw=4 noet
