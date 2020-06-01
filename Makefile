.PHONY: all clean install install-headers run grub

PROJECTS = Libc hal drivers object_manager kernel hello

all:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE}) \
		done

clean:
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE} clean) \
		done;
		rm -rf sysroot

install: install_headers
		for dir in $(PROJECTS); do \
				(cd $$dir; ${MAKE} install) \
		done
		cp grub/grub-$(QEMU_TYPE).cfg sysroot/boot/grub/grub.cfg

install_headers:
		mkdir -p sysroot/boot/grub
		mkdir -p sysroot/lib
		mkdir -p sysroot/include
		cp hello/hello.elf hello.elf
		cp -r include/*  sysroot/include/

run:
		./run
grub:
		./grub-disk

run_grub: install
		./run-grub
