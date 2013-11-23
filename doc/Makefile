xsl = http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl
xsltproc = xsltproc --nonet \
	--param man.charmap.use.subset 0 \
	--param man.copyright.section.enabled 0 \

xml_files = $(wildcard *.xml)
man_files = $(xml_files:.xml=.1)

.PHONY: all
all: $(man_files)

%.1: %.xml
	$(xsltproc) $(xsl) $(<)

.PHONY: clean
clean:
	rm -f $(man_files)

# vim:ts=4
