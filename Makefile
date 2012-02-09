#=====================================================================
#
#  Copyright 2010-2012, Freescale Semiconductor, Inc., All Rights Reserved.
#
#  This file contains copyrighted material. Use of this file is restricted
#  by the provisions of a Freescale Software License Agreement, which has
#  either accompanied the delivery of this software in shrink wrap
#  form or been expressly executed between the parties.
#
#=====================================================================

# NetCommSw defines mapping:
#    p3, p4  :e500mc
#    P5(32b) :e5500
#    p5(64B) :e5500
#    p1      :e500v2

#environment variabiles - set for archive building
CROSS_COMPILE?=
KERNEL_SOURCE?=/mnt/opt/sdk-devel/linux

#library version - set for binary tarball and recorded version in .version
FM_LIB_VERSION=$(shell cat .version)
FM_LIB_DOCFILES=COPYING INSTALL README 

FM_IOCTL_INC ?= $(KERNEL_SOURCE)/include/linux/fmd
FM_LIB_INC ?= ./include/fmd
FM_LIB_SRCDIR = ./src

FM_LIB_INCLUDE= $(FM_IOCTL_INC) \
		$(FM_IOCTL_INC)/Peripherals \
		$(FM_IOCTL_INC)/integrations \
		$(FM_LIB_INC) \
		$(FM_LIB_INC)/etc \
		$(FM_LIB_INC)/Peripherals \
		$(FM_LIB_INC)/integrations 

CFLAGS += -O2 -g0 -Wall \
	  -fexpensive-optimizations -frename-registers \
	  -fomit-frame-pointer -maix-struct-return \
	  -D__STDC_LIMIT_MACROS -DNCSW_LINUX

CC=$(CROSS_COMPILE)gcc
AR=$(CROSS_COMPILE)ar rcsv
INSTALL=install

%.a: %.o
	@($(AR) $@ $^)
	@(echo "(AR) $(@)")

all: libfm-ppc32e5500.a libfm-ppc64e5500.a libfm-ppce500mc.a libfm-ppce500v2.a

libfm-ppce500mc.o: $(FM_LIB_SRCDIR)/fm_lib.c
	@(echo "(CC)  $@")
	@($(CC) -te500mc $(CFLAGS) $(addprefix -I,$(FM_LIB_INCLUDE)) -DP4080 -c -o $(@) $<)

libfm-ppc32e5500.o: $(FM_LIB_SRCDIR)/fm_lib.c
	@(echo "(CC)  $@")
	@($(CC) -mcpu=e5500 -m32 $(CFLAGS) $(addprefix -I,$(FM_LIB_INCLUDE)) -DP4080 -o $@ -c $<)

libfm-ppc64e5500.o: $(FM_LIB_SRCDIR)/fm_lib.c
	@(echo "(CC)  $@")
	@($(CC) -mcpu=e5500 -m64 $(CFLAGS) $(addprefix -I,$(FM_LIB_INCLUDE)) -DP4080 -o $@ -c $<)

libfm-ppce500v2.o: $(FM_LIB_SRCDIR)/fm_lib.c
	@(echo "(CC)  $@")
	@($(CC) -mcpu=8548 -msoft-float $(CFLAGS) $(addprefix -I,$(FM_LIB_INCLUDE)) -DP1023 -o $@ -c $<)

.PHONY: targets version archive clean

targets:
	@(echo "make all: build libraries for all platforms")
	@(echo "make archive: build tarball with fm libraries")

archive:
	@(echo "Creating tarball...")
	@(tar -czf fm-lib-$(FM_LIB_VERSION)-bi.tar.gz . \
		--transform "s,\\.\\(.*\\),fm-lib-$(FM_LIB_VERSION)\\1," \
		--exclude=Makefile --exclude=.version --exclude-vcs --exclude=*.tar.gz)

install-%: %
	@(echo "Installing...")
	@($(INSTALL) -d $(DESTDIR)$(PREFIX)/lib)
	@($(INSTALL) $< $(DESTDIR)$(PREFIX)/lib)
	@(ln -s $(DESTDIR)$(PREFIX)/lib/$< $(DESTDIR)$(PREFIX)/lib/libfm.a)
	@(cp -r -p ./include $(DESTDIR)$(PREFIX))
	@($(INSTALL) -d $(DESTDIR)$(PREFIX)/share/doc/fm-lib-$(FM_LIB_VERSION))
	@($(INSTALL) $(FM_LIB_DOCFILES) $(DESTDIR)$(PREFIX)/share/doc/fm-lib-$(FM_LIB_VERSION))

clean:
	@(echo "Cleaning...")
	@(rm -rf *.a *.o *.d)
