CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=../../sysroot
SYSROOT?=../../sysroot
BOOTDIR?=/boot
INCLUDEDIR?=../../include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -I$(INCLUDEDIR) $(DEFINES)
LIBS:=$(LIBS) -nostdlib -lgcc

OBJS=\
		parallel.o \

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c

all: parallel.a

parallel.a:	$(OBJS)
		$(AR) rcs $@ $(OBJS)

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
clean:
			rm -f parallel.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp parallel.a $(DESTDIR)$(LIBDIR)/parallel.a

-include $(OBJS:.o=.d)
