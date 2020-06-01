CFLAGS?=-O2 -g
LDFLAGS?=
LIBS?=

DESTDIR?=../sysroot
SYSROOT?=../sysroot
BOOTDIR?=/boot
INCLUDEDIR?=../include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -I$(INCLUDEDIR) $(DEFINES)
LIBS:=$(LIBS) -nostdlib -lgcc

include $(HALARCHDIR)/make.config
include $(HALSUBARCHDIR)/make.config

HAL_OBJS=\
		hal.o \

OBJS=\
		$(HAL_ARCH_OBJS) \
		$(HAL_SUB_ARCH_OBJS) \
		$(HAL_OBJS) \

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: hal.a

hal.a:	$(OBJS)
		$(AR) rcs $@ $(OBJS)

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)

.asm.o:
		nasm -f$(NASM_ARCH) -o $@ $<

clean:
			rm -f hal.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp hal.a $(DESTDIR)$(LIBDIR)/hal.a

-include $(OBJS:.o=.d)
