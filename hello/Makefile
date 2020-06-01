CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=../sysroot
SYSROOT?=../sysroot
BOOTDIR?=/boot
INCLUDEDIR?=../include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra -I$(INCLUDEDIR) $(DEFINES)
LIBS:=$(LIBS) -nostdlib -lgcc

OBJS=\
		hello.o \

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: hello.elf

hello.elf:	$(OBJS)
		$(CC) -o $@ $(CFLAGS) $(LINK_LIST)

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.asm.o:
			nasm -felf32 $< -o $@

clean:
			rm -f hello.elf
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp hello.elf $(DESTDIR)$(BOOTDIR)/hello.elf

-include $(OBJS:.o=.d)
