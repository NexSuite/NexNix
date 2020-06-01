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
		video.o

LINK_LIST=\
		$(OBJS) \
		$(LIBS) \

.PHONY: all clean install

.SUFFIXES: .o .c

all: video.a

video.a:	$(OBJS)
		$(AR) rcs $@ $(OBJS)

.c.o:
		$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS)
clean:
			rm -f video.a
			rm -f $(OBJS) *.o */*.o */*/*.o
			rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install:
		cp video.a $(DESTDIR)$(LIBDIR)/video.a

-include $(OBJS:.o=.d)
