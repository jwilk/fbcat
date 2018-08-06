rst2xml = $(notdir $(shell command -v rst2xml || echo rst2xml.py))
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

.PHONY: check
check: check-changelog check-rst check-xml

.PHONY: check-changelog
check-changelog: changelog
	dpkg-parsechangelog -l$(<) --all 2>&1 >/dev/null | { ! grep .; }

.PHONY: check-rst
check-rst: tested.txt
	$(rst2xml) --input-encoding=UTF-8 --strict $(<) > /dev/null

.PHONY: check-xml
check-xml: $(xml_files)
	xmllint --nonet --noout --valid $(^)

.PHONY: clean
clean:
	rm -f $(man_files)

# vim:ts=4 sts=4 sw=4 noet
