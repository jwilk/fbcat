# Copyright © 2009-2021 Jakub Wilk
#
# This package is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; version 2 dated June, 1991.

CFLAGS ?= -g -O2
CFLAGS += -Wall -Wextra
CFLAGS += -D_FILE_OFFSET_BITS=64

PREFIX = /usr/local
DESTDIR =

bindir = $(PREFIX)/bin
mandir = $(PREFIX)/share/man

.PHONY: all
all: fbcat

fbcat: fbcat.o
	$(LINK.c) $(^) $(LDLIBS) -o $(@)

.PHONY: install
install: fbcat
	install -d $(DESTDIR)$(bindir)
	install -m755 fbcat $(DESTDIR)$(bindir)/
	install -m755 fbgrab $(DESTDIR)$(bindir)/
ifeq "$(wildcard doc/fbcat.1 doc/fbgrab.1)" ""
	# run "$(MAKE) -C doc" to build the manpages
else
	install -d $(DESTDIR)$(mandir)/man1
	install -m644 doc/fbcat.1 $(DESTDIR)$(mandir)/man1/fbcat.1
	install -m644 doc/fbgrab.1 $(DESTDIR)$(mandir)/man1/fbgrab.1
endif

.PHONY: clean
clean:
	rm -f fbcat *.o

# vim:ts=4 sts=4 sw=4 noet
