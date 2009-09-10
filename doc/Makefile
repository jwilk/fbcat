XSL = http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl
XSLTPROC = /usr/bin/xsltproc --nonet --param man.charmap.use.subset 0

XML_FILES = $(wildcard *.xml)
MAN_FILES = $(XML_FILES:.xml=.1)

.PHONY: all
all: $(MAN_FILES)

%.1: %.xml
	$(XSLTPROC) $(XSL) $(<)

.PHONY: clean
clean:
	rm -f $(MAN_FILES)

# vim:ts=4
