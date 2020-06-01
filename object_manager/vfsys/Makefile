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
		vfsys.o \

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: vfsys.a

vfsys.a: $(OBJS)
		$(AR) rcs $@ $(OBJS)

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
.asm.o:
		nasm -f$(NASM_ARCH) -o $@ $<
clean:
			rm -f vfsys.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp vfsys.a $(DESTDIR)$(LIBDIR)/vfsys.a

-include $(OBJS:.o=.d)
