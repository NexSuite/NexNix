CFLAGS?=-g
LDFLAGS?=
LIBS?=

DESTDIR?=../sysroot
SYSROOT?=../sysroot
BOOTDIR?=/boot
INCLUDEDIR?=../include
LIBDIR?=/lib

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -I$(INCLUDEDIR) $(DEFINES)
LIBS:=$(LIBS) klibs.a -nostdlib -lgcc

include $(ARCHDIR)/make.config

KERNEL_OBJS=\
$(KERNEL_ARCH_OBJS)\
kernel/kernel.o \
kernel/panic.o \
kernel/init.o \
kernel/ustar.o \
kernel_memmgr/heap.o \
kernel_memmgr/cache.o \
proc/loader.o \
proc/sysapi.o \
proc/queue.o \
proc/scheduler.o \
proc/proc_aux.o \
proc/event.o\
driver/driver.o \

OBJS=\
		$(KERNEL_OBJS) \

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c .asm

all: nexnix.kernel

nexnix.kernel:	$(OBJS) $(ARCHDIR)/link.ld
		$(AR) -M <libs.mri
		$(CC) -T$(ARCHDIR)/link.ld  -o $@ $(CFLAGS) $(LINK_LIST)
		grub-file --is-x86-multiboot nexnix.kernel

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
.asm.o:
		nasm -f$(NASM_ARCH) -o $@ $<
clean:
			rm -f nexnix.kernel
			rm -f klibs.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp nexnix.kernel $(DESTDIR)$(BOOTDIR)/nexnix.kernel
		cp klibs.a $(DESTDIR)$(LIBDIR)/klibs.a

-include $(OBJS:.o=.d)
