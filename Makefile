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

# WARNING!
# Although invoking the all, archive targets in this Makefile from a Yocto-like
# environment may succeed, you will end up with N different libraries that are
# actually being built using the same compiler flags, i.e. the CFLAGS from the
# environment. That is because Yocto builds the fm-lib for various platforms
# one at a time, by invoking only the corresponding libfm-<arch>.a, then
# install-<arch> targets for each platform that it's currently configured for.

# Set this as appropriate for local builds.
TARGET_PREFIX?=powerpc-linux-gnu-

# You must set KERNEL_SOURCE before invoking this Makefile
# (Yocto doesn't set this either!)
KERNEL_SOURCE?=/mnt/opt/sdk-devel/linux

# This is inherited from the environment with which Yocto invokes us
# (if not, then uncomment this line):
#CC=$(TARGET_PREFIX)gcc

# The Yocto environment contains no var. named AR, so we have no choice but
# to set it here:
AR=$(TARGET_PREFIX)ar rcsv

INSTALL?=install

# Don't forget to increment .version before doing a new release!
FM_LIB_VERSION:=$(shell cat .version)

# Add any collateral files that need to be included in the archive, here:
FM_LIB_DOCFILES=COPYING INSTALL README 

# Don't touch these!
FM_IOCTL_INC?=$(KERNEL_SOURCE)/include/linux/fmd
FM_LIB_INC?=./include/fmd
FM_LIB_SRCDIR=./src
FM_LIB_INCLUDE:=$(FM_IOCTL_INC) \
		$(FM_IOCTL_INC)/Peripherals \
		$(FM_IOCTL_INC)/integrations \
		$(FM_LIB_INC) \
		$(FM_LIB_INC)/etc \
		$(FM_LIB_INC)/Peripherals \
		$(FM_LIB_INC)/integrations 

# These flags need to be passed to the compiler in any circumstance:
EXTRA_CFLAGS=-DNCSW_LINUX

# CFLAGS to use during out-of-Yocto (i.e. "local") build:
LOCAL_CFLAGS=-O2 -g0 -Wall \
	  -fexpensive-optimizations -frename-registers \
	  -fomit-frame-pointer -maix-struct-return \
	  -D__STDC_LIMIT_MACROS $(EXTRA_CFLAGS)


%.a: %.o
	@(echo "(AR) $(@)")
	@($(AR) $@ $^)

all: libfm-ppc32e5500.a libfm-ppc64e5500.a libfm-ppce500mc.a libfm-ppce500v2.a

libfm-ppce500mc.o libfm-ppc32e5500.o libfm-ppc64e5500.o: EXTRA_CFLAGS+=-DP4080
libfm-ppce500v2.o:  EXTRA_CFLAGS+=-DP1023

libfm-ppce500mc.o:  CFLAGS?=-m32 -mhard-float -mcpu=e500mc $(LOCAL_CFLAGS)
libfm-ppc32e5500.o: CFLAGS?=-m32 -mhard-float -mcpu=e5500  $(LOCAL_CFLAGS)
libfm-ppc64e5500.o: CFLAGS?=-m64 -mhard-float -mcpu=e5500  $(LOCAL_CFLAGS) 
libfm-ppce500v2.o:  CFLAGS?=-m32 -msoft-float -mcpu=8548   $(LOCAL_CFLAGS) 

CFLAGS+=$(EXTRA_CFLAGS)

libfm-%.o: $(FM_LIB_SRCDIR)/fm_lib.c $(addsuffix /*.h,$(FM_LIB_INCLUDE))
	@(echo "(CC)  $@")
	@(echo $(CC) $(CFLAGS) $(addprefix -I,$(FM_LIB_INCLUDE)) -c -o $@ $< > .$@.cmd)
	@($(CC) $(CFLAGS) $(addprefix -I,$(FM_LIB_INCLUDE)) -c -o $@ $<)

archive: all .version
	@(echo "Creating tarball for fmlib-$(FM_LIB_VERSION)...")
	@(tar -czf fm-lib-$(FM_LIB_VERSION)-bi.tar.gz . \
		--transform "s,\\.\\(.*\\),fm-lib-$(FM_LIB_VERSION)\\1," \
		--exclude=Makefile --exclude=.version --exclude-vcs --exclude=*.tar.gz)

install-%: %.a
	@(echo "Installing...")
	@($(INSTALL) -d $(DESTDIR)$(PREFIX)/lib)
	@($(INSTALL) $< $(DESTDIR)$(PREFIX)/lib)
	@(ln -s $(DESTDIR)$(PREFIX)/lib/$< $(DESTDIR)$(PREFIX)/lib/libfm.a)
	@(cp -r -p ./include $(DESTDIR)$(PREFIX))
	@($(INSTALL) -d $(DESTDIR)$(PREFIX)/share/doc/fm-lib-$(FM_LIB_VERSION))
	@($(INSTALL) $(FM_LIB_DOCFILES) $(DESTDIR)$(PREFIX)/share/doc/fm-lib-$(FM_LIB_VERSION))

targets:
	@(echo "make all: build libraries for all platforms (local build)")
	@(echo "make archive: build tarball with fm libraries")
	@(echo "make libfm-<arch>.a: build tarball with fm libraries")
	@(echo "make install-<arch>: install the library and headers to the location specified by DESTDIR, PREFIX")
	@(echo "The available <arch> options are:")
	@(echo "    ppce500mc:	P3, P4")
	@(echo "    ppc32e5500:	P5(32b)")
	@(echo "    ppc64e5500:	P5(64b)")
	@(echo "    ppce500v2:	P1")

clean:
	@(echo "Cleaning...")
	@(rm -rf *.a *.o *.d .*.o.cmd)

.PHONY: targets clean
