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
		vga.o \
		terminal.o \

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c

all: terminal.a

terminal.a:	$(OBJS)
		$(AR) rcs $@ $(OBJS)

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
clean:
			rm -f terminal.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp terminal.a $(DESTDIR)$(LIBDIR)/terminal.a

-include $(OBJS:.o=.d)
