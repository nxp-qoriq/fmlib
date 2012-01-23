# Makefile for generating the fm-lib archive
# (look for the result in the ../ dir.).

# Increment this when generating a new version
VERSION=01.00.07


all:
	tar -czf ../fm-lib-$(VERSION)-bi.tar.gz	. \
		--transform "s,\\.\\(.*\\),fm-lib-$(VERSION)\\1," \
		--transform "s,share/doc/fm-lib-\\([0-9]\\{2\\}\\.\\)\\{2\\}[0-9]\\{2\\},share/doc/fm-lib-$(VERSION)," \
		--exclude=Makefile --exclude=.version --exclude-vcs
	echo $(VERSION) > .version

