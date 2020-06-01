CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=../sysroot
SYSROOT?=../sysroot
BOOTDIR?=/boot
INCLUDEDIR?=../include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -I$(INCLUDEDIR) $(DEFINES) -D__is_libk
LIBS:=$(LIBS) -nostdlib -lgcc

include $(ARCHDIR)/make.config

LIBK_OBJS=\
stdlib/abort.libk.o \
string/string.libk.o \
stdio/printf.libk.o \
string/memory.libk.o \
stdlib/math.libk.o \
stdio/error.libk.o \
stdio/io.libk.o \

OBJS=\
		$(LIBK_OBJS)

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .libk.o .c

all: libk.a

libk.a:	$(OBJS)
		$(AR) rcs $@ $(OBJS)

.c.libk.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
clean:
			rm -f libk.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp libk.a $(DESTDIR)$(LIBDIR)/libk.a

-include $(OBJS:.o=.d)
